#pragma once
#include "core.h"

#include <vector>
#include <unordered_map>

namespace core {

	typedef unsigned int IndexBuffer;
	typedef unsigned int IndexBufferID;
	typedef unsigned int IndexBufferCount;

	IndexBufferID RegisterIndexBuffer(IndexBuffer* ibo, size_t size, unsigned int glDrawHint = GL_STATIC_DRAW);

	inline void BindIndexBuffer(IndexBufferID ibo) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); }
	inline void UnbindIndexBuffer() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	class DynamicIndexBuffer {
	private:

		struct DIB_element {
			EntityID entity_backref;
			unsigned int buffer_offset;
			unsigned int vertex_offset;
		};

		std::vector<IndexBuffer> m_indexBuffer;

		IndexBufferID m_IBO;
		unsigned int m_maxIndices;

		std::vector<DIB_element> meshes; // represents 1 mesh of index buffer data
		std::unordered_map<EntityID, unsigned int> meshMap; // points to the index location of its mesh

		bool m_shouldUpdate;
	public:
		DynamicIndexBuffer(unsigned int nMaxIndices = DYNAMIC_BUFFER_DEFAULT_LIMIT);
		~DynamicIndexBuffer();

		IndexBufferID RegisterWithVAO();

		int PushBack(EntityID key, IndexBuffer* indices, unsigned int numIndices, unsigned int numVertices);
		int InsertAt(unsigned int meshIndex, EntityID key, const std::vector<IndexBuffer>& indices, unsigned int numVertices);
		void Remove(EntityID key);

		void BindIBO();
		IndexBufferCount glUpdateBuffer();

	};
}
