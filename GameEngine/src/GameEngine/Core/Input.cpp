#include "gepch.h"
#include "GameEngine/Core/Input.h"

#ifdef GE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace GameEngine {
	Scope<Input> Input::s_Instance = Input::create();

	Scope<Input> Input::create() {
	#ifdef GE_PLATFORM_WINDOWS
		return createScope<WindowsInput>();
	#else
		GE_CORE_ASSERT(flase, "Unknown platform!");
		return nullptr;
	#endif
	}
}