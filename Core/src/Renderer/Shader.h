#pragma once

#include <string>
#include <memory>

namespace Core {

	class Shader
	{
	public:
		Shader() = default;
		~Shader();

		static void LoadShaders();
		static void Bind();
	private:
		std::string ReadFile(const std::string& filepath);
	private:
		unsigned int m_ShaderProgram;

		static std::unique_ptr<Shader> s_Instance;
	};

}
