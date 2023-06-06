#include "cpch.h"
#include "Application.h"

#include "Log.h"

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
			LOG_TRACE("Trace");
			LOG_INFO("Info");
			LOG_WARN("Warn");
			LOG_ERROR("Error");
		}

		s_Instance = this;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Running = false;
		}
	}

}