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
#define MAG_INFO_CORE(...)		Log::GetCoreLogger()->info(__VA_ARGS__)
#define MAG_WARN_CORE(...)		Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MAG_ERROR_CORE(...)		Log::GetCoreLogger()->error(__VA_ARGS__)
#define MAG_CRITICAL_CORE(...)	Log::GetCoreLogger()->critical(__VA_ARGS__)

#define MAG_INFO(...)			Log::GetClientLogger()->info(__VA_ARGS__)
#define MAG_WARN(...)			Log::GetClientLogger()->warn(__VA_ARGS__)
#define MAG_ERROR(...)			Log::GetClientLogger()->error(__VA_ARGS__)
#define MAG_CRITICAL(...)		Log::GetClientLogger()->critical(__VA_ARGS__)
/////////////////////////////////////////////////////////////


