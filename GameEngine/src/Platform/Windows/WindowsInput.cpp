#include "gepch.h"
#include "Platform/Windows/WindowsInput.h"

#include "GameEngine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace GameEngine {

	bool WindowsInput::isKeyPressedImpl(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::getMouseXImpl()
	{
		auto [x, y] = getMousePosImpl();
		return x;
	}

	float WindowsInput::getMouseYImpl()
	{
		auto [x, y] = getMousePosImpl();
		return y;
	}

}