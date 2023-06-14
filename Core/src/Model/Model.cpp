#include "cpch.h"
#include "Model.h"

#include "Renderer/Texture.h"

namespace Core {

	std::unique_ptr<Model> Model::s_Instance = std::make_unique<Model>();

	void Model::Load(const std::string& filepath)
	{
		if (!s_Instance->m_Meshes.empty())
		{
			auto& textures = s_Instance->m_Meshes[0].GetTextures();
			for (auto& texture : textures)
			{
				Texture::Delete(texture.Type);
			}

			s_Instance->m_Meshes.clear();
			s_Instance->m_TexturesLoaded.clear();

			s_Instance->m_Info.VerticeCount = 0;
			s_Instance->m_Info.MeshCount = 0;
			s_Instance->m_Info.TextureCount.clear();
		}

		s_Instance->LoadModel(filepath);
	}

	void Model::Draw()
	{
		if (s_Instance->m_Meshes.empty())
			return;

		for (auto& mesh : s_Instance->m_Meshes)
		{
			mesh.Draw();
		}
	}

	void Model::LoadModel(const std::string& filepath)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes | aiProcess_GenSmoothNormals);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("Assimp: {0}", import.GetErrorString());
			return;
		}

		m_Directory = filepath.substr(0, filepath.find_last_of("\\"));
		ProcessNode(scene->mRootNode, scene);
	}

	std::vector<MeshTexture> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName)
	{
		std::vector<MeshTexture> textures;

		for (int i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString str;

			material->GetTexture(type, i, &str);

			std::string string = str.C_Str();
			std::string fullpath = m_Directory + "/" + string;

			bool skip = false;

			for (unsigned int j = 0; j < m_TexturesLoaded.size(); j++)
			{
				if (m_TexturesLoaded[j].Path.compare(fullpath) == 0)
				{
					textures.push_back(m_TexturesLoaded[j]);
					skip = true;
					break;
				}
			}

			if (!skip)
			{
				MeshTexture texture;
				texture.ID = Texture::Load(typeName, fullpath);
				texture.Type = typeName;
				texture.Path = fullpath;
				textures.push_back(texture);
				m_TexturesLoaded.push_back(texture);
				m_Info.TextureCount.push_back(typeName);
			}

		}

		return textures;
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<MeshVertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<MeshTexture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			MeshVertex vertex;

			glm::vec3 posVector(1.0f);
			posVector.x = mesh->mVertices[i].x;
			posVector.y = mesh->mVertices[i].y;
			posVector.z = mesh->mVertices[i].z;
			vertex.Position = posVector;

			if (mesh->HasNormals())
			{
				glm::vec3 normalVector(1.0f);
				normalVector.x = mesh->mNormals[i].x;
				normalVector.y = mesh->mNormals[i].y;
				normalVector.z = mesh->mNormals[i].z;
				vertex.Normal = normalVector;
			}

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 textureVector(0.0f);
				textureVector.x = mesh->mTextureCoords[0][i].x;
				textureVector.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = textureVector;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f);
			}

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<MeshTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			
			std::vector<MeshTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		m_Info.VerticeCount += vertices.size();
		m_Info.MeshCount++;

		return Mesh(vertices, indices, textures);
	}

}