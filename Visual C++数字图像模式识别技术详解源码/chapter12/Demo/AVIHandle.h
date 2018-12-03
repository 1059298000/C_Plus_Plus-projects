// AVIHandle.h: interface for the AVIHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVIHANDLE_H__A05DC085_F715_46FD_9568_DA9107583ED5__INCLUDED_)
#define AFX_AVIHANDLE_H__A05DC085_F715_46FD_9568_DA9107583ED5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vfw.h>

class AVIHandle  
{
public:
	AVIHandle(void);
	AVIHandle(CString filename);
public:
	~AVIHandle(void);
public:
	BOOL LoadVideo(CString filename);
private:
	int width; //ͼ����
	int height;//ͼ��߶�
	int length;//����
	int defaultPad;
	BOOL loaded;
	CString AVIfilename; //AVI�ļ���
	LPBITMAPINFOHEADER lpbm;
	//δ���ҶȻ��壨24Bit�ɲ�ɫ����
	unsigned char* gray_value;
	//�����ҶȻ��壨24Bit�ɲ�ɫ����
	unsigned char* gray_value_square;
	PGETFRAME pgf;
public:
	unsigned char* GetSingleFrame(int i);
	int GetFrameCount(void);
	int GetFrameWidth(void);
	int GetFrameHeight(void);
	LPBITMAPINFOHEADER GetLPBM(void);
	BOOL isLoaded(void);
};

#endif // !defined(AFX_AVIHANDLE_H__A05DC085_F715_46FD_9568_DA9107583ED5__INCLUDED_)
