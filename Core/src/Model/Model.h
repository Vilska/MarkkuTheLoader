#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

namespace Core {

	class Model
	{
	public:
		Model(const std::string& filepath);

		void Draw();
	private:
		void LoadModel(const std::string& filepath);
		std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
		
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	private:
		std::vector<Mesh> m_Meshes;
		std::vector<MeshTexture> m_TexturesLoaded;
		std::string m_Directory;
	};

}
