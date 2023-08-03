#pragma once
#include "core.h"
#include "entity.h"
#include <unordered_map>

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

	struct Vertex {
		float position[3];
		float texCoords[2];
		int texID;
		float colorRGBA[4];
	};

	/*
		Contains 3-float positions and 2-float texCoords.
	*/
	struct Vertex_PT {
		float position[3];
		float texCoords[2];
	};

	/*
		Contains 3-float positions, 2-float texCoords, and 4-float RGBA.
	*/
	struct Vertex_PTC {
		float position[3];
		float texCoords[2];
		float colorRGBA[4];
	};

	struct Vertex_PC {
		float position[3];
		float colorRGBA[4];
	};

#define VERTEX_TYPE_BASE sizeof(Vertex)
#define VERTEX_TYPE_PTC sizeof(Vertex_PTC)
#define VERTEX_TYPE_PT sizeof(Vertex_PT)
#define VERTEX_TYPE_PC sizeof(Vertex_PC)

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