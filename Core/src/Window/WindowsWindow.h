#pragma once

#include "Core/Window.h"

#include <GLFW/glfw3.h>

namespace Core {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() override;

		virtual void Update() override;

		virtual std::tuple<uint16_t, uint16_t> GetSize() const override { return { m_Data.Width, m_Data.Height }; };
	private:
		void Init(const WindowProps& props);
		void Shutdown();
		void SetCallbacks();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint16_t Width;
			uint16_t Height;
		};

		WindowData m_Data;
	};

}
