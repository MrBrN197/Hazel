#include "hzpch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"


namespace Hazel {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Path(""), m_Width(width), m_Height(height) {
		m_InternalFormat = GL_RGBA8, m_Format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(data, "Failed To Load Image");
		m_Width = width;
		m_Height = height;

		m_InternalFormat = 0, m_Format = 0;
		if (channels == 3) {
			m_InternalFormat = GL_RGB8;
			m_Format = GL_RGB;
		}
		else {
			m_InternalFormat = GL_RGBA8;
			m_Format = GL_RGBA;
		}
		HZ_ASSERT(m_InternalFormat && m_Format, "Texture format not set");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_Format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		uint32_t bpp = m_InternalFormat == GL_RGBA8 ? 4 : 3;
		HZ_CORE_ASSERT(size == m_Width * m_Height * bpp, "size must equal width*height*bpp");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_Format, GL_UNSIGNED_BYTE, data);
	}


	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_RendererID);
	}
}