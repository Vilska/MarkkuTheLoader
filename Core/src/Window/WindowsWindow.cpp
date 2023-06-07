#include "cpch.h"
#include "WindowsWindow.h"

#include "glad/glad.h"
#include "Event/EventHandler.h"

namespace Core {

	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		// Window
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, (char*)m_Data.Title.c_str(), NULL, NULL);
		if (m_Window == NULL)
		{
			LOG_ERROR("Failed to create GLFW window!");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glViewport(0, 0, 1280, 720);

		// GLFW callbacks
		SetCallbacks();
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetCallbacks()
	{
		// Window size
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			EventHandler::AddEvent(WindowCloseEvent);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			EventHandler::AddEvent(WindowResizeEvent);
		});
	}

	void WindowsWindow::Update()
	{
		glClearColor(0.2f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

}