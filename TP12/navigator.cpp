#include <cstdlib>
#include <algorithm>

// for mac osx
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
// only for windows
#ifdef _WIN32
#include <windows.h>
#endif
// for windows and linux
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define SPEED 1 // OpenGL units
#define ANG_SPEED (GLfloat) 0.5 // degrees

GLfloat CAM_POS_X = 0, CAM_POS_Y = 0, CAM_POS_Z = 5; // position of the camera
GLfloat CAM_ROT_X = 0, CAM_ROT_Y = 0; // rotation of the camera

#include <iostream>
using namespace std;

void display()
{
    // clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // set current matrix as GL_MODELVIEW
    glMatrixMode(GL_MODELVIEW);

    // draw scene
    {
        // add a copy of the curr. matrix to the stack
        glPushMatrix();
        {
            glPushMatrix();
            // translate by -3 on the z
            glTranslatef(.0f, .0f, -3.f);
            // set drawing color to red
            glColor3f(1.0f, 0.0f, 0.0f);
            // middle red teapot
            glutWireTeapot(1);
            // translate by 2 on the y
            glTranslatef(.0f, 2.f, .0f);
            // set drawing color to green
            glColor3f(.0f, 1.0f, .0f);
            // rotate 90 deg around x
            glRotatef(90.f, 1.0f, 0.0f, 0.0f);
            // top green teapot
            glutWireTeapot(1);
            // pop the current matrix
            glPopMatrix();
        }
        // translate -2 on y and -1 on z
        glTranslatef(.0f, -2.f, -1.f);
        // set drawing color to blue
        glColor3f(.0f, .0f, 1.f);
        // bottom blue teapot
        glutWireTeapot(1);
        // pop the current matrix
        glPopMatrix();
    }

    // flush drawing routines to the window
    glFlush();
}

void redraw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(CAM_POS_X, CAM_POS_Y, CAM_POS_Z, // viewpoint
              CAM_POS_X, CAM_POS_Y, -1, // look at
              .0, 1., .0); // up vector
    glRotatef(CAM_ROT_X, 1, 0, 0);
    glRotatef(CAM_ROT_Y, 0, 1, 0);
    glutPostRedisplay();
}

// Function called everytime a key is pressed
void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
    // echap
    case 27: exit(EXIT_SUCCESS);
    // forward Z
    case 'z':
    case 'Z':
        CAM_POS_Z -= SPEED;
        break;
    // backward Z
    case 's':
    case 'S':
        CAM_POS_Z += SPEED;
        break;
    // left X
    case 'q':
    case 'Q':
        CAM_POS_X -= SPEED;
        break;
    // right X
    case 'd':
    case 'D':
        CAM_POS_X += SPEED;
        break;
    // up Y
    case 'a':
    case 'A':
        CAM_POS_Y -= SPEED;
        break;
    // down Y
    case 'w':
    case 'W':
        CAM_POS_Y += SPEED;
        break;
    default: break;
    }
    redraw();
}

void special(int key, int, int)
{
    switch (key)
    {
    // rotate Y
    case GLUT_KEY_UP:
        CAM_ROT_X += ANG_SPEED;
        break;
    // rotate Y
    case GLUT_KEY_DOWN:
        CAM_ROT_X -= ANG_SPEED;
        break;
    // rotate X
    case GLUT_KEY_LEFT:
        CAM_ROT_Y += ANG_SPEED;
        break;
    // rotate X
    case GLUT_KEY_RIGHT:
        CAM_ROT_Y -= ANG_SPEED;
        break;
    default: break;
    }
    redraw();
}

void reshape(int width, int height)
{
    // define the viewport transformation
    glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
    // initialize GLUT, using any commandline parameters passed to the program
    glutInit(&argc, argv);

    // setup the size, position, and display mode for new windows
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB);

    // create and set up a window
    glutCreateWindow("Navigator");
    // Set up the callback functions
    // for display
    glutDisplayFunc(display);
    // for the keyboard
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    // for reshaping
    glutReshapeFunc(reshape);

    // define the projection transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000);

    // define the viewing transformation
    glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    gluLookAt(.0, .0, 5., .0, .0, -1., .0, 1., .0);

    // tell GLUT to wait for events
    glutMainLoop();
}
