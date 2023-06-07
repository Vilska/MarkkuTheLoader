#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Core {

	enum EventTypes
	{
		WindowCloseEvent
	};

	using EventVector = std::vector<EventTypes*>;

	class EventHandler
	{
	public:
		EventHandler() = default;

		static void AddEvent(EventTypes event);
		static EventVector GetEvents() { return s_Instance->m_Events; }
	private:
		EventVector m_Events;
		static std::unique_ptr<EventHandler> s_Instance;
	};

}
