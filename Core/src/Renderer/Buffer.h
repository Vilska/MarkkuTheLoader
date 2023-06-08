#pragma once

#include <memory>

namespace Core {

	class VertexBuffer
	{
	public:
		VertexBuffer(float* vertices, uint32_t size);

		void Bind();

		static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
	private:
		uint32_t m_VertexBuffer;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);

		void Bind();

		uint32_t GetCount() const { return m_Count; }

		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t size);
	private:
		uint32_t m_IndexBuffer;
		uint32_t m_Count;
	};

}
