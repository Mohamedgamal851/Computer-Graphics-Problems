#include <GL/glut.h>
#include <math.h>
float bicyclePosX = 0.0f;
float wheelRotationAngle = 0.0f;
float cameraAngle = 0.0f;
float cameraHeight = 0.0f;
bool animationEnabled = false;
float doorAngle = 0.0f;
float windowAngle = 0.0f;
int Alltheta = 0;
void init() {
    glClearColor(0.0, 0.5, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //to handle how the scene is viewed
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void drawBuilding() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    //The Ground of the building
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(-4.0, -0.6, -4.0);
    glVertex3f(4.0, -0.6, -4.0);
    glVertex3f(4.0, -0.6, 4.0);
    glVertex3f(-4.0, -0.6, 4.0);
    glEnd();
    ///////////
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    //front wall of first floor
    glVertex3f(-0.3, -0.6, 0.7);
    glVertex3f(0.3, -0.6, 0.7);
    glVertex3f(0.3, 0.0, 0.7);
    glVertex3f(-0.3, 0.0, 0.7);
    //back wall of first floor
    glVertex3f(-0.3, -0.6, 0.2);
    glVertex3f(0.3, -0.6, 0.2);
    glVertex3f(0.3, 0.0, 0.2);
    glVertex3f(-0.3, 0.0, 0.2);
    //left wall of first floor
    glVertex3f(-0.3, -0.6, 0.2);
    glVertex3f(-0.3, 0.0, 0.2);
    glVertex3f(-0.3, 0.0, 0.7);
    glVertex3f(-0.3, -0.6, 0.7);
    //right wall of first floor
    glVertex3f(0.3, -0.6, 0.2);
    glVertex3f(0.3, 0.0, 0.2);
    glVertex3f(0.3, 0.0, 0.7);
    glVertex3f(0.3, -0.6, 0.7);
    ////////////////////////////
    // Front wall of second floor
    glVertex3f(-0.3, 0.0, 0.7);
    glVertex3f(0.3, 0.0, 0.7);
    glVertex3f(0.3, 0.4, 0.7);
    glVertex3f(-0.3, 0.4, 0.7);
    // Back wall of second floor
    glVertex3f(-0.3, 0.0, 0.2);
    glVertex3f(0.3, 0.0, 0.2);
    glVertex3f(0.3, 0.4, 0.2);
    glVertex3f(-0.3, 0.4, 0.2);
    // Left wall of second floor
    glVertex3f(-0.3, 0.0, 0.2);
    glVertex3f(-0.3, 0.4, 0.2);
    glVertex3f(-0.3, 0.4, 0.7);
    glVertex3f(-0.3, 0.0, 0.7);
    // Right wall of second floor
    glVertex3f(0.3, 0.0, 0.2);
    glVertex3f(0.3, 0.4, 0.2);
    glVertex3f(0.3, 0.4, 0.7);
    glVertex3f(0.3, 0.0, 0.7);
    ////////////////////////////////
    // Back wall of roof
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0); // green color
    glVertex3f(-0.3, 0.4, 0.2);
    glVertex3f(0.3, 0.4, 0.2);
    glVertex3f(0.3, 0.6, 0.2);
    glVertex3f(-0.3, 0.6, 0.2);
    glEnd();
    // Front wall of roof
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0); // black color
    glVertex3f(-0.3, 0.4, 0.7);
    glVertex3f(0.3, 0.4, 0.7);
    glVertex3f(0.3, 0.6, 0.7);
    glVertex3f(-0.3, 0.6, 0.7);
    glEnd();
    // Left wall of roof
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0); // Red color
    glVertex3f(-0.3, 0.4, 0.2);
    glVertex3f(-0.3, 0.6, 0.2);
    glVertex3f(-0.3, 0.6, 0.7);
    glVertex3f(-0.3, 0.4, 0.7);
    glEnd();
    // Right wall of roof
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1); // White color
    glVertex3f(0.3, 0.4, 0.2);
    glVertex3f(0.3, 0.6, 0.2);
    glVertex3f(0.3, 0.6, 0.7);
    glVertex3f(0.3, 0.4, 0.7);
    glEnd();
    glEnd();
    //////////////////////////////////////////
    //make an ground for first floor and roof
    glColor3f(0.545, 0.271, 0.075);
    glBegin(GL_QUADS);
    glVertex3f(-0.3, 0.0, 0.2);
    glVertex3f(0.3, 0.0, 0.2);
    glVertex3f(0.3, 0.0, 0.7);
    glVertex3f(-0.3, 0.0, 0.7);
    //second floor
    glVertex3f(-0.3, 0.4, 0.2);
    glVertex3f(0.3, 0.4, 0.2);
    glVertex3f(0.3, 0.4, 0.7);
    glVertex3f(-0.3, 0.4, 0.7);
    glEnd();
    ///////////////////////////
    glLineWidth(6.0);
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.5);
    // Line between first and second floor from front side
    glVertex3f(-0.3, 0.0, 0.71);
    glVertex3f(0.3, 0.0, 0.71);
    // Line between first and second floor from back side
    glVertex3f(-0.3, 0.0, .19);
    glVertex3f(0.3, 0.0, .19);
    // Separator line from left side
    glVertex3f(-0.3, 0.0, 0.2);
    glVertex3f(-0.3, 0.0, 0.7);
    // Separator line from right side
    glVertex3f(0.3, 0.0, 0.2);
    glVertex3f(0.3, 0.0, 0.7);
    glEnd();
    // separator line between second floor and roof
    glLineWidth(6.0);
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.5);
    // Line between second floor and roof from back side
    glVertex3f(-0.3, 0.4, 0.7);
    glVertex3f(0.3, 0.4, 0.7);
    // Line between second floor and roof from back side
    glVertex3f(-0.3, 0.4, 0.2);
    glVertex3f(0.3, 0.4, 0.2);
    // Separator line from left side
    glVertex3f(-0.3, 0.4, 0.2);
    glVertex3f(-0.3, 0.4, 0.7);
    // Separator line from right side
    glVertex3f(0.3, 0.4, 0.2);
    glVertex3f(0.3, 0.4, 0.7);
    glEnd();
    /////////////////////////////
        // Door
    glPushMatrix();
    glTranslatef(-0.05f, -0.45f, 0.71);
    // Rotate the door
    glRotated(doorAngle, 0, 1, 0);
    glTranslatef(0.05f, 0.45f, -0.71);
    glBegin(GL_QUADS);
    glColor3f(0.545, 0.271, 0.075);
    glVertex3f(-0.05, -0.6, 0.71);
    glVertex3f(0.05, -0.6, 0.71);
    glVertex3f(0.05, -0.3, 0.71);
    glVertex3f(-0.05, -0.3, 0.71);
    glEnd();
    //door handle
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(0.03, -0.45, 0.72);
    glVertex3f(0.03, -0.47, 0.72);
    glVertex3f(0.01, -0.47, 0.72);
    glVertex3f(0.01, -0.45, 0.72);
    glEnd();
    glPopMatrix();
    //////////////////////
    // Windows
    // Window 1 (Top-left)
    glPushMatrix();
    glTranslatef(-0.2f, 0.25f, 0.71f);
    // Rotate the window
    glRotatef(windowAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.2f, -0.25f, -0.71f);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-0.2, 0.3, 0.71);
    glVertex3f(-0.1, 0.3, 0.71);
    glVertex3f(-0.1, 0.2, 0.71);
    glVertex3f(-0.2, 0.2, 0.71);
    glEnd();
    glPopMatrix();
    // Window 2 (Top-right)
    glPushMatrix();
    glTranslatef(0.2f, 0.25f, 0.71f);
    // Rotate the window
    glRotatef(-windowAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.2f, -0.25f, -0.71f);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.2, 0.3, 0.71);
    glVertex3f(0.1, 0.3, 0.71);
    glVertex3f(0.1, 0.2, 0.71);
    glVertex3f(0.2, 0.2, 0.71);
    glEnd();
    glPopMatrix();
    // Window 3 (Bottom-left)
    glPushMatrix();
    glTranslatef(-0.2f, -0.15f, 0.71f);
    // Rotate the window
    glRotatef(windowAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.2f, 0.15f, -0.71f);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-0.2, -0.1, 0.71);
    glVertex3f(-0.1, -0.1, 0.71);
    glVertex3f(-0.1, -0.2, 0.71);
    glVertex3f(-0.2, -0.2, 0.71);
    glEnd();
    glPopMatrix();
    // Window 4 (Bottom-right)
    glPushMatrix();
    glTranslatef(0.2f, -0.15f, 0.71f);
    // Rotate the window
    glRotatef(-windowAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.2f, 0.15f, -0.71f);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.2, -0.1, 0.71);
    glVertex3f(0.1, -0.1, 0.71);
    glVertex3f(0.1, -0.2, 0.71);
    glVertex3f(0.2, -0.2, 0.71);
    glEnd();
    glPopMatrix();
    glFlush();
    glPopMatrix();
}
void drawBicycle() {
    glPushMatrix();
    glTranslatef(bicyclePosX, 0.0f, 2.0);
    // front wheel
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.1f, -0.545f, 0.0f);
    glRotatef(wheelRotationAngle, 0.0f, 0.0f, 1.0f); // Rotate wheel
    glutSolidTorus(0.01, 0.05, 40, 40);
    glPopMatrix();
    // back wheel
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-0.1f, -0.545f, 0.0f);
    glRotatef(wheelRotationAngle, 0.0f, 0.0f, 1.0f); // Rotate wheel
    glutSolidTorus(0.01, 0.05, 40, 40);
    glPopMatrix();
    // Frame
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.003f, -0.46f, 0.0f);
    glScalef(0.3f, 0.05f, 0.04f); // Scale to appropriate dimensions
    glutSolidCube(1.0f);
    glPopMatrix();
    // Seat
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0.0f, -0.43f, 0.0f);
    glScalef(0.08f, 0.02f, 0.04f); // Scale to appropriate dimensions
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 1, 1); // Black color
    glTranslatef(-0.05f, -0.4f, 0.0f);
    glScalef(0.03f, 0.07f, 0.04f); // Scale to appropriate dimensions
    glutSolidCube(1.0f);
    glPopMatrix();
    //Handle
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.04f, -0.4f, 0.0f);
    glScalef(0.01f, 0.08f, 0.03f); // Scale to appropriate dimensions
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 1.0f);
    glTranslatef(0.04f, -0.35f, 0.01f);
    glScalef(0.01f, 0.02f, 0.15f); // Scale to appropriate dimensions
    glutSolidCube(1.0f);
    glPopMatrix();
    glFlush();
    glPopMatrix();

}
// Update function to rotate the bicycle
void update(int value) {
    if (animationEnabled) {
        Alltheta += 3;
        wheelRotationAngle += 3.0f; // Rotate the wheels
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
void display() {
    //This line is used to clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Start the scene with clean transformation
    glLoadIdentity();
    // Set the camera
    gluLookAt(5.0f * sin(cameraAngle * 3.14159 / 180.0), cameraHeight, 5.0f * cos(cameraAngle * 3.14159 / 180.0), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    drawBuilding();
    // Rotate the bicycle around the building
    glRotated(Alltheta, 0, 1, 0);
    drawBicycle();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'f':
        bicyclePosX += 0.1f;
        wheelRotationAngle += 5.0f;
        if (bicyclePosX > 2.0f)
            bicyclePosX = 2.0f;
        break;
    case 'b':
        bicyclePosX -= 0.1f;
        wheelRotationAngle -= 5.0f;
        if (bicyclePosX < -2.0f)
            bicyclePosX = -2.0f;
        break;
    case 'r':
        wheelRotationAngle -= 5.0f;
        break;
    case 'l':
        wheelRotationAngle += 5.0f;
        break;
    case 'w':
        cameraHeight += 0.1f;
        break;
    case 's':
        cameraHeight -= 0.1f;
        break;
    case 'a':
        cameraAngle += 5.0f;
        break;
    case 'd':
        cameraAngle -= 5.0f;
        break;
    case 'o':
        if (doorAngle > -180.0f)
            doorAngle -= 90.0f;
        break;
    case 'c':
        if (doorAngle < 0.0f)
            doorAngle += 90.0f;
        break;
    case 'O':
        if (windowAngle > -180.0f)
            windowAngle -= 90.0f;
        break;
    case 'C':
        if (windowAngle < 0.0f)
            windowAngle += 90.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        animationEnabled = true;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        animationEnabled = false;

    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Graphic Project");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(16, update, 0);
    // Initialize OpenGL
    init();

    glutMainLoop();

    return 0;
}
