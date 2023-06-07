#include "cpch.h"
#include "EventHandler.h"

namespace Core {

	std::unique_ptr<EventHandler> EventHandler::s_Instance = std::make_unique<EventHandler>();

	void EventHandler::AddEvent(Event event)
	{
		auto& events = s_Instance->m_Events;

		if (events.size() == 0)
			events.push_back(&event);

		for (auto e : events)
		{
			if (e->EventType == event.EventType)
				continue;

			events.push_back(&event);
		}
	}
}