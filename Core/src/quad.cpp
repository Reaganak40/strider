#include "quad.h"

Quad::Quad(EntityID id, float nPosition[3], float nSize[3])
	: eid(id)
{
		
	vertices = new core::Vertex[4];

	position.x = nPosition[0];
	position.y = nPosition[1];
	position.z = nPosition[2];

	size.width  = nSize[0];
	size.height = nSize[1];
	size.depth  = nSize[2];

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
		vertices[i].colorRGBA[0] = 1.0f;
		vertices[i].colorRGBA[1] = 1.0f;
		vertices[i].colorRGBA[2] = 1.0f;
		vertices[i].colorRGBA[3] = 1.0f;

		vertices[i].texCoords[0] = 0.0f;
		vertices[i].texCoords[1] = 0.0f;
		vertices[i].texID = 0;
	}

}

Quad::~Quad()
{
	delete[] vertices;
}
