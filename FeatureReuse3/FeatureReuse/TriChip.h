#include "OpenGL\OpenGLDC.h"
#pragma once

class CTriChip
{
public:
	CTriChip();
	~CTriChip();

	CPoint3D  vex[3]; // Ĭ��STL�������� 
	CVector3D normal; // Ĭ��STL�����淨ʧ����

	CPoint3D  tri[3]; // ������Ƭ�������� 
	CPoint3D  fourFace[4]; //�������ĸ��ǵ����� 
};

