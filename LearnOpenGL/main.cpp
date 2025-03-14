#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Shader.h";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) // Automatically Resize Window
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void initialize_window(GLFWwindow* &window) {
    // Setting Up GLFW

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // Setting Up GLAD

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    // OpenGL Configuration

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set window resize callback function
}

int main() {

    // Create Window
    GLFWwindow* window;
    initialize_window(window);

    //Create Shader Program
    Shader shaderProgram = Shader("vertexShader.glsl", "fragmentShader.glsl");

    shaderProgram.use();





    // Vertex Data and Vertex Buffer Object

    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    unsigned int indices[] = {  // For Element Buffer Objects (optimize repeating vertices position, for example creating a rectangle out of 2 triangles)
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

 

    // Head
    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set our vertex attributes pointers


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) // Render Loop
    {
        // input
        processInput(window);

        // rendering commands

        // Some Kind of Skybox
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
        //glUniform4f(vertexColorLocation, greenValue/2, greenValue, greenValue, 1.0f);

        glClearColor(greenValue/2, greenValue, greenValue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

  


        // 4. draw the object
        shaderProgram.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // standard
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

float map(float number, float minNumber, float maxNumber, float minTarget, float maxTarget) {
    if (minNumber == 0 && maxNumber == 0) { return 0; }
    float percentageToReduce;
    const float maxNumberReduce = maxNumber - minNumber;
    const float maxTargetReduce = maxTarget - minTarget;

    percentageToReduce = number / maxNumber;

    float newNumber = maxTarget - (maxTargetReduce * percentageToReduce);

    return newNumber;
}

std::vector<float> map_toGL(std::vector<std::vector<int>> coords, GLFWwindow* window) {
    std::vector<float> gl_coords;
    
    int max_width;
    int max_height;

    for (auto vector3 : coords) {
        for (int i = 0; i < 3; i++) {
            int maxVal;

            glfwGetWindowSize(window, &max_width, &max_height);

            switch (i) {
            case 0:
                maxVal = max_width;
                break;
            case 1:
                maxVal = max_height;
                break;
            case 2:
                maxVal = 0;
                break;
            default:
                std::cout << "joever\n";
                break;
            }

            float newVal = map((float)vector3[i], 0, (float)maxVal, -1.0f, 1.0f);
            gl_coords.push_back(newVal);
        }
    }

    return gl_coords;
}






class GameObject {
public:
    std::vector<int> vaos;
    int x;
    int y;

    GameObject(std::vector<int> a, int b, int c) {
        vaos = a;
        x = b;
        y = c;
    }

    void render() {

    }
};