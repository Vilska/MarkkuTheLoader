#include "cpch.h"
#include "EventHandler.h"

namespace Core {

	std::unique_ptr<EventHandler> EventHandler::s_Instance = std::make_unique<EventHandler>();

	void EventHandler::AddEvent(EventTypes event)
	{
		s_Instance->m_Events.push_back(&event);
	}
}