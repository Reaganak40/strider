#include "renderer.h"
#include "error.h"

#include "scene.h"
#include "utils.h"

namespace core {
	Renderer::Renderer(int windowWidth, int windowHeight)
		: m_current_VAO(0), m_current_VBO(0), m_current_IBO(0), m_current_shader(0)
	{
		proj = glm::ortho(0.0f, float(windowWidth), 0.0f, float(windowHeight), -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		translation = glm::vec3(0, 0, 0);
		model = glm::translate(glm::mat4(1.0f), translation);
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::SetDefaultShader(int windowWidth, int windowHeight)
	{
		proj = glm::ortho(0.0f, float(windowWidth), 0.0f, float(windowHeight), -1.0f, 1.0f);
		glm::mat4 mvp = proj * view * model;

		std::shared_ptr<Shader> defaultShader;
		if (!(defaultShader = m_shader_manager.GetShader("default"))) {
			defaultShader = std::make_shared<Shader>(
				ReadFile("resources/shaders/vertex.glsl"),
				ReadFile("resources/shaders/fragment.glsl")
			);
			
			m_shader_manager.AddShader("default", defaultShader);
		}

		defaultShader->Bind();
		defaultShader->SetUniform<Strider::vec4f>("uColor", { 1.0f, 1.0f, 0.0f, 1.0f });
		defaultShader->SetUniform<glm::mat4>("uMVP", mvp);
	}


	void Renderer::Draw(std::shared_ptr<Scene> scene)
	{
		if (scene->m_VAO.GetID() != m_current_VAO) {
			scene->m_VAO.Bind();
			m_current_VAO = scene->m_VAO.GetID();
		}

		BatchBufferID possibleBBID = 0;
		for (const auto& cru: scene->m_VAO.GetCRUs()) {
			if (m_current_VBO != cru.vbo) {
				BindVertexBuffer(cru.vbo);
				m_current_VBO = cru.vbo;
			}

			if (m_current_IBO != cru.ibo) {
				BindIndexBuffer(cru.ibo);
				m_current_IBO = cru.ibo;
			}

			scene->m_VAO.UpdateBatchBuffer(possibleBBID);

			if (m_current_shader != cru.shader) {
				BindShader(cru.shader);
				m_current_shader = cru.shader;
			}

			glCall(glDrawElements(GL_TRIANGLES, cru.iboCount, GL_UNSIGNED_INT, 0));
		}

	}
}