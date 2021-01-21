#include "gepch.h"
#include "GameEngine/Physics/Physics2D.h"

#include "PhysicsEngine/Engine.h"

namespace GameEngine {
	void Physics2D::init(float gravity, float airDrag, float friction, float elasticity) {
		PhysicsEngine::Engine::init(gravity, airDrag, friction, elasticity);
	}

	void Physics2D::init() {
		PhysicsEngine::Engine::init();
	}

	uint32_t Physics2D::createRigidBodyQuad(glm::vec2 pos, bool dynamic, float rot, bool canRot, float width, float height, float mass, glm::vec2 velocity) {
		return PhysicsEngine::Engine::createRigidBodyQuad(pos.x, pos.y, dynamic, rot, canRot, width, height, mass, velocity.x, velocity.y);
	}

	uint32_t Physics2D::createRigidBodyQuad(glm::vec2 pos, bool dynamic, float rot, bool canRot, float width, float height, float mass, glm::vec2 velocity, float gravity, float airDrag, float friction, float elasticity) {
		return PhysicsEngine::Engine::createRigidBodyQuad(pos.x, pos.y, dynamic, rot, canRot, width, height, mass, velocity.x, velocity.y, gravity, airDrag, friction, elasticity);
	}

	void Physics2D::destroyRigidBody(uint32_t id) {
		PhysicsEngine::Engine::destroyRigidBody(id);
	}

	glm::vec2 Physics2D::getRigidBodyPos(uint32_t id) {
		std::vector<float> pos = PhysicsEngine::Engine::getRigidBodyPos(id);
		return { pos[0], pos[1] };
	}

	float Physics2D::getRigidBodyRot(uint32_t id) {
		return PhysicsEngine::Engine::getRigidBodyRot(id);
	}

	void Physics2D::runSimulation(float deltaTime) {
		PhysicsEngine::Engine::runSimulation(deltaTime);
	}

	// Getters / Setters

	void Physics2D::setGravity(float gravity) {
		PhysicsEngine::Engine::setGravity(gravity);
	}

	void Physics2D::setAirDrag(float airDrag) {
		PhysicsEngine::Engine::setAirDrag(airDrag);
	}

	void Physics2D::setFriction(float friction) {
		PhysicsEngine::Engine::setFriction(friction);
	}

	void Physics2D::setElasticity(float elasticity) {
		PhysicsEngine::Engine::setElasticity(elasticity);
	}

	float Physics2D::getGravity() {
		return PhysicsEngine::Engine::getGravity();
	}

	float Physics2D::getAirDrag() {
		return PhysicsEngine::Engine::getAirDrag();
	}

	float Physics2D::getFriction() {
		return PhysicsEngine::Engine::getFriction();
	}

	float Physics2D::getElasticity() {
		return PhysicsEngine::Engine::getElasticity();
	}

}