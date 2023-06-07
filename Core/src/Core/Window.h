#pragma once

#include "cpch.h"

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
		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual std::tuple<uint16_t, uint16_t> GetSize() const = 0;
		virtual void* GetNativeWindow() = 0;

		static std::unique_ptr<Window> Create(const WindowProps& props);
	};

}