#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

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

void create_shader_program(unsigned int &shaderProgram) {
        const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}";

    // Shaders
    // Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Shader Program
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int main() {
    // Create Window
    GLFWwindow* window;
    initialize_window(window);

    //Create Shader Program
    unsigned int shaderProgram;
    create_shader_program(shaderProgram);

    glUseProgram(shaderProgram);

    // Vertex Data and Vertex Buffer Object

    float vertices_head[] = {
         0.1f,  0.2f, 0.0f,  // top right
         0.1f, -0.2f, 0.0f,  // bottom right
        -0.1f, -0.1f, 0.0f,  // bottom left
        -0.1f,  0.1f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // For Element Buffer Objects (optimize repeating vertices position, for example creating a rectangle out of 2 triangles)
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    float vertices_body[] = {
     0.1f,  -0.1f, 0.0f,  // top right
     0.1f, -0.5f, 0.0f,  // bottom right
    -0.05f, -0.5f, 0.0f,  // bottom left
    -0.05f,  -0.1f, 0.0f   // top left 
    };

    float vertices_leg[] = {
    // Leg 1
     0.0f,  -0.5f, 0.0f,  // top right
     0.0f, -0.7f, 0.0f,  // bottom right
    -0.05f, -0.7f, 0.0f,  // bottom left
    -0.05f,  -0.5f, 0.0f,   // top left 
    // Leg 2
     0.1f,  -0.5f, 0.0f,  // top right
     0.1f, -0.7f, 0.0f,  // bottom right
    0.05f, -0.7f, 0.0f,  // bottom left
    0.05f,  -0.5f, 0.0f   // top left 
    };

    unsigned int leg_indices[] = {  // For Element Buffer Objects (optimize repeating vertices position, for example creating a rectangle out of 2 triangles)
    0, 1, 3,   // first triangle
    1, 2, 3,    // second triangle

    4, 5, 7,
    5, 6, 7
    };

    unsigned int VAO_head, VAO_body, VAO_leg;
    glGenVertexArrays(1, &VAO_head);
    glGenVertexArrays(1, &VAO_body);
    glGenVertexArrays(1, &VAO_leg);

    unsigned int VBO_head, VBO_body, VBO_leg;
    glGenBuffers(1, &VBO_head);
    glGenBuffers(1, &VBO_body);
    glGenBuffers(1, &VBO_leg);

    unsigned int EBO_head, EBO_body, EBO_leg;
    glGenBuffers(1, &EBO_head);
    glGenBuffers(1, &EBO_body);
    glGenBuffers(1, &EBO_leg);

    // Head
    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO_head);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO_head);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_head), vertices_head, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_head);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Body
    glBindVertexArray(VAO_body);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_body);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_body), vertices_body, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_body);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Leg
    glBindVertexArray(VAO_leg);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_leg);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_leg), vertices_leg, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_leg);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(leg_indices), leg_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) // Render Loop
    {
        // input
        processInput(window);

        // rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 4. draw the object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO_head);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO_body);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO_leg);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        // standard
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}