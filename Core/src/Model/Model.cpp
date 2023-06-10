#include "cpch.h"
#include "Model.h"

namespace Core {

	Model::Model(const std::string& filepath)
	{
		LoadModel(filepath);
	}

	void Model::Draw()
	{
		for (auto& mesh : m_Meshes)
		{
			mesh.Draw();
		}
	}

	void Model::LoadModel(const std::string& filepath)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("Assimp: {0}", import.GetErrorString());
			return;
		}

		m_Directory = filepath.substr(0, filepath.find_last_of("/"));
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<MeshVertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<MeshTexture> textures;

		// Process vertices
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			MeshVertex vertex;

			// Vertex position
			glm::vec3 posVector(0.0f);
			posVector.x = mesh->mVertices[i].x;
			posVector.y = mesh->mVertices[i].y;
			posVector.z = mesh->mVertices[i].z;
			vertex.Position = posVector;

			// Vertex normals
			glm::vec3 normalVector(0.0f);
			normalVector.x = mesh->mNormals[i].x;
			normalVector.y = mesh->mNormals[i].y;
			normalVector.z = mesh->mNormals[i].z;
			vertex.Normal = normalVector;

			// Texture coordinates
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

		// Process indices
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// Process materials TODO
		//if (mesh->mMaterialIndex >= 0)
		//{
		//	
		//}

		return Mesh(vertices, indices, textures);
	}

}