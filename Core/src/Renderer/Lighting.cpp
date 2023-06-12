#include "cpch.h"
#include "Lighting.h"

#include "Shader.h"
#include "Camera.h"

namespace Core {

	void Lighting::SetLight(const std::string& shaderName, const LightData& lightData)
	{
		Shader::UploadUniform(shaderName, "light.position", lightData.Position);
		Shader::UploadUniform(shaderName, "light.color", lightData.Color);
		Shader::UploadUniform(shaderName, "light.ambient", lightData.Ambient);
		Shader::UploadUniform(shaderName, "light.diffuse", lightData.Diffuse);
		Shader::UploadUniform(shaderName, "light.specular", lightData.Specular);
		Shader::UploadUniform(shaderName, "ViewPos", Camera::GetPosition());
	}

}