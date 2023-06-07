#pragma once

#include "Core/Input.h"
#include "Event/EventHandler.h"

namespace Core {

	class WindowsInput : public Input
	{
	public:
		WindowsInput() = default;

		virtual void IsWindowBeingClosedImpl(const std::function<void()>& func) override;
		virtual void IsWindowBeingResizedImpl(const std::function<void(ResizeTuple)>& func) override;
	private:
		bool CheckEvent(EventTypes eventType);
	};

}
