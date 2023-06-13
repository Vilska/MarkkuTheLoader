#pragma once

#include <string>

#include "Core.h"

namespace Core {

	class SettingsPanel
	{
	public:
		static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
		static void DrawModelBrowser(bool& request, std::string& path);
	};

}
