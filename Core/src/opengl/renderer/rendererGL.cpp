#include "rendererGL.h"
#include "opengl/glCore.h"

#include "scene.h"
#include "utils.h"
#include "rendererGL.h"

namespace core {
	RendererGL::RendererGL(int windowWidth, int windowHeight)
		: m_current_VAO(0), m_current_VBO(0), m_current_IBO(0), m_current_shader(0), m_GuiCount(0)
	{
		proj = glm::ortho(0.0f, float(windowWidth), 0.0f, float(windowHeight), -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		translation = glm::vec3(0, 0, 0);
		model = glm::translate(glm::mat4(1.0f), translation);
	}

	RendererGL::~RendererGL()
	{
	}

	void RendererGL::SetDefaultShader(int windowWidth, int windowHeight)
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


	void RendererGL::Draw(const SceneID& s_ID)
	{
		VertexArray* sceneVAO = m_VAOs[s_ID].get();

		if (sceneVAO->GetID() != m_current_VAO) {
			sceneVAO->Bind();
			m_current_VAO = sceneVAO->GetID();
		}

		LayerID l_ID = 0;
		for (const auto& cru : sceneVAO->GetCRUs()) {

			if (m_current_VBO != cru.vbo) {
				BindVertexBuffer(cru.vbo);
				m_current_VBO = cru.vbo;
			}

			if (m_current_IBO != cru.ibo) {
				BindIndexBuffer(cru.ibo);
				m_current_IBO = cru.ibo;
			}

			sceneVAO->UpdateBatchBuffer(l_ID);

			if (m_current_shader != cru.shader) {
				BindShader(cru.shader);
				m_current_shader = cru.shader;
			}

			glCall(glDrawElements(GL_TRIANGLES, cru.iboCount, GL_UNSIGNED_INT, 0));

			sceneVAO->RenderGUI(l_ID);
			l_ID++;
		}

	}
	void RendererGL::AddBatchBufferLayer(const SceneID& s_ID, const LayerID& l_ID)
	{
		if (m_VAOs.find(s_ID) == m_VAOs.end()) {
			m_VAOs[s_ID] = std::make_unique<VertexArray>(&m_shader_manager);
		}

		m_VAOs[s_ID]->Bind();
		m_VAOs[s_ID]->NewBatchBuffer(l_ID);
	}

	Vertex* RendererGL::GetBatchBufferVBO(const SceneID& s_ID, const LayerID& l_ID)
	{
		return m_VAOs[s_ID]->GetBatchBuffer(l_ID)->batchVBO.GetVertexBuffer();
	}

	unsigned int RendererGL::AddMesh(const SceneID& s_ID, const LayerID& l_ID, const Mesh& mesh)
	{
		std::shared_ptr<BatchBuffer> batchBuffer = m_VAOs[s_ID]->GetBatchBuffer(l_ID);

		batchBuffer->batchVBO.PushBack(mesh.eid, mesh.vertices, mesh.vertexCount);
		batchBuffer->batchIBO.PushBack(mesh.eid, mesh.indices, mesh.indexCount, mesh.vertexCount);

		if (batchBuffer->batchVBO.MeshCount() == 1) {
			m_VAOs[s_ID]->Bind();
			batchBuffer->batchVBO.BindVBO();
			batchBuffer->batchVBO.glUpdateBuffer();
			m_VAOs[s_ID]->DefineVertexBufferLayout(sizeof(Vertex));
			m_current_VAO = m_VAOs[s_ID]->GetID();
		}

		return m_VAOs[s_ID]->GetBatchBuffer(l_ID)->batchVBO.GetMeshVectorOffset(mesh.eid);
	}

	void RendererGL::AttachGui(const SceneID& s_ID, const LayerID& l_ID, GuiTemplate*& gui)
	{
		m_VAOs[s_ID]->SetGUI(l_ID, gui);

		if (gui == nullptr) {
			m_GuiCount--;
		}
		else {
			m_GuiCount++;
		}
	}


	void RendererGL::GuiNewFrame()
	{
		if (m_GuiCount > 0) {

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
	}
}


