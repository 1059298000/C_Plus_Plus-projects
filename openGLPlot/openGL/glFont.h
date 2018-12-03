// GLfont.h: interface for the CMiscGL class.
// ��������ࣺ����д�ģ�����by kidwei
// ԭ��������д���ڴ�dc����Ϊһ���ڴ�λͼ���ٽ�λͼ�����������
// һ�����������ʹ�÷�����
// 1�����ͷ�ļ�glFont.h
// 2�����ӳ�Ա������GLfont font��Ҳ���Զ�̬���䣩
// 3��Ĭ�������ڹ��캯���Ѿ���ʼ���ˣ������Ҫ�ı䣬��OpenGL��ʼ�������µ��ã�
//      font.CreateFont("����", 12, FW_DONTCARE,false,false,false)
// 4����������� font.ShowText(-0.90,-0.99,"���������",0,1,0); �������귶Χ��-1��1������������������ɫ
// ����Ӣ������ʹ�÷�����
// 1.2 ������������ͬ
// 3. �����ڳ�����ʼ����ʱ����ã�  font.BuildEnglishFont(hdc,12);
// 4. ���������font.glPrintEnglish(0,0,0,1,1,"this is my English font:%d",5);
// 5. ǰ����������λ�ã��м�������������ɫ�������Ը�ʽ�����
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MISCGL_H__3CF8DCE9_7A54_4519_AA65_5B375C048664__INCLUDED_)
#define AFX_MISCGL_H__3CF8DCE9_7A54_4519_AA65_5B375C048664__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
class GLfont
{
 HFONT m_hFont;
 unsigned int base;
public:
 GLfont();
 virtual ~GLfont();
 void BuildEnglishFont(HDC hDC,int size); 
 void glPrintEnglish(float x,float y,float r,float g,float b,const char *fmt, ...);
 void CreateFont(char *facename, int height, int weight, bool italic,bool underline,bool strikeout);
 void ShowText(float x, float y, LPCTSTR lpszText,float r,float g,float b);

};

#endif // !defined(AFX_MISCGL_H__3CF8DCE9_7A54_4519_AA65_5B375C048664__INCLUDED_)



