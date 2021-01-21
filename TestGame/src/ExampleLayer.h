#pragma once

#include "GameEngine.h"

class ExampleLayer : public GameEngine::Layer {
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(GameEngine::Timestep ts) override;
	virtual void onImGuiRender() override;
	void onEvent(GameEngine::Event& e) override;

private:
	GameEngine::ShaderLibrary m_ShaderLibrary;

	GameEngine::Ref<GameEngine::Shader> m_TriangleShader;
	GameEngine::Ref<GameEngine::VertexArray> m_VertexArray;

	GameEngine::Ref<GameEngine::Shader> m_FlatColorShader;
	GameEngine::Ref<GameEngine::VertexArray> m_SquareVA;

	GameEngine::Ref<GameEngine::Texture2D> m_Texture, m_ChernoLogoTexture;

	GameEngine::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};