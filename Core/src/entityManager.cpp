#include "entityManager.h"


EntityManager::EntityManager(SceneID owner)
	: m_framework(Framework::GetInstance()), m_SceneID(owner)
{

}

EntityManager::~EntityManager()
{
}

void EntityManager::SetSceneID(SceneID nOwner)
{
	m_SceneID = nOwner;
}

void EntityManager::OnRequest(Request& nRequest)
{
	switch (nRequest.context) {
	case SCENE_LAYER_ADDED:
		break;
	default:
		printf("Warning: [EntityManager] Could not interpret request: %d\n", nRequest.context);
	}
}

EntityID EntityManager::PushNewEntity(const LayerID& l_ID, EntityTemplate*& nEntity)
{
	nEntity->SetEntityID(Count());
	unsigned int vertexOffset = AddMesh(l_ID, nEntity->GetMesh());
	m_batch_bit_map.push_back({ l_ID, vertexOffset, nEntity->GetMesh().vertexCount });


	m_entities.push_back(nEntity->GetEntityProfile());
	
	
	const void* component = nEntity->GetComponent(TRANSFORM);
	if (component == nullptr) {
		m_transforms.push_back({});
	}
	else {
		m_transforms.push_back(*((TransformComponent*)component));
	}

	component = nEntity->GetComponent(DIMENSIONALITY);
	if (component == nullptr) {
		m_transforms.push_back({});
	}
	else {
		m_dimensionalities.push_back(*((DimensionalComponent*)component));
		
		printf("%f, %f, %f\n",
			m_dimensionalities.back().position.x,
			m_dimensionalities.back().position.y,
			m_dimensionalities.back().position.z
			);
	}
	
	return m_entities.size() - 1;
}


void EntityManager::PushNewBatch(LayerID l_ID)
{
	m_batches.push_back(m_framework->Platform()->GetMeshBatchLocation(m_SceneID, l_ID));
}


unsigned int EntityManager::AddMesh(const LayerID& l_ID, const Mesh& mesh)
{
	return m_framework->Platform()->AddMesh(m_SceneID, l_ID, mesh);
}
