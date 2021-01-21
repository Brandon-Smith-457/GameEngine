#pragma once

#include "GameEngine.h"

class TestGame2D : public GameEngine::Layer {
public:
	TestGame2D();
	virtual ~TestGame2D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(GameEngine::Timestep ts) override;
	virtual void onImGuiRender() override;
	void onEvent(GameEngine::Event& event) override;

private:
	GameEngine::OrthographicCameraController m_CameraController;

	// Temporary
	GameEngine::Ref<GameEngine::Texture2D> m_CheckerboardTexture;
	GameEngine::Ref<GameEngine::Texture2D> m_PenguinTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	uint32_t m_RigidBodyID;
};