#include "cpch.h"
#include "Renderer.h"

#include "glad/glad.h"

#include "Camera.h"
#include "Shader.h"

namespace Core {

	std::unique_ptr<Renderer> Renderer::s_Instance = std::make_unique<Renderer>();

	void Renderer::BeginScene()
	{
		s_Instance->m_ViewProjection = Camera::GetViewProjectionMatrix();

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::EndScene() {}

	void Renderer::AddShape(const std::string& name, const std::string& shaderName, float* vertices, uint32_t verticesSize, const BufferLayout& bufferLayout, const void* indices, const glm::mat4& transform)
	{
		std::shared_ptr<VertexArray> vao = VertexArray::Create();
		std::shared_ptr<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		std::shared_ptr<IndexBuffer> ibo = IndexBuffer::Create(indices, sizeof(indices));

		vbo->SetLayout(bufferLayout);
		vao->AddVertexBuffer(vbo);
		vao->SetIndexBuffer(ibo);

		ShapeData data(name, shaderName, vao);
		s_Instance->m_Shapes.push_back(data);
	}

	void Renderer::AddShape(const std::string& name, const std::string& shaderName, float* vertices, uint32_t verticesSize, const BufferLayout& bufferLayout, const glm::mat4& transform)
	{
		std::shared_ptr<VertexArray> vao = VertexArray::Create();
		std::shared_ptr<VertexBuffer> vbo = VertexBuffer::Create(vertices, verticesSize);

		vbo->SetLayout(bufferLayout);
		vao->AddVertexBuffer(vbo);

		ShapeData data(name, shaderName, vao);
		s_Instance->m_Shapes.push_back(data);
	}

	void Renderer::UpdateShapeTransform(const std::string& name, const glm::mat4& transform)
	{
		for (auto& shape : s_Instance->m_Shapes)
		{
			if (shape.Name != name)
				continue;

			shape.Transform = transform;
		}
	}

	void Renderer::UpdateShapeColor(const std::string& name, const glm::vec3& color)
	{
		for (auto& shape : s_Instance->m_Shapes)
		{
			if (shape.Name != name)
				continue;

			shape.Color = color;
		}
	}

	void Renderer::Draw()
	{
		for (auto& shape : s_Instance->m_Shapes)
		{
			Shader::Bind(shape.ShaderName);
			Shader::UploadUniform(shape.ShaderName, "ViewProjection", s_Instance->m_ViewProjection);
			Shader::UploadUniform(shape.ShaderName, "Transform", shape.Transform);
			Shader::UploadUniform(shape.ShaderName, "CubeColor", shape.Color);

			shape.VAO->Bind();

			if (shape.VAO->GetIndexBuffer() != nullptr)
			{
				glDrawElements(GL_TRIANGLES, shape.VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
	}

}