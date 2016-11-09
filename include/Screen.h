#ifndef SCREEN_H
#define SCREEN_H

#include "Definitions.h"
#include <string>

class Screen
{
    private:
        int width, height;
        uint8_t* pixels;
        unsigned int buffer = 0, program;
    public:
        Screen(int width, int height);
        virtual ~Screen();

        void Render();
        void Reset();
        void SetPixels(int offset, uint8_t value);
    private:
        std::string vertexSource =
        ((std::string)"#version 330\n") +
        "in vec3 data\n" +
        "out uint color\n" +
        "void main() {\n" +
        "   color = data[2];\n" +
        "   gl_Position = vec4(data[0], data[1], 0.0, 1.0);\n" +
        "}\n";

        std::string fragmentSource =
        ((std::string)"#version 330\n") +
        "in uint color\n" +
        "out vec4 colorOut\n" +
        "void main() {\n" +
        "   switch (color) {\n" +
        "       case 1:\n" +
        "           color = 96; break;\n" +
        "       case 2:\n" +
        "           color = 192; break;\n" +
        "       case 3:\n" +
        "           color = 256; break;\n" +
        "   }\n" +
        "   colorOut = vec4(color, color, color, 1.0);\n" +
        "}\n";
};

#endif // SCREEN_H
