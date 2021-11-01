#pragma once
#include "StdAfx.h"


class B836042
{
public:
	GLfloat m_airplane_speed, m_speed; //����ü �ӵ�
	GLfloat m_countLeft, m_countRight, m_countUp, m_countDown; //����ü �̵�
	BOOL m_isLeft, m_isRight, m_isUp, m_isDown; //����ü ȸ��
	BOOL m_isMoved; 

	BOOL m_defaultMode;
	GLfloat m_positionY, m_positionZ;
public:
	void draw();

	void destroy();
	void initialize();

private:
	void init_triangle();
	void draw_airplane();
	void draw_space();
	void getNormalVector3f(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[]);
};