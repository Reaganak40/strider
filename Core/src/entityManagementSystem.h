#pragma once

#include <renderer/renderer.h>
#include "mathTypes.h"

#include "entity.h"

class EntityManagementSystem {
private:

	std::vector<EntityProfile> m_entities;
	std::vector<DimensionalComponent> m_dimensionalities;
	std::vector<TransformComponent> m_transforms;
	std::vector<BatchBitMap> m_batch_bit_map;

	std::vector<core::Vertex*> m_batches;
public:
	EntityManagementSystem();
	~EntityManagementSystem();

	EntityID PushNewEntity(
		EntityProfile nEntity,
		DimensionalComponent dimensionality = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
		TransformComponent transform = { 0.0f, 0.0f, 0.0f },
		BatchBitMap eBBM = { 0, 0, 0 }
		);

	inline unsigned int Count() { return m_entities.size(); }


	friend class Procedure;
	friend class Scene;
private:
	void PushNewBatch(core::Vertex* nBatchVBO);

	
};
