#include "cpch.h"
#include "WindowsInput.h"

#include "Event/EventHandler.h"

namespace Core {

	std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

	bool WindowsInput::IsWindowBeingClosedImpl()
	{
		EventHandler::GetEvents();
		for (auto& event : EventHandler::GetEvents())
		{
			if (*event != EventTypes::WindowCloseEvent)
				continue;

			return true;
		}

		return false;
	}

}