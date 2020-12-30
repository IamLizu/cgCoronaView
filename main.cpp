#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
int ucounter= 25;/// update counter-------------------
bool rain;
bool day=true;
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

void drawPixelInt(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
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
void drawSun(){
 glColor3f(255, 255, 0);   //sun color
    draw_circle(300,760,30);
    }
void drawMoon(){
    glColor3f(255, 255, 255);   //sun color
    draw_circle(300,760,20);
}

void DrawCity()
{

    ///==================================== Draw Sun
    if(day){
    drawSun();///==================sun on the day
    }
    else{
    drawMoon();///==================moon on the night
    }
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
void rainfunc()/// rain -------------------------------------------------------
{
    int x=0;
    int y=778;
    static float a=-760.0f;
    if(a<=-768)
    {
         a=-760.0f;

    }
    else
    {
        a-=0.5f;

    }
    glColor3ub(255,255,255);
    glPushMatrix();
    glTranslatef(0.0f,a,0.0f);
    glBegin(GL_LINES);
    for(int i=500;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            glVertex3i(x,y,0);
            glVertex3i(x+3,y+10,0);
            x+=rand()%1050;
        }
        y+=rand()%15;
        x=0;

    }
    glEnd();
    ///ucounter =100;
    glPopMatrix();
    glutPostRedisplay();

}
void daymode(){

glClearColor(0.0,0.7,1.5,0.0);
    DrawCity();
    DrawMainRoad();
    plane();
    if(rain){
        rainfunc();
    }

}
void nightmode(){

glClearColor(0.0,0.0,0.0,0.0);
    DrawCity();
    DrawMainRoad();
    plane();
    if(rain){
        rainfunc();
    }

}




int flag=0;///FLAG FOR GOING THROUGH WELCOME,HELP MENU THEN START

void startscreen(void)///welcome screen-------------------------------------
{
    setFont(GLUT_BITMAP_HELVETICA_18);
    glClearColor(0.000, 0.000, 0.000,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,0);
    drawstring(150.0,750.0,0.0,"AMERICAN INTERNATIONAL UNIVERSITY-BANGLADESH");
    glColor3f(0,0,1);
    drawstring(147,700,0.0,"FACULTY OF SCIENCE AND INFORMATION TECHNOLOGY");
    glColor3f(0.7,0.7,0.7);
    drawstring(325,625,0.0,"PROJECT ON");
    drawstring(200,590,0.0,"COMPUTER GRAPHICS: CORONA VIEW");
    glColor3f(1,0.5,0);
    drawstring(50,500,0.0,"SUBMITTED BY:");
    glColor3f(1,1,1);
    drawstring(50,450,0.0,"RAHAT,MD ASHFAQUR RAHMAN       (17-34492-2)");
    drawstring(50,400,0.0,"HASAN,S M MAHMUDUL   (17-35752-3)");
    drawstring(50,350,0.0,"RAFAT,RIZWAN KARIM           (17-33609-1)");
    drawstring(50,300,0.0,"RAFA,HUMAYARA CHOWDHURY      (17-35413-3)");
    drawstring(50,250,0.0,"UDOY,IKTEDAR AHMED      (17-35667-3)");
    glColor3f(1,0.5,0);
    drawstring(600,500,0.0,"SUBMITTED TO:");
    glColor3f(1,1,1);
    drawstring(575,450,0.0,"MD. KISHOR MOROL");
    glColor3f(0,1,0);
    drawstring(300,175,0.0,"PRESS ENTER TO START");
    glFlush();
}

void controlsScreen()
{
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glClearColor(0.000, 0.000, 0.000,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.596, 0.984, 0.596);
    drawstring(250.0,700.0,0.0,"INSTRUCTIONS");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,640.0,0.0,"DAY MODE");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,640.0,0.0,"PRESS 'D'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,640.0,0.0,"DAY MODE");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,640.0,0.0,"PRESS 'D'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,600.0,0.0,"NIGHT MODE");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,600.0,0.0,"PRESS 'N'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,560.0,0.0,"CAR MOVING");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,560.0,0.0,"PRESS 'C'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,520.0,0.0,"RAIN MODE");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,520.0,0.0,"PRESS 'R'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,480.0,0.0,"NO RAIN");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,480.0,0.0,"PRESS 'E'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,440.0,0.0,"TOP VIEW");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,440.0,0.0,"PRESS 'T'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,400.0,0.0,"PLANE MOVEMENT");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,400.0,0.0,"PRESS 'P'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,360.0,0.0,"Help");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,360.0,0.0,"PRESS 'H'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(300.0,320.0,0.0,"Escape");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(150.0,320.0,0.0,"PRESS 'ESC'");
    glColor3f(0.596, 0.984, 0.596);
    drawstring(250.0,200.0,0.0,"NOW PRESS ENTER");
    glFlush();
}
void display(){
    if(day){
        daymode();
    }
    else{
        nightmode();
    }


}

void myDisplay(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    if(flag==0){
        startscreen();///renders the start screen with names and intro
    }

    if(flag==1){
    controlsScreen();

    }

    if(flag>1){
        display();
    }
    glFlush ();
    glutSwapBuffers();
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
    glutTimerFunc(ucounter, update, 100); //Add a timer
    glutKeyboardFunc(keyboard);     //keyboard
    myInit ();
    glutMainLoop();
}

// Keyboard handler
void keyboard(unsigned char key, int x, int y){

  if(key==13)
{
    flag++;
    myDisplay();
}
  if(key=='h')
  {
    flag=1;
    myDisplay();

  }
  if(key=='r')
  {
    rain=true;

  }
  if(key=='s')
  {
    rain=false;

  }
   if(key=='d')
  {
    day=true;

  }
   if(key=='n')
  {
    day=false;

  }
  }




void update(int value) {
    move_cloud = move_cloud + .5;
    if(move_cloud > 800)
    {
        move_cloud = -500;
    }
    move_dust = move_dust + .2;

	glutPostRedisplay(); //Tell GLUT that the display has changed
	glutTimerFunc(ucounter, update, 0);   //Tell GLUT to call update again in 25 milliseconds
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
