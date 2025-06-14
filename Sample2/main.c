#include <GL/glut.h>
#include <stdio.h>

// Function to set pixel in OpenGL
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Function to perform boundary fill using 4-connected approach
void boundaryFill4(int x, int y, float fillColor[3], float borderColor[3]) {
    float interiorColor[3];
    glGetFloatv(GL_CURRENT_COLOR, interiorColor); // Get current color as initial boundary color

    if(memcmp(interiorColor, borderColor, 3 * sizeof(float)) != 0 &&
       memcmp(interiorColor, fillColor, 3 * sizeof(float)) != 0) {
        setPixel(x, y);
        glColor3fv(fillColor);
        boundaryFill4(x + 1, y, fillColor, borderColor);
        boundaryFill4(x - 1, y, fillColor, borderColor);
        boundaryFill4(x, y + 1, fillColor, borderColor);
        boundaryFill4(x, y - 1, fillColor, borderColor);
    }
}

// Function to draw a polygon
void drawPolygon() {
    glColor3f(0.0, 0.0, 1.0); // Border color: blue
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(300, 100);
    glVertex2i(300, 300);
    glVertex2i(200, 400);
    glVertex2i(100, 300);
    glEnd();
}

// Function to handle key presses
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
            glColor3f(1.0, 0.0, 0.0); // Fill color: red boundaryFill4(200, 200, fillColor, borderColor);
            break;
        default:
            break;
    }
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    glFlush();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Boundary Fill Algorithm");

    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);

    glutMainLoop();
    return 0;
}
