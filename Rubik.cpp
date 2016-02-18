#include <iostream>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <vector>
#include <string.h>
#include <windows.h>
#include <GL/glut.h>
#include <ctime>

#include "glm.h"
#include "tgaload.h"

using namespace std;

GLuint texture_id[1];
enum Color {WHITE,ORANGE,BLUE,RED,YELLOW,GREEN,GRAY};
enum Side {TOP,BOTTOM,LEFT,RIGHT,FRONT,BACK};


const float quadSize = 1.2f;
float quadPos = (quadSize + 0.10f);

/*float colors[6][3] = {
	{1,0.50f,0.25f}, //Turuncu //top
	{1.f,1,1},//beyaz bottom
	
	{0,1,0}, //Yeþil right
	{0,0,1}, //mavi left
	
	{1,1,0},//sarý front
	{1,0,0} //Kýrmýzý back 
	
};

const float quadSize = 0.1f;
float camx = 0.0f;
float camy = 0.0f;
int increment = 0;
class Quad{
public:
	float x;
	float y;
	float z;
	Side side;
	Quad():x(0.f),y(0.f),z(0.f){}
	Quad(float x, float y,float z,Side s): x(x),y(y),z(z),side(s){ }
	void draw()
	{
		glBegin(GL_QUADS);
		switch(side)
		{
		case Side::TOP : //Kübün üstü
			glColor3fv(colors[TOP]);
			glNormal3f(0.0, 1.0f, 0.0f);
			glVertex3f(-x, y, -z);
			glVertex3f(-x, y, z);
			glVertex3f(x, y, z);
			glVertex3f(x, y, -z);
			//printf("top");
			break;
		case Side::BOTTOM : //Kübün altý
			glColor3fv(colors[BOTTOM]);
			glNormal3f(0.0, -1.0f, 0.0f);
			glVertex3f(-x, -y, -z);
			glVertex3f(x,-y, -z);
			glVertex3f(x, -y, z);
			glVertex3f(-x, -y, z);
			//printf("bottom");
			break;
		case Side::BACK: //Kübün arkasý
			glColor3fv(colors[BACK]);
			glNormal3f(0.0, 0.0f, -1.0f);
			glVertex3f(-x, -y, -z);
			glVertex3f(-x,y, -z);
			glVertex3f(x, y, -z);
			glVertex3f(x, -y, -z);
			//printf("back");
			break;
		case Side::FRONT : //Kübün önü
			glColor3fv(colors[FRONT]);
			glNormal3f(0.0, 0.0f, 1.0f);
			glVertex3f(-x, -y, z);
			glVertex3f(x,-y, z);
			glVertex3f(x, y, z);
			glVertex3f(-x, y, z);
			//printf("front!");
			break;
		case Side::LEFT : //Kübün solu
			glColor3fv(colors[LEFT]);
			glNormal3f(-1.0, 0.0f, 0.0f);
			glVertex3f(-x, -y, -z);
			glVertex3f(-x,-y, z);
			glVertex3f(-x, y, z);
			glVertex3f(-x, y, -z);
			//printf("left");
			break;
		case  Side::RIGHT: //Kübün saðý
			glColor3fv(colors[RIGHT]);
			glNormal3f(1.0, 0.0f, 0.0f);
			glVertex3f(x, -y, -z);
			glVertex3f(x,y, -z);
			glVertex3f(x, y, z);
			glVertex3f(x, -y, z);
			//printf("right");
			break;
		}
		glEnd();
	}
};
class Rotate{
public:
	float angle;
	float x;
	float y;
	float z;
};
class Cube{
public:
	Quad *quad;

	float x;
	float y;
	float z;

	std::vector<Rotate> rotasyon;

	float trxp; // Translate için x
	float tryp; //Translate için y
	float trzp; //Translate için z
	Cube():x(0),y(0),z(0),quad(new Quad[6]){
		for(int i=0;i<6;i++)
		{

			Quad q(quadSize,quadSize,quadSize,(Side)i);
			quad[i] = q;
		}
	}
	Cube(float x,float y, float z):x(x),y(y),z(z),quad(new Quad[6]){
		for(int i=0;i<6;i++)
		{
			Quad q(quadSize,quadSize,quadSize,(Side)i);
			quad[i] = q; 
		}
	}
	Quad get(Side s)
	{
		return quad[s];
	}
	void draw()
	{
		
		
		
		glPushMatrix();
		/*
		for(std::vector<int>::size_type i = 0; i != rotasyon.size();++i)
		{
			glRotatef(rotasyon[i].angle,rotasyon[i].x,rotasyon[i].y,rotasyon[i].z);
		}
		//Rotate r = rotasyon.back();
		//glRotatef(r.angle,r.x,r.y,r.z);
		for(int i=0;i<6;i++)
		{
			
			quad[i].draw();
		}
		glPopMatrix();
	}
	void turnX()
	{
		Quad q[6];
		for(int i=0;i<6;i++)
		{
			switch(i){
				case FRONT:
					q[i] = quad[RIGHT];
					break;
				case RIGHT:
					q[i] = quad[BACK];
					break;
				case LEFT:
					q[i] = quad[BACK];
					break;
				case BACK:
					q[i] = quad[RIGHT];
					break;
				case TOP :
					q[i] = quad[TOP];
					break;
				case BOTTOM:
					q[i] = quad[BOTTOM];
			}
		}
		for(int i=0;i<6;i++)
			quad[i] = q[i];
	}
	void printQuads()
	{
		for(int i=0;i<6;i++)
			printf("Side : %d \n",quad[i].side);
	}
	void turnY()
	{
		Quad q[6];
		for(int i=0;i<6;i++)
		{
			switch(i){
				case FRONT:
					q[i] = quad[BOTTOM];
					break;
				case RIGHT:
					q[i] = quad[RIGHT];
					break;
				case LEFT:
					q[i] = quad[LEFT];
					break;
				case BACK:
					q[i] = quad[TOP];
					break;
				case TOP :
					q[i] = quad[FRONT];
					break;
				case BOTTOM:
					q[i] = quad[BACK];
			}
		}
		for(int i=0;i<6;i++)
			quad[i] = q[i];
	}
	void addrotate(Rotate r)
	{
		rotasyon.push_back(r);
	}
};

class Rubik
{
private: 
	Cube *kup;
public:
	Rubik():kup(new Cube[27]){
		for(int i=0;i<27;i++)
		{
			Cube c;
			kup[i] = c; 
		}
	}
	void draw(){
		int index = 0;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				for(int k=0;k<3;k++)
				{
					glPushMatrix();
					glTranslatef((quadSize + 0.11f) * i,(quadSize + 0.11f) * j,(quadSize + 0.11f) * k);
					kup[index++].draw();
					glColor3f (0.1F, 0.1F, 0.1F);
					glLineWidth(4.0);
					glutWireCube(quadSize +0.11f);
					glLineWidth(1.0);
					glPopMatrix();
				}
			}
			
		}
	}
	void rotateBlock(int rotate) //klavye
	{

		Rotate r1;
		r1.angle = -90;
		r1.z = 1;
		r1.x = 1;
		Rotate r2;
		r2.angle = -90;
		r2.z = 1;
		r2.y = 1;
			switch(rotate)
			{
			case 0:
				{
				
					for(int i=0;i<9;i++)
						kup[i].turnX();
					//kup[18].turnX();
					kup[0].addrotate(r1);
					kup[1].addrotate(r1);
				printf("here..");
				}
					break;
			case 1:
				for(int i=9;i<18;i++)
					kup[i].addrotate(r2);
				break;
			case 2:
				for(int i=18;i<27;i++)
					kup[i].addrotate(r2);
				break;
			case 3:
				{
				int kups[9] = {0,1,2,9,10,11,18,19,20};
				for(int i=0;i<9;i++)
					kup[kups[i]].addrotate(r1);
				}
				break;
			case 4:
				kup[1].addrotate(r1);
				kup[4].addrotate(r1);
				kup[7].addrotate(r1);
				kup[10].addrotate(r1);
				kup[13].addrotate(r1);
				kup[16].addrotate(r1);
				kup[19].addrotate(r1);
				kup[22].addrotate(r1);
				kup[25].addrotate(r1);
				break;
			case 5:
				kup[2].addrotate(r1);
				kup[5].addrotate(r1);
				kup[8].addrotate(r1);
				kup[11].addrotate(r1);
				kup[14].addrotate(r1);
				kup[17].addrotate(r1);
				kup[20].addrotate(r1);
				kup[23].addrotate(r1);
				kup[26].addrotate(r1);
				break;

			}
		
			//Turuncu //top 0
			//beyaz bottom 1
		    //Yeþil right 2
		    //mavi left 3
		   //sarý front 4
          //Kýrmýzý back  5
				
	}
};
Rubik *rub = new Rubik();

void locateCamera()
{
	
	
	glRotatef(camy,0,1,0);
	glRotatef(camx,1,0,0);
	
}
void display(){
	//printf("display...");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	locateCamera();
	glPushMatrix();
	glTranslatef((-quadSize) * 2.5,(-quadSize) * 3,0); //ortala
	
	glPopMatrix();
		rub->draw();

	glutSwapBuffers();
	glFlush();
}
void processNormalKeys(unsigned char key, int x, int y)
{
	
	//printf("increment %d",increment);
	//rub->rotateBlock(increment++);
	switch(key)
	{
	case 'z':
		rub->rotateBlock(3);
		break;
	case 'a':
		rub->rotateBlock(4);
		break;
	case 'q':
		rub->rotateBlock(5);
		break;
	case 's':
		rub->rotateBlock(0);
		break;
	case 'd':
		rub->rotateBlock(1);
		break;
	case 'f':
		rub->rotateBlock(2);
		break;
	}
	glutPostRedisplay();
}
void processSpecialKeys(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		camy += 30.f;
		
		break;
	case GLUT_KEY_RIGHT:
		camy -= 30.f;
		
		break;
	case GLUT_KEY_UP:
		camx -= 30.f;
		
		break;
	case GLUT_KEY_DOWN:	
		
		camx += 30.f;
		break;
	}
	glutPostRedisplay();
}*/

float colors[7][3] = {
		{0.9,0.9,0.9},
		{1.0,0.5,0.0},
		{0.0,0.0,1.0},
		{1.0,0.0,0.0},
		{1.0,1.0,0.0},
		{0.0,1.0,0.0},
		{0.3,0.3,0.3}
};
float 	viewx = -20.0;
int 	winWidth, winHeight;
float 	camx = 0.f,camy = 0.f;


int surfaces[6][9];
int tempsurfaces[6][9];

int initsurfaces[6][9]={
		{0,1,2,5,8,7,6,3,4},
		{23,24,25,22,19,18,17,20,21},
		{0,3,6,14,23,20,17,9,12},
		{8,5,2,11,19,22,25,16,13},
		{6,7,8,16,25,24,23,14,15},
		{2,1,0,9,17,18,19,11,10}};
int colorOfFace[6][9];
int initColorOfFace[6][9]={
		{WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
		{ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE},
		{BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE},
		{RED,RED,RED,RED,RED,RED,RED,RED,RED},
		{YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW},
		{GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN}
};
int tempOfColor[6][9];



float initialPos[26][3] = {
		{-quadPos, quadPos, -quadPos},
		{0,quadPos, -quadPos},
		{quadPos, quadPos, -quadPos},
		{-quadPos, quadPos, 0},
		{0, quadPos, 0},
		{quadPos, quadPos, 0},
		{-quadPos, quadPos, quadPos},
		{0, quadPos, quadPos},
		{quadPos, quadPos, quadPos},
		{-quadPos,0, -quadPos},
		{0, 0, -quadPos},
		{quadPos, 0, -quadPos},
		{-quadPos, 0, 0},
		{quadPos, 0, 0},
		{-quadPos, 0, quadPos},
		{0, 0, quadPos},
		{quadPos, 0, quadPos},
		{-quadPos,-quadPos, -quadPos},
		{0, -quadPos, -quadPos},
		{quadPos, -quadPos, -quadPos},
		{-quadPos, -quadPos, 0},
		{0, -quadPos, 0},
		{quadPos, -quadPos, 0},
		{-quadPos, -quadPos, quadPos},
		{0, -quadPos, quadPos},
		{quadPos,-quadPos, quadPos}
};

float currentPos[26][3];
float tempPos[26][3];

int i,j;
void initCubes();
void init();
void rotateFace(int face);
void rotateColors(int face);
void isFinished();

bool userMove = false;

void rotateColors(int face){
	for(i=0;i<9;i++){
		tempOfColor[TOP][i] = colorOfFace[TOP][i];
		tempOfColor[BOTTOM][i] = colorOfFace[BOTTOM][i];
		tempOfColor[LEFT][i] = colorOfFace[LEFT][i];
		tempOfColor[RIGHT][i] = colorOfFace[RIGHT][i];
		tempOfColor[FRONT][i] = colorOfFace[FRONT][i];
		tempOfColor[BACK][i] = colorOfFace[BACK][i];

	}

	switch(face)
	{
	case TOP:
		for(i=0;i<8;i++)
			tempOfColor[TOP][i] = colorOfFace[TOP][(i+6) % 8];

		tempOfColor[LEFT][0] = colorOfFace[FRONT][0];
		tempOfColor[LEFT][1] = colorOfFace[FRONT][1];
		tempOfColor[LEFT][2] = colorOfFace[FRONT][2];

		tempOfColor[RIGHT][0] = colorOfFace[BACK][0];
		tempOfColor[RIGHT][1] = colorOfFace[BACK][1];
		tempOfColor[RIGHT][2] = colorOfFace[BACK][2];

		tempOfColor[FRONT][0] = colorOfFace[RIGHT][0];
		tempOfColor[FRONT][1] = colorOfFace[RIGHT][1];
		tempOfColor[FRONT][2] = colorOfFace[RIGHT][2];

		tempOfColor[BACK][0] = colorOfFace[LEFT][0];
		tempOfColor[BACK][1] = colorOfFace[LEFT][1];
		tempOfColor[BACK][2] = colorOfFace[LEFT][2];
		break;
	case BOTTOM:
		for(i=0;i<8;i++)
			tempOfColor[BOTTOM][i] = colorOfFace[BOTTOM][(i+6) % 8];

		tempOfColor[LEFT][6] = colorOfFace[BACK][6];
		tempOfColor[LEFT][5] = colorOfFace[BACK][5];
		tempOfColor[LEFT][4] = colorOfFace[BACK][4];

		tempOfColor[RIGHT][6] = colorOfFace[FRONT][6];
		tempOfColor[RIGHT][5] = colorOfFace[FRONT][5];
		tempOfColor[RIGHT][4] = colorOfFace[FRONT][4];

		tempOfColor[FRONT][6] = colorOfFace[LEFT][6];
		tempOfColor[FRONT][5] = colorOfFace[LEFT][5];
		tempOfColor[FRONT][4] = colorOfFace[LEFT][4];

		tempOfColor[BACK][6] = colorOfFace[RIGHT][6];
		tempOfColor[BACK][5] = colorOfFace[RIGHT][5];
		tempOfColor[BACK][4] = colorOfFace[RIGHT][4];
		break;
	case LEFT:
		for(i=0;i<8;i++)
			tempOfColor[LEFT][i] = colorOfFace[LEFT][(i+6) % 8];

		tempOfColor[TOP][6] = colorOfFace[BACK][2];
		tempOfColor[TOP][7] = colorOfFace[BACK][3];
		tempOfColor[TOP][0] = colorOfFace[BACK][4];

		tempOfColor[BOTTOM][6] = colorOfFace[FRONT][6];
		tempOfColor[BOTTOM][7] = colorOfFace[FRONT][7];
		tempOfColor[BOTTOM][0] = colorOfFace[FRONT][0];

		tempOfColor[FRONT][6] = colorOfFace[TOP][6];
		tempOfColor[FRONT][7] = colorOfFace[TOP][7];
		tempOfColor[FRONT][0] = colorOfFace[TOP][0];

		tempOfColor[BACK][2] = colorOfFace[BOTTOM][6];
		tempOfColor[BACK][3] = colorOfFace[BOTTOM][7];
		tempOfColor[BACK][4] = colorOfFace[BOTTOM][0];
		break;
	case RIGHT:
		for(i=0;i<8;i++)
			tempOfColor[RIGHT][i] = colorOfFace[RIGHT][(i+6) % 8];

		tempOfColor[TOP][2] = colorOfFace[FRONT][2];
		tempOfColor[TOP][3] = colorOfFace[FRONT][3];
		tempOfColor[TOP][4] = colorOfFace[FRONT][4];

		tempOfColor[BOTTOM][2] = colorOfFace[BACK][6];
		tempOfColor[BOTTOM][3] = colorOfFace[BACK][7];
		tempOfColor[BOTTOM][4] = colorOfFace[BACK][0];

		tempOfColor[FRONT][2] = colorOfFace[BOTTOM][2];
		tempOfColor[FRONT][3] = colorOfFace[BOTTOM][3];
		tempOfColor[FRONT][4] = colorOfFace[BOTTOM][4];

		tempOfColor[BACK][0] = colorOfFace[TOP][4];
		tempOfColor[BACK][7] = colorOfFace[TOP][3];
		tempOfColor[BACK][6] = colorOfFace[TOP][2];
		break;
	case FRONT:
		for(i=0;i<8;i++)
			tempOfColor[FRONT][i] = colorOfFace[FRONT][(i+6) % 8];

		tempOfColor[TOP][6] = colorOfFace[LEFT][4];
		tempOfColor[TOP][5] = colorOfFace[LEFT][3];
		tempOfColor[TOP][4] = colorOfFace[LEFT][2];

		tempOfColor[BOTTOM][0] = colorOfFace[RIGHT][6];
		tempOfColor[BOTTOM][1] = colorOfFace[RIGHT][7];
		tempOfColor[BOTTOM][2] = colorOfFace[RIGHT][0];

		tempOfColor[LEFT][2] = colorOfFace[BOTTOM][0];
		tempOfColor[LEFT][3] = colorOfFace[BOTTOM][1];
		tempOfColor[LEFT][4] = colorOfFace[BOTTOM][2];

		tempOfColor[RIGHT][6] = colorOfFace[TOP][4];
		tempOfColor[RIGHT][7] = colorOfFace[TOP][5];
		tempOfColor[RIGHT][0] = colorOfFace[TOP][6];
		break;
	case BACK:
		for(i=0;i<8;i++)
			tempOfColor[BACK][i] = colorOfFace[BACK][(i+6) % 8];

		tempOfColor[TOP][0] = colorOfFace[RIGHT][2];
		tempOfColor[TOP][1] = colorOfFace[RIGHT][3];
		tempOfColor[TOP][2] = colorOfFace[RIGHT][4];

		tempOfColor[BOTTOM][4] = colorOfFace[LEFT][6];
		tempOfColor[BOTTOM][5] = colorOfFace[LEFT][7];
		tempOfColor[BOTTOM][6] = colorOfFace[LEFT][0];

		tempOfColor[LEFT][0] = colorOfFace[TOP][2];
		tempOfColor[LEFT][7] = colorOfFace[TOP][1];
		tempOfColor[LEFT][6] = colorOfFace[TOP][0];

		tempOfColor[RIGHT][2] = colorOfFace[BOTTOM][4];
		tempOfColor[RIGHT][3] = colorOfFace[BOTTOM][5];
		tempOfColor[RIGHT][4] = colorOfFace[BOTTOM][6];
		break;
	}
	for (i=0;i<6;i++){
		for (j=0;j<9;j++)
		{
			colorOfFace[i][j]= tempOfColor[i][j];
		}
	}
}

void drawCube(int cubeId){
	int i,j;
	int temp[6];
	for(i=0;i<6;i++){
		temp[i] = GRAY;
		for(j=0;j<9;j++){
			if(cubeId == surfaces[i][j]){
				temp[i] = colorOfFace[i][j];
			}
		}
	}

	glBegin(GL_QUADS);
	//Top
	glColor3fv(colors[temp[TOP]]);
	glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(-quadSize / 2, quadSize / 2, -quadSize / 2);
	glVertex3f(-quadSize / 2, quadSize / 2, quadSize / 2);
	glVertex3f(quadSize / 2, quadSize / 2, quadSize / 2);
	glVertex3f(quadSize / 2, quadSize / 2, -quadSize / 2);
	//Bottom
	glColor3fv(colors[temp[BOTTOM]]);
	glNormal3f(0.0, -1.0f, 0.0f);
	glVertex3f(-quadSize / 2, -quadSize / 2, -quadSize / 2);
	glVertex3f(quadSize / 2, -quadSize / 2, -quadSize / 2);
	glVertex3f(quadSize / 2, -quadSize / 2, quadSize / 2);
	glVertex3f(-quadSize / 2, -quadSize / 2, quadSize / 2);
	//Left
	glColor3fv(colors[temp[LEFT]]);
	glNormal3f(-1.0, 0.0f, 0.0f);
	glVertex3f(-quadSize / 2, -quadSize / 2, -quadSize / 2);
	glVertex3f(-quadSize / 2, -quadSize / 2, quadSize / 2);
	glVertex3f(-quadSize / 2, quadSize / 2, quadSize / 2);
	glVertex3f(-quadSize / 2, quadSize / 2, -quadSize / 2);
	//Right
	glColor3fv(colors[temp[RIGHT]]);
	glNormal3f(1.0, 0.0f, 0.0f);
	glVertex3f(quadSize / 2, -quadSize / 2, -quadSize / 2);
	glVertex3f(quadSize / 2, quadSize / 2, -quadSize / 2);
	glVertex3f(quadSize / 2, quadSize / 2, quadSize / 2);
	glVertex3f(quadSize / 2, -quadSize / 2, quadSize / 2);
	//Front
	glColor3fv(colors[temp[FRONT]]);
	glNormal3f(0.0, 0.0f, 1.0f);
	glVertex3f(-quadSize / 2, -quadSize / 2, quadSize / 2);
	glVertex3f(quadSize / 2, -quadSize / 2, quadSize / 2);
	glVertex3f(quadSize / 2,quadSize / 2, quadSize / 2);
	glVertex3f(-quadSize / 2, quadSize / 2, quadSize / 2);
	//Back
	glColor3fv(colors[temp[BACK]]);
	glNormal3f(0.0, 0.0f, -1.0f);
	glVertex3f(-quadSize / 2, -quadSize / 2, -quadSize / 2);
	glVertex3f(-quadSize / 2, quadSize / 2, -quadSize / 2);
	glVertex3f(quadSize / 2, quadSize / 2, -quadSize / 2);
	glVertex3f(quadSize / 2, -quadSize / 2, -quadSize / 2);

	glEnd();

}

void rotateFace(int face){
	for(i=0;i<9;i++){
		tempsurfaces[TOP][i] = surfaces[TOP][i];
		tempsurfaces[BOTTOM][i] = surfaces[BOTTOM][i];
		tempsurfaces[LEFT][i] = surfaces[LEFT][i];
		tempsurfaces[RIGHT][i] = surfaces[RIGHT][i];
		tempsurfaces[FRONT][i] = surfaces[FRONT][i];
		tempsurfaces[BACK][i] = surfaces[BACK][i];
	}

	switch(face)
	{
	case TOP:
		for(i=0;i<8;i++)
			tempsurfaces[TOP][i] = surfaces[TOP][(i+6) % 8];

		tempsurfaces[LEFT][0] = surfaces[TOP][6];
		tempsurfaces[LEFT][1] = surfaces[TOP][5];
		tempsurfaces[LEFT][2] = surfaces[TOP][4];

		tempsurfaces[RIGHT][0] = surfaces[TOP][2];
		tempsurfaces[RIGHT][1] = surfaces[TOP][1];
		tempsurfaces[RIGHT][2] = surfaces[TOP][0];

		tempsurfaces[FRONT][0] = surfaces[TOP][4];
		tempsurfaces[FRONT][1] = surfaces[TOP][3];
		tempsurfaces[FRONT][2] = surfaces[TOP][2];

		tempsurfaces[BACK][0] = surfaces[TOP][0];
		tempsurfaces[BACK][1] = surfaces[TOP][7];
		tempsurfaces[BACK][2] = surfaces[TOP][6];
		break;
	case BOTTOM:
		for(i=0;i<8;i++)
			tempsurfaces[BOTTOM][i] = surfaces[BOTTOM][(i+6) % 8];

		tempsurfaces[LEFT][6] = surfaces[BOTTOM][4];
		tempsurfaces[LEFT][5] = surfaces[BOTTOM][5];
		tempsurfaces[LEFT][4] = surfaces[BOTTOM][6];

		tempsurfaces[RIGHT][6] = surfaces[BOTTOM][0];
		tempsurfaces[RIGHT][5] = surfaces[BOTTOM][1];
		tempsurfaces[RIGHT][4] = surfaces[BOTTOM][2];

		tempsurfaces[FRONT][6] = surfaces[BOTTOM][6];
		tempsurfaces[FRONT][5] = surfaces[BOTTOM][7];
		tempsurfaces[FRONT][4] = surfaces[BOTTOM][0];

		tempsurfaces[BACK][6] = surfaces[BOTTOM][2];
		tempsurfaces[BACK][5] = surfaces[BOTTOM][3];
		tempsurfaces[BACK][4] = surfaces[BOTTOM][4];
		break;
	case LEFT:
		for(i=0;i<8;i++)
			tempsurfaces[LEFT][i] = surfaces[LEFT][(i+6) % 8];

		tempsurfaces[TOP][6] = surfaces[LEFT][0];
		tempsurfaces[TOP][7] = surfaces[LEFT][7];
		tempsurfaces[TOP][0] = surfaces[LEFT][6];

		tempsurfaces[BOTTOM][6] = surfaces[LEFT][4];
		tempsurfaces[BOTTOM][7] = surfaces[LEFT][3];
		tempsurfaces[BOTTOM][0] = surfaces[LEFT][2];

		tempsurfaces[FRONT][6] = surfaces[LEFT][2];
		tempsurfaces[FRONT][7] = surfaces[LEFT][1];
		tempsurfaces[FRONT][0] = surfaces[LEFT][0];

		tempsurfaces[BACK][2] = surfaces[LEFT][6];
		tempsurfaces[BACK][3] = surfaces[LEFT][5];
		tempsurfaces[BACK][4] = surfaces[LEFT][4];
		break;
	case RIGHT:
		for(i=0;i<8;i++)
			tempsurfaces[RIGHT][i] = surfaces[RIGHT][(i+6) % 8];

		tempsurfaces[TOP][2] = surfaces[RIGHT][0];
		tempsurfaces[TOP][3] = surfaces[RIGHT][7];
		tempsurfaces[TOP][4] = surfaces[RIGHT][6];

		tempsurfaces[BOTTOM][2] = surfaces[RIGHT][4];
		tempsurfaces[BOTTOM][3] = surfaces[RIGHT][3];
		tempsurfaces[BOTTOM][4] = surfaces[RIGHT][2];

		tempsurfaces[FRONT][2] = surfaces[RIGHT][6];
		tempsurfaces[FRONT][3] = surfaces[RIGHT][5];
		tempsurfaces[FRONT][4] = surfaces[RIGHT][4];

		tempsurfaces[BACK][0] = surfaces[RIGHT][0];
		tempsurfaces[BACK][7] = surfaces[RIGHT][1];
		tempsurfaces[BACK][6] = surfaces[RIGHT][2];
		break;
	case FRONT:
		for(i=0;i<8;i++)
			tempsurfaces[FRONT][i] = surfaces[FRONT][(i+6) % 8];

		tempsurfaces[TOP][6] = surfaces[FRONT][6];
		tempsurfaces[TOP][5] = surfaces[FRONT][7];
		tempsurfaces[TOP][4] = surfaces[FRONT][0];

		tempsurfaces[BOTTOM][0] = surfaces[FRONT][4];
		tempsurfaces[BOTTOM][1] = surfaces[FRONT][3];
		tempsurfaces[BOTTOM][2] = surfaces[FRONT][2];

		tempsurfaces[LEFT][2] = surfaces[FRONT][6];
		tempsurfaces[LEFT][3] = surfaces[FRONT][5];
		tempsurfaces[LEFT][4] = surfaces[FRONT][4];

		tempsurfaces[RIGHT][6] = surfaces[FRONT][2];
		tempsurfaces[RIGHT][7] = surfaces[FRONT][1];
		tempsurfaces[RIGHT][0] = surfaces[FRONT][0];
		break;
	case BACK:
		for(i=0;i<8;i++)
			tempsurfaces[BACK][i] = surfaces[BACK][(i+6) % 8];

		tempsurfaces[TOP][0] = surfaces[BACK][0];
		tempsurfaces[TOP][1] = surfaces[BACK][7];
		tempsurfaces[TOP][2] = surfaces[BACK][6];

		tempsurfaces[BOTTOM][4] = surfaces[BACK][4];
		tempsurfaces[BOTTOM][5] = surfaces[BACK][3];
		tempsurfaces[BOTTOM][6] = surfaces[BACK][2];

		tempsurfaces[LEFT][0] = surfaces[BACK][0];
		tempsurfaces[LEFT][7] = surfaces[BACK][1];
		tempsurfaces[LEFT][6] = surfaces[BACK][2];

		tempsurfaces[RIGHT][2] = surfaces[BACK][6];
		tempsurfaces[RIGHT][3] = surfaces[BACK][5];
		tempsurfaces[RIGHT][4] = surfaces[BACK][4];
		break;
	}
	
	for (i=0;i<6;i++){
		for (j=0;j<9;j++)
		{
			int previous = surfaces[i][j];
			int current = tempsurfaces[i][j];
			surfaces[i][j]= current;

			int k;
			for (k=0;k<3;k++){
				tempPos[current][k] = currentPos[previous][k];

			}
		}
	}
}
void clickFace(int face)
{
		rotateColors(face);
		rotateFace(face);
		if(userMove)
			isFinished();
}
void printInfo(){
	printf("-----------------------\n");
	printf("Q - turn front face");
	printf("E - turn back face\n");
	printf("W - turn top face\n");
	printf("S turn bottom face\n");
	printf("A turn left face\n");
	printf("D turn right face\n");
	printf("Keyboard directional keys change the camera position\n");
	printf("F initializes the rubik default\n");
	printf("R turn rubik cube randomly\n");
	printf("ESC - exit\n");

}

float counter = 0.f;
void animate(int face)
{
	
}

void turnRandomly()
{
	int turnCount = 3;
	int face;
	for(i=0;i<turnCount;i++)
	{
		face = rand() % 6;
		clickFace(face);
	}
}
void processNormalKeys(unsigned char key, int x, int y) {
	
	switch (key) {
	case 'w':
		userMove = true;
		clickFace(TOP);
		userMove = false;
	break;
	case 'a':
		userMove = true;
		clickFace(LEFT);
		userMove = false;
		break;
	case 'd':
		userMove = true;
		clickFace(RIGHT);
		userMove = false;
		break;
	case 's':
		userMove = true;
		clickFace(BOTTOM);
		userMove = false;
		break;
	case 'q':
		userMove = true;
		clickFace(FRONT);
		userMove = false;
		break;
	case 'e':
		userMove = true;
		clickFace(BACK);
		userMove = false;
		break;
	case 'r':
		//random
		turnRandomly();
		break;
	case 'f':
		//baþlangýç
		initCubes();
		break;
	case 'h':
		printInfo();
		break;
	case 27: //Esc
		exit(0);
	}
	for(int a=0;a<26;a++){
		for(int b=0;b<3;b++){
			currentPos[a][b] = tempPos[a][b];
		}
	}
	glutPostRedisplay();
}
void processSpecialKeys(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		camy -= 30.f;
		
		break;
	case GLUT_KEY_RIGHT:
		camy += 30.f;
		
		break;
	case GLUT_KEY_UP:
		camx += 30.f;
		
		break;
	case GLUT_KEY_DOWN:	
		
		camx -= 30.f;
		break;
	}
	glutPostRedisplay();
}
void initCubes(){

	for (i=0;i<26;i++)
		for (j=0;j<3;j++){

			currentPos[i][j] = initialPos[i][j];
			tempPos[i][j] = initialPos[i][j];
		}

	for (i=0;i<6;i++)
		for (j=0;j<9;j++){

			surfaces[i][j] = initsurfaces[i][j];
			tempsurfaces[i][j] = initsurfaces[i][j];
			colorOfFace[i][j] = initColorOfFace[i][j];
		}
}
void locateCamera()
{
	glRotatef(camy,0,1,0);
	glRotatef(camx,1,0,0);
	
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	winWidth = w;
	winHeight = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void initializeTextures()
{
	image_t temp_image;

	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	tgaLoad("kub.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY | TGA_NO_MIPMAPS);
	glDisable(GL_TEXTURE_2D);
}

void init(){

	initializeTextures();

	glShadeModel(GL_SMOOTH);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST); //renklerin karýþmasý düzeldi
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
}
void isFinished()
{
	bool flag = false; //içteki döngüyü bitirdiðimizde dýþtakide bitmeli
	for(i=0;i<6;i++)
	{
		for(j=0;j<9;j++)
		{
			if(colorOfFace[i][j] != colorOfFace[i][(j+1)%9])
			{
				flag = true;
				break;
			}
		}
		if(flag)
			break;
	}
	//printf("%d \n",i);
	if(i==6)
		printf("\n##################\nCongratulations! You've solved the cube.\n##################\n");
}

void drawRotationCube()
{

	glEnable(GL_TEXTURE_2D);
	glColor3f(.9f, .9f, .9f);

	glPushMatrix();

	glTranslatef( 7.0, 0.0, -5.0 );
	glRotatef(-12.5,0.0,1.0,0.0);
	glScalef(.8f, .8f, .8f);
	glBindTexture (GL_TEXTURE_2D, texture_id[0]);

	locateCamera();
	
	glBegin ( GL_QUADS );
	
	glTexCoord2f(0.25, 0.215);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(0.75, 0.215);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(0.75, 0.41);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.25, 0.41);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	
	
	glTexCoord2f(0.25,0.97);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.25,0.78);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.75,0.78);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.75,0.97);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	
	
	glTexCoord2f(0.25,0.78 );
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.25,0.41 );
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.75,0.41 );
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.75,0.78);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	
	
	glTexCoord2f(0.25,0.032);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.75,0.032);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.75,0.215);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(0.25,0.215);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	
	
	glTexCoord2f(1,0.78);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.75,0.78 );
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.75,0.4);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1,0.4);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	
	
	glTexCoord2f(0, 0.78);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0, 0.4);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(0.25, 0.4);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.25, 0.78);
	glVertex3f(-1.0f,  1.0f, -1.0f);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void display() {

	

	glClearColor (1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, viewx);

	init();
	drawRotationCube();
	locateCamera();
	

	glPushMatrix();
		for(i=0; i < 26; i++){
			glPushMatrix();

			glTranslatef(currentPos[i][0],
					currentPos[i][1],
					currentPos[i][2]);
			glColor3f (0.1F, 0.1F, 0.1F);
			glLineWidth(4.0);
			glutWireCube(quadSize+0.01f);
			glLineWidth(1.0);
			drawCube(i);

			glPopMatrix();
		}
	glPopMatrix();
	glFlush();

	glutSwapBuffers();
}


int main(int argc, char** argv) {

	srand((unsigned)time(NULL));
	printInfo();
	// init GLUT and create window

	glutInit(&argc, argv);// don't remove this line

	initCubes();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	init();// Initialize OpenGL state in this
	// register callbacks
	// you can remove the ones that you don't need and add other ones here 
	// you do these here once and forget about glut
	// glut will call them when they are needed
	glutInitWindowSize(600, 600);
	glutCreateWindow("GLUT Window");
	glutIdleFunc( NULL );
	glutDisplayFunc( display );
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glutReshapeFunc( reshape );

	// enter GLUT event processing cycle. you no more have control. glut does.
	glutMainLoop();
	return 0;
}
