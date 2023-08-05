#include "indexBuffer.h"

namespace core {

	IndexBufferID RegisterIndexBuffer(IndexBuffer* ibo, size_t size, unsigned int glDrawHint) {
		IndexBufferID bufferID = 0;
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, ibo, glDrawHint);
		return bufferID;
	}

	DynamicIndexBuffer::DynamicIndexBuffer(unsigned int nMaxIndices)
		: m_maxIndices(nMaxIndices), m_IBO(0), m_shouldUpdate(false)
	{
		m_indexBuffer = {};
	}

	DynamicIndexBuffer::~DynamicIndexBuffer()
	{
	}

	IndexBufferID DynamicIndexBuffer::RegisterWithVAO()
	{
		return m_IBO = RegisterIndexBuffer(nullptr, sizeof(IndexBuffer) * m_maxIndices, GL_DYNAMIC_DRAW);
	}

	int DynamicIndexBuffer::PushBack(EntityID key, IndexBuffer* indices, unsigned int numIndices, unsigned int numVertices)
	{
		if ((m_indexBuffer.size() + numIndices) >= m_maxIndices) {
			printf("Warning: Exceeded index buffer size limit!\n");
			return -1;
		}
		unsigned int currentVertexOffset = meshes.size() == 0 ? 0 : meshes.back().vertex_offset;

		DIB_element nMesh;
		nMesh.entity_backref = key;
		nMesh.buffer_offset = m_indexBuffer.size();
		nMesh.vertex_offset = currentVertexOffset + numVertices;
		meshes.push_back(nMesh);

		for (unsigned int i = 0; i < numIndices; i++) {
			m_indexBuffer.push_back(indices[i] + currentVertexOffset);
		}

		meshMap[key] = meshes.size() - 1;

		m_shouldUpdate = true;
		return 0;
	}

	int DynamicIndexBuffer::InsertAt(unsigned int meshIndex, EntityID key, const std::vector<IndexBuffer>& indices, unsigned int numVertices)
	{
		if ((m_indexBuffer.size() + indices.size()) >= m_maxIndices) {
			printf("Warning: Exceeded index buffer size limit!\n");
			return -1;
		}

		unsigned int currentVertexOffset = meshIndex == 0 ? 0 : meshes[meshIndex - 1].vertex_offset;

		DIB_element nMesh;
		nMesh.entity_backref = key;
		nMesh.buffer_offset = meshes[meshIndex].buffer_offset;
		nMesh.vertex_offset = currentVertexOffset + numVertices;

		m_indexBuffer.insert(m_indexBuffer.begin() + nMesh.buffer_offset, indices.begin(), indices.end());
		
		unsigned int index = 0;
		for (auto it = (m_indexBuffer.begin() + meshIndex); it != m_indexBuffer.end(); ++it) {
			
			if (index < indices.size()) {
				*it += currentVertexOffset;
				index++;
			}
			else {
				*it += numVertices;
			}
		}

		meshes.insert(meshes.begin() + meshIndex, nMesh);
		index = meshIndex + 1;
		for (auto it = (meshes.begin() + index); it != meshes.end(); ++it) {
			it->buffer_offset += indices.size();
			it->vertex_offset += numVertices;
			meshMap[it->entity_backref] = index++;
		}

		m_shouldUpdate = true;
		return 0;
	}

	void DynamicIndexBuffer::Remove(EntityID key)
	{
		unsigned int removeIndex = meshes[meshMap[key]].buffer_offset;
		unsigned int indexCount;
		unsigned int numVertices = meshes[meshMap[key]].vertex_offset;
		
		if (meshMap[key] == (meshes.size() - 1)) {
			indexCount = m_indexBuffer.size() - removeIndex;
		}
		else {
			indexCount = meshes[meshMap[key] + 1].buffer_offset - removeIndex;
		}

		if (meshMap[key] != 0) {
			numVertices -= meshes[meshMap[key] - 1].vertex_offset;
		}

		m_indexBuffer.erase(m_indexBuffer.begin() + removeIndex, m_indexBuffer.begin() + (removeIndex + indexCount));
		
		for (auto it = m_indexBuffer.begin() + removeIndex; it != m_indexBuffer.end(); ++it) {
			*it -= numVertices;
		}

		unsigned int index = meshMap[key];
		meshes.erase(meshes.begin() + index);
		for (auto it = (meshes.begin() + index); it != meshes.end(); ++it) {
			it->buffer_offset -= indexCount;
			it->vertex_offset -= numVertices;
			meshMap[it->entity_backref] = index++;
		}

		m_shouldUpdate = true;
	}
	void DynamicIndexBuffer::BindIBO()
	{
		glBindBuffer(GL_VERTEX_ARRAY, m_IBO);
	}

	bool DynamicIndexBuffer::glUpdateBuffer()
	{
		if (m_shouldUpdate) {
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(IndexBuffer) * m_indexBuffer.size(), &m_indexBuffer[0]);
			m_shouldUpdate = false;
			return true;
		}

		return false;
	}
}

