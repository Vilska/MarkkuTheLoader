#pragma once

#include <string>

#include "Event/Event.h"

namespace Core {

	class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void Update() {}
		virtual void OnGuiRender() {}
	};

}
