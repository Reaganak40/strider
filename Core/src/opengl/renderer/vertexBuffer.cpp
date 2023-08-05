#include "vertexBuffer.h"

namespace core {
	VertexBufferID RegisterVertexBuffer(void* vertices, size_t size, unsigned int glDrawHint) {
		VertexBufferID bufferID = 0;
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, glDrawHint);
		return bufferID;
	}
	
	
	DynamicVertexBuffer::DynamicVertexBuffer(unsigned int nMaxVertices)
		: m_max_vertices(nMaxVertices), m_vertex_count(0), m_VBO(0)
	{
		m_buffer = std::make_unique<Vertex[]>(nMaxVertices);
	}

	DynamicVertexBuffer::~DynamicVertexBuffer()
	{
	}

	VertexBufferID DynamicVertexBuffer::RegisterWithVAO()
	{
		return m_VBO = RegisterVertexBuffer(nullptr, sizeof(Vertex) * m_max_vertices, GL_DYNAMIC_DRAW);
	}

	int DynamicVertexBuffer::PushBack(EntityID key, Vertex* mesh, unsigned int vertexCount)
	{
		if ((m_vertex_count + vertexCount) > m_max_vertices) {
			printf("Warning: Exceeded Dynamic Buffer size\n");
			return -1;
		}

		memcpy(m_buffer.get() + m_vertex_count, mesh, sizeof(Vertex) * vertexCount);

		meshes.push_back(m_vertex_count);
		meshMap[key] = meshes.size() - 1;
		mesh_backref.push_back(key);


		m_vertex_count += vertexCount;
		
		return 0;
	}

	int DynamicVertexBuffer::Remove(EntityID key)
	{
		return -1;
	}

	int DynamicVertexBuffer::InsertAt(unsigned int meshIndex, EntityID key, Vertex* mesh, unsigned int vertexCount)
	{
		return -1;
	}


	Vertex* DynamicVertexBuffer::GetMeshBuffer(EntityID key, int meshIndexOffset)
	{
		if (meshMap.find(key) == meshMap.end()) {
			return nullptr;
		}

		return m_buffer.get() + meshes[meshMap[key] + meshIndexOffset];
	}

	unsigned int DynamicVertexBuffer::GetMeshVectorOffset(EntityID key)
	{
		return meshes[meshMap[key]];
	}

	Vertex* DynamicVertexBuffer::GetVertexBuffer()
	{
		return m_buffer.get();
	}

	void DynamicVertexBuffer::BindVBO()
	{
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));

	}

	void DynamicVertexBuffer::glUpdateBuffer()
	{
		glCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertex_count * sizeof(Vertex), m_buffer.get()));
	}
}
