#pragma once

#include <renderer/vertexBuffer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Quad {
private:
	struct vec4_position {
		float x, y, z;
	};

	struct vec3_size {
		float width, height, depth;
	};

	vec4_position position;
	vec3_size size;

	core::Vertex* vertices;

public:
	EntityID eid;
	Quad(EntityID id, float position[3], float size[3]);
	~Quad();

	friend class Scene;
};
