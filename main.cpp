#include "stdafx.h"
#include "util.h"
#include "Cube.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

// extension loading library
#include "GL\glew.h"
// window handling - can handle keyboard as well
#include "GLFW\glfw3.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

const int windowWidth = 640;
const int windowHeight = 480;
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

    /////////////// rendering a 3x3 cube
    Cube cube;

    GLuint VertexArrayId;
    glGenVertexArrays(1, &VertexArrayId);
    glBindVertexArray(VertexArrayId);
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer); // generates 1 buffer and puts the result in vertexBuffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 162 * sizeof(GLfloat), cube.GetVertices(), GL_STATIC_DRAW);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 162 * sizeof(GLfloat), cube.GetFaceColors(), GL_STATIC_DRAW);


    // Projection matrix : 45° Field of View, 4 : 3 ratio, display range : 0.1 unit <-> 100 units
    // multiplying by this results in homogenous coordinates in the camera view
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

    // Camera matrix
    // multiplying by this gives coordinates relative to the camera
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 2, 4), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix 
    // multiplying by this gives world coordinates, (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

    GLuint programID = LoadShaders("SimpleVertexShader.vert", "SimpleFragmentShader.frag");

    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    do
    {
        // clears the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // calls the shader
        glUseProgram(programID);

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        // coordinate attribute
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0, // this matches the input to "layout" in the vertex shader 
            3, // size
            GL_FLOAT, // type 
            GL_FALSE, // normalized
            0, // stride 
            (void*)0); // array buffer offset

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(
            1, // attribute. No particular reason for 1, but must match the layout in the shader.
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0, // stride
            (void*)0 // array buffer offset
        );
        
        glDrawArrays(GL_TRIANGLES, 0, 3 * 54);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return 0;
}

