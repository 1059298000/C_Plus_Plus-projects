// OpenGLDC.cpp: implementation of the COpenGLDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGLDC.h"

#define GL_PI 3.1415f

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenGLDC::COpenGLDC(HWND hWnd):m_hWnd(hWnd)
{
	m_bSelectionMode = FALSE;
}

COpenGLDC::~COpenGLDC()
{
}

BOOL COpenGLDC::InitDC()
{
	if (m_hWnd == NULL) return FALSE;
	
	m_Camera.init();

	m_hDC = ::GetDC(m_hWnd);			// Get the Device context

	int pixelformat;
	PIXELFORMATDESCRIPTOR pfdWnd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Structure size.
		1,                             // Structure version number.
		PFD_DRAW_TO_WINDOW |           // Property flags.
		PFD_SUPPORT_OPENGL |
 		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,                            // 24-bit color.
		0, 0, 0, 0, 0, 0,              // Not concerned with these.
		0, 0, 0, 0, 0, 0, 0,           // No alpha or accum buffer.
		32,                            // 32-bit depth buffer.
		0, 0,                          // No stencil or aux buffer.
		PFD_MAIN_PLANE,                // Main layer type.
		0,                             // Reserved.
		0, 0, 0                        // Unsupported.
	};

    if ( (pixelformat = ChoosePixelFormat(m_hDC, &pfdWnd)) == 0 )
	{
		AfxMessageBox(_T("ChoosePixelFormat to wnd failed"));
		return FALSE;
	}

    if (SetPixelFormat(m_hDC, pixelformat, &pfdWnd) == FALSE)
        AfxMessageBox(_T("SetPixelFormat failed"));

	m_hRC=wglCreateContext(m_hDC);

	VERIFY(wglMakeCurrent(m_hDC,m_hRC));
	GLSetupRC();
	wglMakeCurrent(NULL,NULL);
	return m_hRC!=0;
}


void COpenGLDC::GLResize(int w,int h)
{
	wglMakeCurrent(m_hDC,m_hRC);

	// Prevent a divide by zero
	if(h == 0) h = 1;
	if(w == 0) w = 1;
	m_Camera.set_screen(w,h);
}

void COpenGLDC::GLSetupRC()
{
	//initialize color and rendering
	m_bShading = TRUE;

	//bright white light - full intensity RGB values
	// ����һ����Դ
	// ���û��������ɫ���
	GLfloat lightAmbient[] = {0.75f,0.75f,0.75f,1.0f};

	// ��������������ɫ���
	GLfloat lightDiffuse[] = {0.6f,0.6f,0.6f,1.0f};

	// ���þ�������ɫ���
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };

	// ��Դλ�ã���ʸ��(1,1,1)��������Զ��
	GLfloat lightPos[] = { 1.0f,1.0f,1.0f,0.0f };

	glEnable(GL_DEPTH_TEST);		//Hidden surface removal
	glEnable(GL_CULL_FACE);			//Do not calculate inside of object
	glFrontFace(GL_CCW);			//counter clock-wise polygons face out

	// ʹ�ù���
	glEnable(GL_LIGHTING);			//enable lighting

	//setup and enable light 0 ���ù�ԴGL_LIGHT0
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmbient); // Ϊ��Դ0���û�����
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuse); // Ϊ��Դ0�����������
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular); // Ϊ��Դ0���þ����
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // ���ù�Դ0��λ��
	SetLightDirection(1,1,1);					 // ���ù��߷���

	// �򿪹�ԴGL_LIGHT0
	glEnable(GL_LIGHT0);

	//Initialize Material Color to Gray
	// ���ñ�����Ĭ����ɫ(��ɫ)
	SetBkColor(RGB(0,0,0));				//black background

	// ���ò��ϵ�Ĭ����ɫ
	SetMaterialColor(RGB(225,175,22));	//golden material color

	// ���ÿ����ʾ��Ĭ����ɫ(��ɫ)
	SetColor(RGB(255,255,255));			//white frame color

	// ���ø�������ʾ����ɫ(��ɫ)
	SetHighlightColor(RGB(255,0,0));	//red highlight color	

	//Point Size
	glPointSize(3.0); // ���õ�Ļ��Ƴߴ�
}


void COpenGLDC::Ready()
{
	wglMakeCurrent(m_hDC,m_hRC);
	ClearBkground();
	OnShading();
	m_Camera.projection();
}

void COpenGLDC::Finish()
{
	glFlush();
	SwapBuffers(m_hDC);
	wglMakeCurrent(m_hDC,NULL);
}


//////////////////LIGHT && MATERIALS SETTING//////////
void COpenGLDC::ClearBkground()
{
	GLclampf	r,g,b;
	// ��ȡ����ɫ����m_clrBk����ɫRGB����
	r = (GLclampf)GetRValue(m_clrBk)/255.0;
	g = (GLclampf)GetGValue(m_clrBk)/255.0;
	b = (GLclampf)GetBValue(m_clrBk)/255.0;

	// ����������RGBA��ɫ
	glClearColor(r,g,b,0.0f);

	// ����
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//setting model
void COpenGLDC::OnShading()
{
	if(m_bShading){
		glEnable( GL_LIGHTING );
	    glEnable(GL_LIGHT0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
	else{
		glDisable( GL_LIGHTING );
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
}

void COpenGLDC::Shading(BOOL bShading)
{
	m_bShading = bShading;
}

BOOL COpenGLDC::IsShading()
{
	return m_bShading;
}

void COpenGLDC::Lighting(BOOL bLighting)
{
	if(bLighting)
		glEnable( GL_LIGHTING );
	else
		glDisable( GL_LIGHTING );
}

BOOL COpenGLDC::IsLighting()
{
	GLboolean bLighting;
	glGetBooleanv(GL_LIGHTING,&bLighting);   
	return bLighting;
}

void COpenGLDC::SetLightDirection(float dx,float dy,float dz)
{
	m_vecLight[0] = dx; //m_vecLight�����б��浱ǰ��Դ����ĳ�Ա����
	m_vecLight[1] = dy;
	m_vecLight[2] = dz;

	// ��������꽫��Դλ����������ʸ��(dx, dy, dz)���������Զ��
	GLfloat lightPos[] = { dx, dy, dz, 0.0f };
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
}

void COpenGLDC::GetLightDirection(float& dx,float& dy,float& dz)
{
	dx = m_vecLight[0];
	dy = m_vecLight[1];
	dz = m_vecLight[2];
}

//rendering color
void COpenGLDC::SetMaterialColor(COLORREF clr)
{
	m_clrMaterial = clr; // m_clrMaterial�����б����������ɫ�ĳ�Ա����

	BYTE r,g,b;
	r = GetRValue(clr); // ��ȡ��ɫclr�ĺ�ɫ����
	g = GetGValue(clr); // ��ȡ��ɫclr����ɫ����
	b = GetBValue(clr); // ��ȡ��ɫclr����ɫ����

	// ��������ɫ����Ϊ��ǰ�Ĳ�������
	GLfloat mat_amb_diff[] = {(GLfloat)r/255,(GLfloat)g/255,(GLfloat)b/255,1.0};
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
}

void COpenGLDC::GetMaterialColor(COLORREF& clr)
{
	clr = m_clrMaterial;
}

void COpenGLDC::SetBkColor(COLORREF clr)
{
	m_clrBk = clr;
}

void COpenGLDC::GetBkColor(COLORREF& clr)
{
	clr = m_clrBk;
}

void COpenGLDC::SetColor(COLORREF clr)
{
	m_clr = clr;
	BYTE r,g,b;
	r = GetRValue(clr);
	g = GetGValue(clr);
	b = GetBValue(clr);
	glColor3ub(r,g,b);
}

void COpenGLDC::GetColor(COLORREF& clr)
{
	clr =  m_clr;
}

void COpenGLDC::SetHighlightColor(COLORREF clr)
{
	m_clrHighlight = clr;
}

void COpenGLDC::GetHighlightColor(COLORREF& clr)
{
	clr = m_clrHighlight;
}

void COpenGLDC::Highlight(BOOL bHighlight)
{
	BYTE r,g,b;
	if(bHighlight){
		r = GetRValue(m_clrHighlight);
		g = GetGValue(m_clrHighlight);
		b = GetBValue(m_clrHighlight);
	}
	else{
		r = GetRValue(m_clrMaterial);
		g = GetGValue(m_clrMaterial);
		b = GetBValue(m_clrMaterial);
	}
	GLfloat mat_amb_diff[] = {(GLfloat)r/255,(GLfloat)g/255,(GLfloat)b/255,1.0};
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
}


//////////////////////// drawing functions ////////////////////////
//draw point
void COpenGLDC::DrawPoint(const CPoint3D& pt)
{
	glBegin(GL_POINTS);
		glVertex3f(pt.x,pt.y,pt.z);
	glEnd();
}

void COpenGLDC::DrawLine(const CPoint3D& sp,const CPoint3D& ep)
{
	glBegin(GL_LINES);
		glVertex3f(sp.x,sp.y,sp.z);
		glVertex3f(ep.x,ep.y,ep.z);
	glEnd();
}

void COpenGLDC::DrawPolyline(const CPoint3D* pt,int size)
{
	glBegin(GL_LINE_STRIP);
	for(int i=0;i<size;i++)
		glVertex3f(pt[i].x,pt[i].y,pt[i].z);
	glEnd();
}

// Ĭ�ϻ���ģʽ������stl��ʽ��������Ƭ
void COpenGLDC::DrawTriChip(double n0,double n1,double n2,double v00,double v01,double v02,
					double v10,double v11,double v12,double v20,double v21,double v22)
{
	glBegin(GL_TRIANGLES);
		glNormal3d(n0,n1,n2);
		glVertex3d(v00,v01,v02);
		glVertex3d(v10,v11,v12);
		glVertex3d(v20,v21,v22);
	glEnd();
}
// ���غ���1������ģʽ1�����������ʷֺ��������Ƭ����
void COpenGLDC::DrawTriChip(double v00, double v01, double v02, double v10, double v11, double v12, double v20, double v21, double v22)
{
	glBegin(GL_TRIANGLES);
	glVertex3d(v00, v01, v02);
	glVertex3d(v10, v11, v12);
	glVertex3d(v20, v21, v22);
	glEnd();
}

// ���غ���2������ģʽ2�����������ʷֺ�����������
void COpenGLDC::DrawTriChip(double v00, double v01, double v02, double v10, double v11, 
	double v12, double v20, double v21, double v22, double v30, double v31, double v32,boolean bl)
{
		// ��1
		glBegin(GL_TRIANGLES);
		glVertex3d(v00, v01, v02);
		glVertex3d(v10, v11, v12);
		glVertex3d(v20, v21, v22);
		glEnd();
		// ��2
		glBegin(GL_TRIANGLES);
		glVertex3d(v00, v01, v02);
		glVertex3d(v10, v11, v12);
		glVertex3d(v30, v31, v32);
		glEnd();
		// ��3
		glBegin(GL_TRIANGLES);
		glVertex3d(v00, v01, v02);
		glVertex3d(v20, v21, v22);
		glVertex3d(v30, v31, v32);
		glEnd();
		// ��4
		glBegin(GL_TRIANGLES);
		glVertex3d(v10, v11, v12);
		glVertex3d(v20, v21, v22);
		glVertex3d(v30, v31, v32);
		glEnd();
}

//Draw 3D Solid
void COpenGLDC::DrawSphere(const CPoint3D& cen,double r,const CVector3D& vec)
{
	glPushMatrix();

	// ƽ�Ʊ任����cen
	glTranslatef(cen.x,cen.y,cen.z);

	glLoadIdentity();

	CVector3D vecNY(0,-1,0);
	CVector3D axis = vecNY*vec;

	// ����ʸ����нǣ�����_AngleBetween�ǿ�GeomCalc.dll���������
	double ang = _AngleBetween(vecNY,vec);
	ang = ang*180/GL_PI;
	
	// ��ת�任
	glRotatef(ang,axis.dx,axis.dy,axis.dz);

	auxSolidSphere(r);  // ����Բ��
	glPopMatrix();
}

void COpenGLDC::DrawCylinder(const CPoint3D& cen,double r,const CVector3D& h)
{
	glPushMatrix();
	// ƽ�Ʊ任����cen
	glTranslatef(cen.x,cen.y,cen.z);

	CVector3D vecNY(0,-1,0);
	CVector3D axis = vecNY*h;

	double ang = _AngleBetween(vecNY,h);
	ang = ang*180/GL_PI;

	// ��ת�任
	glRotatef(ang,axis.dx,axis.dy,axis.dz);

	// ����Բ��
	auxSolidCylinder(r,h.GetLength());
	glPopMatrix();
}

void COpenGLDC::DrawTorus(const CPoint3D& cen,const CVector3D& ax,double r_in,double r_out)
{
	glPushMatrix();
	// ƽ�Ʊ任����cen
	glTranslatef(cen.x,cen.y,cen.z);

	CVector3D vecNY(0,-1,0);
	CVector3D axis = vecNY*ax;
	double ang = _AngleBetween(vecNY,ax);
	ang = ang*180/GL_PI;

	// ��ת�任
	glRotatef(ang,axis.dx,axis.dy,axis.dz);

	// ����Բ��
	auxSolidTorus(r_in,r_out);
	glPopMatrix();
}

void COpenGLDC::DrawTeapot(const CPoint3D& cen, double size, const CVector3D& vec)
{

	glPushMatrix();

	// ƽ�Ʊ任����cen
	glTranslatef(cen.x, cen.y, cen.z);

	glLoadIdentity();

	CVector3D vecNY(0, -1, 0);
	CVector3D axis = vecNY*vec;

	// ����ʸ����нǣ�����_AngleBetween�ǿ�GeomCalc.dll���������
	double ang = _AngleBetween(vecNY, vec);
	ang = ang * 180 / GL_PI;

	// ��ת�任
	glRotatef(ang, axis.dx, axis.dy, axis.dz);

	auxSolidTeapot(size);  // ���Ʋ��
	glPopMatrix();
}

void COpenGLDC::DrawTetrahedron(const CPoint3D & cen, double radius, const CVector3D & vec)
{
	glPushMatrix();

	// ƽ�Ʊ任����cen
	glTranslatef(cen.x, cen.y, cen.z);

	glLoadIdentity();

	CVector3D vecNY(0, -1, 0);
	CVector3D axis = vecNY*vec;

	// ����ʸ����нǣ�����_AngleBetween�ǿ�GeomCalc.dll���������
	double ang = _AngleBetween(vecNY, vec);
	ang = ang * 180 / GL_PI;

	// ��ת�任
	glRotatef(ang, axis.dx, axis.dy, axis.dz);

	auxSolidTetrahedron(radius);  // ����4����
	glPopMatrix();
}

void COpenGLDC::DrawOctahedron(const CPoint3D & cen, double radius, const CVector3D & vec)
{
	glPushMatrix();

	// ƽ�Ʊ任����cen
	glTranslatef(cen.x, cen.y, cen.z);

	glLoadIdentity();

	CVector3D vecNY(0, -1, 0);
	CVector3D axis = vecNY*vec;

	// ����ʸ����нǣ�����_AngleBetween�ǿ�GeomCalc.dll���������
	double ang = _AngleBetween(vecNY, vec);
	ang = ang * 180 / GL_PI;

	// ��ת�任
	glRotatef(ang, axis.dx, axis.dy, axis.dz);

	auxSolidOctahedron(radius);  // ����8����
	glPopMatrix();

}

void COpenGLDC::DrawIcosahedron(const CPoint3D& cen, double radius, const CVector3D& vec)
{
	glPushMatrix();

	// ƽ�Ʊ任����cen
	glTranslatef(cen.x, cen.y, cen.z);

	glLoadIdentity();

	CVector3D vecNY(0, -1, 0);
	CVector3D axis = vecNY*vec;

	// ����ʸ����нǣ�����_AngleBetween�ǿ�GeomCalc.dll���������
	double ang = _AngleBetween(vecNY, vec);
	ang = ang * 180 / GL_PI;

	// ��ת�任
	glRotatef(ang, axis.dx, axis.dy, axis.dz);

	auxSolidIcosahedron(radius);  // ����12����
	glPopMatrix();
}

void COpenGLDC::DrawCone(const CPoint3D& cen, double r, const CVector3D& h)
{
	glPushMatrix();
	// ƽ�Ʊ任����cen
	glTranslatef(cen.x,cen.y,cen.z);

	CVector3D vecNY(0,-1,0);
	CVector3D axis = vecNY*h;
	double ang = _AngleBetween(vecNY,h);
	ang = ang*180/GL_PI;

	glRotatef(ang,axis.dx,axis.dy,axis.dz);

	// ����Բ׶��
	GLfloat angle,x,y;
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0,0,h.GetLength());
		for(angle =0.0f;angle<(2.0f*GL_PI);angle += (GL_PI/8.0f))
		{
			x = r*sin(angle);
			y = r*cos(angle);
			glVertex2f(x,y);
		}
	glEnd();

	// Begin a new triangle fan to cover the bottom
	// ����Բ׶����
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0f,0.0f);
		for(angle =0.0f;angle<(2.0f*GL_PI);angle += (GL_PI/8.0f))
		{
			x = r*sin(angle);
			y = r*cos(angle);
			glVertex2f(x,y);
		}
	glEnd();
	glPopMatrix();
}

////////////////////////////////////////

void COpenGLDC::DrawCoord() // ���û�����ϵԭ�����һ������ϵ���
{

	BOOL bLighting = IsLighting(); // ���浱ǰ����ģʽ
	Lighting(FALSE); // �رչ���ģʽ

	// ��ȡ��ǰ�����Ŀ�͸�
	double width,height;
	m_Camera.get_view_rect(width,height);
	double len = min(width,height);
	len *= 0.2; // ȡ��ǰ��Ļ���ߵ�20%��Ϊ������Ļ��Ƴ���

	CPoint3D cPt,xPt,yPt,zPt;
	xPt.x = yPt.y = zPt.z = len;

	COLORREF old_clr;
	GetColor(old_clr); // ��ȡ�����浱ǰ��ͼ��ɫ

	//axis-x: red �ú�ɫ����x��
	SetColor(RGB(255,0,0));
	DrawLine(cPt,xPt);

	//axis-y: green ����ɫ����y��
	SetColor(RGB(0,255,0));
	DrawLine(cPt,yPt);

	//axis-z: blue ����ɫ����z��
	SetColor(RGB(0,0,255));
	DrawLine(cPt,zPt);

	Lighting(bLighting); // �ָ�ԭ�ȹ���ģʽ
	SetColor(old_clr); // �ָ�ԭ�Ȼ�ͼ��ɫ
}

//////////////////////////////////////////////////
void COpenGLDC::BeginSelection(int xPos,int yPos)
{
	// ��ʶʰȡ���̿�ʼ
	m_bSelectionMode = TRUE;

	// ��ǰ����Ⱦ����
	wglMakeCurrent(m_hDC,m_hRC);
	GLint	viewport[4];
	
	//set up selection buffer	����ѡ�񻺴���
	glSelectBuffer(BUFFER_LENGTH,m_selectBuff);
	
	//switch to projection and save the matrix
	// �л���ѡ��ģʽ�£����������λ�ô���ѡ���Ӿ���
	m_Camera.selection(xPos,yPos);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// ��ʼ�����ƶ�ջ
	InitNames();
}

int	COpenGLDC::EndSelection(UINT* items)
{
	// ��ʶʰȡ���̽���
	m_bSelectionMode = FALSE;

	// �л�����ͼģʽ��������ѡ�񻺴�����ʰȡ��¼��Ŀ
	int hits = glRenderMode(GL_RENDER);

	// ����ʰȡ��¼
	for(int i=0;i<hits;i++){
		items[i] = m_selectBuff[i*4+3];
	}

	// �ǵ�ǰ����Ⱦ����
	wglMakeCurrent(m_hDC,NULL);
	return hits;
}

BOOL COpenGLDC::IsSelectionMode()
{
	return m_bSelectionMode;
}

void COpenGLDC::InitNames()
{
	glInitNames();
	glPushName(0);
}

void COpenGLDC::LoadName(UINT name)
{
	glLoadName(name);
}

void COpenGLDC::PushName(UINT name)
{
	glPushName(name);
}

void COpenGLDC::PopName()
{
	glPopName();
}