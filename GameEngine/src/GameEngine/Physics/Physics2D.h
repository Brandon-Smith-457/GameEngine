#pragma once

#include "glm/glm.hpp"

namespace GameEngine {

	class Physics2D {
	public:
		static void init(float gravity, float airDrag, float friction, float elasticity);
		static void init();

		static uint32_t createRigidBodyQuad(glm::vec2 pos, bool dynamic, float rot, bool canRot, float width, float height, float mass, glm::vec2 velocity);
		static uint32_t createRigidBodyQuad(glm::vec2 pos, bool dynamic, float rot, bool canRot, float width, float height, float mass, glm::vec2 velocity, float gravity, float airDrag, float friction, float elasticity);

		static void destroyRigidBody(uint32_t id);

		static glm::vec2 getRigidBodyPos(uint32_t id);
		static float getRigidBodyRot(uint32_t id);

		static void runSimulation(float deltaTime);

		static void setGravity(float gravity);
		static void setAirDrag(float airDrag);
		static void setFriction(float friction);
		static void setElasticity(float elasticity);
		static float getGravity();
		static float getAirDrag();
		static float getFriction();
		static float getElasticity();
	};

}