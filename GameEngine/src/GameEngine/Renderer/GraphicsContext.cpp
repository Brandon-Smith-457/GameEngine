#include "gepch.h"
#include "GameEngine/Renderer/GraphicsContext.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace GameEngine {

	Scope<GraphicsContext> GraphicsContext::create(void* window) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:	GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return createScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}