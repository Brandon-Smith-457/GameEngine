#pragma once

#include "GameEngine/Core/Core.h"

#include "GameEngine/Core/Window.h"
#include "GameEngine/Core/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"

#include "GameEngine/Core/Timestep.h"

#include "GameEngine/imgui/ImguiLayer.h"

int main(int argc, char** argv);

namespace GameEngine {

	class Application {
	public:
		Application();
		virtual ~Application();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		inline Window& getWindow() { return *m_Window; }

		inline static Application& get() { return *s_Instance; }
	private:
		void run();
		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	//To be defined in the client program
	Application* createApplication();

}