#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>



void triangleFloat(float v0, float v1, float v01_v1, float v2, float v21) {
    glBegin(GL_TRIANGLES);
    glVertex2f(v0, v01_v1);
    glVertex2f(v1, v01_v1);
    glVertex2f(v2, v21);
    glEnd();
}

void quadHorzFloat(float pT, float pB, float fixedP, float fixedQ) {
    glBegin(GL_QUADS);
    glVertex2f(pB, fixedP);
    glVertex2f(pT, fixedP);
    glVertex2f(pT, fixedQ);
    glVertex2f(pB, fixedQ);
    glEnd();
}


void init() {
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // ami kisu kori nai

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1365, 767);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Corona View");
    glutDisplayFunc(display);
    init();
    // glutMouseFunc(handleMouse);
    // glutTimerFunc(1000, update, 0);
    glutMainLoop();
    return 0;
}
