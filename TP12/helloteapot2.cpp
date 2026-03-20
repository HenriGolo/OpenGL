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

bool isWire = true;

// function called everytime the windows is refreshed
void display()
{
    // clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // draw scene
    if (isWire) glutWireTeapot(.5);
    else glutSolidTeapot(.5);

    // flush drawing routines to the window
    glFlush();
}

// Function called everytime a key is pressed
void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
    case 'w': isWire = !isWire;
        break;
    // the 'esc' key
    case 27:
    // the 'q' key
    case 'q': exit(EXIT_SUCCESS);
    default: break;
    }
    glutPostRedisplay();
}

// Function called every time the main window is resized
void reshape(int width, int height)
{
    // define the viewport transformation;
    int length = width < height ? width : height;
    glViewport((width - length) / 2, (height - length) / 2, length, length);
}

// Main routine
int main(int argc, char* argv[])
{
    // initialize GLUT, using any commandline parameters passed to the
    //   program
    glutInit(&argc, argv);

    // setup the size, position, and display mode for new windows
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB);

    // create and set up a window
    glutCreateWindow("Hello, teapot!");

    // Set up the callback functions:
    // for display
    glutDisplayFunc(display);
    // for the keyboard
    glutKeyboardFunc(keyboard);
    // for reshaping
    glutReshapeFunc(reshape);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 0, 15);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(.0, .0, -1.3, // viewpoint
              0.0, 0.0, 0.0, // look at
              1.0, 1.0, .0); // up vector

    // tell GLUT to wait for events
    glutMainLoop();
}
