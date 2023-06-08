#include "cpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Core {

	// Assign instance to nullptr
	Application* Application::s_Instance = nullptr;

	// Constructor
	Application::Application(const ApplicationProperties& props)
	{
		// Handle application initialization
		if (!s_Instance)
		{
			// Initialize log
			Log::Init();
			LOG_INFO("Application initialized!");
		}

		s_Instance = this;

		m_Window = Window::Create({ props.Label, props.Width, props.Height});

		//m_Gui = new GuiLayer();
		//PushLayer(m_Gui);

		// Triangle test
		float vertices[] =
		{
			-0.5, -0.5, 0.0f,
			0.5, -0.5, 0.0f,
			0.0, 0.5, 0.0f
		};

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		Shader::LoadShaders();
	}

	Application::~Application()
	{
		for (auto& layer : m_Layers)
		{
			layer->OnDetach();
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Clear();

			// Check for window related events
			Input::IsWindowBeingClosed([&]()
			{
				m_Running = false;
			});

			// Update layers
			for (auto& layer : m_Layers)
			{
				layer->OnUpdate();
			}

			//Render GUI
			//m_Gui->Begin();
			//for (auto& layer : m_Layers)
			//{
			//	layer->OnGuiRender();
			//}
			//m_Gui->End();

			// Update the window

			glBindVertexArray(m_VertexArray);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			m_Window->Update();

		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

}