#pragma once

#include "GameEngine/Core/Window.h"
#include "GameEngine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace GameEngine {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_Data.width; }
		inline unsigned int getHeight() const override { return m_Data.height; }

		// window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.eventCallback = callback; }
		void setVSync(bool enable) override;
		bool isVSync() const override;

		inline virtual void* getNativeWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool vSync;
			EventCallbackFn eventCallback;
		};

		WindowData m_Data;

		virtual void init(const WindowProps& props);
		virtual void shutdown();
	};

}