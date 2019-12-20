#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override;

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;

	};
}