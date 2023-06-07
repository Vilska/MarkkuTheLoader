#pragma once

#include "Core/Input.h"

namespace Core {

	class WindowsInput : public Input
	{
	public:
		WindowsInput() = default;

		virtual bool IsWindowBeingClosedImpl() override;
	};

}
