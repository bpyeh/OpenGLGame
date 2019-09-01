// vertex shader
#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

out vec3 fragmentColor;

void main() {
    //gl_Position.xyz = vertexPosition_modelspace;
    //gl_Position.w = 1.0;
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    // forward to fragment shader
    fragmentColor = vertexColor;
}