#pragma once

#include "Window.h"
#include "Layer.h"
#include "GUI/GuiLayer.h"

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
		~Application();

		void Run();

		void PushLayer(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool m_Running = true;

		// Subclass pointers
		std::unique_ptr<Window> m_Window;
		GuiLayer* m_Gui;

		// Vectors
		std::vector<Layer*> m_Layers;

		// Instance
		static Application* s_Instance;
	};
}
