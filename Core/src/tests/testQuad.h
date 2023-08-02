#pragma once
#include "test.h"
#include <renderer/vertexArray.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace core;
namespace test {
	class TestBasicQuad : public Test {
	private:
		
		float quadWidth;
		float quadHeight;
		float quadColor[4];
		int maxX;
		int maxY;

		VertexArray vao;
		Vertex_PTC positions[4];

		IndexBuffer indices[6];
		IndexBufferID ibo;
		IndexBufferCount iboCount;

		UniformVariable uMVP;
		UniformVariable uColor;
		ShaderID shader;

		glm::mat4 proj;
		glm::mat4 view;
		glm::vec3 translation;

	public:
		TestBasicQuad(GLFWwindow* windowContext);
		~TestBasicQuad();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
