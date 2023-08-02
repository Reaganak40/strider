#pragma once

#include "vertexArray.h"
#include "indexBuffer.h"

#include "error.h"

typedef unsigned int RendererID;

class Scene;
namespace core {


	class Renderer {
	private:
		VertexArrayID m_current_VAO;
		VertexBufferID m_current_VBO;
		IndexBufferID m_current_IBO;
		ShaderID m_current_shader;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
		glm::vec3 translation;


	public:
		ShaderManager m_shader_manager;

		Renderer(int windowWidth = 1, int windowHeight = 1);
		~Renderer();

		void SetDefaultShader(int windowWidth, int windowHeight);

		void inline Clear() { glClear(GL_COLOR_BUFFER_BIT); }

		void Draw(std::shared_ptr<Scene> scene);

		void inline SetBackgroundColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
	};
}