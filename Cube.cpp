#include "stdafx.h"
#include "Cube.h"

#include <cstdlib>

static const GLfloat s_colors[6][3] = {
    { 1.0f, 0.0f, 0.0f }, // red
    { 0.0f, 1.0f, 0.0f }, // green
    { 0.0f, 0.0f, 1.0f }, // blue
    { 1.0f, 1.0f, 1.0f }, // white
    { 0.0f, 1.0f, 1.0f }, // yellow
    { 1.0f, 0.66f, 0.0f } // orange
};

#define EPS 0.018f
#define ELEMENTS_PER_VERTEX 3
#define VERTICES_PER_TRIANGLE 3
#define TRIANGLES_PER_SQUARE 2
#define SQUARES_PER_FACE 9
#define TRIANGLES_PER_FACE (SQUARES_PER_FACE * TRIANGLES_PER_SQUARE)
#define VERTICES_PER_FACE (TRIANGLES_PER_FACE * VERTICES_PER_TRIANGLE)
#define ELEMENTS_PER_FACE (VERTICES_PER_FACE * ELEMENTS_PER_VERTEX)

Cube::Cube()
{
    m_vertices = new GLfloat[6 * ELEMENTS_PER_FACE];  
    m_faceColors = new GLfloat[6 * ELEMENTS_PER_FACE];
    
    const GLfloat interval = 2.0f / 3.0f;
    int ind = 0;

    { // face 0 - normal (1, 0, 0), x constant
        GLfloat tl[] = { 1.0f, -1.0f,            -1.0f };
        GLfloat br[] = { 1.0f, tl[1] + interval, tl[2] + interval };

        int face = 0;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                // coordinates of the minisquare, going CW from top left
                // minus EPS to render a space between each minisquare
                GLfloat p1[] = { tl[0], tl[1] + (interval * r) + EPS,       tl[2] + (interval * c) + EPS };
                GLfloat p2[] = { tl[0], tl[1] + (interval * r) + EPS,       tl[2] + (interval * (c + 1)) - EPS };
                GLfloat p3[] = { tl[0], tl[1] + (interval * (r + 1)) - EPS, tl[2] + (interval * (c + 1)) - EPS };
                GLfloat p4[] = { tl[0], tl[1] + (interval * (r + 1)) - EPS, tl[2] + (interval * c) + EPS };

                // triangle 1
                memcpy(&m_vertices[ind],      p1, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 3],  p2, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 6],  p3, 3 * sizeof(GLfloat));
                // triangle 2
                memcpy(&m_vertices[ind + 9],  p3, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 12], p4, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 15], p1, 3 * sizeof(GLfloat));

                memcpy(&m_faceColors[ind],      s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 3],  s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 6],  s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 9],  s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 12], s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 15], s_colors[face], 3 * sizeof(GLfloat));
                ind += 18;
            }
        }
    }
    
    { // face 1 - normal (0, 1, 0), y constant
        GLfloat tl[] = { -1.0f,            1.0f, -1.0f };
        GLfloat br[] = { tl[0] + interval, 1.0f, tl[2] + interval };

        int face = 1;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                // coordinates of the minisquare, going CW from top left
                // minus EPS to render a space between each minisquare
                GLfloat p1[] = { tl[0] + (interval * r) + EPS,       tl[1], tl[2] + (interval * c) + EPS };
                GLfloat p2[] = { tl[0] + (interval * r) + EPS,       tl[1], tl[2] + (interval * (c + 1)) - EPS };
                GLfloat p3[] = { tl[0] + (interval * (r + 1)) - EPS, tl[1], tl[2] + (interval * (c + 1)) - EPS };
                GLfloat p4[] = { tl[0] + (interval * (r + 1)) - EPS, tl[1], tl[2] + (interval * c) + EPS };

                // triangle 1
                memcpy(&m_vertices[ind],      p1, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 3],  p2, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 6],  p3, 3 * sizeof(GLfloat));
                // triangle 2
                memcpy(&m_vertices[ind + 9],  p3, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 12], p4, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 15], p1, 3 * sizeof(GLfloat));

                memcpy(&m_faceColors[ind],      s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 3],  s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 6],  s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 9],  s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 12], s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 15], s_colors[face], 3 * sizeof(GLfloat));
                ind += 18;
            }
        }
    }

    { // face 5 - normal (0, 0, 1), z constant
        GLfloat tl[] = { -1.0f,           -1.0f ,             1.0f };
        GLfloat br[] = { tl[0] + interval, tl[2] + interval,  1.0f };

        int face = 5;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                // coordinates of the minisquare, going CW from top left
                // minus EPS to render a space between each minisquare
                GLfloat p1[] = { tl[0] + (interval * r) + EPS,       tl[1] + (interval * c) + EPS      , tl[2] };
                GLfloat p2[] = { tl[0] + (interval * r) + EPS,       tl[1] + (interval * (c + 1)) - EPS, tl[2] };
                GLfloat p3[] = { tl[0] + (interval * (r + 1)) - EPS, tl[1] + (interval * (c + 1)) - EPS, tl[2] };
                GLfloat p4[] = { tl[0] + (interval * (r + 1)) - EPS, tl[1] + (interval * c) + EPS      , tl[2] };

                // triangle 1
                memcpy(&m_vertices[ind], p1, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 3], p2, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 6], p3, 3 * sizeof(GLfloat));
                // triangle 2
                memcpy(&m_vertices[ind + 9], p3, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 12], p4, 3 * sizeof(GLfloat));
                memcpy(&m_vertices[ind + 15], p1, 3 * sizeof(GLfloat));

                memcpy(&m_faceColors[ind], s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 3], s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 6], s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 9], s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 12], s_colors[face], 3 * sizeof(GLfloat));
                memcpy(&m_faceColors[ind + 15], s_colors[face], 3 * sizeof(GLfloat));
                ind += 18;
            }
        }
    }
}


Cube::~Cube()
{
    delete[] m_vertices;
    delete[] m_faceColors;
}
