#include "stdafx.h"
#include "util.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

GLuint LoadShaders(const char * vertex_filepath, const char * fragment_filepath)
{
    // create the shaders
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // read the vertex shader code from input file
    string vertexShaderCode;
    ifstream vertexShaderStream(vertex_filepath, ios::in);
    if (vertexShaderStream.is_open()) {
        stringstream ss;
        ss << vertexShaderStream.rdbuf();
        vertexShaderCode = ss.str();
        vertexShaderStream.close();
    } else {
        printf("Can't open %s.", vertex_filepath);
        getchar();
        return 0;
    }

    // read the fragment shader code
    string fragmentShaderCode;
    ifstream fragmentShaderStream(fragment_filepath, ios::in);
    if (fragmentShaderStream.is_open()) {
        stringstream ss;
        ss << fragmentShaderStream.rdbuf();
        fragmentShaderCode = ss.str();
        fragmentShaderStream.close();
    } else {
        printf("Can't open %s.", fragment_filepath);
        getchar();
        return 0;
    }

    // compile vertex shader
    printf("Compiling shader : %s\n", vertex_filepath);
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    GLint res = GL_FALSE;
    int infoLogLen = 0;

    // Check Vertex Shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &res);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 0) {
        vector<char> errorMsg(infoLogLen + 1);
        glGetShaderInfoLog(vertexShaderID, infoLogLen, NULL, &errorMsg[0]);
        printf("%s\n", &errorMsg[0]);
    }

    // compile fragment Shader
    printf("Compiling shader : %s\n", fragment_filepath);
    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &res);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 0) {
        vector<char> errorMsg(infoLogLen + 1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLen, NULL, &errorMsg[0]);
        printf("%s\n", &errorMsg[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &res);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 0) {
        std::vector<char> errorMsg(infoLogLen + 1);
        glGetProgramInfoLog(programID, infoLogLen, NULL, &errorMsg[0]);
        printf("%s\n", &errorMsg[0]);
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}