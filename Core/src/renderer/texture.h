#pragma once

#include <string>

namespace core {

	typedef unsigned int TextureID;

	/*
		Wrapping containing all data associated with a texture.
	*/
	struct Texture {
		TextureID id;
		unsigned char* imageBuffer;
		int imageWidth;
		int imageHeight;
		int bitsPerPixel;
	};

	Texture LoadTexture(std::string filepath);

	void DeleteTexture(Texture* texture);

	void BindTexture(TextureID textureID, unsigned int slot = 0);
	void inline UnbindTexture(TextureID texture) { glBindTexture(GL_TEXTURE_2D, 0); }

}