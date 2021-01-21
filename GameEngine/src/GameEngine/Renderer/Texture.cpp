#include "gepch.h"
#include "GameEngine/Renderer/Texture.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace GameEngine {
	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(width, height);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::create(const std::string& path) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(path);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}