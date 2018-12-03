// ImgSegment.h: interface for the ImgSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGSEGMENT_H__8745C184_7B7A_4116_9351_36AEA5427282__INCLUDED_)
#define AFX_IMGSEGMENT_H__8745C184_7B7A_4116_9351_36AEA5427282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class ImgSegment : public ImageDib  
{
public:
	int m_nBitCountOut;	//���ͼ��ÿ����λ��
	unsigned char * m_pImgDataOut;	//���ͼ��λͼ����ָ��
	LPRGBQUAD m_lpColorTableOut;	//���ͼ����ɫ��
private:
	int m_imgWidthOut;	//���ͼ��Ŀ�
	int m_imgHeightOut;	//���ͼ��ĸ�
	int m_nColorTableLengthOut;	//���ͼ����ɫ����
public:
	ImgSegment();	//���������Ĺ��캯��
	ImgSegment(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);	//�������Ĺ��캯��
	virtual ~ImgSegment();	//��������
	CSize GetDimensions();	//������Ϊ��λ�������ͼ��ĳߴ�
public:
	int threshOtus(int histArray[256]);	//�����ֵ�ָ�
	void AdaptThreshSeg(unsigned char *pImgData);
	void Roberts();	//Roberts����
	void Sobel();	//Sobel����
	void Prewitt();	//Prewitt����
	void Laplacian();	//Laplacian����
public:
	void RegionGrow(CPoint SeedPos, int thresh);	//��������
	void EdgeTrace();	//���߸���
private:
	//ģ��������
	void TemplateEdge(unsigned char *imgIn, int width, int height, int nBitCount,
		int *mask, int maskW, int maskH, unsigned char *imgOut);
	
	//��������ʽ�µ��߼��hough�任
	void HoughTransform(unsigned char *imgBinaryIn, int width, int height, int *houghBuf,
		int  houghWidth, int houghHeight,float radiusResolution, float angleResolution,
					 float *radius, float *angle);

};

#endif // !defined(AFX_IMGSEGMENT_H__8745C184_7B7A_4116_9351_36AEA5427282__INCLUDED_)
