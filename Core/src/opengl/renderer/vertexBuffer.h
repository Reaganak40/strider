#pragma once
#include "core.h"
#include "opengl/glCore.h"

#include "entity.h"
#include <unordered_map>

#include <iostream>
namespace core {
	struct VertexBufferLayoutElement {
		unsigned int glType;
		int count;

		unsigned int GetSize() {
			switch (glType) {
			case GL_FLOAT:
				return sizeof(float);
			case GL_INT:
				return sizeof(int);
			}
			std::cout << "Warning: Could not find sizeof(type): " << std::hex << glType << std::endl;
			return 0;
		}
	};


	typedef unsigned int VertexBufferID;

	VertexBufferID RegisterVertexBuffer(void* vertices, size_t size, unsigned int glDrawHint = GL_STATIC_DRAW);

	inline void BindVertexBuffer(VertexBufferID vbo) { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
	inline void UnbindVertexBuffer() { glBindBuffer(GL_ARRAY_BUFFER, 0); }


	class DynamicVertexBuffer {
	private:

		VertexBufferID m_VBO;

		std::unique_ptr<Vertex[]> m_buffer;
		unsigned int m_max_vertices;
		unsigned int m_vertex_count;

		std::vector<unsigned int> meshes;
		std::unordered_map<EntityID, unsigned int> meshMap;
		std::vector<EntityID> mesh_backref;

	public:
		DynamicVertexBuffer(unsigned int nMaxVertices=DYNAMIC_BUFFER_DEFAULT_LIMIT);
		~DynamicVertexBuffer();

		DynamicVertexBuffer& operator= (DynamicVertexBuffer&&) = default;

		/*
			Registers the vertex buffer with the currently binded VAO.
		*/
		VertexBufferID RegisterWithVAO();

		int PushBack(EntityID key, Vertex* mesh, unsigned int vertexCount);
		int Remove(EntityID key);
		int InsertAt(unsigned int meshIndex, EntityID key, Vertex* mesh, unsigned int vertexCount);

		Vertex* GetMeshBuffer(EntityID key, int meshIndexOffset = 0);

		unsigned int GetMeshVectorOffset(EntityID key);

		Vertex* GetVertexBuffer();

		void BindVBO();

		void glUpdateBuffer();

		int inline MeshCount() { return meshes.size(); }
	};
}