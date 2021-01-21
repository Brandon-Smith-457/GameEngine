#pragma once

#include "GameEngine/Renderer/RenderCommand.h"

#include "GameEngine/Renderer/OrthographicCamera.h"
#include "GameEngine/Renderer/Shader.h"

namespace GameEngine {

	class Renderer {
	public:
		static void init();
		static void shutdown();

		static void onWindowResize(uint32_t width, uint32_t height);

		static void beginScene(OrthographicCamera& camera);
		static void endScene();

		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};

}