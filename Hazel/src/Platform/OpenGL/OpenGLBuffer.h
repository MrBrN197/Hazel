#pragma once
#include "Hazel\Renderer\Buffer.h"

namespace Hazel {

	class OpenGLVertexBuffer: public VertexBuffer{
	public:
		virtual ~OpenGLVertexBuffer();
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual const BufferLayout& GetLayout() const { return m_Layout; }
		virtual void SetLayout(BufferLayout layout) {
			m_Layout = layout;
		}

		virtual void* MapBuffer() const override;
		virtual void UnmapBuffer() const override;


	private:
		BufferLayout m_Layout;
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual inline uint32_t GetCount() const override { return m_Count; }
		virtual inline void SetCount(uint32_t count) override { m_Count = count;}

		virtual void* MapBuffer() const override;
		virtual void UnmapBuffer() const override;

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};


}