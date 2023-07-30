#pragma once

#pragma once
#include "test.h"
#include "vertexArray.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
	class TestTexture2D : public Test {
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

		ShaderID shader;
		Texture texture;
		UniformVariable uMVP;
		UniformVariable uTexture;

		glm::mat4 proj;
		glm::mat4 view;
		glm::vec3 translation;

	public:
		TestTexture2D(GLFWwindow* windowContext);
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
