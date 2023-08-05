#pragma once
#include <memory>

enum RequestContext {
	NULL_REQUEST = 0,
	SCENE_LAYER_ADDED,
	ATTACH_GUI,
	DETACH_GUI,
};

struct Request {
	RequestContext context;
	void* params;
};
