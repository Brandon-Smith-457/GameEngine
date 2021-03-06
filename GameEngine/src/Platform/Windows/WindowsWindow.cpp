#include "gepch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "GameEngine/Core/Input.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"

#include "GameEngine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/OpenGL/OpenGLVersion.h"

namespace GameEngine {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description) {
		GE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		GE_PROFILE_FUNCTION();

		init(props);
	}

	WindowsWindow::~WindowsWindow() {
		GE_PROFILE_FUNCTION();

		shutdown();
	}

	void WindowsWindow::init(const WindowProps& props) {
		GE_PROFILE_FUNCTION();

		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;

		GE_CORE_INFO("Creating Window {0} ({1}, {2})", props.title, props.width, props.height);

		if (s_GLFWWindowCount == 0) {
			int success = glfwInit();
			GE_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			GE_PROFILE_SCOPE("glfwCreateWindow");
		#if defined(GE_DEBUG)
			if (Renderer::getAPI() == RendererAPI::API::OpenGL)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif
			m_Window = glfwCreateWindow((int)props.width, (int)props.height, m_Data.title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		m_Context = GraphicsContext::create(m_Window);
		m_Context->init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window,
			[](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.eventCallback(event);
			});

		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
					case GLFW_PRESS: {
						KeyPressedEvent event(static_cast<KeyCode>(key), 0);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE: {
						KeyReleasedEvent event(static_cast<KeyCode>(key));
						data.eventCallback(event);
						break;
					}
					case GLFW_REPEAT: {
						KeyPressedEvent event(static_cast<KeyCode>(key), 1);
						data.eventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window,
			[](GLFWwindow* window, unsigned int keycode) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data.eventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
					case GLFW_PRESS: {
						MouseButtonPressedEvent event(static_cast<MouseCode>(button));
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE: {
						MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
						data.eventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window,
			[](GLFWwindow* window, double xOffset, double yOffset) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xPos, double yPos) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.eventCallback(event);
			});
	}

	void WindowsWindow::shutdown() {
		GE_PROFILE_FUNCTION();

		OpenGLVersion::shutdown();
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;
		if (s_GLFWWindowCount == 0) {
			glfwTerminate();
		}
	}

	void WindowsWindow::onUpdate() {
		GE_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->swapBuffers();
	}

	void WindowsWindow::setVSync(bool enabled) {
		GE_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.vSync = enabled;
	}

	bool WindowsWindow::isVSync() const {
		return m_Data.vSync;
	}

}