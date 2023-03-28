#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <memory>

#include "../src/InnerPlanetsUI.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height); //resizing render size prototype
void processInput(GLFWwindow* window); //prototype function returns whether this key is currently being pressed

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //using version 3 of glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //using core profile

    //GLFW window creation-------------------------------------------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "5-Body Simulation", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glad loading OpenGL function pointers---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Imgui initialise
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //Fonts
    io.Fonts->AddFontFromFileTTF("src/assets/font/OpenSans-Bold.ttf", 18.0f);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("src/assets/font/OpenSans-Regular.ttf", 18.0f);

    //Inner planets
    std::shared_ptr<std::pair<std::string, bool>> Moon = std::make_shared<std::pair<std::string, bool>>("Moon", true);
    std::shared_ptr<std::pair<std::string, bool>> Earth = std::make_shared<std::pair<std::string, bool>>("Earth", true);
    std::shared_ptr<std::pair<std::string, bool>> Sun = std::make_shared<std::pair<std::string, bool>>("Sun", true);
    std::shared_ptr<std::pair<std::string, bool>> Mercury = std::make_shared<std::pair<std::string, bool>>("Mercury", true);
    std::shared_ptr<std::pair<std::string, bool>> Venus = std::make_shared<std::pair<std::string, bool>>("Venus", true);

    std::vector<std::shared_ptr<std::pair<std::string, bool>>> CelestialBodies(5);
    CelestialBodies = { Moon,Earth,Sun,Mercury,Venus };


    std::vector<double> defaultPositions(15);
    defaultPositions = { -27440663.8165208e3, 144729193.335639e3, 24808.236184314e3,
                        -27067884.6257174e3, 144587718.527863e3, -1969.59490492195e3,
                        0.0, 0.0, 0.0,
                        -5.912134174085139e10, -1.122619296617797e10, 4.544945202497724e9,
                        -7.094183693077585e10, -8.250232669178858e10, 2.956505086981911e9 };

    std::vector<double> initialPositions(15);
    initialPositions = defaultPositions;

    //Simulation
    std::vector<double> finalPositions;
    finalPositions = Simulate::SymplecticEulerSim(CelestialBodies, 5, 10000);


    while (!glfwWindowShouldClose(window)) //render loop
    {
        //Input
        processInput(window);

        //Specifiying background colour
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //Clean back buffer and assign new colour to it
        glClear(GL_COLOR_BUFFER_BIT);

        //Starting the new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        InnerPlanetsUI::RenderUI(CelestialBodies, initialPositions, finalPositions);



        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //escape key
        glfwSetWindowShouldClose(window, true);
}