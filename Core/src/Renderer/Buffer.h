#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace Core {

	// Buffer layout
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		return 0;
	}

	// Element
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement(const std::string& name, ShaderDataType type, bool normalized = false)
			: Name(name), Type(type), Offset(0), Size(ShaderDataTypeSize(type)), Normalized(normalized) {}

		uint32_t GetComponentCount() const { return ShaderDataTypeSize(Type) / 4; }
	};

	// Layout
	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride();
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	// Vertex buffer
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* vertices, uint32_t size);
		~VertexBuffer();

		void Bind();

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

		static std::shared_ptr<VertexBuffer> Create(const void* vertices, uint32_t size);
	private:
		uint32_t m_VertexBuffer;
		BufferLayout m_Layout;
	};

	// Index buffer
	class IndexBuffer
	{
	public:
		IndexBuffer(const void* indices, uint32_t size);
		~IndexBuffer();

		void Bind();

		uint32_t GetCount() const { return m_Count; }

		static std::shared_ptr<IndexBuffer> Create(const void* indices, uint32_t size);
	private:
		uint32_t m_Count;
		uint32_t m_IndexBuffer;
	};

}
