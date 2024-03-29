#pragma once

#include <string>
#include <memory>
#include <functional>

#include "Event/Event.h"

namespace Core {

	struct WindowProps
	{
		std::string Title;
		uint16_t Width;
		uint16_t Height;

		WindowProps(const std::string& title, uint16_t width, uint16_t height)
			: Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual uint16_t GetWidth() const = 0;
		virtual uint16_t GetHeight() const = 0;
		virtual void* GetNativeWindow() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static std::unique_ptr<Window> Create(const WindowProps& props);
	};

}