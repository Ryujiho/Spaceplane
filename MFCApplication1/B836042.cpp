#include "pch.h"
#include "B836042.h"

void draw_cube();
void draw_cube_quads();

void B836042::draw() {
	draw_line();
	draw_cube();
}
void getNormalVector3f(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[]) {
	// 두 정점간의 거리
	GLfloat e1[] = { v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2] }; //v2-v1
	GLfloat e2[] = { v1[0] - v3[0], v1[1] - v3[1], v1[2] - v3[2] };//v3-v1

	// 외적
	normal[0] = e1[1] * e2[2] - e1[2] * e2[1];
	normal[1] = e1[2] * e2[0] - e1[0] * e2[2];
	normal[2] = e1[0] * e2[1] - e1[1] * e2[0];
}

void twoLightsEnable()
{
	GLfloat light_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat light0_position[] = { 0.f, 2.f, 1.f, 1.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	GLfloat light_ambient[] = { 0.67,0.25,0.39, 1.0f };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { 3.f, 3.f, 6.f, 1.f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat high_shininess[] = { 70.0 };
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0};
	//glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
}

void spotLightEnable()
{
	GLfloat light_ambient[] = {0.2f, 0.5f, 0.7f, 1.0f};
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);

	GLfloat light_position[] = { 0.1f, 0.f, -1.f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	GLfloat light_spot_direction[] = { 0.f, 0.f, 1.f };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_spot_direction);
	 
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 24.f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.f);

	glEnable(GL_LIGHT1);
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
}

void draw_cube() 
{
	GLfloat v[][3] = {
		{-0.5, -0.5, -0.5}, //0 
		{-0.5, 0.5, -0.5},	//1
		{-0.5, 0.5, 0.5},	//2
		{-0.5, -0.5, 0.5},	//3
		{0.5, -0.5, -0.5},	//4
		{0.5, 0.5, -0.5},	//5
		{0.5, 0.5, 0.5},	//6
		{0.5, -0.5, 0.5}	//7
	};

	glEnable(GL_LIGHTING);
	//twoLightsEnable(); //light0, 1
	spotLightEnable(); //light5

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1.f);

	GLfloat normal[3];
	getNormalVector3f(v[0], v[1], v[2], normal);
	glNormal3fv(normal);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);
	glVertex3fv(v[2]);
	glVertex3fv(v[0]);
	glVertex3fv(v[2]);
	glVertex3fv(v[3]);

	getNormalVector3f(v[0], v[1], v[5], normal);
	glNormal3fv(normal);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);
	glVertex3fv(v[5]);
	glVertex3fv(v[0]);
	glVertex3fv(v[4]);
	glVertex3fv(v[5]);

	getNormalVector3f(v[1], v[2], v[6], normal);
	glNormal3fv(normal);
	glVertex3fv(v[1]);
	glVertex3fv(v[2]);
	glVertex3fv(v[6]);
	glVertex3fv(v[1]);
	glVertex3fv(v[5]);
	glVertex3fv(v[6]);

	getNormalVector3f(v[4], v[5], v[6], normal);
	glNormal3fv(normal);
	glVertex3fv(v[4]);
	glVertex3fv(v[5]);
	glVertex3fv(v[6]);
	glVertex3fv(v[4]);
	glVertex3fv(v[6]);
	glVertex3fv(v[7]);

	getNormalVector3f(v[0], v[4], v[7], normal);
	glNormal3fv(normal);
	glVertex3fv(v[0]);
	glVertex3fv(v[4]);
	glVertex3fv(v[7]);
	glVertex3fv(v[0]);
	glVertex3fv(v[3]);
	glVertex3fv(v[7]);

	getNormalVector3f(v[2], v[3], v[7], normal);
	glNormal3fv(normal);
	glVertex3fv(v[2]);
	glVertex3fv(v[3]);
	glVertex3fv(v[7]);
	glVertex3fv(v[2]);
	glVertex3fv(v[6]);
	glVertex3fv(v[7]);
	
	glEnd();
}

void draw_cube_quads() {
	GLfloat v[][3] = {
		{-0.5, -0.5, -0.5}, //0 
		{-0.5, 0.5, -0.5},	//1
		{-0.5, 0.5, 0.5},	//2
		{-0.5, -0.5, 0.5},	//3
		{0.5, -0.5, -0.5},	//4
		{0.5, 0.5, -0.5},	//5
		{0.5, 0.5, 0.5},	//6
		{0.5, -0.5, 0.5}	//7
	};

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3fv(v[0]); //좌
	glVertex3fv(v[1]);
	glVertex3fv(v[2]);
	glVertex3fv(v[3]);

	glColor3f(0, 1, 0);
	glVertex3fv(v[2]); //앞
	glVertex3fv(v[3]);
	glVertex3fv(v[7]);
	glVertex3fv(v[6]);

	glColor3f(0, 1, 0); 
	glVertex3fv(v[3]); //바닥
	glVertex3fv(v[0]);
	glVertex3fv(v[4]);
	glVertex3fv(v[7]);

	glColor3f(0, 1, 0);
	glVertex3fv(v[4]); //우
	glVertex3fv(v[5]);
	glVertex3fv(v[6]);
	glVertex3fv(v[7]);

	glColor3f(0, 1, 0);
	glVertex3fv(v[1]); //위
	glVertex3fv(v[2]);
	glVertex3fv(v[6]);
	glVertex3fv(v[5]);

	glColor3f(0, 1, 0);
	glVertex3fv(v[5]); //뒤
	glVertex3fv(v[4]);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);


	glEnd();
}

void B836042::draw_line() {
	glBegin(GL_LINES);
		GLfloat mat_green[] = { 0.f, 1.f, 0.f, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_green);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(10.f, 0.f, 0.f);
		glVertex3f(-10.f, 0.f, 0.f);

		GLfloat mat_red[] = { 1.f, 0.f, 0.f, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_red);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.f, 10.f, 0.f);
		glVertex3f(0.f, -10.f, 0.f);

		GLfloat mat_blue[] = { 0.f, 0.f, 1.f, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_blue);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.f, 10.f);
		glVertex3f(0.f, 0.f, -10.f);

	glEnd();

}

void B836042::destroy() {

}
void B836042::initialize() {

}