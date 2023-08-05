#pragma once

#include "core.h"
#include "gui.h"
#include "vertexArray.h"
#include "indexBuffer.h"


typedef unsigned int RendererID;

class Scene;
namespace core {


	class RendererGL {
	private:
		VertexArrayID m_current_VAO;
		VertexBufferID m_current_VBO;
		IndexBufferID m_current_IBO;
		ShaderID m_current_shader;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
		glm::vec3 translation;

		std::unordered_map<SceneID, std::unique_ptr<VertexArray>> m_VAOs;

		int m_GuiCount;

	public:
		ShaderManager m_shader_manager;

		RendererGL(int windowWidth = 1, int windowHeight = 1);
		~RendererGL();

		void SetDefaultShader(int windowWidth, int windowHeight);

		void inline Clear() { glClear(GL_COLOR_BUFFER_BIT); }

		void Draw(const SceneID& s_ID);

		void inline SetBackgroundColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }

		void AddBatchBufferLayer(const SceneID& s_ID, const LayerID& l_ID);
		Vertex* GetBatchBufferVBO(const SceneID& s_ID, const LayerID& l_ID);
		unsigned int AddMesh(const SceneID& s_ID, const LayerID& l_ID, const Mesh& mesh);

		void AttachGui(const SceneID& s_ID, const LayerID& l_ID, GuiTemplate*& gui);

		void GuiNewFrame();

	};
}