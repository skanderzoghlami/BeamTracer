#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
class PPMImage
{
public:
    int width, height;
    std::vector<unsigned char> data;

    PPMImage(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file)
            throw std::runtime_error("Could not open file");

        std::string format;
        file >> format;
        if (format != "P3")
            throw std::runtime_error("Invalid PPM format (must be P3)");

        // Read width, height, and max color value
        file >> width >> height;
        int maxval;
        file >> maxval;
        if (maxval != 255)
            throw std::runtime_error("Only 8-bit PPM supported");

        // Read pixel data
        data.reserve(width * height * 3); // Preallocate memory
        int r, g, b;
        while (file >> r >> g >> b)
        {
            data.push_back(static_cast<unsigned char>(r));
            data.push_back(static_cast<unsigned char>(g));
            data.push_back(static_cast<unsigned char>(b));
        }

        // Ensure we read the correct number of pixels
        if (data.size() != static_cast<size_t>(width * height * 3))
        {
            throw std::runtime_error("Mismatch between image size and pixel data");
        }
    }
};

void displayImage(const PPMImage &img)
{
    if (!glfwInit())
        return;

    GLFWwindow *window = glfwCreateWindow(img.width, img.height, "PPM Viewer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    glOrtho(0, img.width, 0, img.height, -1, 1);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawPixels(img.width, img.height, GL_RGB, GL_UNSIGNED_BYTE, img.data.data());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
#endif