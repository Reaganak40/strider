#include "entityManagementSystem.h"


EntityManagementSystem::EntityManagementSystem()
{
}

EntityManagementSystem::~EntityManagementSystem()
{
}

EntityID EntityManagementSystem::PushNewEntity(
	EntityProfile nEntity,
	DimensionalComponent locality,
	TransformComponent transform,
	BatchBitMap eBBM)
{
	m_entities.push_back(nEntity);
	m_dimensionalities.push_back(locality);
	m_transforms.push_back(transform);
	m_batch_bit_map.push_back(eBBM);

	return m_entities.size() - 1;
}


void EntityManagementSystem::PushNewBatch(core::Vertex* nBatchVBO)
{
	m_batches.push_back(nBatchVBO);
}
