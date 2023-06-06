#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace Core {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

#define LOG_TRACE(...)	::Core::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	::Core::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	::Core::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	::Core::Log::GetLogger()->error(__VA_ARGS__)
