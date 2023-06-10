#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace Core {

	struct ShaderPack
	{
		std::string Name;
		uint32_t Program;

		ShaderPack(const std::string& name, uint32_t program)
			: Name(name), Program(program) {}
	};

	class Shader
	{
	public:
		Shader() = default;
		~Shader();

		static void LoadShaders(const std::initializer_list<std::string>& shaders);
		static void Bind(const std::string& shaderPackName);

		template<typename T>
		static void UploadUniform(const std::string& shaderPackName, const std::string& uniformName, T value)
		{
			for (auto& shaderPack : s_Instance->m_ShaderPacks)
			{
				if (shaderPack.Name != shaderPackName)
					continue;

				s_Instance->UploadUniformImpl(shaderPack.Program, uniformName, value);
			}
		}
	private:
		std::string ReadFile(const std::string& filepath);

		void UploadUniformImpl(uint32_t program, const std::string& name, int value);
		void UploadUniformImpl(uint32_t program, const std::string& name, float value);
		void UploadUniformImpl(uint32_t program, const std::string& name, const glm::vec2& value);
		void UploadUniformImpl(uint32_t program, const std::string& name, const glm::vec3& value);
		void UploadUniformImpl(uint32_t program, const std::string& name, const glm::vec4& value);
		void UploadUniformImpl(uint32_t program, const std::string& name, const glm::mat3& matrix);
		void UploadUniformImpl(uint32_t program, const std::string& name, const glm::mat4& matrix);
	private:
		std::vector<ShaderPack> m_ShaderPacks;

		uint32_t m_ShaderProgram;

		static std::unique_ptr<Shader> s_Instance;
	};

}
