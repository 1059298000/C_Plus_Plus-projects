// PlateTrans.h: interface for the PlateTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLATETRANS_H__22078346_C360_4BAB_966C_FAC26E9959BF__INCLUDED_)
#define AFX_PLATETRANS_H__22078346_C360_4BAB_966C_FAC26E9959BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"
class PlateTrans : public ImageDib  
{
public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;

	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;
	
	unsigned char * m_pImgDataIn1;
	unsigned char * m_pImgDataIn2;

	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;

private:
	void initmodule();
	int BeWhite(char *Col);
	int BeBlue(char *Col);
	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;

	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;

	//���ͼ����ɫ����
	int m_nColorTableLengthOut;

	int m_modules[40][20][40];
	char m_chars[40];


public:
	void charrecognize();
	
	//���������Ĺ��캯��
	PlateTrans();

	//�������Ĺ��캯��
	PlateTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData1,unsigned char *pImgData2);

	//��������
	~PlateTrans();
	

	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();

	void ColorPairSearch();
};

#endif // !defined(AFX_PLATETRANS_H__22078346_C360_4BAB_966C_FAC26E9959BF__INCLUDED_)
