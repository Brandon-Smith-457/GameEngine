#include "gepch.h"
#include "GameEngine/Renderer/VertexArray.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GameEngine {

	Ref<VertexArray> VertexArray::create() {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLVertexArray>();
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}