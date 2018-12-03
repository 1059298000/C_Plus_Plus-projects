// GetFeature.h: interface for the GetFeature class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETFEATURE_H__82AF2137_3B0D_45AA_BD6E_7FDF0669B22E__INCLUDED_)
#define AFX_GETFEATURE_H__82AF2137_3B0D_45AA_BD6E_7FDF0669B22E__INCLUDED_

#include "ImageDib.h"
#include "NumRecognition.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GetFeature : public ImageDib 
{
public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;

	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;

	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;

	//����λ��
	int m_charleft,m_chartop,m_charright,m_charbottom;

	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;

	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;
private:
	//���ͼ����ɫ����
	int m_nColorTableLengthOut;

public:
	GetFeature();
	GetFeature(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);
	virtual ~GetFeature();
	CSize GetDimensions();
	GetPosition();
	SetFeature();
	ShowFeature();
	ShowPattern(double feature[]);
	double Cal(int row, int col);

};

#endif // !defined(AFX_GETFEATURE_H__82AF2137_3B0D_45AA_BD6E_7FDF0669B22E__INCLUDED_)
