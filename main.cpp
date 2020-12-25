#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


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
float moveCar1 = 0.0f;
float moveCar2 = 800.0f;
float move_cloud=0;
float move_dust=0;
float moveBusUp=0.0f;
float positionOfCarOne=0;
float positionOfCarTwo=0;

void DrawCarOne();
void DrawCarTow();
void DrawBodyOfCarOne();
void DrawBodyOfCarTow();
void DrawPassengerStandby();

int partN=1000;///deafault particles 1000 shoqing more corona particles

void points(double a,double b){ ///gLPoints func
    glBegin(GL_POINTS);
    glVertex2d(a,b);
    glEnd();
}

void CoronaParticle(){          ///Corona particles generator
    for(int i=0;i<partN;i++){
        int A=rand()%800;
        int B=rand()%800;
        glColor3ub(0,255,0);
        glPointSize(2.0);
        points(A,B);
        glEnd();
    }
}

void plane() {
    static float planeTFactX = -180.0f; // plane translation factor X
    static float planeTFactY = 0.0f; // plane translation factor Y

    if(planeTFactX >= 900) {
         planeTFactX = -180.0f;
         planeTFactY = 0.0f;

    } else {
        planeTFactX += 1.8f;
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
    glVertex2i(0,200);
    glVertex2i(800,200);
    glVertex2i(800,400);
    glVertex2i(0,400);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(153, 102, 51);
    glVertex2i(0,380);
    glVertex2i(800,380);
    glVertex2i(800,405);
    glVertex2i(0,405);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(153, 102, 51);
    glVertex2i(0,200);
    glVertex2i(800,200);
    glVertex2i(800,220);
    glVertex2i(0,220);
    glEnd();


    ///====================================Top Border of road
    glBegin(GL_LINES);
    glLineWidth(5);
	glColor3ub(223, 191, 159);
    glVertex2i(0,380);
    glVertex2i(800,380);
    glEnd();

    ///====================================bottom Border of road
    glBegin(GL_LINES);
    glLineWidth(5);
	glColor3f(1.0,1.0,1.0);
    glVertex2i(0,220);
    glVertex2i(800,220);
    glEnd();

     ///====================================road divider
    glBegin(GL_LINES);
    glColor3f(1.0,1.0,1.0);
    int dividerLine=0;
    for(int i=0;i<20;i++){
        glVertex2i(dividerLine+20,300);
        glVertex2i(dividerLine+40,300);
        dividerLine=dividerLine+40;
    }
    glEnd();

    ///==================================== Bottom Road Side Bar


    int changeX1=0,changeX2=40;

    for(int i=0;i<20;i++){
        glBegin(GL_POLYGON);
        if(i%2==0){
            glColor3ub(1,1,1);  //black color
        }else{
            glColor3ub(217, 217, 217);  //white color
        }

        glVertex2i(changeX1,180);
        glVertex2i(changeX2,180);
        glVertex2i(changeX2,210);
        glVertex2i(changeX1,210);

        changeX1=changeX2;
        changeX2=changeX2+40;
        glEnd();
    }



    ///==================================== Bottom Road Side Bar Top View
    glBegin(GL_LINES);
    glLineWidth(5);
	glColor3f(204, 153, 0);     //yellow color
    glVertex2i(0,210);
    glVertex2i(800,210);
    glEnd();

     ///==================================== Top Road Side Bar


    int TopChangeX1=0,TopchangeX2=40;

    for(int i=0;i<20;i++){
        glBegin(GL_POLYGON);
        if(i%2==1){
            glColor3ub(1,1,1);  //black color
        }else{
            glColor3ub(217, 217, 217);  //white color
        }

        glVertex2i(TopChangeX1,400);
        glVertex2i(TopchangeX2,400);
        glVertex2i(TopchangeX2,420);
        glVertex2i(TopChangeX1,420);

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


void DrawGrassField(){
     ///==================================== add grass
    glBegin(GL_POLYGON);
	glColor3f(0,0.60,0);     //green color
    glVertex2i(0,0);
    glVertex2i(800, 0);
    glVertex2i(800,180);
    glVertex2i(0, 180);
    glEnd();

    ///====================================1st lane Tree draw
    int treeDistance=0;
    for(int i=0;i<4;i++){
        glBegin(GL_POLYGON);
        glColor3ub(102, 51, 0);  //tree body color
        glVertex2i(60+treeDistance,30);
        glVertex2i(70+treeDistance,30);
        glVertex2i(65+treeDistance,150);
        glEnd();
        glColor3f(0, 153, 0);   //tree leaf color
        draw_circle(50+treeDistance,100,20);     //tree  top 1st leaf
        draw_circle(80+treeDistance,100,20);     //tree top 2nd leaf
        draw_circle(58+treeDistance,130,18);     //tree middle 1st leaf
        draw_circle(72+treeDistance,130,18);     //tree middle 2nd leaf
        draw_circle(65+treeDistance,150,14);     //tree top leaf

        treeDistance=treeDistance+200;
    }

    ///====================================2nd lane Tree draw
    treeDistance=100;
    for(int i=0;i<4;i++){
        glBegin(GL_POLYGON);
        glColor3ub(102, 51, 0);  //tree body color
        glVertex2i(60+treeDistance,100);
        glVertex2i(70+treeDistance,100);
        glVertex2i(65+treeDistance,220);
        glEnd();
        glColor3f(0, 153, 0);   //tree leaf color
        draw_circle(50+treeDistance,170,20);     //tree  top 1st leaf
        draw_circle(80+treeDistance,170,20);     //tree top 2nd leaf
        draw_circle(58+treeDistance,200,18);     //tree middle 1st leaf
        draw_circle(72+treeDistance,200,18);     //tree middle 2nd leaf
        draw_circle(65+treeDistance,220,14);     //tree top leaf

        treeDistance=treeDistance+200;
    }
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
void DrawIndustry(){
     ///==================================================garments

     for(int i=0;i<300;i++){
        glColor3f(0, 0, 0);
        if(i%2==0){
            draw_circle(356.5,630+move_dust-(i*5),2);
            draw_circle(363.5,630+move_dust-(i*5),2);
            draw_circle(370.5,630+move_dust-(i*5),2);
        }else{
            draw_circle(353,630+move_dust-(i*5),2);
            draw_circle(360,630+move_dust-(i*5),2);
            draw_circle(367,630+move_dust-(i*5),2);
            draw_circle(375,630+move_dust-(i*5),2);
        }

    }

    glBegin(GL_POLYGON);
	glColor3ub(153, 51, 0);
    glVertex2i(350,420);
    glVertex2i(500,420);
    glVertex2i(500,590);
    glVertex2i(380,590);
    glVertex2i(380,630);
    glVertex2i(350,630);
    glEnd();

    glBegin(GL_POLYGON);
	glColor3f(0.0,0.7,1.5);
    glVertex2i(350,730);
    glVertex2i(380,730);
    glVertex2i(380,830);
    glVertex2i(350,830);
    glEnd();

    int b4y1=585,b4y2=582;
	for(int i=0;i<7;i++){
        //=================flor of building 4
        glBegin(GL_POLYGON);
        glColor3ub(153, 153, 102);
        glVertex2i(350,b4y1);
        glVertex2i(500,b4y1);
        glVertex2i(500,b4y2);
        glVertex2i(350,b4y2);
        glEnd();
        b4y1=b4y1-25;
        b4y2=b4y2-25;
	}

	int b4y01=438,b4y02=450;
    int b4x01=355,b4x02=370;

    for(int j=1;j<37;j++){
        glBegin(GL_POLYGON);

        if(j%10==0){
            glColor3f(0, 0, 0);
        }else{
             glColor3ub(242, 242, 242);
        }
        glVertex2i(b4x01,b4y01);
        glVertex2i(b4x02,b4y01);
        glVertex2i(b4x02,b4y02);
        glVertex2i(b4x01,b4y02);
        glEnd();


        b4x01=b4x01+25;
        b4x02=b4x02+25;
        if(j%6==0){
            b4x01=355;
            b4x02=370;
            b4y01=b4y01+25;
            b4y02=b4y02+25;
        }

    }
}

void DrawPassengerStandby(){



    glBegin(GL_POLYGON);
    glColor3ub(153, 153, 102);
    glVertex2i(600,400);
    glVertex2i(670,400);
    glVertex2i(670,430);
    glVertex2i(600,430);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3ub(153, 153, 102);
    glVertex2i(650,410);
    glVertex2i(650,380);
    glVertex2i(670,400);
    glVertex2i(670,430);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(153, 153, 102);
    glVertex2i(580,410);
    glVertex2i(580,380);
    glVertex2i(600,400);
    glVertex2i(600,430);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 51, 204);
    glVertex2i(580,410);
    glVertex2i(650,410);
    glVertex2i(670,430);
    glVertex2i(600,430);
    glEnd();

}
void DrawDMP(){
    ///==================================== Draw Building DMP
    glBegin(GL_POLYGON);
	glColor3ub(153, 51, 51);
    glVertex2i(610,420);
    glVertex2i(760,420);
    glVertex2i(760,600);
    glVertex2i(610,600);
    glEnd();

    int dmpY1=585,dmpY2=582;
	for(int i=0;i<8;i++){
        //=================flor of building 1
        if(i==2 || i==3){

        }
        else{
            glBegin(GL_POLYGON);
            glColor3ub(153, 153, 102);
            glVertex2i(610,dmpY1);
            glVertex2i(760,dmpY1);
            glVertex2i(760,dmpY2);
            glVertex2i(610,dmpY2);
            glEnd();
        }
        dmpY1=dmpY1-25;
        dmpY2=dmpY2-25;
	}

    //======================================D
    glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
    glVertex2i(630,498);
    glVertex2i(630,552);
    glEnd();
    glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
    glVertex2i(630,550);
    glVertex2i(655,550);
    glVertex2i(660,545);
    glVertex2i(660,505);
    glVertex2i(655,500);
    glVertex2i(630,500);
    glEnd();

    //======================================M
    glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
    glVertex2i(670,500);
    glVertex2i(670,550);
    glEnd();
    glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
    glVertex2i(670,550);
    glVertex2i(685,530);
    glEnd();
    glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
    glVertex2i(685,530);
    glVertex2i(700,550);
    glEnd();
    glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
    glVertex2i(700,550);
    glVertex2i(700,500);
    glEnd();

    //======================================P
    glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
    glVertex2i(710,500);
    glVertex2i(710,550);
    glEnd();
    glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
    glVertex2i(710,550);
    glVertex2i(740,550);
    glVertex2i(740,525);
    glVertex2i(710,525);
    glEnd();

}
void DrawCity()
{

    ///==================================== Draw Sun
    glColor3f(255, 255, 0);   //sun color
    draw_circle(300,760,30);
    //===================================tree
    glBegin(GL_POLYGON);
    glColor3ub(112, 51, 0);  //tree body color
    glVertex2i(310,420);
    glVertex2i(320,420);
    glVertex2i(315,540);
    glEnd();
    glColor3f(0, 153, 0);   //tree leaf color
    draw_circle(300,490,20);     //tree  top 1st leaf
    draw_circle(330,490,20);     //tree top 2nd leaf
    draw_circle(308,510,18);     //tree middle 1st leaf
    draw_circle(322,510,18);     //tree middle 2nd leaf
    draw_circle(315,535,14);     //tree top leaf


    //====================================tree
    glBegin(GL_POLYGON);
    glColor3ub(112, 51, 0);  //tree body color
    glVertex2i(600,420);
    glVertex2i(610,420);
    glVertex2i(605,540);
    glEnd();
    glColor3f(0, 153, 0);   //tree leaf color
    draw_circle(590,490,20);     //tree  top 1st leaf
    draw_circle(620,490,20);     //tree top 2nd leaf
    draw_circle(598,510,18);     //tree middle 1st leaf
    draw_circle(612,510,18);     //tree middle 2nd leaf
    draw_circle(605,535,14);     //tree top leaf

    //====================================tree
    glBegin(GL_POLYGON);
    glColor3ub(112, 51, 0);  //tree body color
    glVertex2i(510,420);
    glVertex2i(520,420);
    glVertex2i(515,540);
    glEnd();
    glColor3f(0, 153, 0);   //tree leaf color
    draw_circle(500,490,20);     //tree  top 1st leaf
    draw_circle(530,490,20);     //tree top 2nd leaf
    draw_circle(508,510,18);     //tree middle 1st leaf
    draw_circle(522,510,18);     //tree middle 2nd leaf
    draw_circle(515,535,14);     //tree top leaf

    DrawIndustry();
    DrawCloud();


    DrawDMP();

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
void DrawCar()
{
    glPushMatrix();
    DrawCarOne();
    DrawCarTow();


}
void DrawBodyOfCarOne(){
    glVertex2i(0,330);
    glVertex2i(120,330);
    glVertex2i(120,345);
    glVertex2i(115,350);
    glVertex2i(90,350);
    glVertex2i(70,365);
    glVertex2i(40,365);
    glVertex2i(20,350);
    glVertex2i(0,350);
    glEnd();
}
void DrawCarOne(){

    glPushMatrix();
    glTranslatef(moveCar1, 0.0f, 0.0f);
    positionOfCarOne=120+moveCar1;
    //==================================Body of a car
	glBegin(GL_POLYGON);
    glColor3ub(204, 204, 0);
    DrawBodyOfCarOne();


    glBegin(GL_LINE_LOOP);
    glColor3ub(255, 255, 255);
    DrawBodyOfCarOne();

    //==================================glass of a car
    glBegin(GL_POLYGON);
    glColor3ub(204, 51, 0);
    glVertex2i(25,350);
    glVertex2i(85,350);
    glVertex2i(67,360);
    glVertex2i(43,360);
    glEnd();
    //==================================chaka of a car
    glColor3f(0, 0, 0);
    draw_circle(15+moveCar1,330,10);
    draw_circle(90+moveCar1,330,10);
    glPopMatrix();
}

void DrawCarTow(){
    glPushMatrix();
    glTranslatef(moveCar2,moveBusUp, 0.0f);

    positionOfCarTwo=0+moveCar2;
    //==================================Body of a bus
	glBegin(GL_POLYGON);
	glColor3ub(204, 0, 0);
	DrawBodyOfCarTow();


    //==================================Sidebar of Bus
    glBegin(GL_LINE_LOOP);
    glColor3ub(255, 255, 255);
    DrawBodyOfCarTow();

    //==================================glass of of a bus
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
    glVertex2i(90,270);
    glVertex2i(110,270);
    glVertex2i(110,280);
    glVertex2i(90,280);
    glEnd();

    glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
    glVertex2i(65,270);
    glVertex2i(85,270);
    glVertex2i(85,280);
    glVertex2i(65,280);
    glEnd();

    glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
    glVertex2i(60,270);
    glVertex2i(40,270);
    glVertex2i(40,280);
    glVertex2i(60,280);
    glEnd();

    glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
    glVertex2i(35,270);
    glVertex2i(15,270);
    glVertex2i(15,280);
    glVertex2i(35,280);
    glEnd();

    //==================================chaka of a bus carTwo
    glColor3f(0, 0, 0);
    draw_circle(20+moveCar2,255+moveBusUp,8);
    draw_circle(105+moveCar2,255+moveBusUp,8);
    draw_circle(85+moveCar2,255+moveBusUp,8);
    glPopMatrix();
}
void DrawBodyOfCarTow(){
    glVertex2i(0,260);
    glVertex2i(5,255);
    glVertex2i(120,255);
    glVertex2i(120,290);
    glVertex2i(5,290);
    glVertex2i(0,285);
    glEnd();
}
void myDisplay(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    DrawCity();
    DrawMainRoad();
    DrawCar();
    DrawGrassField();
    DrawPassengerStandby();
    plane();
    CoronaParticle();
    glFlush ();
}

void myInit (void)
{
    glClearColor(0.0,0.7,1.5,0.0);  //sky color
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (280,0);
    glutCreateWindow ("Corona View");
    glutDisplayFunc(myDisplay);
    glutTimerFunc(25, update, 100); //Add a timer
    glutKeyboardFunc(keyboard);     //keyboard
    myInit ();
    glutMainLoop();
}


//=============================================method
void keyboard(unsigned char key, int x, int y)
{

    if(key=='s' &&  (moveBusUp+270)<320)
    {
        //speed up of car 1
        moveCar1=moveCar1+5;
        moveCar2=moveCar2-5;
        glutPostRedisplay();
    }
    else if(key=='u' && (moveBusUp+270)<350)
    {
        //speed up of car 2

            moveBusUp=moveBusUp+1;
            glutPostRedisplay();
    }
    else if(key=='d' && (moveBusUp+270)>245)
    {
        //speed up of car 2
        moveBusUp=moveBusUp-1;
        glutPostRedisplay();
    }
    else if(key=='x')
    {
        moveCar1=moveCar1-2;
        moveCar2 = moveCar2+2;
        glutPostRedisplay();
    }

    if(key=='q'){ ///press q to show that it is in quarantine mode
        partN=300;
    }
}
void update(int value) {

    moveCar1 = moveCar1+2;  //initial speed

    moveCar2 = moveCar2-2;  //initial speed

    if(moveCar2< 0 && moveCar1> 800)
    {
        moveCar1 =-200;
        moveCar2 =1000;
    }
    move_cloud=move_cloud+.5;
    if(move_cloud> 800)
    {
        move_cloud =-500;
    }
    move_dust=move_dust+.2;

    if((positionOfCarOne==positionOfCarTwo)&& (moveBusUp+270)>320){
       moveCar1=moveCar1-2;
       moveCar2 = moveCar2+2;
    }
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
