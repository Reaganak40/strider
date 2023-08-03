#pragma once

#include <renderer/vertexBuffer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mathTypes.h"
#include "entity.h"

#include "procedure.h"


class Quad : public EntityTemplate {
private:
	EntityProfile m_Entity;

	core::Vertex vertices[4];

public:
	Strider::PositionVec3f position;
	Strider::SizeVec3f size;
	Strider::ColorVec4f color;

	Strider::TranslateVec3f transform;

	Quad(Strider::PositionVec3f nPosition, Strider::SizeVec3f nSize, Strider::ColorVec4f nColor = {0.0f, 0.0f, 0.0f, 1.0f});
	~Quad();

	void Move(float dx = 0, float dy = 0, float dz = 0);

	friend class Scene;
};


class UpdateQuad : public Procedure {
public:
	UpdateQuad();
	~UpdateQuad();

	void OnUpdate(float deltaTime) override;
};