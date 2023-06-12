#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Core {

	struct LightData
	{
		glm::vec3 Position;
		glm::vec3 Color;
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
	};

	class Lighting
	{
	public:
		static void SetLight(const std::string& shaderName, const LightData& lightData);
	};

}
