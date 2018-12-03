#include "StdAfx.h"
#include "AVIHandle.h"
#include <vfw.h>

#pragma comment(lib,"vfw32.lib")


AVIHandle::AVIHandle(void):gray_value(NULL),gray_value_square(NULL)
{
	this->loaded = FALSE;
}

AVIHandle::AVIHandle(CString filename):gray_value(NULL),gray_value_square(NULL)
{
	this ->loaded = FALSE;
	LoadVideo(filename);
}
AVIHandle::~AVIHandle(void)
{
	if(gray_value != NULL) free(gray_value);
	if(gray_value_square != NULL) free(gray_value_square);
}



//������Ƶ����
BOOL AVIHandle::LoadVideo(CString filename)
{
	//��ȡAVI�ļ���Ϣ
	HRESULT result;
	AVIFileInit(); //ʹ��AVI�庯����ȡAVI�ļ�ǰӦ���ȵ���
	
	PAVIFILE pfile;//AVI�ļ�ָ��
	AVIFILEINFO pfi;//AVI�ļ���Ϣ
	PAVISTREAM pavi;//AVI��
	AVISTREAMINFO stinfo;//AVI����Ϣ
	
	//��AVI�ļ�
	result=AVIFileOpen(&pfile,filename,OF_READ,NULL);
	//AVI�ļ���Ϣ
	result=AVIFileInfo(pfile,&pfi,sizeof(AVIFILEINFO));
	//���AVI��Ƶ��
	result=AVIFileGetStream(pfile,&pavi,streamtypeVIDEO,0);
	//���AVI��Ƶ����Ϣ
	result=AVIStreamInfo(pavi,&stinfo,sizeof(AVISTREAMINFO));
	//���AVI��
	pgf = AVIStreamGetFrameOpen(pavi,NULL);
 
    if (pgf==NULL)
    {
		//���ݳ���
		return FALSE;
    }

	HRESULT hr;

	//�������Ŀ�͸�
	int cx=pfi.dwWidth;//ͼ�����
	int cy=pfi.dwHeight;
	
	width=cx;
	height=cy;
	length=pfi.dwLength;


	//AVI���ʽ��λͼHeader,λͼ�����ʽ��
	lpbm = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf,1);
	
	defaultPad=3;

	//���仺���ڴ�ռ�
	//����仺��
	gray_value = (unsigned char*)malloc(sizeof(unsigned char)*width*height*3);
	//��仺��
	gray_value_square = (unsigned char*)malloc(sizeof(unsigned char)*(width+defaultPad)*(height+defaultPad)*3);

	this->loaded = TRUE;

	return TRUE;
}

//���һ��Frame
unsigned char* AVIHandle::GetSingleFrame(int i)
{
	return (unsigned char*)AVIStreamGetFrame(pgf,i);
	//return NULL;
}

int AVIHandle::GetFrameCount(void)
{
	return this->length;
}


int AVIHandle::GetFrameWidth(void)
{
	return this->width;
	//return 0;
}


int AVIHandle::GetFrameHeight(void)
{
	return this->height;
	//return 0;
}

//����ͼ���BMP��ʽ����
LPBITMAPINFOHEADER AVIHandle::GetLPBM(void)
{
	return this->lpbm;
}

BOOL AVIHandle::isLoaded(void)
{
	return this->loaded;
}
