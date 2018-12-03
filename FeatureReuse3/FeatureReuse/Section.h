#pragma once
#include "stdafx.h"
#include <vector>
#include "OpenGL\OpenGLDC.h"

class Section
{
public:
	Section();
	~Section();

	bool isModified;
	vector<int> Index; // ���ڴ洢ÿ����������˹�ϵ�������ţ�
	vector<CPoint2D> point_2D; // ����ƽ�������
	vector<CPoint2D> speed_2D;  // ƽ���ٶ�ʸ
	vector<double> strain;				// Ӧ��
	vector<double> stress;				// Ӧ��
};

