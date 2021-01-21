#pragma once
#include "GameEngine/Core/Core.h"

#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::createApplication();

int main(int argc, char** argv) {
	GameEngine::Log::init();

	GE_PROFILE_BEGIN_SESSION("Startup", "GameEngineProfile-Startup.json");
	auto app = GameEngine::createApplication();
	GE_PROFILE_END_SESSION();

	GE_PROFILE_BEGIN_SESSION("Runtime", "GameEngineProfile-Runtime.json");
	app->run();
	GE_PROFILE_END_SESSION();

	GE_PROFILE_BEGIN_SESSION("Shutdown", "GameEngineProfile-Shutdown.json");
	delete app;
	GE_PROFILE_END_SESSION();
}
#endif
