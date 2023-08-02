#pragma once

#include <renderer/vertexBuffer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mathTypes.h"

class Quad {
private:
	EntityID m_ID;


	core::Vertex* vertices;

public:
	strider::PositionVec3f position;
	strider::SizeVec3f size;
	strider::ColorVec4f color;

	Quad(strider::PositionVec3f nPosition, strider::SizeVec3f nSize, strider::ColorVec4f nColor = {0.0f, 0.0f, 0.0f, 1.0f});
	~Quad();

	void Move(float dx = 0, float dy = 0, float dz = 0);

	friend class Scene;
};
