#include "procedure.h"

Procedure::Procedure()
	: m_EMS(nullptr)
{
}

Procedure::~Procedure()
{
}

UpdateFinal::UpdateFinal()
{
}

UpdateFinal::~UpdateFinal()
{
}

void UpdateFinal::OnUpdate(float deltaTime)
{
	auto& entityProfiles = GetComponentPool<EntityProfile>();
	auto& dimensionalities = GetComponentPool<DimensionalComponent>();
	auto& batchLocations = GetComponentPool<BatchBitMap>();
	auto& batches = GetComponentPool<core::Vertex*>();
	auto& transforms = GetComponentPool<TransformComponent>();

	for (int i = 0; i < m_EMS->Count(); i++) {

		if (HasComponent(entityProfiles[i], TRANSFORM)) {

			if (HasComponent(entityProfiles[i], DIMENSIONALITY)) {
				dimensionalities[i].position.x += (transforms[i].translate.dx * deltaTime);
				dimensionalities[i].position.y += (transforms[i].translate.dy * deltaTime);
				dimensionalities[i].position.z += (transforms[i].translate.dz * deltaTime);
			}

			if (HasComponent(entityProfiles[i], MESH)) {

				for (unsigned int currentVertex = 0; currentVertex < batchLocations[i].vertexCount; currentVertex++) {
					batches[batchLocations[i].batchIndex][batchLocations[i].vertexOffset + currentVertex].position[0] += (transforms[i].translate.dx * deltaTime);
					batches[batchLocations[i].batchIndex][batchLocations[i].vertexOffset + currentVertex].position[1] += (transforms[i].translate.dy * deltaTime);
					batches[batchLocations[i].batchIndex][batchLocations[i].vertexOffset + currentVertex].position[2] += (transforms[i].translate.dz * deltaTime);
				}
			}
		}
	}
}
