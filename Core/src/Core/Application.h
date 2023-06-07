#pragma once

#include "Window.h"

namespace Core {

	//struct ApplicationProperties
	//{
	//	const std::string Label = "Default";
	//	uint16_t Width = 1280;
	//	uint16_t Height = 720;
	//};

	class Application
	{
	public:
		Application();

		void Run();

		static Application* Get() { return s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool m_Running = true;

		std::unique_ptr<Window> m_Window;

		static Application* s_Instance;
	};
}
