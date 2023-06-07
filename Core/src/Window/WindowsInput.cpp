#include "cpch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "Core/Application.h"

namespace Core {

	std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

	void WindowsInput::IsWindowBeingClosedImpl(const std::function<void()>& func)
	{
		if (!CheckEvent(WindowCloseEvent))
			return;

		func();
	}

	void WindowsInput::IsWindowBeingResizedImpl(const std::function<void(ResizeTuple)>& func)
	{
		if (!CheckEvent(WindowResizeEvent))
			return;

		int width, height;
		glfwGetWindowSize(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()), &width, &height);

		func({ uint16_t(width), uint16_t(height) });
	}

	bool WindowsInput::CheckEvent(EventTypes eventType)
	{
		auto& events = EventHandler::GetEvents();
		for (auto& event : events)
		{
			if (event->EventType != eventType || event->Handled)
				continue;
			
			event->Handled = true;
			return true;
		}

		return false;
	}

}