#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

namespace Core {

	struct ModelInfo
	{
		uint32_t VerticeCount = 0; uint32_t MeshCount = 0;
		std::vector<std::string> TextureCount;
	};

	class Model
	{
	public:
		Model() = default;

		static void Load(const std::string& filepath);
		static void Draw();

		static ModelInfo GetModelInfo() { return s_Instance->m_Info; }
	private:
		void LoadModel(const std::string& filepath);
		std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
		
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	private:
		std::vector<Mesh> m_Meshes;
		std::vector<MeshTexture> m_TexturesLoaded;
		std::string m_Directory;

		static std::unique_ptr<Model> s_Instance;

		ModelInfo m_Info;
	};

}
