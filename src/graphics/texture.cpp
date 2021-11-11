#include "texture.h"
#include "util/stb_image.h"
#include "../util/log.h"

namespace Graphics
{

std::map<std::string, unsigned int> Texture::textures;

Texture::Texture(const char* fileName)
{
    // Load the texture if it already exists
    if(textures.count(fileName)) {
        ID = textures[fileName];
        return;
    }

    // Load the texture
    unsigned char* data = stbi_load(fileName, &width, &height, &channels, 0);
    if(!data) { 
        Log::write("Failed to load texture!");
        return;
    }

    // Set up the texture with OpenGL
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Save the texture ID for later
    textures.insert({fileName, ID});

    // Cleanup
    stbi_image_free(data);
}

void Texture::use()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

}