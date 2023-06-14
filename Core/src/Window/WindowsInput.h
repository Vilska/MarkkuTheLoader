#pragma once

#include "Core/Input.h"

namespace Core {

	class WindowsInput : public Input
	{
	public:
		WindowsInput() = default;

		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::tuple<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}
