#include <stb/stb_image.h>

#include "core.h"
#include "error.h"
#include "texture.h"

Texture LoadTexture(std::string filepath)
{
	Texture nTexture;
	stbi_set_flip_vertically_on_load(1);

	nTexture.imageBuffer = stbi_load(filepath.c_str(),
		&nTexture.imageWidth,
		&nTexture.imageHeight,
		&nTexture.bitsPerPixel, 4);
	
	glGenTextures(1, &nTexture.id);
	glBindTexture(GL_TEXTURE_2D, nTexture.id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
		nTexture.imageWidth, nTexture.imageHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, nTexture.imageBuffer));

	glBindTexture(GL_TEXTURE_2D, 0);

	return nTexture;
}

void BindTexture(TextureID textureID, unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void DeleteTexture(Texture* texture)
{
	glDeleteTextures(1, &(texture->id));
	
	if (texture->imageBuffer != nullptr) {
		delete[] texture->imageBuffer;
		texture->imageBuffer = nullptr;
	}
}

