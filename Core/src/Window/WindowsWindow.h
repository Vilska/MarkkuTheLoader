#pragma once

#include "Core/Window.h"

#include <GLFW/glfw3.h>

namespace Core {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() override;

		virtual void Clear() override;
		virtual void Update() override;

		virtual uint16_t GetWidth() const override { return m_Data.Width; };
		virtual uint16_t GetHeight() const override { return m_Data.Height; };
		virtual void* GetNativeWindow() override { return m_Window; }

		inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
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

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
