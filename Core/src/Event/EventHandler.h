#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Core {

	enum EventTypes
	{
		WindowCloseEvent,
		WindowResizeEvent
	};

	struct Event
	{
		EventTypes EventType;
		bool Handled = false;

		Event(EventTypes eventType)
			: EventType(eventType) {}
	};

	using EventVector = std::vector<Event*>;

	class EventHandler
	{
	public:
		EventHandler() = default;

		static void AddEvent(Event event);
		static EventVector GetEvents() { return s_Instance->m_Events; }
	private:
		EventVector m_Events;
		static std::unique_ptr<EventHandler> s_Instance;
	};

}
