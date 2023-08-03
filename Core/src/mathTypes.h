#pragma once

namespace Strider {
	struct vec4f {
		float v0, v1, v2, v3;

	};

	struct PositionVec3f {
		float x, y, z;
	};

	struct SizeVec3f {
		float width, height, depth;
	};

	struct ColorVec4f {
		float red, green, blue, alpha;
	};

	struct TranslateVec3f {
		float dx, dy, dz;
	};
}