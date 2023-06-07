#include "cpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"

namespace Core {

	// Assign instance to nullptr
	Application* Application::s_Instance = nullptr;

	// Constructor
	Application::Application()
	{
		// Handle application initialization
		if (!s_Instance)
		{
			// Initialize log
			Log::Init();
			LOG_INFO("Application initialized!");
		}

		s_Instance = this;

		m_Window = Window::Create({"Testi", 1920, 1080});

		m_Gui = new GuiLayer();
		PushLayer(m_Gui);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Check for window related events
			//Input::IsWindowBeingClosed([&]()
			//{
			//	m_Running = false;
			//});

			// Update layers
			for (auto& layer : m_Layers)
			{
				layer->OnUpdate();
			}

			// Render GUI
			m_Gui->Begin();
			for (auto& layer : m_Layers)
			{
				layer->OnGuiRender();
			}
			m_Gui->End();

			// Update the window
			m_Window->Update();

		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

}