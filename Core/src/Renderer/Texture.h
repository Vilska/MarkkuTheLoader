#pragma once

#include <string>
#include <tuple>
#include <memory>

namespace Core {

	class Texture
	{
	public:
		Texture(const std::string& filepath);
		~Texture();

		void Bind(int textureID);

		std::tuple<uint16_t, uint16_t> GetSize() const { return { m_Width, m_Height }; }

		static std::unique_ptr<Texture> Create(const std::string& filepath);
	private:
		int OpenGLTextureInt(int value);
	private:
		std::string m_Path;
		uint16_t m_Width, m_Height;
		uint32_t m_Texture;
	};

}
