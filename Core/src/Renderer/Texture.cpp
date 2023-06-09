#include "cpch.h"
#include "Texture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Core {

	std::unique_ptr<Texture> Texture::Create(const std::string& filepath)
	{
		return std::make_unique<Texture>(filepath);
	}

	Texture::Texture(const std::string& filepath)
		: m_Path(filepath)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

		if (data == NULL)
		{
			LOG_ERROR("Failed to load texture: {0}", filepath);
			return;
		}

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_Texture);
	}

	void Texture::Bind(int textureID)
	{
		glActiveTexture(OpenGLTextureInt(textureID));
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}

	int Texture::OpenGLTextureInt(int value)
	{
		switch (value)
		{
			case 0: return GL_TEXTURE0;
			case 1: return GL_TEXTURE1;
			case 2: return GL_TEXTURE2;
			case 3: return GL_TEXTURE3;
			case 4: return GL_TEXTURE4;
			case 5: return GL_TEXTURE5;
			case 6: return GL_TEXTURE6;
			case 7: return GL_TEXTURE7;
			case 8: return GL_TEXTURE8;
			case 9: return GL_TEXTURE9;
			case 10: return GL_TEXTURE10;
			case 11: return GL_TEXTURE11;
			case 12: return GL_TEXTURE12;
			case 13: return GL_TEXTURE13;
			case 14: return GL_TEXTURE14;
		}
	}

}