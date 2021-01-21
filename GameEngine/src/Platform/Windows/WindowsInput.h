#pragma once

#include "GameEngine/Core/Input.h"

namespace GameEngine {

	class WindowsInput : public Input {
	protected:
		virtual bool isKeyPressedImpl(KeyCode key) override;
		virtual bool isMouseButtonPressedImpl(MouseCode button) override;
		virtual std::pair<float, float> getMousePosImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
	};

}