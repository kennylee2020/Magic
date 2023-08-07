#include "magicpch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Magic {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::info);

		s_CoreLogger = std::make_shared<spdlog::logger>("MAGIC", console_sink);
		s_ClientLogger = std::make_shared<spdlog::logger>("APP", console_sink);
	}
}

