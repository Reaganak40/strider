#include <sstream>

#include "error.h"
#include "core.h"

void glClearError() {
	int count = 0;
	while (glGetError() != GL_NO_ERROR) {
		count++;
	}
	if (count > 0) {
		std::cout << "Warning: found (" << count << ") unbounded errors\n";
	}
}

bool glLogError(const char* function, const char* filename, int line) {

	bool noErrors = true;
	while (GLenum error = glGetError()) {
		std::cout << "[Error::Opengl-Core]\n" <<
			"\tfunction: " << function << std::endl <<
			"\tfilepath: " << filename << std::endl <<
			"\tline: " << line << std::endl <<
			"\terror: (" << glErrorContext(error) << ")\n";
		noErrors = false;
	}

	return noErrors;
}

std::string glErrorContext(unsigned int error) {

	switch (error) {

	case 0x0500:
		return "GL_INVALID_ENUM";
	default:
		std::stringstream ss;
		ss << "0x" << std::hex << error;
		return ss.str();
	}

	return "FAIL";
}