#pragma once
#include <vector>

namespace Hazel {

	enum class ShaderDataType{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		
		switch (type)
		{
			case Hazel::ShaderDataType::Float:	return 4;
			case Hazel::ShaderDataType::Float2:	return 4 * 2;
			case Hazel::ShaderDataType::Float3:	return 4 * 3;
			case Hazel::ShaderDataType::Float4:	return 4 * 4;
			case Hazel::ShaderDataType::Mat3:	return 4 * 3 * 3;
			case Hazel::ShaderDataType::Mat4:	return 4 * 4 * 4;
			case Hazel::ShaderDataType::Int:	return 4;
			case Hazel::ShaderDataType::Int2:	return 4 * 2;
			case Hazel::ShaderDataType::Int3:	return 4 * 3;
			case Hazel::ShaderDataType::Int4:	return 4 * 4;
			case Hazel::ShaderDataType::Bool:	return 1;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement {
		ShaderDataType Type;
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;
		BufferElement(ShaderDataType type, std::string name, bool normalized = false) : Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		static uint32_t GetComponentCount(ShaderDataType type) {

			switch (type)
			{
			case Hazel::ShaderDataType::Float:	return 1;
			case Hazel::ShaderDataType::Float2:	return 2;
			case Hazel::ShaderDataType::Float3:	return 3;
			case Hazel::ShaderDataType::Float4:	return 4;
			case Hazel::ShaderDataType::Mat3:	return 3 * 3;
			case Hazel::ShaderDataType::Mat4:	return 4 * 4;
			case Hazel::ShaderDataType::Int:	return 1;
			case Hazel::ShaderDataType::Int2:	return 2;
			case Hazel::ShaderDataType::Int3:	return 3;
			case Hazel::ShaderDataType::Int4:	return 4;
			case Hazel::ShaderDataType::Bool:	return 1;
			}

			HZ_CORE_ASSERT(false, "Unknonw ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements) : m_Elements(elements) {
			CalculateOffsetsAndStride();
		}

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		uint32_t GetStride() const { return m_Stride; }
	private:
		void CalculateOffsetsAndStride() {
			
			uint32_t offset = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
			}
			m_Stride = offset;
		}
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};



	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(BufferLayout layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);

	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};

}