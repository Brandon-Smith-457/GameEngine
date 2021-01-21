#include <GameEngine.h>
#include "GameEngine/Core/EntryPoint.h"

#include "TestGame2D.h"
#include "ExampleLayer.h"


class TestGame : public GameEngine::Application {
public:
	TestGame() {
		//pushLayer(new ExampleLayer());
		pushLayer(new TestGame2D());
	}
	
	~TestGame() {

	}
};

GameEngine::Application* GameEngine::createApplication() {
	return new TestGame();
}