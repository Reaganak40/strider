#include "quad.h"
#include "entityManagementSystem.h"

Quad::Quad(Strider::PositionVec3f nPosition, Strider::SizeVec3f nSize, Strider::ColorVec4f nColor)
	: EntityTemplate(MESH | TRANSFORM | DIMENSIONALITY), transform{0.0f, 0.0f, 0.0f}
{
	position = nPosition;
	size = nSize;
	color = nColor;

	vertices[0].position[0] = position.x;
	vertices[0].position[1] = position.y;
	vertices[0].position[2] = position.z;

	vertices[1].position[0] = position.x + size.width;
	vertices[1].position[1] = position.y;
	vertices[1].position[2] = position.z;

	vertices[2].position[0] = position.x + size.width;
	vertices[2].position[1] = position.y + size.height;
	vertices[2].position[2] = position.z;

	vertices[3].position[0] = position.x;
	vertices[3].position[1] = position.y + size.height;
	vertices[3].position[2] = position.z;

	for (int i = 0; i < 4; i++) {
		vertices[i].colorRGBA[0] = color.red;
		vertices[i].colorRGBA[1] = color.green;
		vertices[i].colorRGBA[2] = color.blue;
		vertices[i].colorRGBA[3] = color.alpha;

		vertices[i].texCoords[0] = 0.0f;
		vertices[i].texCoords[1] = 0.0f;
		vertices[i].texID = 0;
	}
}

Quad::~Quad()
{
}

void Quad::Move(float dx, float dy, float dz)
{
	for (int i = 0; i < 4; i++) {
		vertices[i].position[0] += dx;
		vertices[i].position[1] += dy;
		vertices[i].position[2] += dz;
	}
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

UpdateQuad::UpdateQuad()
{
}

UpdateQuad::~UpdateQuad()
{
}

void UpdateQuad::OnUpdate(float deltaTime)
{
	auto& dimensionalities = GetComponentPool<DimensionalComponent>();
	auto& transforms = GetComponentPool<TransformComponent>();

	for (unsigned int i = 0; i < m_EMS->Count(); i++) {
		if ((dimensionalities[i].position.x + dimensionalities[i].size.width) >= 1280.0f) {
			transforms[i].translate.dx = -(float)abs(transforms[i].translate.dx);
		} else if ((dimensionalities[i].position.x) <= 0.0f) {
			transforms[i].translate.dx = (float)abs(transforms[i].translate.dx);
		}

		if ((dimensionalities[i].position.y + dimensionalities[i].size.height) >= 720.0f) {
			transforms[i].translate.dy = -(float)abs(transforms[i].translate.dy);
		} else if ((dimensionalities[i].position.y) <= 0.0f) {
			transforms[i].translate.dy = (float)abs(transforms[i].translate.dy);
		}
	}
}
