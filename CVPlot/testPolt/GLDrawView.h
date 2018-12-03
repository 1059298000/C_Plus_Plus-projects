#pragma once

#include "glut\glut.h"
#include "glut\glInfo.h"
#include "glut\glext.h"

using namespace std;

// CGLDrawView ��ͼ

class CGLDrawView : public CView
{

public:
	CGLDrawView();
	virtual ~CGLDrawView();

protected:
    BOOL InitGL(GLvoid);				//��ʼ��openGL
    int DrawGLScene(GLvoid);			//��ͼ������
    void drawString(const char* str);   //��ʾ����
    void drawCoordinate();				//������
    void drawRulerX();					//�������ߡ��̶ȡ�����
    void drawRulerY();					//�������ߡ��̶ȡ�����
    void drawData();					//��������ֵ
    void drawMouseRect();				//�������ŵľ��ο�
    void fit2Rect(CRect &rect);			//��������
	void resetData();


    GLdouble viewHalfWidth_,viewHalfHight_;     //�Ӿ������
    GLsizei clientWidth_,clientHeight_;         //���ڿ��
    GLfloat vcWidthRatio_,vcHightRatio_;        //�Ӵ���
    GLsizei marginWidth_,marginHight_;          //�ǻ�ͼ����
    
    GLuint textLists_;	//������ʾ�б�
    LONG charWidth_;	//�ַ�ƽ���ֿ�
    LONG charHight_;	//�ַ��߶�

    GLfloat translateX_,translateY_;	//��������ƽ����
    GLfloat scaleX_,scaleY_;			//��������������

    GLdouble dispHightPerUnitY_;	//Y��ÿ��λ���Ӿ����еĳ���
    GLdouble pixelPerUnitY_;		//Y��ÿ��λռ���ڵ�����ֵ
    GLdouble dispWidthPerUnitX_;	//X��ÿ��λ���Ӿ����еĳ���
    GLdouble pixelPerUnitX_;		//X��ÿ��λռ���ڵ�����ֵ

    GLfloat* data_;    //����
    GLuint dataSize_;  //���ݴ�С

public:
	BOOL loadData();
};
