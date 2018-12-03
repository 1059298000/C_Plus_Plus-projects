// charsRecognition.h: interface for the CharsRecognition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARSRECOGNITION_H__851ED4A3_186E_447B_B380_B10FCC9AC344__INCLUDED_)
#define AFX_CHARSRECOGNITION_H__851ED4A3_186E_447B_B380_B10FCC9AC344__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"
#include "structure.h"
class charsRecognition  : public ImageDib 
{
public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;
	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;
	unsigned char * m_pImgDataIn;
	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;
	list<h> m_ProjX;//��ֱ�����ϵ�ͶӰX���
	list<CFtChinese> m_fChinese;//����
	string m_strResult;//�ַ����
    match L[20];         //���ֽ��ں�ѡֵ
	match Lm[10];
	match Lp[10];
private:
	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;
	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;
	//���ͼ����ɫ����
	int m_nColorTableLengthOut;
public:
	//���������Ĺ��캯��
	charsRecognition();
	//�������Ĺ��캯��
	charsRecognition(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);
	//��������
	~charsRecognition();
	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();
	HprojX();
	int LineCluster();
	MergeProjX(int lWm);
	CutImage(int lWm);
	LONG RoundCut(LONG iy,h ix,int iW);
	GetMinRect(Position &pos);
	BlockNormalization();
	Norm(CFtChinese &itx);
	MyRound(double x);
	Thinning(int SWH,CFtChinese &it);
	Normalization(Position &pos,int SWH,int *iImage);
	GetCrudeFeature();
	Density();
	CrossMesh(CFtChinese &it);
	CrossPeriphery(CFtChinese &it);
	CrudeMatchChinese();
	BOOL CrudeMatch(CFtChinese &it);
	DrawRect();
};

#endif // !defined(AFX_CHARSRECOGNITION_H__851ED4A3_186E_447B_B380_B10FCC9AC344__INCLUDED_)

inline int charsRecognition::MyRound(double x)
{
	if ((x-(int)x)>=0.5)
	{
		return (int)(x+0.5);
	}
	else
	{
		return (int)x;
	}
}
