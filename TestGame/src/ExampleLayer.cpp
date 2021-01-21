#include "ExampleLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleLayer::ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f, true) {
	m_VertexArray = GameEngine::VertexArray::create();

	//TRIANGLE
	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	GameEngine::Ref<GameEngine::VertexBuffer> vertexBuffer = GameEngine::VertexBuffer::create(vertices, sizeof(vertices));
	GameEngine::BufferLayout layout = {
		{ GameEngine::ShaderDataType::Float3, "a_Position" },
		{ GameEngine::ShaderDataType::Float4, "a_Color" }
	};

	vertexBuffer->setLayout(layout);
	m_VertexArray->addVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	GameEngine::Ref<GameEngine::IndexBuffer> indexBuffer = GameEngine::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->setIndexBuffer(indexBuffer);

	//SQUARE
	m_SquareVA = GameEngine::VertexArray::create();

	float squareVertices[4 * 5] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	GameEngine::Ref<GameEngine::VertexBuffer> squareVB = GameEngine::VertexBuffer::create(squareVertices, sizeof(squareVertices));

	squareVB->setLayout({
		{ GameEngine::ShaderDataType::Float3, "a_Position" },
		{ GameEngine::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->addVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	GameEngine::Ref<GameEngine::IndexBuffer> squareIB = GameEngine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->setIndexBuffer(squareIB);

	std::string triangleVertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;
		out vec4 v_Color;
		
		void main() {
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)";

	std::string triangleFragmentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main() {
			color = vec4(v_Position * 0.5 + 0.5, 1.0);
			color = v_Color;
		}
	)";


	m_TriangleShader = GameEngine::Shader::create("VertexPosColor", triangleVertexSrc, triangleFragmentSrc);

	std::string flatColorShaderVertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;
		
		void main() {
			v_Position = a_Position;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)";

	std::string flatColorShaderFragmentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 color;

		in vec3 v_Position;

		uniform vec3 u_Color;

		void main() {
			color = vec4(u_Color, 1.0);
		}
	)";

	m_FlatColorShader = GameEngine::Shader::create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

	auto textureShader = m_ShaderLibrary.load("Assets/Shaders/Texture.glsl");
	//m_TextureShader = GameEngine::Shader::create("Texture", "Assets/Shaders/VertexTexture.glsl", "Assets/Shaders/FragmentTexture.glsl", true);

	m_Texture = GameEngine::Texture2D::create("Assets/Textures/Checkerboard.png");
	m_ChernoLogoTexture = GameEngine::Texture2D::create("Assets/Textures/ChernoLogo.png");

	textureShader->bind();
	textureShader->setInt("u_Texture", 0);
}

void ExampleLayer::onAttach() {

}

void ExampleLayer::onDetach() {

}

void ExampleLayer::onUpdate(GameEngine::Timestep ts) {
	// Update
	m_CameraController.onUpdate(ts);

	// Render
	GameEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GameEngine::RenderCommand::clear();

	GameEngine::Renderer::beginScene(m_CameraController.getCamera());

	static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->bind();
	m_FlatColorShader->setFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			glm::vec3 pos(x * 0.11f, y * 0.11f, -0.1f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			GameEngine::Renderer::submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	auto textureShader = m_ShaderLibrary.get("Texture");

	m_Texture->bind();
	GameEngine::Renderer::submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->bind();
	GameEngine::Renderer::submit(textureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.1f }) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	// Triangle
	//GameEngine::Renderer::submit(m_Shader, m_VertexArray);

	GameEngine::Renderer::endScene();
}

void ExampleLayer::onImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::onEvent(GameEngine::Event& event) {
	m_CameraController.onEvent(event);
}
