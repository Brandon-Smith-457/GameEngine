#include "gepch.h"
#include "GameEngine/Renderer/Shader.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GameEngine {
	
	Ref<Shader> Shader::create(const std::string& filepath) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLShader>(filepath);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::create(const std::string& name, const std::string& vertexFilepath, const std::string& fragmentFilepath, bool fileFlag)
	{
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLShader>(name, vertexFilepath, fragmentFilepath, fileFlag);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	// Shader Library ------------------------------

	void ShaderLibrary::add(const Ref<Shader>& shader) {
		auto& name = shader->getName();
		add(name, shader);
	}

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader) {
		GE_CORE_ASSERT(!exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& filepath) {
		auto shader = Shader::create(filepath);
		add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::get(const std::string& name) {
		GE_CORE_ASSERT(exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}