#pragma once

#include "GL\glew.h"


class Cube
{
private:

public:
    Cube();
    ~Cube();
    GLfloat * m_vertices;
    GLfloat * m_faceColors;
    GLfloat * GetVertices() { return m_vertices; };
    GLfloat * GetFaceColors() { return m_faceColors; }
};

