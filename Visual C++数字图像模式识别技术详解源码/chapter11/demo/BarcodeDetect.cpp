// BarcodeDetect.cpp: implementation of the BarcodeDetect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo1.h"
#include "BarcodeDetect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BarcodeDetect::BarcodeDetect()
{
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	
	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0

	ImageArray = NULL;
}

BarcodeDetect::BarcodeDetect(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					 unsigned char *pImgData):
ImageDib(size, nBitCount, lpColorTable, pImgData)
{
    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0
	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
	m_pImgDataIn=pImgData;//m_pImgData;

	int lineByte=(size.cx*m_nBitCount/8+3)/4*4;	
	int i,j,t;

	ImageArray = NULL;
	
	ImageArray=new BYTE*[m_imgHeight];
	for(t=0;t<m_imgHeight;t++)
		ImageArray[t]=new BYTE[m_imgWidth];

	for(i=0;i<m_imgHeight;i++)
		for(j=0;j<m_imgWidth;j++){
			if(*(m_pImgDataIn+i*lineByte+j)==0){
				ImageArray[i][j]=1;
			}
			else{
				ImageArray[i][j]=0;
			}
		}

}

BarcodeDetect::~BarcodeDetect()
{
	int i;
	if(ImageArray!=NULL)
	{
		for(i=0; i<m_imgHeight; i++)
			if(ImageArray[i]!=NULL) 
				delete ImageArray[i];
		delete ImageArray;
	}
}

/******************************************************************************
 * ���ܣ���������ͼ�����Ԥ�����ó��������
******************************************************************************/
BOOL BarcodeDetect::PreProcess()
{

	int i, j;
	int tempMax;
	int tempArray[1000];

	//����ˮƽ����ʹ�ֱ�����ϵ�ֱ��ͼͳ��
	for(i=0; i<m_imgHeight; i++)
		arPixelV[i] = 0;
	for(i=0; i<m_imgWidth; i++)
		arPixelH[i] = 0;
	for(i=0; i<m_imgHeight; i++)
	{
		for(j=0; j<m_imgWidth; j++)
		{
			if(ImageArray[i][j] == 1)
			{
				arPixelV[i] += 1;
				arPixelH[j] += 1;
			}
		}
	}

	//Ѱ�Ұ��������������
	//��Ѱ��ˮƽ�����Ϻ�����������
	
	tempMax = 0;
	for(i=0; i<m_imgHeight; i++)
	{
		if(arPixelV[i]>tempMax)
			tempMax = arPixelV[i];
		arMark[i] = false;
	}
	
	for(i=0; i<m_imgHeight-1; i++)
	{
		//������
		arDifference[i] = arPixelV[i+1] - arPixelV[i];

		//������������㹻���ұ仯���󣬱��Ϊtrue
		if( (abs(arDifference[i])<20) && (arPixelV[i]>(0.75*tempMax)) )
			arMark[i] = true;
	}
	
	//ȷ�������������
	int iLengthThrehold = 40;
	int iCount;
	for(i=0; i<m_imgHeight-iLengthThrehold; i++)
	{
		iCount = 0;
		for(j=0; j<iLengthThrehold; j++)
		{
			if(arMark[i+j] == true)
				iCount++;
		}
		if(iCount >= 37)
		{
			ImageTop = i+10;		//ȷ������
			break;
		}
	}

	for(i=m_imgHeight-1; i>=iLengthThrehold-1; i--)
	{
		iCount = 0;
		for(j=0; j<iLengthThrehold; j++)
		{
			if(arMark[i-j] == true)
				iCount++;
		}
		if(iCount >= 37)	//iLengthThrehold-3
		{
			ImageBottom = i-10;		//ȷ���ײ�
			break;
		}
	}
	
	//Ѱ�����Ե,Ϊ�˱�֤³���ԣ����Ѿ�ȷ�������±߽���ȫ������
	for(i=ImageTop; i<=ImageBottom; i++)
	{
		for(j=20; j<m_imgWidth; j++)
		{
			if( (ImageArray[i][j-1]==0) && (ImageArray[i][j]==1) )
			{
				arLeftEdge[i] = j;
				break;
			}
		}
	}
	
	//Ϊ���������ĸ��ţ�����ȷ��׼ȷ����߽�
	tempMax = 0;
	int iMax = 0;
	for(i=ImageTop; i<=ImageBottom; i++)
	{
		if(arLeftEdge[i] > tempMax)
		{
			tempMax = arLeftEdge[i];
			iMax = i;
		}
	}
	
	//��б�Ȳ��ܴ���1/10
	iCount = 0;
	for(i=ImageTop; i<=ImageBottom; i++)
	{
		if( abs(tempMax-arLeftEdge[i]) < abs(i-iMax)/6+1 )
		{
			iCount++;
		}
	}
	
	if( (iCount/(ImageBottom-ImageTop))<0.6 )
		return false;
	
	//�������
	for(i=iMax; i>ImageTop; i--)
	{
		if( abs(arLeftEdge[i]-arLeftEdge[i-1])>=2 )
		{
			if(ImageArray[i-1][arLeftEdge[i]]-ImageArray[i-1][arLeftEdge[i]-1] == 1)
				arLeftEdge[i-1] = arLeftEdge[i];
			else if(ImageArray[i-1][arLeftEdge[i]-1]-ImageArray[i-1][arLeftEdge[i]-2] == 1)
				arLeftEdge[i-1] = arLeftEdge[i]-1;
			else if(ImageArray[i-1][arLeftEdge[i]+1]-ImageArray[i-1][arLeftEdge[i]] == 1)
				arLeftEdge[i-1] = arLeftEdge[i]+1;
			else
				arLeftEdge[i-1] = arLeftEdge[i];
		}
	}
	
	for(i=iMax; i<ImageBottom; i++)
	{
		if(i == ImageBottom)
			break;
	
		if( abs(arLeftEdge[i]-arLeftEdge[i+1])>=2 )
		{
			if(ImageArray[i+1][arLeftEdge[i]]-ImageArray[i+1][arLeftEdge[i]-1] == 1)
				arLeftEdge[i+1] = arLeftEdge[i];
			else if(ImageArray[i+1][arLeftEdge[i]-1]-ImageArray[i+1][arLeftEdge[i]-2] == 1)
				arLeftEdge[i+1] = arLeftEdge[i]-1;
			else if(ImageArray[i+1][arLeftEdge[i]+1]-ImageArray[i+1][arLeftEdge[i]] == 1)
				arLeftEdge[i+1] = arLeftEdge[i]+1;
			else
				arLeftEdge[i+1] = arLeftEdge[i];
		}
	}
	
	int n;
	//���������еĿ��
	for(n=0; n<29; n++)
	{
		//���������ұ�Ե
		for(i=ImageTop; i<=ImageBottom; i++)
		{
			for(j = arLeftEdge[i]+1; j<m_imgWidth; j++)
			{
				if( (ImageArray[i][j-1]==1) && (ImageArray[i][j]==0) )
				{
					arLeftEdge1[i] = j;
					break;
				}
			}
			arDelta[i] = arLeftEdge1[i] - arLeftEdge[i];
		}
		
		//�ٶ����ͿյĿ�����Ϊ11
		//���򣬿�����Ϊ���м��5�������ƽ�����
		for(i=ImageTop; i<ImageBottom; i++)
			tempArray[i] = arDelta[i];
		
		for(i=ImageTop; i<ImageBottom; i++)
		{
			for(j=ImageBottom; j>i; j--)
			{
				int tempSwap;
				if(tempArray[j] < tempArray[j-1])
				{
					tempSwap = tempArray[j];
					tempArray[j] = tempArray[j-1];
					tempArray[j-1] = tempSwap;
				}
			}
		}
		
		if(tempArray[ImageTop+(ImageBottom-ImageTop)/2+2]-tempArray[ImageTop+(ImageBottom-ImageTop)/2-2]>1)
			return false;
		else
			arWidth[2*n] = tempArray[ImageTop+(ImageBottom-ImageTop)/2];
		
		//������һ�б�Ե
		for(i=ImageTop; i<=ImageBottom; i++)
		{
			if(abs(arDelta[i] - arWidth[2*n])>2)
				arLeftEdge1[i] = arLeftEdge[i] + arWidth[2*n];
			arLeftEdge[i] = arLeftEdge1[i];
		}
		
		//�����յ��ұ�Ե
		for(i=ImageTop; i<=ImageBottom; i++)
		{
			for(j = arLeftEdge[i]+1; j<m_imgWidth; j++)
			{
				if( (ImageArray[i][j-1]==0) && (ImageArray[i][j]==1) )
				{
					arLeftEdge1[i] = j;
					break;
				}
			}
			arDelta[i] = arLeftEdge1[i] - arLeftEdge[i];
		}
		
		//�ٶ����ͿյĿ�����Ϊ11
		//���򣬿�����Ϊ���м��5�������ƽ�����
		for(i=ImageTop; i<ImageBottom; i++)
			tempArray[i] = arDelta[i];
		
		for(i=ImageTop; i<ImageBottom; i++)
		{
			for(j=ImageBottom; j>i; j--)
			{
				int tempSwap;
				if(tempArray[j] < tempArray[j-1])
				{
					tempSwap = tempArray[j];
					tempArray[j] = tempArray[j-1];
					tempArray[j-1] = tempSwap;
				}
			}
		}
		
		if(tempArray[ImageTop+(ImageBottom-ImageTop)/2+2]-tempArray[ImageTop+(ImageBottom-ImageTop)/2-2]>1)
			return false;
		else
			arWidth[2*n+1] = tempArray[ImageTop+(ImageBottom-ImageTop)/2];
		
		//������һ�б�Ե
		for(i=ImageTop; i<=ImageBottom; i++)
		{
			if(abs(arDelta[i] - arWidth[2*n+1])>2)
				arLeftEdge1[i] = arLeftEdge[i] + arWidth[2*n+1];
			arLeftEdge[i] = arLeftEdge1[i];
		}
	}
	
	//�������һ�������ұ�Ե
	for(i=ImageTop; i<=ImageBottom; i++)
	{
		for(j = arLeftEdge[i]+1; j<m_imgWidth; j++)
		{
			if( (ImageArray[i][j-1]==1) && (ImageArray[i][j]==0) )
			{
				arLeftEdge1[i] = j;
				break;
			}
		}
		arDelta[i] = arLeftEdge1[i] - arLeftEdge[i];
	}
	
	//�ٶ����ͿյĿ�����Ϊ11
	//���򣬿�����Ϊ���м��5�������ƽ�����
	for(i=ImageTop; i<ImageBottom; i++)
		tempArray[i] = arDelta[i];
	
	for(i=ImageTop; i<ImageBottom; i++)
	{
		for(j=ImageBottom; j>i; j--)
		{
			int tempSwap;
			if(tempArray[j] < tempArray[j-1])
			{
				tempSwap = tempArray[j];
				tempArray[j] = tempArray[j-1];
				tempArray[j-1] = tempSwap;
			}
		}
	}
	
	if(tempArray[ImageTop+(ImageBottom-ImageTop)/2+2]-tempArray[ImageTop+(ImageBottom-ImageTop)/2-2]>1)
		return false;
	else
		arWidth[2*n] = tempArray[ImageTop+(ImageBottom-ImageTop)/2];
	
	//������һ�б�Ե
	for(i=ImageTop; i<=ImageBottom; i++)
	{
		if(abs(arDelta[i] - arWidth[2*n+1])>2)
			arLeftEdge1[i] = arLeftEdge[i] + tempArray[ImageTop+(ImageBottom-ImageTop)/2];
		arLeftEdge[i] = arLeftEdge1[i];
	}

	return true;
}

/******************************************************************************
 * ʶ��
******************************************************************************/
BOOL BarcodeDetect::Recognize()
{
	//�ܹ���7��12��3��2��5�� 95����λ���
	//��4��12��3��2��5��59����ȣ�
	int i;
	int result[12];
	double mx = 0.0;	//ƽ�����

	for(i=0; i<59; i++)
		mx += (double)arWidth[i];
	mx /= 95.0;

	//��ʼ����
	for(i=0; i<3; i++)
	{
		double dTemp = (double)arWidth[i]/mx;
		if( dTemp<0.6 || dTemp>1.4 )
			break;
	}
	//��ʼ�벻����Ҫ��
	//if(i<3)
	//	return false;
	
	//ʶ��ǰ6��
	for(i=0; i<6; i++)
	{
		result[i] = JudgNum(arWidth[i*4+3], arWidth[i*4+4], arWidth[i*4+5], arWidth[i*4+6], mx);
	}
	//ʶ���6��
	for(i=6; i<12; i++)
	{
		result[i] = JudgNum(arWidth[i*4+8], arWidth[i*4+9], arWidth[i*4+10], arWidth[i*4+11], mx);
	}

	//�ж�����
	if( result[0]==7 && result[1]==7 )
	{
		strCodeStyle = "ISSN";
	}
	else if( result[0]==7 && result[1]==8 )
	{
		strCodeStyle = "ISBN";
	}
	else
		strCodeStyle = "Unknown!";

	//�ж��Ƿ�ȫ��ʶ�����
	for(i=0; i<12; i++)
		if(result[i] == -1)
			return false;

	CString strTemp;
	strCodeNumber.Format("");
	for(i=0; i<12; i++)
	{
		strTemp.Format("%d", result[i]);
		strCodeNumber += strTemp;
	}
	return true;
}


/******************************************************************************
 * ���ݿ�������ж�����
******************************************************************************/
int BarcodeDetect::JudgNum(int w1, int w2, int w3, int w4, double mx)
{
	double a1, a2, a3;
	int ia1, ia2, ia3;
	a1 = (double)(w1+w2)/mx;
	a2 = (double)(w2+w3)/mx;
	a3 = (double)(w3+w4)/mx;
	ia1 = (int)(a1+0.5);
	ia2 = (int)(a2+0.5);
	ia3 = (int)(a3+0.5);
		
	//�жϸ���ֵ
	if( (ia1==5 && ia2==3 && ia3==2) || (ia1==2 && ia2==3 && ia3==5) )
		return 0;
	
	if( (ia1==4 && ia2==4 && ia3==3) || (ia1==3 && ia2==4 && ia3==4) )
	{
		if(ia1 == 4)
		{
			double dw2 = (double)w2/mx;
			if(dw2 < 2.4)
				return 1;
			else if(dw2 > 2.6)
				return 7;
			else return -1;
		}
	
		if(ia1 == 3)
		{
			double dw3 = (double)w3/mx;
			if(dw3 < 2.4)
				return 1;
			else if(dw3 > 2.6)
				return 7;
			else return -1;
		}
	}
	
	if( (ia1==3 && ia2==3 && ia3==4) || (ia1==4 && ia2==3 && ia3==3) )
	{
		if(ia1 == 3)
		{
			double dw4 = (double)w4/mx;
			if(dw4 < 2.4)
				return 2;
			else if(dw4 > 2.6)
				return 8;
			else return -1;
		}
	
		if(ia1 == 4)
		{
			double dw1 = (double)w1/mx;
			if(dw1 < 2.4)
				return 2;
			else if(dw1 > 2.6)
				return 8;
			else return -1;
		}
	}
	
	if( (ia1==5 && ia2==5 && ia3==2) || (ia1==2 && ia2==5 && ia3==5) )
		return 3;
	
	if( (ia1==2 && ia2==4 && ia3==5) || (ia1==5 && ia2==4 && ia3==2) )
		return 4;
	
	if( (ia1==3 && ia2==5 && ia3==4) || (ia1==4 && ia2==5 && ia3==3) )
		return 5;
	
	if( (ia1==2 && ia2==2 && ia3==5) || (ia1==5 && ia2==2 && ia3==2) )
		return 6;
	
	if( (ia1==4 && ia2==2 && ia3==3) || (ia1==3 && ia2==2 && ia3==4) )
		return 9;

	return false;
}
