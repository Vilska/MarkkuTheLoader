#include "Application.h"

namespace Core {

	// Assign instance to nullptr
	Application* Application::s_Instance = nullptr;

	// Constructor
	Application::Application()
	{
		// Handle application initialization
		if (!s_Instance)
		{
			std::cout << "Application initialized!\n";
		}

		s_Instance = this;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			std::cout << "The app is running!\n";
			m_Running = false;
		}
	}

}