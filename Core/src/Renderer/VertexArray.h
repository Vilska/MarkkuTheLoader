#pragma once

#include <memory>
#include <vector>

#include "Buffer.h"

namespace Core {

	using VertexVector = std::vector<std::shared_ptr<VertexBuffer>>;

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		const VertexVector& GetVertexBuffers() const { return m_VertexBuffers; }
		const std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }

		static std::shared_ptr<VertexArray> Create();
	private:
		uint32_t m_VertexArray;

		VertexVector m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}
