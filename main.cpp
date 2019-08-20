#include "stdafx.h"

#include <iostream>

// extension loading library
#include "GL\glew.h"

// window handling - can handle keyboard as well
#include "GLFW\glfw3.h"

#include "util.h"

using namespace std;

int main()
{
    glewExperimental = true;
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4 = 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // selects opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    // OpenGL regularly deprecates and removes outdated features. 
    // In a core profile these features aren't available anymore. In a compatibilty profile they are still there.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    // Open a window and create the OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Game", NULL, NULL);
    if (NULL == window)
    {
        cout << "Failed to open GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    // From the doc: If sticky keys are enabled, a key press will ensure that glfwGetKey 
    // returns GLFW_PRESS the next time it is called even if the key had been released 
    // before the call. This is useful when you are only interested in whether keys have 
    // been pressed but not when or in which order
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    /////////////// rendering a triangle
    GLuint VertexArrayId;
    glGenVertexArrays(1, &VertexArrayId);
    glBindVertexArray(VertexArrayId);
    // the vertices of our triangle
    GLfloat vertex_buffer_data[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer); // generates 1 buffer and puts the result in vertexBuffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    GLuint programID = LoadShaders("SimpleVertexShader.vert", "SimpleFragmentShader.frag");

    do
    {
        // clears the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // calls the shader
        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0, // this matches the input to "layout" in the vertex shader 
            3, // size
            GL_FLOAT, // type 
            GL_FALSE, // normalized
            0, // stride 
            (void*)0); // array buffer offset
        glDrawArrays(GL_TRIANGLES, 0, (sizeof(vertex_buffer_data)/sizeof(vertex_buffer_data[0])) / 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return 0;
}

