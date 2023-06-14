#pragma once

#include <string>
#include <tuple>
#include <memory>

namespace Core {

	struct TextureData
	{
		std::string Name;
		uint32_t ID;

		TextureData(const std::string& name, uint32_t id)
			: Name(name), ID(id) {}

		bool operator == (const TextureData& ltd)
		{
			return ltd.Name == Name;
		}
	};

	class Texture
	{
	public:
		Texture() = default;

		static uint32_t Load(const std::string& name, const std::string& filepath);
		static void Bind(const std::string& name);
		static void Delete(const std::string& name);
	private:
		std::vector<TextureData> m_Textures;

		static std::unique_ptr<Texture> s_Instance;
	};

}
