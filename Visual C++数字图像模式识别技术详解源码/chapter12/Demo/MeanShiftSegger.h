// MeanShiftSegger.h: interface for the MeanShiftSegger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEANSHIFTSEGGER_H__0CB542C8_6C53_49C1_BFA4_7124A4712E47__INCLUDED_)
#define AFX_MEANSHIFTSEGGER_H__0CB542C8_6C53_49C1_BFA4_7124A4712E47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define HISTOGRAM_LENGTH 4096   //ֱ��ͼ����
typedef unsigned char pixel;

class MeanShiftSegger  
{
public:
	MeanShiftSegger();
	~MeanShiftSegger();
private:
	int imgWidth;   //ͼ����
	int imgHeight;  //ͼ��߶�

	int trackWinWidth;  //���ڿ��
	int trackWinHeight;  //���ڸ߶�		
	int currentX;       //��ǰĿ�������
	int currentY;       //��ǰĿ��������

private:
	float currHistogram[HISTOGRAM_LENGTH];  //��ǰֱ��ͼ
	float tempHistogram[HISTOGRAM_LENGTH];  //Ŀ��ֱ��ͼ����
public:

    //����Bhattacharyyaϵ��
	float CalculateBhattacharyya(float initHistogram[HISTOGRAM_LENGTH],float tempHistogram[HISTOGRAM_LENGTH]);

    //����Ŀ��λ��
	void InitMeanShiftTracker(unsigned char* firstFrame,int frameWidth,int frameHeight,int targetPosX,int targetPosY,int targetWidth,int targetHeight);
    //����Ŀ��ֱ��ͼ	
	int CalculateHistogramSp(unsigned char*  frame,char kernel,float histogram[HISTOGRAM_LENGTH]);

	//Mean Shift ��������
	void MeanShiftProcessSp(unsigned char * frame);
    //Mean Shift���ٲ�������
	void MeanShiftTrackProcess(unsigned char*  frame,int frameNumber);
	//���ݵ�ǰ���ٴ��ڵĴ�С��Ŀ��λ�û��Ƹ��ٴ�
	void DrawTrackBox(unsigned char*  frame);
};

#endif // !defined(AFX_MEANSHIFTSEGGER_H__0CB542C8_6C53_49C1_BFA4_7124A4712E47__INCLUDED_)
