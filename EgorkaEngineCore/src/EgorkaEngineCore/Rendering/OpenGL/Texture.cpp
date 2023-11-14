#include "Texture.hpp"

#include <algorithm>
#include <cmath>
#include <glad/glad.h>

namespace EgorkaEngine
{
    Texture2D::Texture2D(const unsigned char* _data, const unsigned int _width, const unsigned int _height)
        : width(_width)
        , height(_height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        const GLsizei mip_levels = static_cast<GLsizei>(std::log2(std::max(width, height))) + 1;
        glTextureStorage2D(id, mip_levels, GL_RGB8, width, height);
        glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, _data);
        glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateTextureMipmap(id);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &id);
    }

    Texture2D& Texture2D::operator=(Texture2D&& texture) noexcept
    {
        glDeleteTextures(1, &id);
        id = texture.id;
        width = texture.width;
        height = texture.height;
        texture.id = 0;
        return *this;
    }

    Texture2D::Texture2D(Texture2D&& texture) noexcept
    {
        id = texture.id;
        width = texture.width;
        height = texture.height;
        texture.id = 0;
    }

    void Texture2D::bind(const unsigned int unit) const
    {
        glBindTextureUnit(unit, id);
    }
}