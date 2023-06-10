#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

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
	};

	class Mesh
	{
	public:
		std::vector<MeshVertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<MeshTexture> Textures;

		Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices, std::vector<MeshTexture> textures);

		void Draw();
	private:
		uint32_t VAO, VBO, EBO;

		void SetupMesh();
	};

}
