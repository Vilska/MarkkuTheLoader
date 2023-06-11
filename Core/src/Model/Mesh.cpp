#include "cpch.h"
#include "Mesh.h"

#include <glad/glad.h>

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Core {

	Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices, std::vector<MeshTexture> textures)
		: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
    {
        SetupMesh();
    }

    void Mesh::Draw()
    {
        uint32_t diffuseIndex = 1;
        uint32_t specularIndex = 1;

        Shader::Bind("Model");

        for (int i = 0; i < m_Textures.size(); i++)
        {
            Texture::Bind(m_Textures[i].Type);

            std::string number;
            std::string name = m_Textures[i].Type;

            if (name == "texture_diffuse")
                number = std::to_string(diffuseIndex++);
            else if (name == "texture_specular")
                number = std::to_string(specularIndex++);

            Shader::UploadUniform("Model", ("material." + name + number).c_str(), i);
        }

        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

	void Mesh::SetupMesh()
	{
        m_VertexArray = VertexArray::Create();

        m_VertexBuffer = VertexBuffer::Create(&m_Vertices[0], m_Vertices.size() * sizeof(MeshVertex));
        BufferLayout layout =
        {
        	{ "a_Position", ShaderDataType::Float3},
        	{ "a_Normal", ShaderDataType::Float3 },
        	{ "a_TexturePos", ShaderDataType::Float2 }
        };
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer = IndexBuffer::Create(&m_Indices[0], m_Indices.size() * sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}
}