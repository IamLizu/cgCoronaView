#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>


///change check



void triangleFloat(float v0, float v1, float v01_v1, float v2, float v21) {
    glBegin(GL_TRIANGLES);
    glVertex2f(v0, v01_v1);
    glVertex2f(v1, v01_v1);
    glVertex2f(v2, v21);
    glEnd();
}

void triangleFloat2(float v0, float v01, float v1, float v11, float v2, float v21) {
    glBegin(GL_TRIANGLES);
    glVertex2f(v0, v01);
    glVertex2f(v1, v11);
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

void quadHorzFloat2(float p1, float p2, float q1, float q2, float r1, float r2, float s1, float s2) {
    glBegin(GL_QUADS);
    glVertex2f(p1, p2);
    glVertex2f(q1, q2);
    glVertex2f(r1, r2);
    glVertex2f(s1, s2);
    glEnd();
}

GLfloat planeTFX = 0.0f; // plane translation factor x
GLfloat planeSpeed = 0.01f; // plane speed

void update(int value) {
    if (planeTFX > 2.4) planeTFX = -1.2f;
    planeTFX += planeSpeed;

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

void init() {
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix(); // Plane start
    glTranslatef(planeTFX, 0.0f, 0.0f);
    glColor3b(128, 0, 0);
    quadHorzFloat(-0.8-0.6, -0.6-0.6, 0.8, 0.9); // main body
    triangleFloat2(-0.6-0.6, 0.8, -0.55-0.6, 0.85, -0.6-0.6, 0.9); // head
    quadHorzFloat2(-0.78-0.6, 0.75, -0.70-0.6, 0.75, -0.65-0.6, 0.8, -0.74-0.6, 0.8); // bottom wing
    quadHorzFloat2(-0.78-0.6, 0.95, -0.70-0.6, 0.95, -0.65-0.6, 0.9, -0.74-0.6, 0.9); // top wing
    glPopMatrix(); // Plane end

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
    glutTimerFunc(1000, update, 0);
    glutMainLoop();
    return 0;
}
