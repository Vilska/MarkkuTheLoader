#pragma once

#include <string>
#include <memory>

namespace Core {

	class Shader
	{
	public:
		Shader() = default;
		~Shader() = default;

		static void LoadShaders();
	private:
		std::string ReadFile(const std::string& filepath);
	private:
		static std::unique_ptr<Shader> s_Instance;
	};

}
