#pragma once

#include <memory>
#include <tuple>
#include <functional>

namespace Core {

	using ResizeTuple = std::pair<uint16_t, uint16_t>;

	class Input
	{
	public:
		static void IsWindowBeingClosed(const std::function<void()>& func) { return s_Instance->IsWindowBeingClosedImpl(func); }
		static void IsWindowBeingResized(const std::function<void(ResizeTuple)>& func) { return s_Instance->IsWindowBeingResizedImpl(func); }
	protected:
		virtual void IsWindowBeingClosedImpl(const std::function<void()>& func) = 0;
		virtual void IsWindowBeingResizedImpl(const std::function<void(ResizeTuple)>& func) = 0;
	private:
		static std::unique_ptr<Input> s_Instance;
	};

}
