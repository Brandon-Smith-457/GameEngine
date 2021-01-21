#pragma once

#include "gepch.h"
#include "GameEngine/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace GameEngine {

	class Log {
	public:
		static void init();

		inline static Ref<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define GE_CORE_TRACE(...)	  ::GameEngine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)	  ::GameEngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...)	  ::GameEngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...)	  ::GameEngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_CRITICAL(...) ::GameEngine::Log::getCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define GE_TRACE(...)	 ::GameEngine::Log::getClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...)	 ::GameEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...)	 ::GameEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...)	 ::GameEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define GE_CRITICAL(...) ::GameEngine::Log::getClientLogger()->critical(__VA_ARGS__)
