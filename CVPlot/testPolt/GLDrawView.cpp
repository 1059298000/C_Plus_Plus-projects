// GLDrawView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GLDrawView.h"
#include "IndexLocationDlg.h"
// CGLDrawView
#define MAX_VERTICES 1000000
#define DATA_SIZE 100000

IMPLEMENT_DYNCREATE(CGLDrawView, CView)

CGLDrawView::CGLDrawView()
{

    textLists_ = 0;
    clientWidth_ = 1;
    clientHeight_ = 1;
    vcWidthRatio_ = 1.0;
    vcHightRatio_ = 1.0;
    viewHalfWidth_ = 20;
    viewHalfHight_ = 20;
    marginWidth_ = 50;
    marginHight_ = 50;
    translateX_ = 0.0;
    translateY_ = 0.0;
    bBtnDown_ = false;
    bCtrlDown_ = false;
    scaleX_ = 1;
    scaleY_ = 1;
    dispWidthPerUnitX_ = 2*viewHalfWidth_/20;
    dispHightPerUnitY_ = 2*viewHalfHight_/1000;
    charWidth_ = 1;
    charHight_ = 1;
}



// CGLDrawView ��ͼ

void CGLDrawView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
    DrawGLScene();
}


BOOL CGLDrawView::InitGL( GLvoid )
{
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(1.0,1.0,1.0,0.0);// Background
    glClearDepth(1.0f);                                    // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations
    return TRUE;                                        // Initialization Went OK

}

BOOL CGLDrawView::InitTextLists()
{
    // ����MAX_CHAR����������ʾ�б���
    textLists_ = glGenLists(128);

    // ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
    wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, textLists_);

    TEXTMETRIC tm;
    GetTextMetrics(wglGetCurrentDC(),&tm);
    charWidth_ = tm.tmAveCharWidth;
    charHight_ = tm.tmHeight;

    return TRUE;
}


int CGLDrawView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������
    hDC_ = GetDC()->GetSafeHdc();
    if(SetWindowPixelFormat(hDC_)==FALSE)
    {//�������ظ�ʽ
        return 0;
    }
    if(CreateViewGLContext(hDC_)==FALSE)
    {//����RC��ѡΪ����
        return 0;
    }
    if(!InitGL())
    {//��ʼ��openGL
        return 0;
    }
    if(!InitTextLists())
    {//��ʼ����ʾ�б�
        return 0;
    }
    if(!InitVBO())
    {//��ʼ��vbo
        return 0;
    }

    return 0;
}



int CGLDrawView::DrawGLScene( GLvoid )
{
    pixelPerUnitY_ = dispHightPerUnitY_*scaleY_/vcHightRatio_;
    pixelPerUnitX_ = dispWidthPerUnitX_*scaleX_/vcWidthRatio_;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear Screen And Depth Buffer

    drawCoordinate();
    drawRulerX();
    drawRulerY();
    drawData();
    drawMouseRect();

    ::SwapBuffers(hDC_);
    glFlush();
    return TRUE;                                        // Everything Went OK
}

void CGLDrawView::drawString( const char* str )
{
    // ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
    for(; *str!='\0'; ++str)
        glCallList(textLists_ + *str);
}

void CGLDrawView::drawCoordinate()
{
    glPushMatrix();

    glLoadIdentity();
    glTranslatef( -viewHalfWidth_+marginWidth_*vcWidthRatio_, -viewHalfHight_+marginHight_*vcHightRatio_, 0);

    //����������
    glBegin(GL_LINES );
    glColor3f(0.0f,0.0f,1.0f);
    glVertex2f(0.0f,0.0f);
    glVertex2f(1000.0f,0.0f);
    glVertex2f(0.0f,0.0f);
    glVertex2f(0.0f,1000.0f);
    glEnd();

    glPopMatrix();
}

void CGLDrawView::drawRulerX()
{
    //������
    glPushMatrix();
    glLoadIdentity();
    glScalef(scaleX_,1,1);
    glTranslatef( -viewHalfWidth_+marginWidth_*vcWidthRatio_, -viewHalfHight_+marginHight_*vcHightRatio_, 0);

    glEnable(GL_SCISSOR_TEST);
    glScissor(marginWidth_,0,clientWidth_-marginWidth_,clientHeight_);
    glTranslatef( translateX_*vcWidthRatio_, 0, 0);

    //ԭ��
    glBegin(GL_LINES );
    glColor3f(0.0f,0.0f,1.0f);
    glVertex2f(0.0,0.0);
    glVertex2f(0.0,5*vcHightRatio_);
    glEnd();
    glColor3f(1.0f,0.0f,1.0f);
    glRasterPos2f(0,-12*vcHightRatio_);
    drawString("0");

    UINT xInterval = 1;
    GLdouble stringWidth = charWidth_*7;
    if ( pixelPerUnitX_ > stringWidth )
        xInterval = 1;  //ÿ���̶ȶ���ʶ����
    else if ( (pixelPerUnitX_ > stringWidth/5.0)&&(pixelPerUnitX_ <= stringWidth) )
        xInterval = 5;  //ÿ5���̶ȱ�ʶһ������
    else if ( (pixelPerUnitX_ > stringWidth/10.0)&&(pixelPerUnitX_ <= stringWidth/5.0) )
        xInterval = 10; //ÿ10���̶ȱ�ʶһ������
    else if ( (pixelPerUnitX_ > stringWidth/50.0)&&(pixelPerUnitX_ <= stringWidth/10.0) )
        xInterval = 50; //ÿ50���̶ȱ�ʶһ������
    else if ( (pixelPerUnitX_ > stringWidth/100.0)&&(pixelPerUnitX_ <= stringWidth/50.0) )
        xInterval = 100; //ÿ100���̶ȱ�ʶһ������
    else if ( (pixelPerUnitX_ > stringWidth/500.0)&&(pixelPerUnitX_ <= stringWidth/100.0) )
        xInterval = 500; //ÿ500���̶ȱ�ʶһ������
    else if ( (pixelPerUnitX_ > stringWidth/1000.0)&&(pixelPerUnitX_ <= stringWidth/500.0) )
        xInterval = 1000; //ÿ1000���̶ȱ�ʶһ������
	else
		xInterval = 5000;

    char strXValue[20];
    if (data_&&dataSize_)
    {
        //���¼����º�����������ʾ�ķ�Χ���Խ�ʡ��������
        GLint indexSpan = (GLint)(clientWidth_/pixelPerUnitX_)/2+2;
        GLint startIndex = max(0,(GLint)((clientWidth_/2-translateX_)*scaleX_/pixelPerUnitX_)-indexSpan);
        GLint endIndex = min(DATA_SIZE,startIndex + 2*indexSpan);

        for (int i=startIndex;i<=endIndex;i++)
        {
            //�̶�
            if ((xInterval==1)||(xInterval==5)||(2*i%xInterval==0))
            {
                glBegin(GL_LINES );
                glColor3f(0.0f,0.0f,1.0f);
                glVertex2f(i*dispWidthPerUnitX_,0.0);
                glVertex2f(i*dispWidthPerUnitX_,5*vcHightRatio_);
                glEnd();
            }
            //����
            if ( i%xInterval == 0)
            {
                glColor3f(1.0f,0.0f,1.0f);
                glRasterPos2f(i*dispWidthPerUnitX_,-12*vcHightRatio_);
                sprintf(strXValue,"%d",i);
                drawString(strXValue);
            }
        }
        glPopMatrix();
    }

    glDisable(GL_SCISSOR_TEST);
    glPopMatrix();
}

void CGLDrawView::drawRulerY()
{
    //������
    glPushMatrix();
    glLoadIdentity();
    glScalef(1,scaleY_,1);
    glTranslatef( -viewHalfWidth_+marginWidth_*vcWidthRatio_, -viewHalfHight_+marginHight_*vcHightRatio_, 0);

    glEnable(GL_SCISSOR_TEST);
    glScissor(0,marginHight_,clientWidth_,clientHeight_-marginHight_);
    glTranslatef( 0, translateY_*vcHightRatio_, 0);

    //ԭ��
    glBegin(GL_LINES );
    glColor3f(0.0f,0.0f,1.0f);
    glVertex2f(0.0,0.0);
    glVertex2f(0.0,5*vcHightRatio_);
    glEnd();
    glColor3f(1.0f,0.0f,1.0f);
    glRasterPos2f(-2*charWidth_*vcWidthRatio_,0);
    drawString("0");

    UINT yInterval = 1;
    GLdouble stringHight = charHight_*3;
    if ( pixelPerUnitY_ > stringHight )
        yInterval = 1;  //ÿ���̶ȶ���ʶ����
    else if ( (pixelPerUnitY_ > stringHight/5.0)&&(pixelPerUnitY_ <= stringHight) )
        yInterval = 5;  //ÿ5���̶ȱ�ʶһ������
    else if ( (pixelPerUnitY_ > stringHight/10.0)&&(pixelPerUnitY_ <= stringHight/5.0) )
        yInterval = 10; //ÿ10���̶ȱ�ʶһ������
    else if ( (pixelPerUnitY_ > stringHight/50.0)&&(pixelPerUnitY_ <= stringHight/10.0) )
        yInterval = 50; //ÿ50���̶ȱ�ʶһ������
    else if ( (pixelPerUnitY_ > stringHight/100.0)&&(pixelPerUnitY_ <= stringHight/50.0) )
        yInterval = 100; //ÿ100���̶ȱ�ʶһ������
    else if ( (pixelPerUnitY_ > stringHight/500.0)&&(pixelPerUnitY_ <= stringHight/100.0) )
        yInterval = 500; //ÿ500���̶ȱ�ʶһ������
    else if ( (pixelPerUnitY_ > stringHight/1000.0)&&(pixelPerUnitY_ <= stringHight/500.0) )
        yInterval = 1000; //ÿ1000���̶ȱ�ʶһ������
    else if ( (pixelPerUnitY_ > stringHight/5000.0)&&(pixelPerUnitY_ <= stringHight/1000.0) )
        yInterval = 5000;
    else
        yInterval = 10000;

    //�̶�
    char strYValue[10];
    for (int j=1;j<=30000;j++)
    {
        //�̶�
        if ((yInterval==1)||(yInterval==5)||(2*j%yInterval==0))
        {
            glBegin(GL_LINES );
            glColor3f(0.0f,0.0f,1.0f);
            glVertex2f(0.0,j*dispHightPerUnitY_);
            glVertex2f(5*vcWidthRatio_,j*dispHightPerUnitY_);
            glEnd();
        }
        //����
        if (j%yInterval==0)
        {
            glColor3f(1.0f,0.0f,1.0f);
            glRasterPos2f(-40*vcWidthRatio_,j*dispHightPerUnitY_);
            sprintf(strYValue,"%d",j);
            drawString(strYValue);
        }
    }
    glPopMatrix();
}

void CGLDrawView::drawData()
{
    //���ƾ��������
    glPushMatrix();
    glLoadIdentity();                                    // Reset The Current Modelview Matrix
    glScalef(scaleX_,scaleY_,1);
    glTranslatef( -viewHalfWidth_+marginWidth_*vcWidthRatio_, -viewHalfHight_+marginHight_*vcHightRatio_, 0);

    glEnable(GL_SCISSOR_TEST);
    glScissor(marginWidth_,marginWidth_,clientWidth_-marginWidth_,clientHeight_-marginWidth_);

    glTranslatef( translateX_*vcWidthRatio_, translateY_*vcHightRatio_, 0);

    if (data_&&dataSize_)
    {
        glColor3f(1.0,0.0,0.0);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_);
        glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, dataSize_* 2 *sizeof(GLfloat), data_);
        glDrawArrays(GL_LINE_STRIP , 0, dataSize_);
    }

    glDisable(GL_SCISSOR_TEST);
    glPopMatrix();

}



void CGLDrawView::resetData()
{
    if (data_)
    {
        delete []data_;
        data_ = NULL;
        dataSize_ = 0;
    }
}





