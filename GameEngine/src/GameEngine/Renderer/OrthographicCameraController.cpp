#include "gepch.h"
#include "GameEngine/Renderer/OrthographicCameraController.h"

#include "GameEngine/Core/Input.h"
#include "GameEngine/Core/KeyCodes.h"

namespace GameEngine {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {

	}

	void OrthographicCameraController::onUpdate(Timestep ts) {
		GE_PROFILE_FUNCTION();

		m_CameraTranslationSpeed = m_ZoomLevel;
		
		if (Input::isKeyPressed(GE_KEY_A)) {
			m_CameraPosition.x -= cosf(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sinf(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		if (Input::isKeyPressed(GE_KEY_D)) {
			m_CameraPosition.x += cosf(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sinf(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		if (Input::isKeyPressed(GE_KEY_S)) {
			m_CameraPosition.x -= -sinf(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cosf(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		if (Input::isKeyPressed(GE_KEY_W)) {
			m_CameraPosition.x += -sinf(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cosf(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		//Camera Rotation
		if (m_Rotation) {
			if (Input::isKeyPressed(GE_KEY_Q)) {
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			if (Input::isKeyPressed(GE_KEY_E)) {
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.setRotation(m_CameraRotation);
		}

		m_Camera.setPosition(m_CameraPosition);
	}

	void OrthographicCameraController::onEvent(Event& e) {
		GE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(GE_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e) {
		GE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.getYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e) {
		GE_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.getWidth()/(float)e.getHeight();
		m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}