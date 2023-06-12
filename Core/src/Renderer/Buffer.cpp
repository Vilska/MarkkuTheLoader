#include "cpch.h"
#include "Buffer.h"

#include <glad/glad.h>

namespace Core {

	// Buffer layout
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements) 
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride = offset;
		}
	}

	// Vertex buffer
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* vertices, uint32_t size)
	{
		return std::make_shared<VertexBuffer>(vertices, size);
	}

	VertexBuffer::VertexBuffer(const void* vertices, uint32_t size)
	{
		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_VertexBuffer);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	}

	// Index buffer
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(const void* indices, uint32_t size)
	{
		return std::make_shared<IndexBuffer>(indices, size);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBuffer);
	}

	IndexBuffer::IndexBuffer(const void* indices, uint32_t size)
		: m_Count(size / 32) 
	{
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_IndexBuffer);
	}

}