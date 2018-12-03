// Matlab style plot functions for OpenCV
//author libing64 && Jack Dong
//https://github.com/libing64/CPlot
//

#include "plot.h"
#include<iostream>

int main(int argc, char* argv[])
{
	const int Cnt = 80;
	double X[Cnt] = { 0 };
	double Y[Cnt] = { 0 };
	//for(int i = 0; i < Cnt; i++)
	//{
	//	X[i] = (double)i;
	//	Y[i] = (double)i - 20;
	//}
	//
	//cvNamedWindow("hello",1);
	//CPlot plot;
	//plot.x_max = 100; //�����趨��������������Сֵ
	//plot.x_min = -20;
	//plot.y_max = 400;
	//plot.y_min = -200;
	//plot.axis_color = Scalar(0,255,0);
	//plot.text_color = Scalar(255,0,255);
	//plot.plot(Y, Cnt, CV_RGB(0, 0, 0)); //����ֻ����Yֵ XĬ�ϴ�0��ʼ 
	//plot.title("this is a title"); //�����趨���� ֻ����Ӣ�� ���Ļ����� �н�����������Ǻ��鷳
	//plot.xlabel("this X",Scalar(255,255,0));
	//plot.ylabel("this Y",Scalar(255,255,0));
	//cvShowImage("hello", plot.Figure);
	//cvWaitKey(0);

	//imwrite("1.jpg",Mat(plot.Figure));

	////�����һ��ͼ�л��ƶ������ݣ�ÿ�λ��Ƶ�ͬʱ�������ݽ��д洢��
	//for(int i = 0; i < Cnt; i++)
	//{
	//	X[i] = (double)i;
	//	Y[i] = (double)(5*i - 20);
	//}
	//plot.plot(X, Y, Cnt, CV_RGB(0, 255, 180), '.',false);//���δ���Ĳ����� X�����ݣ� Y�����ݣ� ���ݳ��ȣ� ������ɫ����������ͣ�Ĭ����'*'���������֮���Ƿ���Ҫ���ӣ�Ĭ�����ӣ� 
	//cvShowImage("hello", plot.Figure);
	//cvWaitKey(0);
	//
	//for(int i = 0; i < Cnt; i++)
	//{
	//	X[i] = (double)i;
	//	Y[i] = (double)(-5*i - 20);
	//}
	//plot.plot(X, Y, Cnt, CV_RGB(0,255, 0), 's');
	//cvShowImage("hello", plot.Figure);
	//cvWaitKey(0);
	//imwrite("2.jpg",Mat(plot.Figure));
	//
	//for(int i = 0; i < Cnt; i++)
	//{
	//	X[i] = (double)i;
	//	Y[i] = (double)(50*sin(i*0.1));
	//}
	//plot.plot(X, Y, Cnt, CV_RGB(0, 0, 255), 'x');
	//cvShowImage("hello", plot.Figure);
	//cvWaitKey(0);

	//imwrite("3.jpg",Mat(plot.Figure));



	//plot.clear();//���ǰ��Ĵ洢������


	//for(int i = 0; i < Cnt; i++)
	//{
	//	X[i] = (double)i;
	//	Y[i] = (double)(100*sin(i*0.1));
	//}

	//plot.plot(X, Y, Cnt, CV_RGB(255, 255, 0), 'o',false);
	//cvShowImage("hello", plot.Figure);
	//cvWaitKey(0);

	//imwrite("4.jpg",Mat(plot.Figure));

	//int X2[Cnt] = {0};
	//int Y2[Cnt] = {0};
	//for(int i = 0; i < Cnt; i++)
	//{
	//	X2[i] = i;
	//	Y2[i] = -30*i - 20;
	//}
	//plot.plot(X2, Y2, Cnt/2, CV_RGB(0, 255, 255),'*',false); //Ĭ�ϻ�ѵ����֮��������һ��
	//cvShowImage("hello", plot.Figure);
	//cvWaitKey(0);
	////cvSaveImage("example.jpg", plot.Figure);
	//imwrite("4.jpg",Mat(plot.Figure));



	//C++ ��չ
	Plot p;
	//std::vector<cv::Point2f> points;
	//std::vector<int> Y_points;
	//cv::Point2f p_temp;
	//for(int i = 0; i < Cnt; i++)
	//{
	//	p_temp.x = i;
	//	p_temp.y = -10*i - 20;
	//	points.push_back(p_temp);
	//	Y_points.push_back(i * 5 + 1);
	//}
	//p.plot(Y_points, cv::Scalar(255,255,0));
	//imshow("hi", p.figure());
	//cv::waitKey();

	std::vector<cv::Point2f> points2;
	cv::Point2f p_temp;
	p_temp.x = 0.0130162;
	p_temp.y = 0.94;
	points2.push_back(p_temp);

	p_temp.x = 0.0432221;
	p_temp.y = 0.902222;
	points2.push_back(p_temp);

	p_temp.x = 0.132769;
	p_temp.y = 0.864444;
	points2.push_back(p_temp);

	p_temp.x = 0.351267;
	p_temp.y = 0.826667;
	points2.push_back(p_temp);

	p_temp.x = 0.775798;
	p_temp.y = 0.788889;
	points2.push_back(p_temp);

	p_temp.x = 1.47011;
	p_temp.y = 0.751111;
	points2.push_back(p_temp);

	p_temp.x = 2.4696;
	p_temp.y = 0.713333;
	points2.push_back(p_temp);

	p_temp.x = 3.73663;
	p_temp.y = 0.675556;
	points2.push_back(p_temp);

	p_temp.x = 5.19858;
	p_temp.y = 0.637778;
	points2.push_back(p_temp);

	p_temp.x = 6.72799;
	p_temp.y = 0.6;
	points2.push_back(p_temp);

	p.plot(points2, cv::Scalar(255,0,0), '*', true);
	imshow("hi", p.figure());
	cv::waitKey();

	return 0;
}

