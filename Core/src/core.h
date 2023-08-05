#pragma once

enum FrameworkType {
	USING_NONE = 0,
	USING_GL = 1,
};

#ifdef SR_PLATFORM_GL
	#define SR_PLATFORM_FRAMEWORK 1
#else
	#define SR_PLATFORM_FRAMEWORK 0
#endif // SR_PLATFORM_GL

#define DYNAMIC_BUFFER_DEFAULT_LIMIT 65536

typedef unsigned int SceneID;
typedef unsigned int LayerID;

