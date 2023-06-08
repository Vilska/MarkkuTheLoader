#pragma once

#include <glm/glm.hpp>

namespace Core {

	class Shader
	{
	public:
		Shader() = default;
		~Shader();

		static void LoadShaders();
		static void Bind();

		static void UploadUniformInt(const std::string& name, int value);
		static void UploadUniformFloat(const std::string& name, float value);
		static void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		static void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		static void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		static void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		static void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);
	private:
		unsigned int m_ShaderProgram;

		static std::unique_ptr<Shader> s_Instance;
	};

}
