#include "cpch.h"
#include "Texture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Core {

	std::unique_ptr<Texture> Texture::s_Instance = std::make_unique<Texture>();

	uint32_t Texture::Load(const std::string& name, const std::string& filepath)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

		if (data == NULL)
		{
			LOG_ERROR("Failed to load texture: {0}", filepath);
			return 0;
		}

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

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);

		TextureData texture(name, textureID);
		s_Instance->m_Textures.push_back(texture);

		return textureID;
	}

	void Texture::Bind(const std::string& name)
	{
		for (auto& texture : s_Instance->m_Textures)
		{
			if (texture.Name != name)
				continue;

			glActiveTexture(GL_TEXTURE0 + texture.ID - 3);
			glBindTexture(GL_TEXTURE_2D, texture.ID);
		}
	}

	void Texture::Delete(const std::string& name)
	{
		auto& texVec = s_Instance->m_Textures;
		for (auto& texture : texVec)
		{
			if (texture.Name != name)
				continue;

			glDeleteTextures(1, &texture.ID);
			texVec.erase(std::remove(texVec.begin(), texVec.end(), texture), texVec.end());
		}
	}

}