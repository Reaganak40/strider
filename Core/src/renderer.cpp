#include "renderer.h"

void Renderer::Draw(CoreRenderUnit cru) {
		BindVertexBuffer(cru.vbo);
		BindIndexBuffer(cru.ibo);
		BindShader(cru.shader);
		glDrawElements(GL_TRIANGLES, cru.iboCount, GL_UNSIGNED_INT, nullptr);
}
