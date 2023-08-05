#include "quad.h"

Quad::Quad(Strider::PositionVec3f nPosition, Strider::SizeVec3f nSize, Strider::ColorVec4f nColor)
	: EntityTemplate(MESH)
{
	m_mesh.vertices = vertices;
	m_mesh.indices = indices;

	m_mesh.vertices[0].position[0] = nPosition.x;
	m_mesh.vertices[0].position[1] = nPosition.y;
	m_mesh.vertices[0].position[2] = nPosition.z;
									 
	m_mesh.vertices[1].position[0] = nPosition.x + nSize.width;
	m_mesh.vertices[1].position[1] = nPosition.y;
	m_mesh.vertices[1].position[2] = nPosition.z;
									 
	m_mesh.vertices[2].position[0] = nPosition.x + nSize.width;
	m_mesh.vertices[2].position[1] = nPosition.y + nSize.height;
	m_mesh.vertices[2].position[2] = nPosition.z;
									 
	m_mesh.vertices[3].position[0] = nPosition.x;
	m_mesh.vertices[3].position[1] = nPosition.y + nSize.height;
	m_mesh.vertices[3].position[2] = nPosition.z;

	for (int i = 0; i < 4; i++) {
		m_mesh.vertices[i].colorRGBA[0] = nColor.red;
		m_mesh.vertices[i].colorRGBA[1] = nColor.green;
		m_mesh.vertices[i].colorRGBA[2] = nColor.blue;
		m_mesh.vertices[i].colorRGBA[3] = nColor.alpha;

		m_mesh.vertices[i].texCoords[0] = 0.0f;
		m_mesh.vertices[i].texCoords[1] = 0.0f;
		m_mesh.vertices[i].texID = 0;
	}

	m_mesh.indices[0] = 0;
	m_mesh.indices[1] = 1;
	m_mesh.indices[2] = 2;
	m_mesh.indices[3] = 2;
	m_mesh.indices[4] = 3;
	m_mesh.indices[5] = 0;

	m_mesh.vertexCount = 4;
	m_mesh.indexCount = 6;

	this->AddComponent<DimensionalComponent>({ nPosition, nSize });
}

Quad::~Quad()
{
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
