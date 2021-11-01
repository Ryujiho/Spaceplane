#include "pch.h"
#include "B836042.h"

GLuint triangle;

struct Point3D {
	GLfloat x, y, z;
};
void B836042::draw() {

	glPushMatrix();
		if (m_isMoved) {
			m_speed += m_airplane_speed;
			if (m_speed <= 0) m_speed = 0.1;
			m_airplane_speed = 0;
		}
		GLfloat dy = m_speed * m_countUp - m_speed * m_countDown;
		GLfloat dz = m_speed * m_countLeft - m_speed * m_countRight;

		glTranslatef(0, dy, dz);
		if (!m_defaultMode) {
			m_positionY = dy;
			m_positionZ = dz;
		}

		//default: left
		if (m_isRight) {
			glRotatef(180, 0, 1, 0);
		}
		else if (m_isUp) {
			glRotatef(-90, 1, 0, 0);
		}
		else if (m_isDown) {
			glRotatef(90, 1, 0, 0);
		}
		draw_airplane();	//비행체
	glPopMatrix();
	
	draw_space();		//우주 공간 - 행성, 항성, 운석 등
}

void B836042::draw_airplane() {
	init_triangle();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glCallList(triangle);

	glColor3f(1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glCallList(triangle);

	glColor3f(0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glCallList(triangle);

	glPopMatrix();
}

void B836042::init_triangle() {
	triangle = glGenLists(1);
	glNewList(triangle, GL_COMPILE);

	glBegin(GL_TRIANGLES);
	GLfloat v1[] = { 0, 0, 1.0 };
	GLfloat v2[] = { 0, 0, -0.5 };
	GLfloat v3[] = { -0.5, 0, -0.5 };
	GLfloat normal[3] = { 0, };
	getNormalVector3f(v1, v2, v3, normal);
	glNormal3f(normal[0], normal[1], normal[2]);

	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glEnd();

	glEndList();
}

void B836042::draw_space() {
	// 운석 그리기 - Callout하고 회전해서 그려도 될듯!
	Point3D mPointList[] = {
		{0, 0.5, 0},	{0.3,  0.5, 0},	{0,  0.5, 0.3}, //위1
		{0.5, 1.0, 0},	{0.3,  1.0, 0.5},	{0.5, 1.0, 0.3},//위2
		{0, -0.5, 0},	{0.3,  -0.5, 0},	{0,  -0.5, 0.3},//아래1
		{0.5, -1.0, 0},	{0.3,  -1.0, 0.5},	{0.5, -1.0, 0.3},//아래2
		{0.5, 0.3, 1.0},	{0.5, -0.3, 1.0},	{0.5, 0.4, 1.0}, //우측
		{1.5, 0.3, 0.0},	{1.5 -0.3, 0.0},	{1.5, 0.4, 0.0},
		{-0.5, 0.3, 1.0},	{-0.5, -0.3, 1.0},	{-0.5, 0.4, 1.0}, //좌측
		{-1.5, 0.3, 0.0},	{-1.5 - 0.3, 0.0},	{-1.5, 0.4, 0.0}
	};

	glBegin(GL_POINTS);
	glPointSize(10.0);
	for (int i = 0; i < sizeof(mPointList)/sizeof(Point3D); ++i)
		{
			glVertex3f(mPointList[i].x, mPointList[i].y, mPointList[i].z);
		}
	glEnd();

	glPushMatrix();
		glTranslatef(-3, 0, 0);
		glColor3f(1, 1, 0);
		GLUquadric* quad = gluNewQuadric();
		gluSphere(quad, 1.5, 100, 20);

		glTranslatef(0, 0, 3);
		glColor3f(1, 1, 1);
		gluSphere(quad, 1, 100, 20);

		glTranslatef(0, -3, 0);
		glColor3f(0, 0.5, 1);
		gluSphere(quad, 1, 100, 20);

		glTranslatef(3, 0, 0);
		glColor3f(0, 0.5, 0.5);
		gluSphere(quad, 1, 100, 20);

		glTranslatef(0, 0, -3);
		glColor3f(0.5, 0.5, 0.5);
		gluSphere(quad, 1, 100, 20);
	glPopMatrix();


	glEnable(GL_LINE_STIPPLE);
	glLineStipple(4, 0xAAAA);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex3f(10, 0, 0);
	glVertex3f(-10, 0, 0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void B836042::getNormalVector3f(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[]) {
	// 두 정점간의 거리
	GLfloat e1[] = { v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2] }; //v2-v1
	GLfloat e2[] = { v1[0] - v3[0], v1[1] - v3[1], v1[2] - v3[2] };//v3-v1

	// 외적
	normal[0] = e1[1] * e2[2] - e1[2] * e2[1];
	normal[1] = e1[2] * e2[0] - e1[0] * e2[2];
	normal[2] = e1[0] * e2[1] - e1[1] * e2[0];
}


void B836042::destroy() {

}
void B836042::initialize() {
	m_speed = 0.1f;
	m_airplane_speed = 0.f;

	m_countLeft = m_countRight = m_countUp = m_countDown = 0;
	m_isLeft = m_isRight = m_isUp = m_isDown = false;
	m_isMoved = false;
	m_defaultMode = true;
}