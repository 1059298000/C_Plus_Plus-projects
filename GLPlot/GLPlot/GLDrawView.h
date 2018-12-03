#pragma once

#include "glut\glut.h"
#include "glut\glInfo.h"
#include "glut\glext.h"

using namespace std;

// CGLDrawView ��ͼ

class CGLDrawView : public CView
{
	DECLARE_DYNCREATE(CGLDrawView)

public:
	CGLDrawView();
	virtual ~CGLDrawView();

    PFNGLGENBUFFERSARBPROC glGenBuffersARB;                     // VBO Name Generation Procedure
    PFNGLBINDBUFFERARBPROC glBindBufferARB;                     // VBO Bind Procedure
    PFNGLBUFFERDATAARBPROC glBufferDataARB;                     // VBO Data Loading Procedure
    PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;               // VBO Sub Data Loading Procedure
    PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;               // VBO Deletion Procedure
    PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB; // return various parameters of VBO
    PFNGLMAPBUFFERARBPROC glMapBufferARB;                       // map VBO procedure
    PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;                   // unmap VBO procedure

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    BOOL SetWindowPixelFormat(HDC hDC);	//�������ظ�ʽ
    BOOL CreateViewGLContext(HDC hDC);	//�������ƻ���(RC)��ʹ֮��Ϊ��ǰ���ƻ���
    BOOL InitGL(GLvoid);				//��ʼ��openGL
    BOOL InitTextLists();				//��ʼ��������ʾ�б�
    BOOL InitVBO();						//��ʼ��VBO
    int DrawGLScene(GLvoid);			//��ͼ������
    void drawString(const char* str);   //��ʾ����
    void drawCoordinate();				//������
    void drawRulerX();					//�������ߡ��̶ȡ�����
    void drawRulerY();					//�������ߡ��̶ȡ�����
    void drawData();					//��������ֵ
    void drawMouseRect();				//�������ŵľ��ο�
    void fit2Rect(CRect &rect);			//��������
	void resetData();

    HGLRC m_hGLContext;     //���ƻ���
    HDC hDC_;				//�豸����
    GLuint vbo_;			//vbo��ʶ
    GLdouble viewHalfWidth_,viewHalfHight_;     //�Ӿ������
    GLsizei clientWidth_,clientHeight_;         //���ڿ��
    GLfloat vcWidthRatio_,vcHightRatio_;        //�Ӵ���
    GLsizei marginWidth_,marginHight_;          //�ǻ�ͼ����
    
    GLuint textLists_;	//������ʾ�б�
    LONG charWidth_;	//�ַ�ƽ���ֿ�
    LONG charHight_;	//�ַ��߶�

    GLfloat translateX_,translateY_;	//��������ƽ����
    GLfloat scaleX_,scaleY_;			//��������������
    bool bBtnDown_;		//����������
    bool bCtrlDown_;	//CTRL������
    CPoint initPoint_;	//����������ʱ������
    CPoint lastPoint_;	//�ƶ��б������ʱ����

    GLdouble dispHightPerUnitY_;	//Y��ÿ��λ���Ӿ����еĳ���
    GLdouble pixelPerUnitY_;		//Y��ÿ��λռ���ڵ�����ֵ
    GLdouble dispWidthPerUnitX_;	//X��ÿ��λ���Ӿ����еĳ���
    GLdouble pixelPerUnitX_;		//X��ÿ��λռ���ڵ�����ֵ

    GLfloat* data_;    //����
    GLuint dataSize_;  //���ݴ�С

public:
	BOOL loadData();

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags,short zDelta,CPoint pt );
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnDispInit();
    afx_msg void OnLocateIndex();
    afx_msg void OnDispHelp();

};
