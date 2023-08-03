#pragma once

#include "mathTypes.h"

namespace core {
	class EntityManagementSystem;
}

typedef int EntityID;

enum ComponentType {
	MESH = 0x1,
	TRANSFORM = 0x2,
	DIMENSIONALITY = 0x4,
};
typedef unsigned int EntityProfile;

inline EntityProfile DefineEntity(unsigned int nEntityProfile) { return nEntityProfile; }

inline bool HasComponent(EntityProfile profile, ComponentType ct) { return profile ^ ct; }

/*
		Defines where to find the VBO within the scene's batch buffers.
	*/
struct BatchBitMap {
	unsigned int batchIndex;
	unsigned int vertexOffset;
	unsigned int vertexCount;
};

/*
	Defines how an entity moves, rotates, and scales.
*/
struct TransformComponent {
	Strider::TranslateVec3f translate;
};


/*
	Defines the space that the entity takes up (location and size).
*/
struct DimensionalComponent {
	Strider::PositionVec3f position;
	Strider::SizeVec3f size;
};


class EntityTemplate {
private:
	EntityProfile m_EntityProfile;
public:
	EntityTemplate(EntityProfile nEntityProfile = 0) : m_EntityProfile(nEntityProfile) {}
};

class Entity {
private:
	EntityProfile profile;
	EntityID m_ID;
	
	core::EntityManagementSystem& owner;
public:
	Entity(core::EntityManagementSystem& rEMS) : owner(rEMS) {}
};