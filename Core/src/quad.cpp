#include "quad.h"

Quad::Quad(strider::PositionVec3f nPosition, strider::SizeVec3f nSize, strider::ColorVec4f nColor)
	: m_ID(0)
{
	vertices = new core::Vertex[4];

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
	if (!m_ID) {
		// this quad was never loaded to a scene.
		delete[] vertices;
	}
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
