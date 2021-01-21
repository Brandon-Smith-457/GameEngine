#include "gepch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "OpenGLVersion.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace GameEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		GE_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::init() {
		GE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Failed to initializee Glad!");

		GE_CORE_INFO("OpenGL Info:\n  Vendor: {0}\n  Renderer: {1}\n  Version: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		OpenGLVersion::setVersion(versionMajor, versionMinor);
	}

	void OpenGLContext::swapBuffers() {
		GE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}