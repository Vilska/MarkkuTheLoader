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

		m_Window = Window::Create({"Testi", 1280, 720});
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Update();


			Input::IsWindowBeingClosed([&]()
			{
				LOG_ERROR("TUHOA");
				m_Running = false;
			});

			Input::IsWindowBeingResized([&](ResizeTuple tuple)
			{
				uint16_t x = std::get<0>(tuple);
				uint16_t y = std::get<1>(tuple);

				LOG_TRACE("{0}, {1}", x, y);
			});

		}
	}

}