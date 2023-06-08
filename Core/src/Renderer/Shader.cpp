#include "cpch.h"
#include "Shader.h"

#include <fstream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Core {

	std::unique_ptr<Shader> Shader::s_Instance = std::make_unique<Shader>();
	
	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void Shader::LoadShaders()
	{
		// Create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Specify source and cast it to char*
		std::string& vertexShaderRaw = s_Instance->ReadFile("assets/shaders/vertexShader.glsl");
		const char* vertexShaderSource = vertexShaderRaw.c_str();
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

		// Compile shader to machine code
		glCompileShader(vertexShader);

		// Fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string& fragmentShaderRaw = s_Instance->ReadFile("assets/shaders/fragmentShader.glsl");
		const char* fragmentShaderSource = fragmentShaderRaw.c_str();
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

		glCompileShader(fragmentShader);

		// Create shader program
		s_Instance->m_ShaderProgram = glCreateProgram();

		// Attach proper shaders to the program
		glAttachShader(s_Instance->m_ShaderProgram, vertexShader);
		glAttachShader(s_Instance->m_ShaderProgram, fragmentShader);

		// Link all together
		glLinkProgram(s_Instance->m_ShaderProgram);

		// Delete shaders
		glDetachShader(s_Instance->m_ShaderProgram, vertexShader);
		glDetachShader(s_Instance->m_ShaderProgram, fragmentShader);
	}

	void Shader::Bind()
	{
		glUseProgram(s_Instance->m_ShaderProgram);
	}

	std::string Shader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath.c_str(), std::ios::in | std::ios::binary);

		if (!in)
		{
			LOG_ERROR("Could not load shader named: {0}", filepath);
			return result;
		}

		in.seekg(0, std::ios::end);
		size_t size = in.tellg();

		if (size == -1)
			return result;

		result.resize(size);
		in.seekg(0, std::ios::beg);
		in.read(&result[0], size);

		return result;
	}

}