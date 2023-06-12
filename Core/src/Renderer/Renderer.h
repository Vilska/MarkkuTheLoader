#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Buffer.h"
#include "VertexArray.h"

namespace Core {

	struct ShapeData
	{
		std::string Name;
		std::string ShaderName;
		std::shared_ptr<VertexArray> VAO;
		glm::mat4 Transform;

		ShapeData(const std::string& name, const std::string& shaderName, const std::shared_ptr<VertexArray>& vao)
			: Name(name), ShaderName(shaderName), VAO(vao) 
		{
			Transform = glm::mat4(1.0f);
		}
	};

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void AddShape(const std::string& name, const std::string& shaderName, float* vertices, uint32_t verticesSize, const BufferLayout& bufferLayout, const void* indices, const glm::mat4& transform);
		static void AddShape(const std::string& name, const std::string& shaderName, float* vertices, uint32_t verticesSize, const BufferLayout& bufferLayout, const glm::mat4& transform);

		static void UpdateShapeTransform(const std::string& name, const glm::mat4& transform);
		static void Draw();
	private:
		glm::mat4 m_ViewProjection;

		std::vector<ShapeData> m_Shapes;

		static std::unique_ptr<Renderer> s_Instance;
	};

}
