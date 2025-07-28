#include <GL/glut.h>  // Includes gl.h and glu.h

void init();
void display();
void reshape(int width, int height);

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
}

// Display callback
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffer

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);  // Move back a bit
    glColor3f(1.0f, 0.5f, 0.0f);      // Set color

    // Draw triangle using immediate mode
    glBegin(GL_TRIANGLES);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glVertex3f(0.0f,  1.0f, 0.0f);
    glEnd();

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