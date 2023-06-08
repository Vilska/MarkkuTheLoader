#include "cpch.h"
#include "Buffer.h"

#include "glad/glad.h"

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
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return std::make_shared<VertexBuffer>(vertices, size);
	}

	VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
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
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		return std::make_shared<IndexBuffer>(indices, count);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBuffer);
	}

	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count) 
	{
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_IndexBuffer);
	}

}