#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mathTypes.h"
#include "entity.h"

#include "procedure.h"


class Quad : public EntityTemplate {
private:
	EntityProfile m_Entity;
	Vertex vertices[4];
	IndexBuffer indices[6];
public:

	Quad(Strider::PositionVec3f nPosition, Strider::SizeVec3f nSize, Strider::ColorVec4f nColor = {0.0f, 0.0f, 0.0f, 1.0f});
	~Quad();
};


class UpdateQuad : public Procedure {
public:
	UpdateQuad();
	~UpdateQuad();

	void OnUpdate(float deltaTime) override;
};