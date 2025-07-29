#include <vector>

#include <GL/glut.h>  // Includes gl.h and glu.h

#include "triangle.h"

void init();
void display();
void reshape(int width, int height);

std::vector<Triangle *> triangles;

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Double buffer with depth
    glutInitWindowSize(800, 600);
    glutCreateWindow("Classic OpenGL (glut)");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

// Initialize OpenGL state
void init()
{
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f); // Background color
    glEnable(GL_DEPTH_TEST);              // Enable depth testing

    // Add a triangle
    RenderTriangle* tri = (RenderTriangle *)malloc(sizeof(RenderTriangle));
    tri->verticies[0][0] = -1;
    tri->verticies[0][1] = -1;
    tri->verticies[0][2] = 0;
    tri->verticies[1][0] = 1;
    tri->verticies[1][1] = -1;
    tri->verticies[1][2] = 0;
    tri->verticies[2][0] = 0;
    tri->verticies[2][1] = 1;
    tri->verticies[2][2] = 0;
    tri->red   = 255;
    tri->green = 127;
    tri->blue  = 0;
    triangles.push_back(toTriangle(tri));
}

// Display callback
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffer

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);  // Move back a bit

    for (Triangle* triangle : triangles)
    {
        RenderTriangle* tri = toRender(triangle);

        // Set color
        glColor3f((float)tri->red / (float)255, (float)tri->green / (float)255, (float)tri->blue / (float)255);

        // Draw triangle using immediate mode
        glBegin(GL_TRIANGLES);
            glVertex3f(tri->verticies[0][0], tri->verticies[0][1], tri->verticies[0][2]);
            glVertex3f(tri->verticies[1][0], tri->verticies[1][1], tri->verticies[1][2]);
            glVertex3f(tri->verticies[2][0], tri->verticies[2][1], tri->verticies[2][2]);
        glEnd();

        free(tri);
    }

    glutSwapBuffers(); // Swap buffers (double buffering)
}

// Reshape callback
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
}