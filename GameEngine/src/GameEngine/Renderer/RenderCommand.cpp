#include "gepch.h"
#include "GameEngine/Renderer/RenderCommand.h"

namespace GameEngine {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::create();

}