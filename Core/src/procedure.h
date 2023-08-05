#pragma once

#include <memory>
#include "entityManager.h"

class Procedure {
public:
	Procedure();
	~Procedure();
	
	virtual void OnUpdate(float deltaTime) { printf("Warning: Calling empty procedure!\n"); };
	void inline AssignEMS(EntityManager* sceneEMS) { m_EMS = sceneEMS; }
protected:
	EntityManager* m_EMS;

	template<typename Component>
	std::vector<Component>& GetComponentPool() { return {}; }

	template<>
	std::vector<EntityProfile>& GetComponentPool<EntityProfile>() { return m_EMS->m_entities; }
	template<>
	std::vector<DimensionalComponent>& GetComponentPool<DimensionalComponent>() { return m_EMS->m_dimensionalities; }
	template<>
	std::vector<TransformComponent>& GetComponentPool<TransformComponent>() { return m_EMS->m_transforms; }
	template<>
	std::vector<BatchBitMap>& GetComponentPool<BatchBitMap>() { return m_EMS->m_batch_bit_map; }
	template<>
	std::vector<Vertex*>& GetComponentPool<Vertex*>() { return m_EMS->m_batches; }
};

class UpdateFinal : public Procedure {
private:
public:
	UpdateFinal();
	~UpdateFinal();

	void OnUpdate(float deltaTime) override;
};