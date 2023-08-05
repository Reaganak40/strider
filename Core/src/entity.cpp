#include "entity.h"

EntityTemplate::EntityTemplate(EntityProfile nEntityProfile)
	: m_EntityProfile(nEntityProfile)
{
	m_mesh.eid = -1;
	m_mesh.vertexCount = 0;
	m_mesh.vertices = nullptr;
	m_mesh.indexCount = 0;
	m_mesh.indices = nullptr;
}
