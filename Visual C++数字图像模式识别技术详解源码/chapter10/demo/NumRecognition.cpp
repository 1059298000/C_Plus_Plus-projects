// NumRecognitin.cpp: implementation of the NumRecognition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo1.h"
#include "NumRecognition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern double m_charsample[25];//���������
extern pattern pattern[10];//����ģ��
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NumRecognition::NumRecognition()
{

}

NumRecognition::~NumRecognition()
{

}


number_no NumRecognition::LeastDistance()
{
	double min=10000000000;
	number_no number;
	int i,n;
	for(n=0;n<10;n++)
	{
		for(i=0;i<pattern[n].number;i++)
		{
			if(match(pattern[n].feature[i],m_charsample)<min)
			{
				//ƥ�����Сֵ
				min=match(pattern[n].feature[i],m_charsample);
				number.number  =n;//��Ʒ���
				number.no=i;//��Ʒ���
			}
		}
	}
	return number;//�������ֵ��������
}


/****************************************************************
*   �������ƣ�pipei(double s1[], double s2[])
*   �������ͣ�double 
*   ����˵����double s1[], double s2[]:������Ʒ������
*   �������ܣ�����������Ʒ��ƥ��̶� ,����������Ʒ�ĵ�ƥ��̶ȡ�
****************************************************************/
double NumRecognition::match(double s1[], double s2[])
{
	double count=0.0;
	for(int i=0;i<25;i++)
	{
		count+=(s1[i]-s2[i])*(s1[i]-s2[i]);
	}
	return count;
}
