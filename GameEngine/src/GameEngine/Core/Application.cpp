#include "gepch.h"
#include "GameEngine/Core/Application.h"

#include "GameEngine/Core/Log.h"

#include "GameEngine/Renderer/Renderer.h"

#include "GameEngine/Core/Input.h"

#include "GLFW/glfw3.h"

namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_LastFrameTime(glfwGetTime()) {
		GE_PROFILE_FUNCTION();

		GE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::create();
		m_Window->setEventCallback(GE_BIND_EVENT_FN(Application::onEvent));

		Renderer::init();

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
		GE_PROFILE_FUNCTION();

		Renderer::shutdown();
	}

	void Application::pushLayer(Layer* layer) {
		GE_PROFILE_FUNCTION();

		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer) {
		GE_PROFILE_FUNCTION();

		m_LayerStack.pushOverlay(layer);
		layer->onAttach();
	}

	void Application::onEvent(Event& e) {
		GE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::onWindowClose));
		dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(Application::onWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			(*it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::run() {
		GE_PROFILE_FUNCTION();

		while (m_Running) {
			GE_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); // Platform::getTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				{
					GE_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->onUpdate(timestep);
				}

				m_ImGuiLayer->begin();
				{
					GE_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->onImGuiRender();
				}
				m_ImGuiLayer->end();
			}
			m_Window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& e) {
		GE_PROFILE_FUNCTION();

		if (e.getWidth() == 0 || e.getHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		
		Renderer::onWindowResize(e.getWidth(), e.getHeight());

		return false;
	}

}