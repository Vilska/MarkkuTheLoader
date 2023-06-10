#include "cpch.h"
#include "Shader.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

namespace Core {

	std::unique_ptr<Shader> Shader::s_Instance = std::make_unique<Shader>();
	
	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void Shader::LoadShaders(const std::initializer_list<std::string>& shaderPrefixes)
	{
		std::vector<std::string> prefixVector = shaderPrefixes;

		for (int i = 0; i < prefixVector.size(); i++)
		{
			// Create each shaderPack own program and assign it to the pack
			uint32_t shaderProgram = glCreateProgram();
			ShaderPack shaderPack(prefixVector[i], shaderProgram);
			s_Instance->m_ShaderPacks.push_back(shaderPack);

			//Create vertex shader
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

			//Specify source and cast it to char*
			std::stringstream vertexPath;
			vertexPath << "assets/shaders/" << shaderPack.Name << "VS.glsl";

			std::string& vertexShaderRaw = s_Instance->ReadFile(vertexPath.str());
			const char* vertexShaderSource = vertexShaderRaw.c_str();
			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

			// Compile shader to machine code
			glCompileShader(vertexShader);

			// Fragment shader
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::stringstream fragmentPath;
			fragmentPath << "assets/shaders/" << shaderPack.Name << "FS.glsl";

			std::string& fragmentShaderRaw = s_Instance->ReadFile(fragmentPath.str());
			const char* fragmentShaderSource = fragmentShaderRaw.c_str();
			glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

			glCompileShader(fragmentShader);

			// Attach proper shaders to the program
			glAttachShader(shaderPack.Program, vertexShader);
			glAttachShader(shaderPack.Program, fragmentShader);

			// Link all together
			glLinkProgram(shaderPack.Program);

			// Delete shaders
			glDetachShader(shaderPack.Program, vertexShader);
			glDetachShader(shaderPack.Program, fragmentShader);
		}

	}

	void Shader::Bind(const std::string& shaderPackName)
	{
		for (auto& shaderPack : s_Instance->m_ShaderPacks)
		{
			if (shaderPack.Name != shaderPackName)
				continue;

			glUseProgram(shaderPack.Program);
		}
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

	void Shader::UploadUniformImpl(uint32_t program, const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(program, name.c_str());
		glUniform1i(location, value);
	}

	void Shader::UploadUniformImpl(uint32_t program, const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(program, name.c_str());
		glUniform1f(location, value);
	}

	void Shader::UploadUniformImpl(uint32_t program, const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(program, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void Shader::UploadUniformImpl(uint32_t program, const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(program, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::UploadUniformImpl(uint32_t program, const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(program, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Shader::UploadUniformImpl(uint32_t program, const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(program, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::UploadUniformImpl(uint32_t program, const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(program, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}