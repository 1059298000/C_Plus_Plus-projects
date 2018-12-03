// chafenMul.h: interface for the chafenMul class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAFENMUL_H__3A0FE375_9E4F_481E_A5DD_D7080D40028E__INCLUDED_)
#define AFX_CHAFENMUL_H__3A0FE375_9E4F_481E_A5DD_D7080D40028E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ChafenMul{
public:

	ChafenMul(int width,int height,int targetThreshold);
	~ChafenMul();
public:

	unsigned char *frame1; //��1֡����
	unsigned char *frame2; //��2֡����
	unsigned char *frame3; //��3֡����
	unsigned char *frame4; //��4֡����

	int frameWidth; int frameHeight; //֡��Ⱥ͸߶�

	int readyCount;       //����֡������

	int targetThreshold;  //Ŀ������ֵ
public:
	void PrepareData(unsigned char *buffer,int width,int height);

	void process();
	

};
#endif // !defined(AFX_CHAFENMUL_H__3A0FE375_9E4F_481E_A5DD_D7080D40028E__INCLUDED_)
