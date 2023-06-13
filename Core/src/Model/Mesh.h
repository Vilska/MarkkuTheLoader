#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace Core {

	struct MeshVertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct MeshTexture
	{
		uint32_t ID;
		std::string Type;
		std::string Path;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices, std::vector<MeshTexture> textures);

		void Draw();

		std::vector<MeshTexture> GetTextures() const { return m_Textures; }
	private:
		void SetupMesh();
	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::vector<MeshVertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
		std::vector<MeshTexture> m_Textures;
	};

}
