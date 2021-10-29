#include "pch.h"
#include "Lab.h"

void DrawTriangle() {
	glBegin(GL_TRIANGLES);
	glNormal3f(0.577, 0.577, 0.577);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();
}
void DrawTriangle2() {
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 1, 1);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}
void getNormalVector(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[]) {
	// �� �������� �Ÿ�
	GLfloat e1[] = { v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2] }; //v2-v1
	GLfloat e2[] = { v1[0] - v3[0], v1[1] - v3[1], v1[2] - v3[2] };//v3-v1

	// ����
	normal[0] = e1[1] * e2[2] - e1[2] * e2[1];
	normal[1] = e1[2] * e2[0] - e1[0] * e2[2];
	normal[2] = e1[0] * e2[1] - e1[1] * e2[0];
}

void draw_line() {
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

void Lab::draw_lab1() {
	//opengl ��ġ
}

// ���簢��, ������ü, ����
void Lab::draw_lab2() {
	//gluLookAt(0.f, 0.f, 4.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-5.0,-3.0, -3.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 3.0, -3.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(5, -3.0, -3.0);
	glEnd();

	//���ĺ���(�ﰢ�� �ΰ� ���� ���̰�)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLES);
	// �� �� ���� �׸���.
	glColor4f(0.0, 0, 1, 0.5);
	glVertex3f(-1, 0, -1);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 1, -1);


	glColor4f(1.0, 0, 0, 0.5);
	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 1, 0);

	glEnd();

	float vertices[][3] = {
		{-0.5, -0.5, -0.5},	//0
		{-0.5, 0.5, -0.5},	//1
		{-0.5, 0.5, 0.5},	//2
		{-0.5, -0.5, 0.5},	//3
		{0.5, -0.5, -0.5},	//4
		{0.5, 0.5, -0.5},	//5
		{0.5, 0.5, 0.5},	//6
		{0.5, -0.5, 0.5},	//7
	};

	//ť�� �׸���- ����ü 
	glBegin(GL_QUADS);
		// �� �� ��
		glColor3f(0.0, 0.0, 0.5);
		glVertex3fv(vertices[0]);// �ð� �ݴ� �������
		glVertex3fv(vertices[1]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[3]);
		// TOP
		glColor3f(0.0, 0.0, 1.0);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[7]);
		glVertex3fv(vertices[6]);
		// left
		glColor3f(0.0, 1.0, 0.0);
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[7]);
		//
		glColor3f(0.0, 0.5, 0.0);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[5]);
		glVertex3fv(vertices[6]);
		glVertex3fv(vertices[7]);
		// TOP
		glColor3f(1.0, 0.0, 0.0);
		glVertex3fv(vertices[1]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[6]);
		glVertex3fv(vertices[5]);
		// TOP
		glColor3f(0.5, 0.0, 0.0);
		glVertex3fv(vertices[5]);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[1]);
	glEnd();
}

//LIGHTING( PHONG MODEL )
void Lab::draw_lab3() {
	//gluLookAt(0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

	// 1. Enable lighting
	glEnable(GL_LIGHTING);

	//4. Set light color
	GLfloat colorWhite[] = { 1.f, 1.f, 1.f, 1.0 };
	GLfloat green[] = { 0.0, 1.f, 0.0, 1.0 };
	GLfloat blue[] = { 0.f, 0.f, 1.f, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, green);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT0, GL_SPECULAR, colorWhite);

	//3. Set light position
	GLfloat lightPosition[] = { 0,-0.5,0,1 }; // �̰� �ٲٴϱ� �ȴ�.. 0.1.0
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// 2. Select light source
	glEnable(GL_LIGHT0);

	//draw
	glBegin(GL_TRIANGLES);
	GLfloat v1[] = { 1, -1, -1 };
	GLfloat v2[] = { -1, -1, -1 };
	GLfloat v3[] = { -1, 1, -1 };
	GLfloat v4[] = { 1, 1, -1 };

	GLfloat normal[3];
	getNormalVector(v1, v2, v3, normal);
	glNormal3f(0, 0, 0);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);

	getNormalVector(v1, v3, v4, normal);
	glNormal3fv(normal);
	glVertex3fv(v1);
	glVertex3fv(v3);
	glVertex3fv(v4);

	//5. Set material color(�ݻ���)
	GLfloat no_mat[] = { 0.0,0.0,0.0, 1.0 };
	GLfloat mat_emission[] = { 0.2, 0.2, 0.2, 0.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //�ݻ籤
	GLfloat high_shininess[] = { 5.0 };	//����
	//glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat); //�ֺ���
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //�߻걤
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glEnd();


}

// Transformation
void Lab::draw_lab4() {
	//glMatrixMode(GL_MODELVIEW); - ReSizeGLScene()s
	//glLoadIdentity();

	gluLookAt(0.f, 0.f, 5.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

	//draw
	glColor3f(0, 0, 1);
	DrawTriangle();

	glColor3f(0, 1, 0);
	glRotatef(145, 0, 0, 1);
	DrawTriangle();

	glColor3f(1, 1, 1);
	glRotatef(-145, 0, 0, 1);
	glTranslatef(1, 0, 0);
	DrawTriangle();

	
	glColor3f(0.8, 0.8, 1);
	glTranslatef(1, 0, 0);
	glScalef(2, 2, 2);
	DrawTriangle();
	//glMultMatrixf(matrix_mul); //��İ�
}

void testLighting() {
	GLfloat ambient[4] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat specular[4] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat position[4] = { 6.0, 6.0, 5.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat mat_ambient[4] = { 0.2, 0.2, 0.2, 0.0 };
	GLfloat mat_diffuse[4] = { 0.6, 0.6, 0.6, 0.0 };
	GLfloat mat_specular[4] = { 0.2, 0.2, 0.2, 0.0 };
	GLfloat mat_emissive[4] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_shininess[1] = { 50.0 };
	//�ݻ��ų ��ü�ǻ�?
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emissive);
}


// Ű����, ���콺�� ī�޶� ȸ����Ű��
void Lab::draw_lab5() {
	draw_line();

	// �ﰢ�� ���� �׸���
	GLfloat mat_green[] = { 0, 1, 0, 0.0 };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_green);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glColor3fv(mat_green);
	DrawTriangle();

	GLfloat mat_red[] = { 1, 0, 0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_red);
	glColor3fv(mat_red);
	glRotatef(120, 0, 1, 0); // ����, ȸ����(y-axis)
	DrawTriangle();

	GLfloat mat_blue[] = { 0, 0, 1, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_blue);
	glColor3fv(mat_blue);
	glRotatef(120, 0, 1, 0); // ����, ȸ����(y-axis)
	DrawTriangle();
}


void Lab::draw_lab6() { // �ǽ� 6 (���ü �׸��� ī�޶� ��ǥ ��ȯ)
	/*1. ���ü�׸���
�������������void DrawTriangle() �Լ�����ǥ��ȯ�Լ������̿��Ͽ����ü���ϳ��׸��ÿ�.
-DrawTriangle()�������ﰢ�����׸�����������(1,0,0), 0,1,0), (0,0,1)
-�̶���ǥ��ȯ����Լ����ؾ��ϴ������̻���������ǥ��ȯ���ϰ���ü�ǰ������ϳ����׸��ÿ�.*/
	//specular!!!!!!!

	draw_line();
	GLfloat mat_green[] = { 0, 1, 0, 0.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_green);
	glColor3fv(mat_green);
	DrawTriangle2();

	glRotatef(60, 0, -1, -1);
	//glRotatef(30, 0, 1, 0);
	GLfloat blue[] = { 0, 0, 1, 0.0 };
	glColor3fv(blue);
	DrawTriangle2();

	GLfloat red[] = { 1, 0, 0, 0.0 };
	glColor3fv(red);
	glRotatef(50, 1, 1, 1);
	//DrawTriangle2();

	/*2. ī�޶���ǥ��ȯ�ϱ�
-gluLookAt() �Լ����Ķ���͸������Ͽ����ü��4���Ǵٸ����������������غ��ÿ�*/

	/*3. ī�޶�ȸ����
-������ȯ�����콺�����ؼ����Ͻÿ�.
-����Ŭ���ϰ����µ��ȿ����̸����ȸ���ǵ���.*/
}