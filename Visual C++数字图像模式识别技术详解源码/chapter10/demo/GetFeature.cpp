// GetFeature.cpp: implementation of the GetFeature class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo1.h"
#include "GetFeature.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

double m_charsample[25];//���������
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GetFeature::GetFeature()
{
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

GetFeature::GetFeature(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					 unsigned char *pImgData):
ImageDib(size, nBitCount, lpColorTable, pImgData)
{

    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

GetFeature::~GetFeature()
{
	//�ͷ����ͼ��λͼ���ݻ�����
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//�ͷ����ͼ����ɫ��
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
}

/***************************************************************
*	�������ƣ�GetPosition()
*   �������ͣ�void 
*   �������ܣ��������ֵ�λ�ã���ֵ��bottom,top,right,left
****************************************************************/
GetFeature::GetPosition()
{

	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	int i,j;
	BOOL flag;
	for(j=0;j<m_imgHeight;j++)
	{
		flag=FALSE;
		for(i=0;i<m_imgWidth;i++)
			if(*(m_pImgData+j*lineByte+i)==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	m_charbottom=j;
	for(j=m_imgHeight-1;j>0;j--)
	{
		flag=FALSE;
		for(i=0;i<m_imgWidth;i++)
			if(*(m_pImgData+j*lineByte+i)==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	m_chartop=j;
	for(i=0;i<m_imgWidth;i++)
	{
		flag=FALSE;
		for(j=0;j<m_imgHeight;j++)
			if(*(m_pImgData+j*lineByte+i)==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	m_charleft=i;
	for(i=m_imgWidth-1;i>0;i--)
	{
		flag=FALSE;
		for(j=0;j<m_imgHeight;j++)
			if(*(m_pImgData+j*lineByte+i)==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	m_charright=i;
}

/****************************************************************
*   �������ƣ�Cal(int row, int col)
*   �������ͣ�double 
*   ����˵����int row, int col:��row�У���col������
*   �������ܣ�����ĳһС�����ں�������ռ����,����ĳһС�����ں�������ռ����
****************************************************************/
double GetFeature::Cal(int row, int col)
{
	double w,h,count;
	w=(m_charright-m_charleft)/5;
	h=(m_chartop-m_charbottom)/5;
	count=0;

	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	int i,j;
	for(j=m_charbottom+row*h;j<m_charbottom+(row+1)*h;j++)
	for(i=m_charleft+col*w;i<m_charleft+(col+1)*w;i++)
	{
		if(*(m_pImgData+j*lineByte+i)==0)
			count++;
	}

	return (double)count/(w*h);
}

/***************************************************************
*   �������ƣ�SetFeature()
*   �������ͣ�void 
*   �������ܣ����������������ڱ���testsample��
****************************************************************/
GetFeature::SetFeature()
{
	int i,j;
	for(j=0;j<5;j++)
	{
		for(i=0;i<5;i++)
		{
			m_charsample[5*(4-j)+i]=Cal(j,i);
		}
	}
	i=1;
}

CSize GetFeature::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}

GetFeature::ShowFeature()
{

	//���ͼ��Ϊ���ͼ������,�˴�Ϊ�Ҷ�����
	m_nBitCountOut=8;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=250;
	m_imgHeightOut=250;
	
	int lineByte=(m_imgWidthOut*m_nBitCountOut/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeightOut];
	memset(m_pImgDataOut,255,lineByte*m_imgHeightOut);

	//ѭ��������ͼ�������
	int i,j,m,n;

	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(m_charsample[5*i+j]>0.1){
				for(m=5;m<45;m++)
					for(n=5;n<45;n++)
						*(m_pImgDataOut+(250-i*50-m)*lineByte+j*50+n)=0;
	}
}

GetFeature::ShowPattern(double feature[])
{
	//���ͼ��Ϊ���ͼ������,�˴�Ϊ�Ҷ�����
	m_nBitCountOut=8;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=250;
	m_imgHeightOut=250;
	
	int lineByte=(m_imgWidthOut*m_nBitCountOut/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeightOut];
	memset(m_pImgDataOut,255,lineByte*m_imgHeightOut);

	//ѭ��������ͼ�������
	int i,j,m,n;

	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(feature[5*i+j]>0.1){
				for(m=5;m<45;m++)
					for(n=5;n<45;n++)
						*(m_pImgDataOut+(250-i*50-m)*lineByte+j*50+n)=0;
	}


}
