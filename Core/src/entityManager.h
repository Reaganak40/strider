#pragma once

#include "core.h"
#include "request.h"
#include "mathTypes.h"

#include "entity.h"
#include <vector>

#include "framework.h"

class EntityManager {
private:
	SceneID m_SceneID;
	Framework* m_framework;

	std::vector<EntityProfile> m_entities;
	std::vector<DimensionalComponent> m_dimensionalities;
	std::vector<TransformComponent> m_transforms;
	std::vector<BatchBitMap> m_batch_bit_map;
	std::vector<Vertex*> m_batches;

public:
	EntityManager(SceneID owner = 0);
	~EntityManager();

	void SetSceneID(SceneID nOwner);
	void OnRequest(Request& nRequest);

	EntityID PushNewEntity(const LayerID& l_ID, EntityTemplate*& nEntity);

	inline unsigned int Count() { return (unsigned int)m_entities.size(); }


	friend class Procedure;
	friend class Scene;
private:
	void PushNewBatch(LayerID l_ID);

	/*
		Adds the mesh of the entity to the batch renderer,
		returns the vertex offset of the batch buffer it is in.
	*/
	unsigned int AddMesh(const LayerID& l_ID, const Mesh& mesh);
};
