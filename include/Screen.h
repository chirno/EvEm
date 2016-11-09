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
        ((std::string)"#version 300 es\n") +
        "in vec3 data;\n" +
        "flat out int color;\n" +
        "void main() {\n" +
        "   color = int(data[2]);\n" +
        "   gl_Position = vec4(data[0], data[1], 0.0, 1.0);\n" +
        "}\n";

        std::string fragmentSource =
        ((std::string)"#version 300 es\n") +
        "precision highp float;" +
        "flat in int color;\n" +
        "out vec4 colorOut;\n" +
        "void main() {\n" +
        "   int nc = color;\n" +
        "   switch (nc) {\n" +
        "       case 1:\n" +
        "           nc = 96; break;\n" +
        "       case 2:\n" +
        "           nc = 192; break;\n" +
        "       case 3:\n" +
        "           nc = 256; break;\n" +
        "   }\n" +
        "   colorOut = vec4(nc, nc, nc, 1.0);\n" +
        "}\n";
};

#endif // SCREEN_H
