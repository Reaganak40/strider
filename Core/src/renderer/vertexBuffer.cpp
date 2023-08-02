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
		: m_maxBufferSize(nMaxVertices * sizeof(Vertex)), m_bufferSize(0), m_VBO(0), m_shouldUpdate(0)
	{
		m_buffer = std::make_unique<Vertex[]>(nMaxVertices);
	}

	DynamicVertexBuffer::~DynamicVertexBuffer()
	{
	}

	VertexBufferID DynamicVertexBuffer::RegisterWithVAO()
	{
		return m_VBO = RegisterVertexBuffer(nullptr, m_maxBufferSize, GL_DYNAMIC_DRAW);
	}

	int DynamicVertexBuffer::PushBack(EntityID key, Vertex* mesh, unsigned int vertexCount)
	{
		if ((m_bufferSize + sizeof(Vertex) * vertexCount) > m_maxBufferSize) {
			printf("Warning: Exceeded Dynamic Buffer size\n");
			return -1;
		}

		memcpy(m_buffer.get() + m_bufferSize, mesh, sizeof(Vertex) * vertexCount);

		meshes.push_back(m_buffer.get() + m_bufferSize);
		meshMap[key] = meshes.size() - 1;
		mesh_backref.push_back(key);


		m_bufferSize += (sizeof(Vertex) * vertexCount);

		if (meshes.size() == 1 || m_shouldUpdate == 2) {
			m_shouldUpdate = 2;
		}
		else {
			m_shouldUpdate = 1;
		}
		return 0;
	}

	int DynamicVertexBuffer::Remove(EntityID key)
	{
		if (meshMap.find(key) == meshMap.end()) {
			printf("Warning: Tried to remove non-existent entity.\n");
			return -1;
		}
		
		unsigned int current_index = meshMap[key];
		std::vector<EntityID>::iterator msh_it = mesh_backref.erase(mesh_backref.begin() + current_index);

		// update the meshMap
		// from remove index -- shift all right to the left 1
		for (; msh_it != mesh_backref.end(); ++msh_it)
		{
			meshMap[*msh_it] = current_index++;
		}

		// shift buffer left -- erasing target mesh
		size_t remove_size;
		if ((meshMap[key] + 1) < meshes.size()) {
			remove_size = meshes[meshMap[key] + 1] - meshes[meshMap[key]];
			memcpy(meshes[meshMap[key]], meshes[meshMap[key] + 1], (m_buffer.get() + m_bufferSize) - (meshes[meshMap[key] + 1]));
		}
		else {
			remove_size = (m_buffer.get() + m_bufferSize) - meshes[meshMap[key]];
		}

		// update meshes vector, left-shifting all to the right
		current_index = meshMap[key];
		meshes.erase(meshes.begin() + current_index);
		for (auto it = (meshes.begin() + current_index + 1); it != meshes.end(); ++it) {
			*it -= remove_size;
		}

		m_bufferSize -= remove_size;
		m_shouldUpdate = (!m_shouldUpdate ? 1 : m_shouldUpdate);

		return current_index;
	}

	int DynamicVertexBuffer::InsertAt(unsigned int meshIndex, EntityID key, Vertex* mesh, unsigned int vertexCount)
	{
		size_t nMeshSize = sizeof(Vertex) * vertexCount;

		if ((m_bufferSize + nMeshSize) > m_maxBufferSize) {
			printf("Warning: Exceeded Dynamic Buffer size\n");
			return -1;
		}

		Vertex* insertAddr = meshes[meshIndex];
		size_t rightSize = (size_t)((m_buffer.get() + m_bufferSize) - insertAddr);
		Vertex* rightData = (Vertex*)malloc(rightSize);

		if (rightData == NULL) {
			printf("Warning: Malloc failed!\n");
			return -1;
		}

		memcpy(rightData, insertAddr, rightSize);
		memcpy(insertAddr, mesh, nMeshSize);
		memcpy(insertAddr + vertexCount, rightData, rightSize);

		int current_index = meshIndex;
		for (auto it = mesh_backref.insert(mesh_backref.begin() + meshIndex, key); it != mesh_backref.end(); ++it) {
			meshMap[*it] = meshIndex++;
		}

		for (auto it = (++meshes.insert(meshes.begin() + meshIndex, insertAddr)); it != meshes.end(); ++it) {
			*it += vertexCount;
		}


		m_shouldUpdate = (!m_shouldUpdate ? 1 : m_shouldUpdate);

		return 0;
	}


	Vertex* DynamicVertexBuffer::GetMeshBuffer(EntityID key)
	{
		if (meshMap.find(key) == meshMap.end()) {
			return nullptr;
		}

		m_shouldUpdate = (!m_shouldUpdate ? 1 : m_shouldUpdate);
		return meshes[meshMap[key]];
	}
	void DynamicVertexBuffer::BindVBO()
	{
		glBindBuffer(GL_VERTEX_ARRAY, m_VBO);

	}
	int DynamicVertexBuffer::glUpdateBuffer()
	{
		int status = m_shouldUpdate;
		if (m_shouldUpdate) {
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSize, m_buffer.get());
			m_shouldUpdate = 0;
		}

		return status;
	}
}
