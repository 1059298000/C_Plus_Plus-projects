// MeanShiftSegger.cpp: implementation of the MeanShiftSegger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\MSMoneyDemo.h"
#include "MeanShiftSegger.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*int max(int x,int y)
{
	if(x > y)
		return x;

	return y;

}
int min(int x,int y)
{
	if(x > y)
		return y;

	return x;

}*/


/***********************************************************************
* �������ƣ�
*     MeanShiftSegger()
*
*˵�������캯�� 
***********************************************************************/
MeanShiftSegger::MeanShiftSegger():
imgWidth(0),imgHeight(0){
    for(int i = 0; i < HISTOGRAM_LENGTH; i ++)
		currHistogram[i] = 0;
    for(int i = 0; i < HISTOGRAM_LENGTH; i ++)
		tempHistogram[i] = 0;
	//memset(currHistogram,0,sizeof(float) * HISTOGRAM_LENGTH);
	//memset(tempHistogram,0,sizeof(float) * HISTOGRAM_LENGTH);
	//SetZeroHistogram(currHistogram);
	//SetZeroHistogram(tempHistogram);
	return;

}
/***********************************************************************
* �������ƣ�
*     ~MeanShiftSegger()
* ˵����
*     ��������
***********************************************************************/
MeanShiftSegger::~MeanShiftSegger(){

}

/***********************************************************************
* �������ƣ�
*     InitMeanShiftTracker()
* ������
*     unsigned char * firstFrame ��һ֡����
*     int frameWidth-֡���
*     int frameHeight-֡�߶�
*     int targetPosX-Ŀ��λ�ú�����
*     int targetPosY-Ŀ��λ��������
*     int targetWidth-Ŀ����
*     int targetHeight-Ŀ��߶�
* ˵����MeanShift���̸��ٳ�ʼ������
***********************************************************************/

void MeanShiftSegger::InitMeanShiftTracker(unsigned char*  firstFrame,int frameWidth,int frameHeight,int targetPosX,int targetPosY,int targetWidth,int targetHeight){
	this->imgWidth = frameWidth;
	this->imgHeight = frameHeight;

	this->currentX = targetPosX;
	this->currentY = targetPosY;

	this->trackWinHeight = targetHeight;
	this->trackWinWidth = targetWidth;
}


/***********************************************************************
* �������ƣ�
*     CalculateHistogramSp
* ������
*     image frame-��ǰ����֡
*     char kernel-������ѡ��Ŀǰֻ֧��Uniform�ˣ�
*     float * histogram-ֱ��ͼ����
* ˵����ͳ��ֱ��ͼ����������ģ�ͣ��޲��������ܶȹ��ƣ�
***********************************************************************/
int MeanShiftSegger::CalculateHistogramSp(unsigned char*  frame,char kernel, float *histogram){
	int pxValue = 0;

	for(int i = 0 ; i < HISTOGRAM_LENGTH; i++)
		histogram[i] = 0;

	if(kernel == 'U')
	{

		for(int j = max(0,currentY - trackWinHeight / 2);j < min(currentY + trackWinHeight / 2,imgHeight - 1); j ++){
			for(int i = max(0,currentX - trackWinWidth / 2); i < min(currentX + trackWinWidth / 2,imgWidth - 1);i ++){
				pixel r = frame[j * imgWidth * 3 + i * 3] / 16;
				pixel g = frame[j * imgWidth * 3 + i * 3 + 1] / 16;
				pixel b = frame[j * imgWidth * 3 + i * 3 + 2] / 16;

				histogram[256 * (int)r + 16 * (int)g + (int)b] += 1;
				pxValue ++;

			}

		}

		for(int i = 0; i < HISTOGRAM_LENGTH; i ++)
			histogram[i] /= pxValue;
	}
	else
	{
		return 0;
	}
	return pxValue;
}

/***********************************************************************
* �������ƣ�
*     MeanShiftTrackerProcess
* ������
*     unsigned char *frame-��ǰ֡����
* ˵���������е�MeanShift����
***********************************************************************/
void MeanShiftSegger::MeanShiftProcessSp(unsigned char * frame){
	float weights[HISTOGRAM_LENGTH];

	float newX = 0.0;
	float newY = 0.0;

	for (int i=0;i<HISTOGRAM_LENGTH;i++)
	{
		if (currHistogram[i] >0.0 )
			weights[i] = (float)tempHistogram[i]/(float)currHistogram[i];
		//Ŀ��ģ��ֱ��ͼ/��ǰֱ��ͼ
		else
			weights[i] = 0;
	}

	float sumOfWeights = 0.0;

		for(int j = max(0,currentY - trackWinHeight / 2);j < min(currentY + trackWinHeight / 2,imgHeight - 1); j ++){
			for(int i = max(0,currentX - trackWinWidth / 2); i < min(currentX + trackWinWidth / 2,imgWidth - 1);i ++){
			pixel r = frame[j * imgWidth * 3 + i * 3] / 16;
			pixel g = frame[j * imgWidth * 3 + i * 3 + 1] / 16;
			pixel b = frame[j * imgWidth * 3 + i * 3 + 2] / 16;

			int ptr = (int)(256 * (int)r + 16 * (int)g + (int)b);

			newX += (weights[ptr] * (float)i);
			newY += (weights[ptr] * (float)j);

			sumOfWeights += weights[ptr];


		}

	}
	if(sumOfWeights != 0){
		currentX = int((newX/sumOfWeights) + 0.5);
		currentY = int((newY/sumOfWeights) + 0.5);
	}
	return;

}


/***********************************************************************
* ��������
*     MeanShiftTrackProcess 
* ������
*     image frame-��ǰ����֡
*     int frameNumber-����֡��
* ˵����MeanShift���������ù���
***********************************************************************/
void MeanShiftSegger::MeanShiftTrackProcess(unsigned char*  frame,int frameNumber)
{
	if(frameNumber == 0){
		//��ָ��λ�ý���Ŀ��ģ��
		CalculateHistogramSp(frame,'U',this->tempHistogram);
	}
	else
	{
		int stopThreshold = 10;
		int iteratorCoumt = 0;
		while(iteratorCoumt < stopThreshold){

			//�ں���֡�м��Ŀ����λ��
			CalculateHistogramSp(frame,'U',this->currHistogram);
			MeanShiftProcessSp(frame); //�����λ��

			//����ֱ��ͼ
			iteratorCoumt++;
		}
		
		DrawTrackBox(frame);

	}
}


/***********************************************************************
* �������ƣ�
*     DrawTrackBox
* ������
*     unsigned char * frame-��ǰ֡����
* ˵����������л����ٴ���
***********************************************************************/
void MeanShiftSegger::DrawTrackBox(unsigned char*  frame)
{

	for(int i = currentX; i < min(imgWidth,currentX + trackWinWidth); i ++)
	{
		frame[currentY * imgWidth * 3 + i * 3 + 0] = 255;
		frame[currentY * imgWidth * 3 + i * 3 + 1] = 255;
		frame[currentY * imgWidth * 3 + i * 3 + 2] = 255;

		frame[min(imgHeight - 1,currentY + trackWinHeight) * imgWidth * 3 + i * 3 + 0] = 255;
		frame[min(imgHeight - 1,currentY + trackWinHeight) * imgWidth * 3 + i * 3 + 1] = 255;
		frame[min(imgHeight - 1,currentY + trackWinHeight) * imgWidth * 3 + i * 3 + 2] = 255;
	}

	for(int j = currentY; j < min(imgHeight - 1,currentY + trackWinHeight); j ++)
	{

		frame[j * imgWidth * 3 + currentX * 3 + 0] = 255;
		frame[j * imgWidth * 3 + currentX * 3 + 1] = 255;
		frame[j * imgWidth * 3 + currentX * 3 + 2] = 255;

		frame[j * imgWidth * 3 + min(imgWidth - 1,currentX + trackWinWidth) * 3 + 0] = 255;
		frame[j * imgWidth * 3 + min(imgWidth - 1,currentX + trackWinWidth) * 3 + 1] = 255;
		frame[j * imgWidth * 3 + min(imgWidth - 1,currentX + trackWinWidth) * 3 + 2] = 255;
	}


}

/***********************************************************************
* �������ƣ�
*     CalculateBhattacharyya
* ˵��������Bhattachryya
***********************************************************************/
float MeanShiftSegger::CalculateBhattacharyya(float initHistogram [HISTOGRAM_LENGTH],float tempHistogram[HISTOGRAM_LENGTH]){
	float dis = 0;

	for(int i = 0;i < HISTOGRAM_LENGTH ;i ++)
		dis += float(sqrt(double(currHistogram[i] * tempHistogram[i])));

	return dis;
}
