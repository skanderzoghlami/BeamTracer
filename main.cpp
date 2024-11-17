#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>

void ppm_image_writer(const int image_width, const int image_height, const char *filename)
{
    if (image_width <= 0 || image_height <= 0)
    {
        std::cerr << "Invalid image size" << std::endl;
        return;
    }
    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }
    fprintf(fp, "P3\n%d %d\n255\n", image_width, image_height);
    for (int j = image_height - 1; j >= 0; --j)
    {
        for (int i = 0; i < image_width; ++i)
        {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;
            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);
            fprintf(fp, "%d %d %d\n", ir, ig, ib);
        }
    }
    fclose(fp);
    std::cout << "Image written to " << filename << std::endl;
}

int main()
{

    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "ImGui Text Input", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    char inputText[256] = "250";
    char inputText2[256] = "250";

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Console Output Example");
        ImGui::InputText("Image Width", inputText, IM_ARRAYSIZE(inputText));
        ImGui::InputText("ImageHeight", inputText2, IM_ARRAYSIZE(inputText2));
        if (ImGui::Button("Submit"))
        {
            std::cout << "Submitted Text: " << inputText << std::endl;
            ppm_image_writer(std::stoi(inputText), std::stoi(inputText2), "output.ppm");
        }
        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
