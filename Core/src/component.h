#pragma once

#include <unordered_map>
#include "mathTypes.h"


typedef int EntityID;

enum ComponentType {
	MESH = 0x1,
	TRANSFORM = 0x2,
	DIMENSIONALITY = 0x4,
};

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