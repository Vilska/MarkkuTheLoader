#pragma once

#include <vector>

#include "Window.h"
#include "Layer.h"
#include "GUI/GuiLayer.h"

#include "Event/Event.h"
#include "Event/WindowEvent.h"

#include "Renderer/Camera.h"

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
		void OnEvent(Event& event);
		//void PushLayer(Layer* layer);
		void PushLayer(Layer* layer);

		static float GetTime();
		static float GetDeltaTime() { return s_Instance->m_DeltaTime; }
		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		inline bool OnWindowClose(WindowCloseEvent& event) { m_Running = false; return m_Running; }
	private:
		bool m_Running = true;
		float m_DeltaTime = 0;

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Camera> m_Camera;
		GuiLayer* m_Gui;

		std::vector<std::unique_ptr<Layer>> m_Layers;

		static Application* s_Instance;
	};
}
