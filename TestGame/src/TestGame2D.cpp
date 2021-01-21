#include "TestGame2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TestGame2D::TestGame2D() : Layer("TestGame2D"), m_CameraController(1280.0f / 720.0f, true) {

}

void TestGame2D::onAttach() {
	GE_PROFILE_FUNCTION();

	m_CheckerboardTexture = GameEngine::Texture2D::create("Assets/Textures/Checkerboard.png");
	m_PenguinTexture = GameEngine::Texture2D::create("Assets/Textures/Penguin.png");
	GameEngine::Physics2D::init();
	m_RigidBodyID = GameEngine::Physics2D::createRigidBodyQuad({ -1.0f, -1.0f }, true, glm::radians(45.0f), true, 1.0f, 1.0f, 1.0f, { 0.0f, 0.0f });
}

void TestGame2D::onDetach() {
	GE_PROFILE_FUNCTION();

	GameEngine::Physics2D::destroyRigidBody(m_RigidBodyID);
}

void TestGame2D::onUpdate(GameEngine::Timestep ts) {
	GE_PROFILE_FUNCTION();
	
	// Update
	m_CameraController.onUpdate(ts);

	// Render
	{
		GE_PROFILE_SCOPE("Renderer Prep");
		GameEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GameEngine::RenderCommand::clear();
	}
	glm::vec2 pos;
	float rot;
	{
		GE_PROFILE_SCOPE("GetPhysicsPosRot");

		pos = GameEngine::Physics2D::getRigidBodyPos(m_RigidBodyID);
		rot = GameEngine::Physics2D::getRigidBodyRot(m_RigidBodyID);
	}
	{
		GE_PROFILE_SCOPE("Renderer Draw");
		GameEngine::Renderer2D::beginScene(m_CameraController.getCamera());

		GameEngine::Renderer2D::drawRotatedQuad(pos, { 1.5f, 1.5f }, rot, { 0.8f, 0.2f, 0.3f, 1.0f });
		GameEngine::Renderer2D::drawRotatedQuad({ 1.0f, 1.0f }, { 0.5f, 1.0f }, glm::radians(90.0f), m_SquareColor);
		GameEngine::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f },  { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		GameEngine::Renderer2D::drawRotatedQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, glm::radians(360.0f), m_PenguinTexture);
		
		GameEngine::Renderer2D::endScene();
	}

	{
		GE_PROFILE_SCOPE("Physics2D::runSimulation");
		GameEngine::Physics2D::runSimulation(ts.getSeconds());
	}
}

void TestGame2D::onImGuiRender() {
	GE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	
	ImGui::End();
}

void TestGame2D::onEvent(GameEngine::Event& event) {
	m_CameraController.onEvent(event);
}