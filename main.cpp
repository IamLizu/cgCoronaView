#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

void drawPixelInt(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void *currentfont;

void setFont(void *font)
{
	currentfont=font;
}
void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);

	for(c=string;*c!='\0';c++)
	{
		glutBitmapCharacter(currentfont,*c);
	}
}

// vertical straight
void twoIntVertS(int pT, int pB, int fixedP) {
    glBegin(GL_LINES);
    glVertex2i(fixedP, pT);
    glVertex2i(fixedP, pB);
    glEnd();
}

// horzt straight
void twoIntHorzS(int pT, int pB, int fixedP) {
    glBegin(GL_LINES);
    glVertex2i(pB, fixedP);
    glVertex2i(pT, fixedP);
    glEnd();
}

void quadHorzInt(int pT, int pB, int fixedP, int fixedQ) {
    glBegin(GL_QUADS);
    glVertex2i(pB, fixedP);
    glVertex2i(pT, fixedP);
    glVertex2i(pT, fixedQ);
    glVertex2i(pB, fixedQ);
    glEnd();
}

void quadHorzInt2(int v0, int v01, int v1, int v11, int v2, int v21, int v3, int v31) {
    glBegin(GL_QUADS);
    glVertex2i(v0, v01);
    glVertex2i(v1, v11);
    glVertex2i(v2, v21);
    glVertex2i(v3, v31);
    glEnd();
}

void triangleNS(int v0, int v01, int v1, int v11, int v2, int v21) {
    glBegin(GL_TRIANGLES);
    glVertex2i(v0, v01);
    glVertex2i(v1, v11);
    glVertex2i(v2, v21);
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

void keyboard(unsigned char , int , int );
void update(int);
void draw_circle(float x, float y, float radius);

float move_cloud=0;
float move_dust=0;


void plane() {
    static float planeTFactX = -180.0f; // plane translation factor X
    static float planeTFactY = 0.0f; // plane translation factor Y

    if(planeTFactX >= 900) {
         planeTFactX = -180.0f;
         planeTFactY = 0.0f;

    } else {
        planeTFactX += 0.1f;
        planeTFactY += 0.005f;
    }

    // Main Body
    glColor3ub(115, 110, 109);

    glPushMatrix();
    glTranslatef(planeTFactX, planeTFactY, 0);
    quadHorzInt2(30, 700, 100, 700, 100, 715, 35, 715);

    // Head
    triangleNS(100, 700, 110, 707, 100, 715);

    // Radar
    quadHorzInt2(37, 715, 57, 715, 40, 730, 20, 730);

    // Left wing
    quadHorzInt2(70, 715, 80, 715, 60, 735, 50, 735);

    // Right wing
    quadHorzInt2(70, 700, 80, 700, 60, 680, 50, 680);

    // Windows
    glColor3ub(255,255,255);
    int planeWindowX = 95;
    for (int i = 0; i < 8; i++) {
        drawPixelInt(planeWindowX, 710);
        planeWindowX -= 5;
    }

    glPopMatrix();
    glutPostRedisplay();

}

void DrawMainRoad(){

    ///==================================== Main Road
    glBegin(GL_POLYGON);
    glColor3f(0.2,0.2,0.2);
    glVertex2i(0,120);
    glVertex2i(800,120);
    glVertex2i(800,330);
    glVertex2i(0,330);
    glEnd();




    glBegin(GL_POLYGON);
    glColor3ub(153, 102, 51);
    glVertex2i(0,350);
    glVertex2i(800,350);
    glVertex2i(800,420);
    glVertex2i(0,420);
    glEnd();






     ///====================================road divider
   glBegin(GL_LINES);
    glColor3f(1.0,1.0,1.0);
    int dividerLine=0;
    for(int i=0;i<200;i++)
    {
        glVertex2i(dividerLine+20,220);
        glVertex2i(dividerLine+40,220);
        dividerLine=dividerLine+40;
    }
    glEnd();

    ///==================================== top Road Side Bar


    int changeX1=0,changeX2=40;

    for(int i=0;i<20;i++){
        glBegin(GL_POLYGON);
        if(i%2==0){
            glColor3ub(1,1,1);  //black color
        }else{
            glColor3ub(217, 217, 217);  //white color
        }

        glVertex2i(changeX1,330);
        glVertex2i(changeX2,330);
        glVertex2i(changeX2,350);
        glVertex2i(changeX1,350);

        changeX1=changeX2;
        changeX2=changeX2+40;
        glEnd();
    }

     ///==================================== bottom Road Side Bar


    int TopChangeX1=0,TopchangeX2=40;

    for(int i=0;i<20;i++){
        glBegin(GL_POLYGON);
        if(i%2==1){
            glColor3ub(1,1,1);  //black color
        }else{
            glColor3ub(217, 217, 217);  //white color
        }

        glVertex2i(TopChangeX1,100);
        glVertex2i(TopchangeX2,100);
        glVertex2i(TopchangeX2,120);
        glVertex2i(TopChangeX1,120);

        TopChangeX1=TopchangeX2;
        TopchangeX2=TopchangeX2+40;
        glEnd();
    }





    ///==================================== Top Road Side Bar Top View
    glBegin(GL_LINES);
    glLineWidth(5);
	glColor3f(204, 153, 0);     //yellow color
    glVertex2i(0,420);
    glVertex2i(800, 420);
    glEnd();

}

void DrawCloud(){
    ///==================================== Draw cloud

    glColor3f(255, 255, 255);   //cloud color
    draw_circle(100+move_cloud,730,33);
    draw_circle(55+move_cloud,730,23);
    draw_circle(145+move_cloud,730,23);

    draw_circle(400+move_cloud,730,33);
    draw_circle(355+move_cloud,730,23);
    draw_circle(445+move_cloud,730,23);
}

void DrawCity()
{

    ///==================================== Draw Sun
    glColor3f(255, 255, 0);   //sun color
    draw_circle(300,760,30);

    DrawCloud();

     ///==================================== Draw Building two
    glBegin(GL_POLYGON);
	glColor3ub(153, 51, 51);
    glVertex2i(100,420);
    glVertex2i(200,420);
    glVertex2i(200,600);
    glVertex2i(100,600);
    glEnd();

    int buildingY1=570,buildingY2=573;
	for(int i=0;i<6;i++){
        //=================flor of building 1
        glBegin(GL_POLYGON);
        glColor3ub(153, 153, 102);
        glVertex2i(100,buildingY1);
        glVertex2i(200,buildingY1);
        glVertex2i(200,buildingY2);
        glVertex2i(100,buildingY2);
        glEnd();
        buildingY1=buildingY1-25;
        buildingY2=buildingY2-25;
	}

	///==================================== Draw Building One
    glBegin(GL_POLYGON);
	glColor3ub(102, 153, 153);
    glVertex2i(10,420);
    glVertex2i(110,420);
    glVertex2i(110,580);
    glVertex2i(10,580);
    glEnd();

    //===============================gate of building one
    glBegin(GL_POLYGON);
	glColor3ub(242, 242, 242);
    glVertex2i(50,420);
    glVertex2i(70,420);
    glVertex2i(70,440);
    glVertex2i(50,440);
    glEnd();

    int b1y1=450,b1y2=460;
    int b1x1=15,b1x2=35;
	for(int i=1;i<16;i++){
        glBegin(GL_POLYGON);

        glColor3ub(242, 242, 242);
        glVertex2i(b1x1,b1y1);
        glVertex2i(b1x2,b1y1);
        glVertex2i(b1x2,b1y2);
        glVertex2i(b1x1,b1y2);
        glEnd();


        b1x1=b1x1+35;
        b1x2=b1x2+35;
        if(i%3==0){
            b1x1=15;
            b1x2=35;
            b1y1=b1y1+25;
            b1y2=b1y2+25;
        }

	}

    ///==================================== Draw Building three
    glBegin(GL_POLYGON);
	glColor3ub(102, 51, 0);
    glVertex2i(190,420);
    glVertex2i(300,420);
    glVertex2i(300,560);
    glVertex2i(190,560);
    glEnd();

    int b3y1=430,b3y2=440;
    int b3x1=200,b3x2=215;
    for(int j=1;j<21;j++){
        glBegin(GL_POLYGON);

        glColor3ub(242, 242, 242);
        glVertex2i(b3x1,b3y1);
        glVertex2i(b3x2,b3y1);
        glVertex2i(b3x2,b3y2);
        glVertex2i(b3x1,b3y2);
        glEnd();


        b3x1=b3x1+25;
        b3x2=b3x2+25;
        if(j%4==0){
            b3x1=200;
            b3x2=215;
            b3y1=b3y1+25;
            b3y2=b3y2+25;
        }

    }
    //==========================================antina

    for(int i=0;i<5;i++){
        glBegin(GL_POLYGON);
        if(i%2==0){
            glColor3ub(153, 204, 0);
        }
        else{
            glColor3ub(153,0, 0);
        }

        glVertex2i(200+(i*10),560+(i*5));
        glVertex2i(290-(i*10),560+(i*5));
        glVertex2i(290-(i*10),565+(i*5));
        glVertex2i(200+(i*10),565+(i*5));
        glEnd();
    }

    glBegin(GL_POLYGON);
	glColor3ub(102, 51, 0);
    glVertex2i(243,585);
    glVertex2i(247,585);
    glVertex2i(247,640);
    glVertex2i(243,640);
    glEnd();
}

// Bank
void DrawBank(){
    quadHorzInt(470, 580, 420, 470); // sanitation tunnel

	setFont(GLUT_BITMAP_TIMES_ROMAN_10);
    glColor3f(0, 0, 0);
    drawstring(475.0,445.0,0.0,"Sanitation Tunnel");

    glColor3ub(231, 226, 57);
    quadHorzInt(580, 730, 420, 580); // Main body
    glColor3ub(0, 0, 0);
    quadHorzInt(550, 580, 420, 600); // Left pillar
    quadHorzInt(730, 760, 420, 600); // Left pillar
    glColor3ub(255, 255, 255);
    twoIntHorzS(550, 760, 580);
    twoIntHorzS(550, 760, 579);
    twoIntHorzS(550, 760, 578);
    glColor3ub(231, 226, 57);
    draw_circle(655,580,30);
    glColor3ub(0, 0, 0);

    setFont(GLUT_BITMAP_HELVETICA_12);
    drawstring(637.0,590.0,0.0,"BANK");
}

void DrawMaskSeller(){
    glColor3b(0, 0, 0);
    draw_circle(625, 447, 8);
    quadHorzInt(620, 630, 405, 440);

    glColor3ub(153, 153, 102);
    quadHorzInt2(640, 415, 640, 385, 645, 395, 645, 425); // right board
    quadHorzInt2(590, 415, 590, 385, 595, 395, 595, 425); // left leg

    glColor3ub(249, 253, 252);
    quadHorzInt2(590, 412, 640, 412, 645, 425, 595, 425); // table board

    // Mask line 1
//    glColor3b(0, 0, 125);
//    int mL1 = 590, mL2 = 595, mL3 = 600, mL4 = 595;
//    for(int i = 0; i < 5; i ++){
//       quadHorzInt2(mL1, 407, mL2, 407, mL3, 414, mL4, 414);
//       mL1 += 10;
//       mL2 += 10;
//       mL3 += 10;
//       mL4 += 10;
//    }
//
    // Mask line 2
    glColor3b(23, 12, 15);
    int mL11 = 595, mL12 = 600, mL13 = 605, mL14 = 600;
    for(int i = 0; i < 5; i ++){
       quadHorzInt2(mL11, 417,mL12, 417, mL13, 424, mL14, 424);
       mL11 += 10;
       mL12 += 10;
       mL13 += 10;
       mL14 += 10;
    }

}

void myDisplay(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    DrawCity();
    DrawMainRoad();
    DrawBank();
    DrawMaskSeller();
    plane();
    glFlush ();
}

void myInit (void)
{
    glClearColor(0.0,0.7,1.5,0.0);  //sky color
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 100.0, 800.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 680);
    glutInitWindowPosition (280,0);
    glutCreateWindow ("Corona View");
    glutDisplayFunc(myDisplay);
    glutTimerFunc(25, update, 100); //Add a timer
    glutKeyboardFunc(keyboard);     //keyboard
    myInit ();
    glutMainLoop();
}

// Keyboard handler
void keyboard(unsigned char key, int x, int y){}

void update(int value) {
    move_cloud = move_cloud + .5;
    if(move_cloud > 800)
    {
        move_cloud = -500;
    }
    move_dust = move_dust + .2;

	glutPostRedisplay(); //Tell GLUT that the display has changed
	glutTimerFunc(25, update, 0);   //Tell GLUT to call update again in 25 milliseconds
}

void draw_circle(float x, float y, float radius) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    static const int circle_points = 100;
    static const float angle = 2.0f * 3.1416f / circle_points;

    glBegin(GL_POLYGON);
    double angle1=0.0;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    int i;
    for (i=0; i<circle_points; i++)
    {
        glVertex2d(radius * cos(angle1), radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();
    glPopMatrix();
}
