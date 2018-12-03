// GLView.cpp : implementation of the CGLView class
//

#include "stdafx.h"
#include "GL.h"

#include "GLDoc.h"
#include "GLView.h"

//#define GLUT_DISABLE_ATEXIT_HACK
//#include <gl\glut.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLView

IMPLEMENT_DYNCREATE(CGLView, CView)

BEGIN_MESSAGE_MAP(CGLView, CView)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLView construction/destruction

CGLView::CGLView()
{
	m_hDC = NULL;
	m_hRC = NULL;
	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_Scale = 1.0f;

}

CGLView::~CGLView()
{
}

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs)
{

	//  Add Window style required for OpenGL before window is created
	cs.style |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CS_OWNDC;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGLView drawing

void CGLView::OnDraw(CDC* pDC)
{
	wglMakeCurrent(m_hDC,m_hRC); // ��ǰ����Ⱦ����

	RenderScene(); // �������⺯�����������OpenGLͼ��

	SwapBuffers(m_hDC); // ����֡��

	wglMakeCurrent(m_hDC,NULL); // �ǵ�ǰ����Ⱦ����
}

/////////////////////////////////////////////////////////////////////////////
// CGLView diagnostics

#ifdef _DEBUG

CGLDoc* CGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLDoc)));
	return (CGLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	GLInit();// ��ͼ���ڴ�����ɺ󣬽���OpenGL Windows�ĳ�ʼ������

	// �ú���Ϊϵͳ����һ�����Ϊ0�Ķ�ʱ��
	//SetTimer(0,50,NULL); // ÿ��50ms������ϢWM_TIMER

	return 0;
}



BOOL CGLView::OnEraseBkgnd(CDC* pDC) // ���ڱ�������
{
	//return CView::OnEraseBkgnd(pDC);
	return FALSE; // ���ε�MFC�Ĵ��ڲ������������α��������������Ļ����Ч��
}

void CGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	VERIFY(wglMakeCurrent(m_hDC,m_hRC));

	GLResize(cx,cy); // ���ڴ����ڳߴ�ı仯

	VERIFY(wglMakeCurrent(NULL,NULL));
}

void CGLView::GLInit()
{
	m_hDC = ::GetDC(m_hWnd); // Get the Device context ��ȡһ���豸����
	ASSERT(m_hDC);

	static	PIXELFORMATDESCRIPTOR pfdWnd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Structure size.
		1,                             // Structure version number.
		PFD_DRAW_TO_WINDOW |           // Property flags.���ػ�������
		PFD_SUPPORT_OPENGL |
 		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,			        // ������ɫģʽ(��ѡ:PFD_TYPE_COLORINDEX,��������ɫģʽ)
		24,                            // 24-bit color.24λ���ɫ
		0, 0, 0, 0, 0, 0,              // Not concerned with these.
		0, 0, 0, 0, 0, 0, 0,           // No alpha or accum buffer.
		32,                            // 32-bit depth buffer.��Ȼ���λ��
		0, 0,                          // No stencil or aux buffer.
		PFD_MAIN_PLANE,                // Main layer type.
		0,                             // Reserved.
		0, 0, 0                        // Unsupported.
	};

	int pixelformat;
	// ����һ�����͵���ţ�����ű�ʾ����Ҫ���������Ϊƥ������ظ�ʽ
    pixelformat = ChoosePixelFormat(m_hDC, &pfdWnd); // Ϊ�豸����ѡ�����ظ�ʽ

    ASSERT(SetPixelFormat(m_hDC, pixelformat, &pfdWnd));// Ϊָ�����豸�����������ظ�ʽ

	m_hRC=wglCreateContext(m_hDC); // �������豸������������Ⱦ����

	//make the rending context current, perform initialization
	VERIFY(wglMakeCurrent(m_hDC,m_hRC));// ѡ����Ⱦ����m_hRcΪ��ǰ����

	GLSetupRC(); // ��ʼ����Ⱦ���� 

	//deselect it
	VERIFY(wglMakeCurrent(NULL,NULL));// �ر���Ⱦ����
}


void CGLView::GLResize(int cx,int cy)
{
	double nRange = 1200.0;

	// Prevent a divide by zero
	if(cy == 0)
		cy = 1;

	// Set Viewport to window dimensions �����ӿ�
    glViewport(0, 0, cx, cy);

	glMatrixMode(GL_PROJECTION); // �л���ǰ����ΪͶӰ����

	// Reset coordinate system ��ʼ������
	glLoadIdentity(); 

	// Establish clipping volume (left, right, bottom, top, near, far) 
	// �����Ӿ����С
	if(cx <= cy)
		glOrtho(-nRange,nRange,-nRange*cy/cx,nRange*cy/cx,nRange,-nRange);
	else
		glOrtho(-nRange*cx/cy,nRange*cx/cy,-nRange,nRange,nRange,-nRange);


	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	// �����ӵ�ͷ���
	double eye[3], ref[3], up_dir[3];
	eye[0] = 0; eye[1] = 0; eye[2] = nRange;
	ref[0] = 0; ref[1] = 0; ref[2] = 0;
	up_dir[0] = 0; up_dir[1] = 1; up_dir[2] = 0;

	gluLookAt(eye[0], eye[1], eye[2], ref[0], ref[1], ref[2],
		up_dir[0], up_dir[1], up_dir[2]);

}

void CGLView::GLSetupRC()// ��ʼ����Ⱦ��������
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glEnable(GL_COLOR_MATERIAL);

	// Lighting components ��Դ����
	GLfloat  ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat  diffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat	 lightPos[] = { 1.0f, 1.0f, -1.0f, 0.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// ��������
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specular);
	glMateriali(GL_FRONT,GL_SHININESS,100);

	// ������ɫ���ã���ɫ��
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); //background color

	// default color ���ò��ϵ�Ĭ����ɫ����ɫ��
	glColor3ub(0, 0, 255);

}

void CGLView::RenderScene() // OpenGLͼ�λ��ƺ���
{
	// �����ɫ�������Ȼ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotate
	glRotatef(3.0f,0.0f, 0.0f, 1.0f); // Rock Z ��z����ת3��
	glRotatef(3.0f,1.0f, 0.0f, 0.0f); // Roll X ��x����ת3��

	glPushMatrix();
	glColor3ub(255,0,0);//red
	auxSolidSphere(360); //0,0,0

	glColor3ub(0,0,255);//blue
	glTranslatef(600,0,200);//600,0,0
	auxSolidSphere(120);

	glColor3ub(0,255,0);//green
	glTranslatef(-1200,600,0);//-600,0,0
	auxSolidSphere(240);

	glPopMatrix();
	glFlush();

}


void CGLView::OnTimer(UINT nIDEvent) 
{
	Invalidate(FALSE);	// ˢ����Ļ��ÿ����ˢ����Ļ20�Σ�
	CView::OnTimer(nIDEvent);
}

void CGLView::OnDestroy()
{
	GLRelease();
	CView::OnDestroy();
}

//clear up rendering context
void CGLView::GLRelease()
{
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}


void CGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_MouseDownPoint = CPoint(0, 0);
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}


void CGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_MouseDownPoint = point;
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nChar)
	{
	case VK_UP:        m_yPos = m_yPos + 0.1f;
		break;
	case VK_DOWN:    m_yPos = m_yPos - 0.1f;
		break;
	case VK_LEFT:    m_xPos = m_xPos - 0.1f;
		break;
	case VK_RIGHT:  m_xPos = m_xPos + 0.1f;
		break;
	default:        //MessageBox(_T("Press the arrow keys only"));
		break;
	}

	InvalidateRect(NULL, FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (GetCapture() == this)
	{
		//Increment the object rotation angles
		m_xAngle += (point.y - m_MouseDownPoint.y) / 3.6;
		m_yAngle += (point.x - m_MouseDownPoint.x) / 3.6;
		//Redraw the view
		InvalidateRect(NULL, FALSE);
		//Set the mouse point
		m_MouseDownPoint = point;
	};

	CView::OnMouseMove(nFlags, point);
}


BOOL CGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_Scale += 0.01 *zDelta / 120;
	InvalidateRect(NULL, FALSE);


	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
