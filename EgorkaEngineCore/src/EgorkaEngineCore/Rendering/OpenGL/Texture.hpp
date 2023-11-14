#pragma once

namespace EgorkaEngine {

    class Texture2D {

    private:
        unsigned int id = 0;
        unsigned int width = 0;
        unsigned int height = 0;

    public:
        Texture2D(const unsigned char* data, const unsigned int width, const unsigned int height);
        ~Texture2D();

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;
        Texture2D& operator=(Texture2D&& texture) noexcept;
        Texture2D(Texture2D&& texture) noexcept;

        void bind(const unsigned int unit) const;
    };

}