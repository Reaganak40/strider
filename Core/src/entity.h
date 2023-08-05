#pragma once

#include <unordered_map>
#include <memory>
#include "mathTypes.h"
#include "component.h"
#include "mesh.h"

namespace core {
	class EntityManagementSystem;
}

typedef int EntityID;

typedef unsigned int EntityProfile;

inline EntityProfile DefineEntity(unsigned int nEntityProfile) { return nEntityProfile; }

inline bool HasComponent(EntityProfile profile, ComponentType ct) { return profile ^ ct; }


class EntityTemplate {
protected:
	Mesh m_mesh;
	std::unordered_map<ComponentType, std::shared_ptr<void>> m_components;
private:
	EntityProfile m_EntityProfile;
public:
	EntityTemplate(EntityProfile nEntityProfile = 0);
	const EntityProfile& GetEntityProfile() { return m_EntityProfile; }
	void SetEntityID(EntityID id) { m_mesh.eid = id; }
	const Mesh& GetMesh() { return m_mesh; }

	template <typename ComponentType>
	void AddComponent(ComponentType component) {}

	template<>
	void AddComponent<TransformComponent>(TransformComponent component) {
		m_EntityProfile |= TRANSFORM;
		m_components[TRANSFORM] = std::make_shared<TransformComponent>(component);
	}
	template<>
	void AddComponent<DimensionalComponent>(DimensionalComponent component) {
		m_EntityProfile |= DIMENSIONALITY;
		m_components[DIMENSIONALITY] = std::make_shared<DimensionalComponent>(component);
	}

	const void* GetComponent(ComponentType type) {
		if (m_components.find(type) == m_components.end()) {
			return nullptr;
		}
		return m_components[type].get();
	}
};