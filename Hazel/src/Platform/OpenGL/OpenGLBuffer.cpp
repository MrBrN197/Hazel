#include "hzpch.h"
#include "OpenGLBuffer.h"
#include <glad\glad.h>


namespace Hazel {


	////////////////////////////////////////////////////////////////////
	///// VertexBuffer /////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		HZ_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		HZ_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		HZ_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLVertexBuffer::Unbind() const {
		HZ_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void* OpenGLVertexBuffer::MapBuffer() const {
		return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	void OpenGLVertexBuffer::UnmapBuffer() const {
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	////////////////////////////////////////////////////////////////////
	///// IndexBuffer //////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count) {
		HZ_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer(){
		HZ_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const {
		HZ_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::Unbind() const {
		HZ_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void* OpenGLIndexBuffer::MapBuffer() const {
		return glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	void OpenGLIndexBuffer::UnmapBuffer() const {
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}

}