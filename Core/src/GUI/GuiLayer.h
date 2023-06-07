#pragma once

#include "Core/Layer.h"

namespace Core {

	class GuiLayer : public Layer
	{
	public:
		GuiLayer() = default;
		~GuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};

}
