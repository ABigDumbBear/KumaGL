#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace Kuma3D {

/******************************************************************************/
Texture::Texture()
{
  glGenTextures(1, &mID);
}

/******************************************************************************/
Texture::~Texture()
{
  glDeleteTextures(1, &mID);
}

/******************************************************************************/
void Texture::LoadFromFile(const std::string& aFile, GLint aLoadFormat)
{
  int channels;
  auto data = stbi_load(aFile.c_str(),
                        &mWidth,
                        &mHeight,
                        &channels,
                        0);

  glBindTexture(GL_TEXTURE_2D, mID);

  // Copy the image data into the currently bound texture.
  glTexImage2D(GL_TEXTURE_2D,
               0,
               aLoadFormat,
               mWidth,
               mHeight,
               0,
               aLoadFormat,
               GL_UNSIGNED_BYTE,
               data);

  // Create a mipmap for this texture; used on small/far away objects.
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

} // namespace Kuma3D