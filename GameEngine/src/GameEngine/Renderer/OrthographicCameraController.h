#pragma once

#include "GameEngine/Renderer/OrthographicCamera.h"
#include "GameEngine/Core/Timestep.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/MouseEvent.h"

namespace GameEngine {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthographicCamera& getCamera() { return m_Camera; }
		const OrthographicCamera& getCamera() const { return m_Camera; }

		void setZoomLevel(float level) { m_ZoomLevel = level; }
		float getZoomLevel() { return m_ZoomLevel; }
	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 5.0f;

		bool m_Rotation;
		float m_CameraRotation = 0;
		float m_CameraRotationSpeed = 180.0f;
	};

}