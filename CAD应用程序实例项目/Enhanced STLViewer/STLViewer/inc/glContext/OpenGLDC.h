// OpenGLDC.h: interface for the COpenGLDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLDC_H__30E692A3_4129_11D4_B1EE_0010B539EBC0__INCLUDED_)
#define AFX_OPENGLDC_H__30E692A3_4129_11D4_B1EE_0010B539EBC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl/gl.h"

#include "gl/glu.h"

#define GLUT_DISABLE_ATEXIT_HACK
#include <gl\glut.h>

#include "gl/glaux.h"
#pragma comment(lib, "glaux")// ����ӵ����������ó����޷�ʶ����ⲿ����
#pragma comment(lib, "legacy_stdio_definitions") // ǿ�Ƽ��ݾɵĴ��룬����ͨ��

#include "camera.h"
#include "..\inc\GeomCalc\cadbase.h"

#define BUFFER_LENGTH 64

class AFX_EXT_CLASS COpenGLDC
{
public:
	// ��������������
	COpenGLDC(HWND hWnd);
	virtual ~COpenGLDC();


private:
	// �������ڵľ��
	HWND	m_hWnd;
	// ��Ⱦ�����ľ��
	HGLRC	m_hRC;
	// �豸�������
	HDC		m_hDC;

	COLORREF	m_clrBk;		//Background Color ���ڱ�����ɫ
	// �ǹ���ģʽ�µ�ģ����ɫ
	COLORREF	m_clr;			//Polygon Color for unshading ģ����ɫ
	// ���ڸ�������ʾʱ��ģ����ɫ����ʰȡ��һ������ʱ��Ҫ��������ʾ
	COLORREF	m_clrHighlight; //for highlight using  
	COLORREF	m_clrMaterial;  //for normal rendering ���ϵ���ɫ
	BOOL		m_bShading;		//use material property �Ƿ������ɫ��ʾ
	GLfloat		m_vecLight[3];	//lighting direction ��Դ�ķ���

	//selection
	BOOL	m_bSelectionMode; // ��ǰ�Ƿ���ѡ��ģʽ
	GLuint	m_selectBuff[BUFFER_LENGTH]; // ѡ�񻺴���
public:
	GCamera		m_Camera; // �����������ȡ������
	

protected:
	void ClearBkground(); // ���������ɫ
	void OnShading(); // ����/�ǹ���ģʽ����
	

public:
	//initialize
	BOOL InitDC(); // ��ʼ��
	void GLResize(int cx,int cy); // ��Ӧ���ڳߴ�仯
	void GLSetupRC(); // ������Ⱦ����

	//uMode :zero for normal rendering. non-zero for selection
	void Ready(); // ����ǰ׼������
	void Finish(); // �������ƺ���

	/////////////////////// light & color //////////////////////
	// ����/�ǹ���ģʽ����
	void Shading(BOOL bShading);

	// ��ǰ�Ƿ�����ɫģʽ
	BOOL IsShading();

	// �Ƿ�ʹ�ù�Դ
	void Lighting(BOOL bLighting);
	BOOL IsLighting();

	//Light direction �������ȡ��Դ����
	void SetLightDirection(float dx,float dy,float dz);
	void GetLightDirection(float& dx,float& dy,float& dz);

	//material �������ȡ������ɫ
	void SetMaterialColor(COLORREF clr);
	void GetMaterialColor(COLORREF& clr);
	
	//back ground �������ȡ������ɫ
	void SetBkColor(COLORREF rgb);
	void GetBkColor(COLORREF& rgb);
	
	//frame material �������ȡ�ǹ���ģʽ�µĻ�����ɫ
	void SetColor(COLORREF rgb);
	void GetColor(COLORREF& rgb);

	//high light setting �������ȡ��������ʾ����ɫ
	void SetHighlightColor(COLORREF clr);
	void GetHighlightColor(COLORREF& clr);

	// ��������������ʾ�л�
	void Highlight(BOOL bLight = TRUE);


	/////////////////// Drawing ////////////////////

	// ����һ���ռ��
	void DrawPoint(const CPoint3D&); 

	//drawing curves
	// �����û�����ϵ
	void DrawCoord();

    //����һ��ֱ��
	void DrawLine(const CPoint3D& sp,const CPoint3D& ep); 
	
	// ������������
	void DrawPolyline(const CPoint3D* pt,int size);
	
	//drawing surface 
	//����һ��������Ƭ
	void DrawTriChip(double n0,double n1,double n2,double v00,double v01,double v02,
					double v10,double v11,double v12,double v20,double v21,double v22);

	//drawing solid entities
	// ����һ��Բ��
	void DrawSphere(const CPoint3D& cen,double r,const CVector3D& vec);

	// ����һ��Բ��
	void DrawCylinder(const CPoint3D& cen,double r,const CVector3D& h);

	// ����һ��Բ׶
	void DrawCone(const CPoint3D& cen,double r,const CVector3D& h);

	// ����һ��Բ��
	void DrawTorus(const CPoint3D& cen,const CVector3D& ax,double r_in,double r_out);

	// ����һ�����
	void DrawTeapot(const CPoint3D& cen, double size, const CVector3D& vec);

	// ����4����
	void DrawTetrahedron(const CPoint3D& cen, double radius, const CVector3D& vec);

	// ����8����
	void DrawOctahedron(const CPoint3D& cen, double radius, const CVector3D& vec);

	// ����12����
	void DrawIcosahedron(const CPoint3D& cen, double radius, const CVector3D& vec);


	//selection Mode
	// ��ʼѡ��
	void	BeginSelection(int xPos,int yPos);

	// ����ѡ�񣬷���ѡ���¼
	int		EndSelection(UINT* items);

	// ��ǰ�Ƿ���ѡ��ģʽ
	BOOL	IsSelectionMode();

	// ����ѡ��ģʽ�µĶ������Ʋ���
	void	InitNames();
	void	LoadName(UINT name);
	void	PushName(UINT name);
	void    PopName();

};

class AFX_EXT_CLASS CGLView : public CView
{
protected:
	COpenGLDC*	m_pGLDC;

protected: // create from serialization only
	CGLView();
	DECLARE_DYNCREATE(CGLView)

// Attributes
public:
	virtual void RenderScene(COpenGLDC* pDC);

	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLView();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// ��ȡ��ǰģ�͵������ݺ�
	virtual BOOL GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1);
	
	// ���ų���
	void	Zoom(double dScale);

	// ����һ�����ʵ����űȣ��Խ�ģ��ȫ����ʾ�ڳ�����
	void	ZoomAll();

	// ʹ�õ����ӽ����۲�ģ��
	void	OnViewType(UINT type);

	// ����ǰ�����ߴ�İٷֱ��ƶ�����������dpx��dpy�ķ�Χ��0-1
	void	MoveView(double dpx,double dpy);
	
};
#endif // !defined(AFX_OPENGLDC_H__30E692A3_4129_11D4_B1EE_0010B539EBC0__INCLUDED_)
