// BarcodeDetect.h: interface for the BarcodeDetect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BARCODEDETECT_H__6D80A444_19EE_4D6B_9300_F9C1F0ED87AF__INCLUDED_)
#define AFX_BARCODEDETECT_H__6D80A444_19EE_4D6B_9300_F9C1F0ED87AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class BarcodeDetect : public ImageDib  
{

	public:
		//���ͼ��ÿ����λ��
		int m_nBitCountOut;
		//���ͼ��λͼ����ָ��
		unsigned char * m_pImgDataOut;
		//���ͼ����ɫ��
		LPRGBQUAD m_lpColorTableOut;
		//����ͼ��λͼ����ָ��
		unsigned char * m_pImgDataIn;

		BYTE** ImageArray;				//ԭʼ��ͼ����������


		int arPixelH[1000];				//Ϊ��ˮƽ����ֱ��ͼͳ����
		int arPixelV[1000];				//Ϊ�˴�ֱ����ֱ��ͼͳ����
		int arWidth[200];				//���������У�������ߵĺ�����ʼ
		int arDifference[1000];			//���
		bool arMark[1000];				//���
		int ImageLeft;					//ͼ������ߵ�����
		int ImageRight;					//ͼ�����ұߵ�����
		int ImageTop;					//�����붥��������
		int ImageBottom;				//�������²�������

	private:
		//���ͼ��Ŀ�����Ϊ��λ
		int m_imgWidthOut;
		//���ͼ��ĸߣ�����Ϊ��λ
		int m_imgHeightOut;
		//���ͼ����ɫ����
		int m_nColorTableLengthOut;
	public:
		//���������Ĺ��캯��
		BarcodeDetect();
		//�������Ĺ��캯��
		BarcodeDetect(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
			unsigned char *pImgData);
		~BarcodeDetect();

		BOOL PreProcess(void);
		BOOL Recognize();
		int JudgNum(int w1, int w2, int w3, int w4, double mx);
		CString strCodeNumber;
		CString strCodeStyle;

	protected:	
		int arDelta[1000];
		int arLeftEdge1[1000];
		int arLeftEdge2[1000];
		int arLeftEdge[1000];
};

#endif // !defined(AFX_BARCODEDETECT_H__6D80A444_19EE_4D6B_9300_F9C1F0ED87AF__INCLUDED_)
