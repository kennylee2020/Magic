#pragma once
#include <spdlog/spdlog.h>

namespace Magic {
	class Log
	{
		public:
			static void Init();
			static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//////////////////////////Log Macro///////////////////////////
#define MAG_CORE_INFO(...)		Log::GetCoreLogger()->info(__VA_ARGS__)
#define MAG_CORE_WARN(...)		Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MAG_CORE_ERROR(...)		Log::GetCoreLogger()->error(__VA_ARGS__)
#define MAG_CORE_CRITICAL(...)	Log::GetCoreLogger()->critical(__VA_ARGS__)

#define MAG_INFO(...)			Log::GetClientLogger()->info(__VA_ARGS__)
#define MAG_WARN(...)			Log::GetClientLogger()->warn(__VA_ARGS__)
#define MAG_ERROR(...)			Log::GetClientLogger()->error(__VA_ARGS__)
#define MAG_CRITICAL(...)		Log::GetClientLogger()->critical(__VA_ARGS__)
/////////////////////////////////////////////////////////////


