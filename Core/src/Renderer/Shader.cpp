#include "cpch.h"
#include "Shader.h"

#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/gtc/type_ptr.hpp"

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
			uint32_t shaderProgram = glCreateProgram();

			ShaderPack shaderPack(prefixVector[i], shaderProgram);
			s_Instance->m_ShaderPacks.push_back(shaderPack);

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

			std::stringstream vertexPath;
			vertexPath << "assets/shaders/" << shaderPack.Name << "VS.glsl";

			std::string& vertexShaderRaw = s_Instance->ReadFile(vertexPath.str());
			const char* vertexShaderSource = vertexShaderRaw.c_str();
			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

			glCompileShader(vertexShader);
			s_Instance->CheckCompilationStatus(vertexShader);

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::stringstream fragmentPath;
			fragmentPath << "assets/shaders/" << shaderPack.Name << "FS.glsl";

			std::string& fragmentShaderRaw = s_Instance->ReadFile(fragmentPath.str());
			const char* fragmentShaderSource = fragmentShaderRaw.c_str();
			glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

			glCompileShader(fragmentShader);
			s_Instance->CheckCompilationStatus(fragmentShader);

			glAttachShader(shaderPack.Program, vertexShader);
			glAttachShader(shaderPack.Program, fragmentShader);

			glLinkProgram(shaderPack.Program);
			s_Instance->CheckLinkingStatus(shaderPack.Program);

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

	void Shader::CheckCompilationStatus(uint32_t shader)
	{
		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success)
			return;

		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(shader);

		LOG_ERROR("Shader compilation failed: {0}", infoLog.data());
	}

	void Shader::CheckLinkingStatus(uint32_t program)
	{
		GLint success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success)
			return;

		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);

		LOG_ERROR("Shader linking failed: {0}", infoLog.data());
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