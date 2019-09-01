#include "hzpch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Hazel {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(data, "Failed To Load Image");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, format = 0;
		if (channels == 3) {
			internalFormat = GL_RGB8;
			format = GL_RGB;
		}
		else {
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
		}
		HZ_ASSERT(internalFormat && format, "Texture format not set");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
		
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_RendererID);
	}
}