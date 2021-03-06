#pragma once

#include "GameEngine/Renderer/RendererAPI.h"

namespace GameEngine {

	class RenderCommand {
	public:
		inline static void init() {
			s_RendererAPI->init();
		}

		inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			s_RendererAPI->setViewport(x, y, width, height);
		}

		inline static void setClearColor(const glm::vec4& color) {
			s_RendererAPI->setClearColor(color);
		}

		inline static void clear() {
			s_RendererAPI->clear();
		}

		inline static void drawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RendererAPI->drawIndexed(vertexArray);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}