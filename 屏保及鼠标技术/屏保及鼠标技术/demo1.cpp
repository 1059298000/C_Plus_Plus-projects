#include <graphics.h>
#include <time.h>
#include <conio.h>
int Height;
int Width;
/*
�˳����޷�ͨ�������ܴ˲�������ݴ�vs�汾
*/
int main()
{
	//���������������
	srand((unsigned)time(NULL));
	//��ʼ������
	initgraph(1920, 1080);
	int x, y; // ��x��y������
	char c;  //�ַ�
	//��������
	settextstyle(16, 8, _T("Courier")); // ��Ϊ�汾���⣬����Ӧ

	//ȥ�߿���������ʽ
	//��ȡ�û�����Ŀ�͸�
	Width = GetSystemMetrics(SM_CXSCREEN);
	Height = GetSystemMetrics(SM_CYSCREEN);

	//���µ��ó�ʼ��ͼ�δ��ڲ����ؾ��
	HWND hwnd = initgraph(Width, Height);

	//��ȡ���嵱ǰ����д��style
	long style = GetWindowLong(hwnd, GWL_STYLE);

	//ȥ������߿�
	style &= ~WS_CAPTION;

	//�޸�style���ô���
	SetWindowLong(hwnd, GWL_STYLE,style);

	//�ƶ�������ȫ��
	MoveWindow(hwnd, 0, 0, Width, Height, true);




	//������ɫ
	settextcolor(GREEN);
	setlinecolor(BLACK);
	for (int i = 0; i <= 1919; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			x = (rand() % 80) * 24; // 24*80 = 1920
			y = (rand() % 20) * 54; // 54*20 = 1080
			c = (rand() % 26) + 65; // ��дӢ��26����ĸ�������
			outtextxy(x, y, c);
		}
		
		line(0, i, 1919, i);		//���߲�����ǰ��ĸ
		Sleep(20);					// ��ʱ����
		if (i >= 1919) i = -1;		//ѭ������
		if (_kbhit()) break;			//_kbhit()��������˳�
	}

	//�رմ���
	closegraph();
	return 0;
}