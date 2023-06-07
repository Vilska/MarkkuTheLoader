#pragma once

#include <memory>

namespace Core {

	class Input
	{
	public:
		static bool IsWindowBeingClosed() { return s_Instance->IsWindowBeingClosedImpl(); };
	protected:
		virtual bool IsWindowBeingClosedImpl() = 0;
	private:
		static std::unique_ptr<Input> s_Instance;
	};

}
