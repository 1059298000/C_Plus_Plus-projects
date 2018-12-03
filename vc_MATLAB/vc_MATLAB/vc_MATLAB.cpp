// vc_MATLAB.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include "engine.h"
#include <string.h> 
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

void Opencv_Matlab_C()
{

	Engine *ep;
	if (!(ep = engOpen(NULL)))
	{
		printf("Cannot open MATLAB Engine.");
	}

	const char *pstrimagename = "17.jpg";
	const char *pstrwindowstitle1 = "Ŀ��ͼ����1";
	const char *pstrwindowstitle2 = "Ŀ��ͼ����2";
	const char *sdtwindowstitle = "ԭͼ";
	//���ļ��ж�ȡͼ��  
	IplImage *img;
	IplImage *gray;
	if (!(img = cvLoadImage(pstrimagename, 1)))
		printf("can't load image");
	gray = cvCreateImage(cvGetSize(img), 8, 1);
	cvCvtColor(img, gray, CV_BGR2GRAY);

	int width = cvGetSize(img).width;
	int height = cvGetSize(img).height;

	// ����903*600��С��mxREALʵ˫���Ⱦ���
	mxArray *gray_MATLAB = mxCreateDoubleMatrix(width, height, mxREAL);
	// ��gray_MATLAB��ֵ
	memcpy(mxGetPr(gray_MATLAB), gray, width * height * sizeof(double));
	engPutVariable(ep, "gray_MATLAB", gray_MATLAB);
	engEvalString(ep, "figure");
	engEvalString(ep, "imshow(gray_MATLAB)");
	printf("press any key to exit!");
	getchar();
	mxDestroyArray(gray_MATLAB);
	engClose(ep);
	cvReleaseImage(&img);
	cvReleaseImage(&gray);
	cvDestroyWindow("gray_MATLAB");

}


void curveChart()
{
	const int N = 20;
	double x[N], y[N];//�������
	double z[256][256];
	//��7�С���9�У�������ʼ��������������Ҫ����ʵ���������������ά���ʹ�С
	for (int i = 0; i < N; i++)
	{
		x[i] = i + 1;
		y[i] = x[i] * x[i];
	}
	//��12�С���16�У��õ�xƽ����20�������꣬����֮���ͼ
	Engine *ep;
	if (!(ep = engOpen(NULL)))
	{
		printf("Cannot open MATLAB Engine.");
	}
	//��19�С���23�У�����MATLAB�ⲿ���������ָ�룬���ж�����ָ�봴���Ƿ�ɹ�
	mxArray *xx = mxCreateDoubleMatrix(1, N, mxREAL);//1��N��
	mxArray *yy = mxCreateDoubleMatrix(1, N, mxREAL);//1��N��
	mxArray *zz = mxCreateDoubleMatrix(256, 256, mxREAL);//256��256��
														 //��26����28�У�������Ҫ���ݸ�MATLAB��ʵ������ָ�룬���������洴���ĳ�ʼ������ָ����ָ���ά�Ⱥʹ�С
	memcpy(mxGetPr(xx), x, N * sizeof(double));
	memcpy(mxGetPr(yy), y, N * sizeof(double));
	memcpy(mxGetPr(zz), z, 256 * 256 * sizeof(double));
	//��31�С���33�У���MATLAB�ı���ָ��ָ���ʼ��������ַ
	engPutVariable(ep, "xx", xx);
	engPutVariable(ep, "yy", yy);
	engPutVariable(ep, "zz", zz);
	//��36�С���38�У�������д��MATLAB�ռ䣬��Ϊ����MATLAB�ռ�������
	//����MATLAB��plot��������������
	engEvalString(ep, "plot(xx,yy)");
	//����MATLAB�е�imread��������ȡһ��ͼƬ
	engEvalString(ep, "zz=imread('cameraman.tif')");
	//����MATLAB�е�figure������imshow������ʾ����ͼƬ
	engEvalString(ep, "figure");
	engEvalString(ep, "imshow(zz)");
	printf("press any key to exit!");
	getchar();
	mxDestroyArray(xx);
	mxDestroyArray(yy);
	mxDestroyArray(zz);
	engClose(ep);
	// ��52�С���55�У��ͷ��ڴ�ռ䣬���ر�MATLAB����
}

void log_transformation()
{
	Engine *ep;
	if (!(ep = engOpen(NULL)))
	{
		printf("Cannot open MATLAB Engine.");
	}
	// mxCreateDoubleMatrix�������ɾ��󣬱���������Ҫ����3��256x256�ľ���
	mxArray *I = mxCreateDoubleMatrix(256, 256, mxREAL);//256����
	mxArray *J = mxCreateDoubleMatrix(256, 256, mxREAL);//256����
	mxArray *H = mxCreateDoubleMatrix(256, 256, mxREAL);//256����
														//����ͨ��MATLAB�������MATLAB�㷨
	engPutVariable(ep, "I", I);
	engPutVariable(ep, "J", J);
	engPutVariable(ep, "H", H);
	//��18�С���20�У�����������д��MATLAB�ռ䣬��Ϊ����MATLAB�ռ�������
	engEvalString(ep, "I=imread('cameraman.tif')");
	engEvalString(ep, "J=double(I)");
	//���ж����任
	engEvalString(ep, "J=40*(log(J+1))");
	engEvalString(ep, "H=uint8(J)");
	engEvalString(ep, "subplot(1,2,1), imshow(I)");
	engEvalString(ep, "subplot(1,2,2), imshow(H)");
	printf("press any key to exit!");
	getchar();
	mxDestroyArray(I);
	mxDestroyArray(J);
	mxDestroyArray(H);
	engClose(ep);
}

void smooth_sharpness()
{
	Engine *ep;
	if (!(ep = engOpen(NULL)))
	{
		printf("Cannot open MATLAB Engine.");
	}
	// mxCreateDoubleMatrix�������ɾ���	
	mxArray *I = mxCreateDoubleMatrix(256, 256, mxREAL);//256����
	mxArray *J = mxCreateDoubleMatrix(256, 256, mxREAL);//256����
	mxArray *A = mxCreateDoubleMatrix(256, 256, mxREAL);//256����
	mxArray *B = mxCreateDoubleMatrix(256, 256, mxREAL);//256����
	mxArray *C = mxCreateDoubleMatrix(256, 256, mxREAL);//256����
	engPutVariable(ep, "I", I);
	engPutVariable(ep, "J", J);
	engPutVariable(ep, "A", A);
	engPutVariable(ep, "B", B);
	engPutVariable(ep, "C", C);
	//����ͨ��MATLAB�������MATLAB�㷨
	engEvalString(ep, "I=imread('cameraman.tif')");
	engEvalString(ep, "J=im2double(I)");
	engEvalString(ep, "subplot ( 2,2,1 ), imshow ( J, [ ] )");
	//���õĸ�ͨ�˲�����ģ��Ϊh1��h2��h3
	engEvalString(ep, "h1=[ 0  -1   0,  -1   5  -1,  0  -1   0]");
	engEvalString(ep, "h2=[-1  -1  -1,  -1   9  -1, -1  -1  -1]");
	engEvalString(ep, "h3=[ 1  -2   1,  -2   5  -2,  1  -2   1]");
	engEvalString(ep, "A = conv2 (J,h1,'same')");
	engEvalString(ep, "subplot (2,2,2), imshow (A, [ ])");
	engEvalString(ep, "B= conv2 ( J, h2, 'same' )");
	engEvalString(ep, "subplot(2,2,3 ), imshow (B, [ ])");
	engEvalString(ep, "C = conv2 (J, h3, 'same' )");
	engEvalString(ep, "subplot (2,2,4), imshow (C, [ ])");
	printf("press any key to exit!");
	getchar();
	mxDestroyArray(I);
	mxDestroyArray(J);
	mxDestroyArray(A);
	mxDestroyArray(B);
	mxDestroyArray(C);
	engClose(ep);
}



//��1�С���3�У�������C�������еı�Ҫ�ļ����ⲿ����MATLAB����������ͷ�ļ�engine.h 
int main()
{
	smooth_sharpness();
	//Opencv_Matlab_C();
	return 0;
}



