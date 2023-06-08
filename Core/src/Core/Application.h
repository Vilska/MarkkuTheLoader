#pragma once

#include "Window.h"
#include "Layer.h"
#include "GUI/GuiLayer.h"
#include "Renderer/Shader.h"

namespace Core {

	struct ApplicationProperties
	{
		const std::string Label;
		uint16_t Width;
		uint16_t Height;

		ApplicationProperties(const std::string& label = "Default", uint16_t width = 1280, uint16_t height = 720)
			: Label(label), Width(width), Height(height) {}
	};

	class Application
	{
	public:
		Application(const ApplicationProperties& props);
		~Application();

		void Run();

		void PushLayer(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool m_Running = true;

		// Test
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		// Subclass pointers
		std::unique_ptr<Window> m_Window;
		//GuiLayer* m_Gui;

		// Vectors
		std::vector<Layer*> m_Layers;

		// Instance
		static Application* s_Instance;
	};
}
