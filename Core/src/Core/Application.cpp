#include "cpch.h"
#include "Application.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Log.h"
#include "Input.h"
#include "Time.h"

namespace Core {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationProperties& props)
	{
		if (!s_Instance)
		{
			Log::Init();
			LOG_INFO("Application initialized!");
		}

		s_Instance = this;

		m_Window = Window::Create({ props.Label, props.Width, props.Height});
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_Camera = Camera::Create(45.0f, (float)props.Width / (float)props.Height);

		m_Gui = new GuiLayer();
		PushLayer(m_Gui);
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
			m_DeltaTime = DeltaTime::Calculate(glfwGetTime());

			m_Camera->Update(m_DeltaTime);

			for (auto& layer : m_Layers)
			{
				layer->Update();
			}

			m_Gui->Begin();
			for (auto& layer : m_Layers)
			{
				layer->OnGuiRender();
			}
			m_Gui->End();

			m_Window->Update();

		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		m_Camera->OnEvent(event);

		for (auto& layer : m_Layers)
			layer->OnEvent(event);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	float Application::GetTime()
	{
		return glfwGetTime();
	}
}