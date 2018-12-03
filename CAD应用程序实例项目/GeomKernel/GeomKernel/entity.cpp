// Entity.cpp: implementation of the CEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <atlconv.h>

#include "Entity.h"
#include "..\inc\glContext\openGLDC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntity::CEntity()
{
	// ��ʼ����������
	// �ڹ���һ����CEntity��������Ķ���ʱ��������캯�������ȵ���
	m_bModified = FALSE;
	m_id = -1;
	m_pBox = NULL;
	m_color = RGB(128,128,128);
	m_name = _T("models");
	m_bVisible = TRUE;
	m_bHighlight = FALSE;
}

CEntity::~CEntity()
{
	if (m_pBox != NULL)
	{
		delete m_pBox;
		m_pBox = NULL;
	}
}

void CEntity::Serialize(CArchive& ar)
{
	if(ar.IsStoring()) // ���л��洢
		ar<<m_id<<m_name<<m_color<<m_bVisible;
	else			   // ���л���ȡ
		ar>>m_id>>m_name>>m_color>>m_bVisible;
}	

BOOL	CEntity::GetBox(CBox3D& box)
{
	// ���ʵ�屻�޸Ĺ�������Ҫ���¼������İ��ݺ�
	if(m_bModified)
		UpdateBox(); // UpdateBox()���ڻ���CEntity�ж���Ĵ����⺯��

	if( m_pBox){
		box = *m_pBox;
		return TRUE;
	}
	else
		return FALSE;
}

// ����CEntity�м��ζ������Ե��йغ���
void	CEntity::SetID(UINT nID)
{
	m_id = nID;
}

UINT	CEntity::GetID()
{
	return m_id;
}

void	CEntity::SetName(LPCTSTR name)
{
	m_name = name;
}

CString	CEntity::GetName()
{
	return m_name;
}

void	CEntity::SetColor(COLORREF color)
{
	m_color = color;
}

COLORREF CEntity::GetColor()
{
	return m_color;
}

void CEntity::SetVisible(BOOL bVisible)
{
	m_bVisible = bVisible;
}

BOOL CEntity::IsVisible()
{
	return m_bVisible;
}

void CEntity::SetHighlight(BOOL bHighlight)
{
	m_bHighlight = bHighlight;
}

BOOL CEntity::IsHighlight()
{
	return m_bHighlight;
}

///////////////////////////
//class tri chip 

IMPLEMENT_SERIAL(CTriChip,CObject,0)

CTriChip::CTriChip()
{
}

CTriChip::CTriChip(const CPoint3D& v0,const CPoint3D& v1,const CPoint3D& v2,const CVector3D& nor)
{
	vex[0] = v0;
	vex[1] = v1;
	vex[2] = v2;
	normal = nor;
}

CTriChip::CTriChip(const CPoint3D& v0, const CPoint3D& v1, const CPoint3D& v2)
{
	tri[0] = v0;
	tri[1] = v1;
	tri[2] = v2;
}

CTriChip::CTriChip(const CPoint3D & v0, const CPoint3D & v1, const CPoint3D & v2, const CPoint3D & v3, 
	const CPoint3D & v4, const CPoint3D & v5, const CPoint3D & v6)
{

	tri[0] = v0;
	tri[1] = v1;
	tri[2] = v2;
	fourFace[0] = v3;
	fourFace[1] = v4;
	fourFace[2] = v5;
	fourFace[3] = v6;
}


CTriChip::~CTriChip()
{
}

const CTriChip& CTriChip::operator=(const CTriChip& tri)
{
	normal = tri.normal;
	for(int i=0;i<3;i++)
		vex[i] = tri.vex[i];

	for (int i = 0; i < 4; i++)
		fourFace[i] = tri.fourFace[i];

	return *this;
}

void CTriChip::Draw(COpenGLDC* pDC, int para)
{
	if (para == 0) // ����Ĭ�ϻ���ģʽ
	{
		//TRACE(_T("������Ϣ��Ĭ�ϻ���ģ��Ĭ�ϻ���ģ�ͣ���������!"));
		pDC->DrawTriChip(normal.dx, normal.dy, normal.dz,
			vex[0].x, vex[0].y, vex[0].z,
			vex[1].x, vex[1].y, vex[1].z,
			vex[2].x, vex[2].y, vex[2].z);
	}
	else if (para == 1) // ���û���ģʽ1��������������
	{
		//TRACE(_T("������Ϣ������ģ��1111Ĭ�ϻ���ģ��111����������!"));
		pDC->DrawTriChip(
			tri[0].x, tri[0].y, tri[0].z,
			tri[1].x, tri[1].y, tri[1].z,
			tri[2].x, tri[2].y, tri[2].z);
	}
	else if (para == 2) // ���û���ģʽ2��������������
	{
		pDC->DrawTriChip(
			fourFace[0].x, fourFace[0].y, fourFace[0].z,
			fourFace[1].x, fourFace[1].y, fourFace[1].z,
			fourFace[2].x, fourFace[2].y, fourFace[2].z,
			fourFace[3].x, fourFace[3].y, fourFace[3].z,true);
	}
}


void CTriChip::Serialize(CArchive& ar)
{
	if(ar.IsStoring()){
		ar << normal.dx << normal.dy << normal.dz;
		for (int i = 0; i < 3; i++) 
			ar << vex[i].x << vex[i].y << vex[i].z;

		for (int i = 0; i < 3; i++) 
			ar <<tri[i].x << tri[i].y << tri[i].z;

		for (int i = 0; i < 4; i++)
			ar << fourFace[i].x << fourFace[i].y << fourFace[i].z;
	}
	else {
		ar >> normal.dx >> normal.dy >> normal.dz;
		for (int i = 0; i < 3; i++)
			ar >> vex[i].x >> vex[i].y >> vex[i].z;

		for (int i = 0; i < 3; i++)
			ar >> tri[i].x >> tri[i].y >> tri[i].z;
	
		for (int i = 0; i < 4; i++)
			ar >> fourFace[i].x >> fourFace[i].y >> fourFace[i].z;
	}
}

//////////////////////////////////////////
//class  CSTLModel

IMPLEMENT_SERIAL(CSTLModel,CObject,0)  // ���л�ʵ��

CSTLModel::CSTLModel()
{
	// ��ʼ������

	tem_tri = NULL;

	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_Scale = 1.0f;
	m_Mode = 0;
}

CSTLModel::~CSTLModel()
{
	for (int i = 0; i < temp_vertex.size(); i++)
	{
		if (temp_vertex[i] != NULL)
		{
			delete temp_vertex[i];
			temp_vertex[i] = NULL;
		}
	}
	
	Clear();
}

void CSTLModel::Add(CTriChip* tri)
{
		m_TriList.Add(tri);
}

// ���ݵ�ǰ������������Ƭ�ļ�����Ϣ������STLModel����������ݺ�
void CSTLModel::UpdateBox()
{
	if(m_pBox){
		delete m_pBox;
		m_pBox = NULL;
	}

	if(m_TriList.GetSize()==0) 
		return;
	
	double x0,y0,z0,x1,y1,z1;
	x0=y0=z0=10000;
	x1=y1=z1=-10000;
	
	CTriChip* tri;
	for(int i=0;i<m_TriList.GetSize();i++){
		tri = m_TriList[i];
		for(int n=0;n<3;n++){
			if (tri->vex[n].x < x0)  x0 = tri->vex[n].x;
			if (tri->vex[n].x > x1)  x1 = tri->vex[n].x;
			if (tri->vex[n].y < y0)  y0 = tri->vex[n].y;
			if (tri->vex[n].y > y1)  y1 = tri->vex[n].y;
			if (tri->vex[n].z < z0)  z0 = tri->vex[n].z;
			if (tri->vex[n].z > z1)  z1 = tri->vex[n].z;

		}
	}

	m_pBox = new CBox3D(x0,y0,z0,x1,y1,z1);
	m_bModified = FALSE;
}


//��ȡ ������STL�ļ��ĸ�������
static bool we_are_little_endian()
{
	char buf[4];
	*(int *)(&buf[0]) = 1;
	return (buf[0] == 1);
}

static inline void swap_unsigned(volatile unsigned &x)
{
	x = (x << 24u) |
		((x << 8u) & 0x00ff0000u) |
		((x >> 8u) & 0x0000ff00u) |
		(x >> 24u);
}

static inline void swap_int(int &x)
{
	swap_unsigned(*(unsigned *)(&x));
}

static inline void swap_float(float &x)
{
	swap_unsigned(*(unsigned *)(&x));
}




//static void InitFacets(tetgenio& in, std::vector<CPoint3D>& points, std::vector<CTriChip>& faces, CBox3D box)
//{
//	in.firstnumber = 0;
//	in.numberoffacets = faces.size() + 6;
//	in.facetlist = new tetgenio::facet[in.numberoffacets];
//	in.facetmarkerlist = new int[in.numberoffacets];
//	memset(in.facetmarkerlist, 0, sizeof(int)*in.numberoffacets);
//	tetgenio::facet *f; tetgenio::polygon *p;
//	for (size_t i = 0; i < faces.size(); i++)
//	{
//		f = &in.facetlist[i];
//		f->numberofpolygons = 1;
//		f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
//		f->numberofholes = 0;
//		f->holelist = NULL;
//		p = &f->polygonlist[0];
//		p->numberofvertices = 3;
//		p->vertexlist = new int[p->numberofvertices];
//		p->vertexlist[0] = faces[i].vex[0];
//		p->vertexlist[1] = faces[i].P1Index;
//		p->vertexlist[2] = faces[i].P2Index;
//	}
//	std::vector<std::vector<long double> > segmentsInbound;
//	segmentsInbound.resize(6);
//	std::vector<std::vector<int> > pointsInbound;
//	pointsInbound.resize(12);
//	InitBoxEdgePoints(in, points, faces, box, pointsInbound);
//	InitBoxSegments(in, points, faces, box, segmentsInbound);
//	InitBoxFacets(in, points, faces, box, segmentsInbound, pointsInbound);
//}
//static void InitBoxEdgePoints(tetgenio& in, std::vector<Point3d>& points, std::vector<Triangle>& faces, Box3Double box, std::vector<std::vector<int> >& boundPoints)
//{
//	int ret[12];
//	for (size_t i = 0; i < points.size(); i++)
//	{
//		if (!InBox(points[i], box))
//		{
//			printf("%f %f %f", points[i].X, points[i].Y, points[i].Z);
//			//throw new exception();
//		}
//		CheckPointAlignBoxEdge(points[i], box, ret);
//		for (int j = 0; j < 12; j++)
//		{
//			if (ret[j] == 1)
//			{
//				boundPoints[j].push_back(i);
//			}
//		}
//	}
//}//����Ƿ��ж�������box���� �ҵ���Щ�� ����boundPoints�Ķ�Ӧ����
//static void InitBoxSegments(tetgenio& in, std::vector<Point3d>& points, std::vector<Triangle>& faces, Box3Double box, std::vector<std::vector<Int16Double> >& boundSegs)
//{
//	int ret[6];
//	for (size_t i = 0; i < faces.size(); i++)
//	{
//		Triangle& t = faces[i];
//		Point3d& p0 = points[t.P0Index];
//		Point3d& p1 = points[t.P1Index];
//		Point3d& p2 = points[t.P2Index];
//		if (!InBox(p0, box) || !InBox(p1, box) || !InBox(p2, box))
//			throw std::exception();
//		CheckSegAlignBoxFace(p0, p1, box, ret);
//		for (int j = 0; j < 6; j++)
//		{
//			if (ret[j] == 1)
//			{
//				Int16Double seg(t.P0Index, t.P1Index);
//				boundSegs[j].push_back(seg);
//			}
//		}
//		CheckSegAlignBoxFace(p1, p2, box, ret);
//		for (int j = 0; j < 6; j++)
//		{
//			if (ret[j] == 1)
//			{
//				Int16Double seg(t.P1Index, t.P2Index);
//				boundSegs[j].push_back(seg);
//			}
//		}
//		CheckSegAlignBoxFace(p2, p0, box, ret);
//		for (int j = 0; j < 6; j++)
//		{
//			if (ret[j] == 1)
//			{
//				Int16Double seg(t.P2Index, t.P0Index);
//				boundSegs[j].push_back(seg);
//			}
//		}
//	}
//}//����Ƿ�������Ƭ��ĳЩ������box���� �ҵ���Щ�߶� ����boundSegs�Ķ�Ӧ����
//static void InitBoxFacets(tetgenio& in, std::vector<CPoint3D>& points, std::vector<CTriChip>& faces, CBox3D box, std::vector<std::vector<long double> >& segInBox, std::vector<std::vector<int> >& pb)
//{
//	tetgenio::facet *f;
//	tetgenio::polygon *p;
//	std::vector<long double>* segs;
//	int count = faces.size();
//	in.facetmarkerlist[count] = -1;
//	in.facetmarkerlist[count + 1] = -2;
//	in.facetmarkerlist[count + 2] = -3;
//	in.facetmarkerlist[count + 3] = -4;
//	in.facetmarkerlist[count + 4] = -5;
//	in.facetmarkerlist[count + 5] = -6;
//	int p0 = in.numberofpoints - 8;
//	int p1 = in.numberofpoints - 8 + 1;
//	int p2 = in.numberofpoints - 8 + 2;
//	int p3 = in.numberofpoints - 8 + 3;
//	int p4 = in.numberofpoints - 8 + 4;
//	int p5 = in.numberofpoints - 8 + 5;
//	int p6 = in.numberofpoints - 8 + 6;
//	int p7 = in.numberofpoints - 8 + 7;
//	//if(p.X==x0&&p.Y==y0)  1 5	pointsInbound[0]
//	//if(p.X==x1&&p.Y==y0)  2 6	pointsInbound[1]
//	//if(p.X==x1&&p.Y==y1)  3 7	 pointsInbound[2]
//	//if(p.X==x0&&p.Y==y1)  4 8	pointsInbound[3]
//	//
//	//if(p.Y==y0&&p.Z==z0)  1 2	pointsInbound[4]
//	//if(p.Y==y1&&p.Z==z0)  3 4	 pointsInbound[5]
//	//if(p.Y==y1&&p.Z==z1)  7 8	pointsInbound[6]
//	//if(p.Y==y0&&p.Z==z1)  5 6	pointsInbound[7]
//	//
//	//if(p.X==x0&&p.Z==z0)  1 4	pointsInbound[8]
//	//if(p.X==x1&&p.Z==z0)  2 3	pointsInbound[9]
//	//if(p.X==x1&&p.Z==z1)  6 7	pointsInbound[10]
//	//if(p.X==x0&&p.Z==z1)  5 8	pointsInbound[11]
//	// Facet  x=x0
//	f = &in.facetlist[count];
//	segs = &(segInBox[0]);
//	f->numberofpolygons = 1 + segs->size();
//	f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
//	f->numberofholes = 0;
//	f->holelist = NULL;
//	p = &f->polygonlist[0];
//	ProcessBoxIntersectedPoints(p0, pb[0], true, p4, pb[11], true, p7, pb[3], false, p3, pb[8], false, p, points);
//	ProcessBoxSegments(f, p, segs);
//	// Facet x=x2
//	f = &in.facetlist[count + 1];
//	segs = &(segInBox[1]);
//	f->numberofpolygons = 1 + segs->size();
//	f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
//	f->numberofholes = 0;
//	f->holelist = NULL;
//	p = &f->polygonlist[0];
//	ProcessBoxIntersectedPoints(p1, pb[9], true, p2, pb[2], true, p6, pb[10], false, p5, pb[1], false, p, points);
//	ProcessBoxSegments(f, p, segs);
//	// Facet  y=y0
//	f = &in.facetlist[count + 2];
//	segs = &(segInBox[2]);
//	f->numberofpolygons = 1 + segs->size();
//	f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
//	f->numberofholes = 0;
//	f->holelist = NULL;
//	p = &f->polygonlist[0];
//	ProcessBoxIntersectedPoints(p0, pb[4], true, p1, pb[1], true, p5, pb[7], false, p4, pb[0], false, p, points);
//	ProcessBoxSegments(f, p, segs);
//	// Facet  y=y2
//	f = &in.facetlist[count + 3];
//	segs = &(segInBox[3]);
//	f->numberofpolygons = 1 + segs->size();
//	f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
//	f->numberofholes = 0;
//	f->holelist = NULL;
//	p = &f->polygonlist[0];
//	ProcessBoxIntersectedPoints(p2, pb[5], false, p3, pb[3], true, p7, pb[6], true, p6, pb[2], false, p, points);
//	ProcessBoxSegments(f, p, segs);
//	// Facet z=z0
//	f = &in.facetlist[count + 4];
//	segs = &(segInBox[4]);
//	f->numberofpolygons = 1 + segs->size();
//	f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
//	f->numberofholes = 0;
//	f->holelist = NULL;
//	p = &f->polygonlist[0];
//	ProcessBoxIntersectedPoints(p0, pb[4], true, p1, pb[9], true, p2, pb[5], false, p3, pb[8], false, p, points);
//	ProcessBoxSegments(f, p, segs);
//	// Facet  z=z2
//	f = &in.facetlist[count + 5];
//	segs = &(segInBox[5]);
//	f->numberofpolygons = 1 + segs->size();
//	f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
//	f->numberofholes = 0;
//	f->holelist = NULL;
//	p = &f->polygonlist[0];
//	ProcessBoxIntersectedPoints(p4, pb[7], true, p5, pb[10], true, p6, pb[6], false, p7, pb[11], false, p, points);
//	ProcessBoxSegments(f, p, segs);
//}



bool CSTLModel::IsTextFile(const char *strFileName) // �ж��ļ��Ƿ����ı���ʽ
{
	if (strFileName == NULL) return false;
	struct stat f_stat;
	if (stat(strFileName, &f_stat) == -1)
	{
		return false;
	}
	long lngFilesize = 0;
	lngFilesize = (long)f_stat.st_size;
	if (lngFilesize <= 0) return false;
	FILE *ft = fopen(strFileName, "rb");
	if (ft == NULL)
	{
		return false;
	}
	char btData[1];
	long lngReadPos;
	long lngMaxRead = 40960;
	if (lngMaxRead > lngFilesize) lngMaxRead = lngFilesize;
	for (lngReadPos = 1; lngReadPos <= lngMaxRead; lngReadPos++)
	{
		fread(&btData, 1, 1, ft);
		if (btData[0] == '\0')
		{
			fclose(ft);
			return false;
		}
	}
	fclose(ft);
	return true;
}

bool  CSTLModel::ReadBinFile(LPCTSTR stlfile)
{
	// ��Ϊʹ�õ���Unicode�ַ�������char* �� LPTSTR���ڲ�ͬ������
	// Ϊ��ʹ����Щ�꣬�����ں����Ŀ�ʼ����USES_CONVERSION����ʼ��ĳЩ�ֲ�����
	USES_CONVERSION;

	FILE *f = fopen(W2A(stlfile), "rb");
	//int c = fgetc(f);
	bool need_swap = !we_are_little_endian();
	char header[80];
	COND_READ(true, header, 80);
	int nfacets;
	COND_READ(true, nfacets, 4);
	if (need_swap)
		swap_int(nfacets);
	faces.reserve(nfacets);
	vertices.reserve(3 * nfacets);
	for (int i = 0; i < nfacets; i++)
	{
		tem_tri = new CTriChip(); // �ڴ�й©��
		float fbuf[12];
		COND_READ(true, fbuf, 48);
		if (need_swap) {
			for (int j = 3; j < 12; j++)
				swap_float(fbuf[j]);
		}
		int v = vertices.size();

		tem_tri->normal.dx = v;
		tem_tri->normal.dy = v + 1;
		tem_tri->normal.dz = v + 2;

		tem_tri->vex[0] = (CPoint3D(fbuf[3], fbuf[4], fbuf[5]));
		tem_tri->vex[1] = (CPoint3D(fbuf[6], fbuf[7], fbuf[8]));
		tem_tri->vex[2] = (CPoint3D(fbuf[9], fbuf[10], fbuf[11]));

		temp_vertex.push_back(tem_tri);

		unsigned char att[2];
		COND_READ(true, att, 2);
	}
	fclose(f);
}


//load with STL File ����ASCII��ʽ��STL�ļ�
BOOL CSTLModel::LoadSTLFile(LPCTSTR stlfile,int mode)
{
	// ��Ϊʹ�õ���Unicode�ַ�������char* �� LPTSTR���ڲ�ͬ������
	// Ϊ��ʹ����Щ�꣬�����ں����Ŀ�ʼ����USES_CONVERSION����ʼ��ĳЩ�ֲ�����
	USES_CONVERSION;
	m_Mode = mode; // �������ģʽ

	// Extension
	CString extension = stlfile;
	extension = extension.Right(4);
	extension.MakeLower();

	const char *ffile = W2A(stlfile);
	
	if (extension == ".stl") //��������ģ�͵�STL��ʽ�ļ�
	{
		if (IsTextFile(ffile))          //�ı���ʽ
		{
			// �Զ����ȡSTL�ļ�����
			if (!Load_Stl_Points(stlfile))
			{
				TRACE(_T("������Ϣ���Զ����ȡ�ı���ʽSTL�ļ�������ȡʧ��!"));
				return FALSE;
			}
		}
		else                               //�����Ƹ�ʽ
		{
			// �Զ����ȡ�����Ƹ�ʽ��STL�ļ�����
			if (!ReadBinFile(stlfile))
			{
				TRACE(_T("������Ϣ���Զ����ȡ�����Ƹ�ʽ��STL�ļ�������ȡʧ��!"));
				return FALSE;
			}
		}
	}
	

	// �Զ����ʷֺ���
	if (!Dissection()) 
	{
		TRACE(_T("������Ϣ���Զ����ʷ�STL�����ʷ�ʧ��!"));
		return FALSE;
	}

	// �Զ��嵼���ʷ����ݺ���
	if (!Input_to_CTriChip())
	{
		TRACE(_T("������Ϣ���Զ��嵼���ʷ����ݺ�����ȡʧ��!"));
		return FALSE;
	}


	char title[80];
	if(GetFileTitle(stlfile, A2W(title),80)==0){// A2W��������ڽ�խ�ֽ�ת��Ϊ���ֽ�
		SetName(A2W(title));
	}
	m_bModified = TRUE; // �����޸ı�־Ϊ���޸�
	return TRUE;
}

// �ʷֺ���
bool CSTLModel::Dissection()
{
	//if (m_Mode != 0) // �ж��Ƿ������������ʷֹ��ܣ���ģʽm_Mode��Ϊ0�����ʷֹ���
	//{
	// �����������������tetgenbehavior.parse_commandline(int argc, char **argv)����
	tetgenbehavior b;
	//-P,�����ļ���һ��PLC(Լ���������������ʷ�)
	b.plc = 1;
	//-q,Ϊ��������������������������ޣ���-qѡ������һ��ֵ��С������Ĭ����2.0��
	b.quality = 1;
	b.minratio = 1.2;
	// -a,�����е�������ǿ��һ������Ԫ���ޣ�-aѡ����һ����С��ֵ��
	//b.fixedvolume = 1;
	//b.maxvolume = 1.0;
	v_tetIN.initialize(); // ��ʼ�������������

	//  ���ȶ�ȡstl�㼰��ʧ���ݣ���Ϊtetgenio�����stl��������
	if (!inputStl_to_Tetgen()) {
		TRACE(_T("������Ϣ������stl����ת����tetgen���io����ʧ��!"));
		return FALSE;
	}

	//if (v_tetIN.load_stl(W2A(stlfile)))
	//{
	//	TRACE(_T("������Ϣ���� ȡ �� ��!!!"));
	//}
	//else {
	//	TRACE(_T("������Ϣ���� ȡ ʧ ��!!!"));
	//	return FALSE;
	//}

	v_tetOUT.initialize(); // ��������ʼ��
	tetrahedralize(&b, &v_tetIN, &v_tetOUT); // �������ʷֺ���

	 // Output mesh to files ��barout(q1.2).node��, ��barout(q1.2).ele�� and ��barout(q1.2).face��.
	v_tetOUT.save_nodes("G:\\develop\\c++Projects\\STLViewer\\Asher\\ barout(q1.2)");
	v_tetOUT.save_elements("G:\\develop\\c++Projects\\STLViewer\\Asher\\ barout(q1.2)");
	v_tetOUT.save_faces("G:\\develop\\c++Projects\\STLViewer\\Asher\\ barout(q1.2)");
	v_tetOUT.save_edges("G:\\develop\\c++Projects\\STLViewer\\Asher\\ barout(q1.2)");

	// �洢node�������  ��PLC�㼯
	for (int i = 0; i < v_tetOUT.numberofpoints; i++)
	{
		// ��ȡ�������ʷֺ�Ľ��������Ϣ
		CPoint3D tempPoint = CPoint3D(v_tetOUT.pointlist[i * 3],
			v_tetOUT.pointlist[i * 3 + 1], v_tetOUT.pointlist[i * 3 + 2]);

		node.push_back(tempPoint); // �洢�������

	}

	// ��������������
	for (int i = 0; i < v_tetOUT.numberoftrifaces; i++) {

		CPoint3D tempFace = CPoint3D(v_tetOUT.trifacelist[i * 3],
			v_tetOUT.trifacelist[i * 3 + 1], v_tetOUT.trifacelist[i * 3 + 2]);

		triface.push_back(tempFace);  //  �洢�����������ǵ�����Ӧ��������

		if (v_tetOUT.trifacemarkerlist != NULL) {
			trifacemarker.push_back(v_tetOUT.trifacemarkerlist[i]);
		}
	}

	// �洢�������б�
	for (int i = 0; i < v_tetOUT.numberoftetrahedra; i++) {
		CPoint4D cpoint4d = CPoint4D(v_tetOUT.tetrahedronlist[i *  v_tetOUT.numberofcorners],
			v_tetOUT.tetrahedronlist[i *  v_tetOUT.numberofcorners + 1],
			v_tetOUT.tetrahedronlist[i *  v_tetOUT.numberofcorners + 2],
			v_tetOUT.tetrahedronlist[i *  v_tetOUT.numberofcorners + 3]);

		tetrahedron.push_back(cpoint4d);  //  �洢�������ĸ��ǵ�����Ӧ��������
		/*for (int j = 0; j < v_tetOUT.numberoftetrahedronattributes; j++) {
			tetrahedronattribute.push_back(v_tetOUT.tetrahedronattributelist
			 [i *  v_tetOUT.numberoftetrahedronattributes + j]);
			}*/
	}

	//// ����������ı�����
	//for (int i = 0; i < v_tetOUT.numberofedges; i++) {
	//	edge.push_back(v_tetOUT.edgelist[i * 2]);
	//	edge.push_back(v_tetOUT.edgelist[i * 2 + 1]);
	//	if (v_tetOUT.edgemarkerlist != NULL) {
	//		edgemarker.push_back(v_tetOUT.edgemarkerlist[i]);
	//	}
	//}
	//}
	return true;
}

// �����ʷ����ݵ�CTriChip������
bool CSTLModel::Input_to_CTriChip()
{
	//if (mode == 0) //  Ĭ��ģ��
	//{
	// ����Ĭ��STL����
	for (int i = 0; i < temp_vertex.size(); i++) {
		tem_tri = new CTriChip();
	
		tem_tri->normal.dx = temp_vertex[i]->normal.dx;
		tem_tri->normal.dy = temp_vertex[i]->normal.dy;
		tem_tri->normal.dz = temp_vertex[i]->normal.dz;

		tem_tri->vex[0].x = temp_vertex[i]->vex[0].x;
		tem_tri->vex[0].y = temp_vertex[i]->vex[0].y;
		tem_tri->vex[0].z = temp_vertex[i]->vex[0].z;

		tem_tri->vex[1].x = temp_vertex[i]->vex[1].x;
		tem_tri->vex[1].y = temp_vertex[i]->vex[1].y;
		tem_tri->vex[1].z = temp_vertex[i]->vex[1].z;

		tem_tri->vex[2].x = temp_vertex[i]->vex[2].x;
		tem_tri->vex[2].y = temp_vertex[i]->vex[2].y;
		tem_tri->vex[2].z = temp_vertex[i]->vex[2].z;

		// ������������ݣ�����OpenGL����
		Add(tem_tri);
	}
	//} 
	//else if (mode == 1) // ģ��1
	//{
	// ��������������
	for (int i = 0; i < triface.size(); i++) {
		tem_tri = new CTriChip();


		tem_tri->tri[0].x = node.at((int)triface[i].x - 1).x;
		tem_tri->tri[0].y = node.at((int)triface[i].x - 1).y;
		tem_tri->tri[0].z = node.at((int)triface[i].x - 1).z;

		tem_tri->tri[1].x = node.at((int)triface[i].y - 1).x;
		tem_tri->tri[1].y = node.at((int)triface[i].y - 1).y;
		tem_tri->tri[1].z = node.at((int)triface[i].y - 1).z;

		tem_tri->tri[2].x = node.at((int)triface[i].z - 1).x;
		tem_tri->tri[2].y = node.at((int)triface[i].z - 1).y;
		tem_tri->tri[2].z = node.at((int)triface[i].z - 1).z;

		// ������������ݣ�����OpenGL����
		Add(tem_tri);
	}
	//}
	//else if (mode == 2) // ģ��2
	//{
	// ��������������
	for (int i = 0; i < tetrahedron.size(); i++) {
		tem_tri = new CTriChip();


		tem_tri->fourFace[0].x = node.at((int)tetrahedron[i].x - 1).x;
		tem_tri->fourFace[0].y = node.at((int)tetrahedron[i].x - 1).y;
		tem_tri->fourFace[0].z = node.at((int)tetrahedron[i].x - 1).z;

		tem_tri->fourFace[1].x = node.at((int)tetrahedron[i].y - 1).x;
		tem_tri->fourFace[1].y = node.at((int)tetrahedron[i].y - 1).y;
		tem_tri->fourFace[1].z = node.at((int)tetrahedron[i].y - 1).z;

		tem_tri->fourFace[2].x = node.at((int)tetrahedron[i].z - 1).x;
		tem_tri->fourFace[2].y = node.at((int)tetrahedron[i].z - 1).y;
		tem_tri->fourFace[2].z = node.at((int)tetrahedron[i].z - 1).z;

		tem_tri->fourFace[3].x = node.at((int)tetrahedron[i].t - 1).x;
		tem_tri->fourFace[3].y = node.at((int)tetrahedron[i].t - 1).y;
		tem_tri->fourFace[3].z = node.at((int)tetrahedron[i].t - 1).z;

		// ������������ݣ�����OpenGL����
		Add(tem_tri);
	}
	//	}
	//else {
	//	TRACE(_T("������Ϣ��pSTLModel->LoadSTLFile(strName,mode)��������ʧ�ܣ�mode���ô��󣡣�!"));
	//}

	return true;
}

// ����ȡ��stl�ļ����ݴ���v_tetIN���������ʷ����������������
bool CSTLModel::inputStl_to_Tetgen()
{

	tetgenmesh::arraypool *plist;
	tetgenio::facet *f;
	tetgenio::polygon *p;
	double *coord;
	int nverts = 0, iverts = 0;
	int nfaces = 0;
	int  i;

	// STL file has no number of points available. Use a list to read points.
	plist = new tetgenmesh::arraypool(sizeof(double) * 3, 10);

	// ����������������ÿһ������Ƭ�����
	for (auto iter = temp_vertex.cbegin(); iter != temp_vertex.cend(); iter++)
	{
		for (int j = 0; j < 3;j++)// ��ѭ��
		{
			// ���ν�һ����ά���x,y,z�������coord��
			plist->newindex((void **)&coord);
			coord[0] = (REAL)(*iter)->vex[j].x;
			coord[1] = (REAL)(*iter)->vex[j].y;
			coord[2] = (REAL)(*iter)->vex[j].z;
		}
	}
		
	nverts = (int)plist->objects;
	// nverts should be an integer times 3 (every 3 vertices denote a face).
	if (nverts == 0 || (nverts % 3 != 0)) {
		printf("Error:  Wrong number of vertices in file.\n");
		delete plist;
		return false;
	}
	
	v_tetIN.numberofpoints = nverts;
	v_tetIN.pointlist = new REAL[nverts * 3];

	for (i = 0; i < nverts; i++) {
		coord = (double *)fastlookup(plist, i);
		iverts = i * 3;
		v_tetIN.pointlist[iverts] = (REAL)coord[0];
		v_tetIN.pointlist[iverts + 1] = (REAL)coord[1];
		v_tetIN.pointlist[iverts + 2] = (REAL)coord[2];
	}

	nfaces = (int)(nverts / 3);
	v_tetIN.numberoffacets = nfaces;
	v_tetIN.facetlist = new tetgenio::facet[nfaces];

	// Default use '1' as the array starting index.
	v_tetIN.firstnumber = 1;
	iverts = v_tetIN.firstnumber;
	for (i = 0; i < nfaces; i++) {
		f = &v_tetIN.facetlist[i];
		v_tetIN.init(f);
		// In .stl format, each facet has one polygon, no hole.
		f->numberofpolygons = 1;
		f->polygonlist = new tetgenio::polygon[f->numberofpolygons]; // �ʷֳ���㣬�ڴ�й©
		p = &f->polygonlist[0];
		v_tetIN.init(p);
		// Each polygon has three vertices.
		p->numberofvertices = 3;
		p->vertexlist = new int[p->numberofvertices]; // �ʷֳ����2�����ڴ�й©
		p->vertexlist[0] = iverts;
		p->vertexlist[1] = iverts + 1;
		p->vertexlist[2] = iverts + 2;
		iverts += 3;
	}
	delete plist;
	return true;
}

// �Զ����ȡstl���ݵ㺯��
bool CSTLModel::Load_Stl_Points(LPCTSTR m_stlfile)
{
	// ��Ϊʹ�õ���Unicode�ַ�������char* �� LPTSTR���ڲ�ͬ������
	// Ϊ��ʹ����Щ�꣬�����ں����Ŀ�ʼ����USES_CONVERSION����ʼ��ĳЩ�ֲ�����
	USES_CONVERSION;

	FILE* file;
	int type = 0;
	if ((file = fopen(W2A(m_stlfile), "r")) == NULL) // W2A��������ڽ����ֽ�ת��Ϊխ�ֽ�
		return FALSE;

	char str[80];

	while (fscanf(file, "%s", str) == 1) {
		if (strncmp(str, "normal", 6) == 0) {
			tem_tri = new CTriChip(); // �ڴ�й©��
			 // ��ȡ��ʧ��������
			fscanf(file, "%lf %lf %lf", &(tem_tri->normal.dx), &(tem_tri->normal.dy), &(tem_tri->normal.dz));
			fscanf(file, "%*s %*s");
			// ��ȡ����Ƭ�Ķ���������Ϣ
			fscanf(file, "%*s %lf %lf %lf", &(tem_tri->vex[0].x), &(tem_tri->vex[0].y), &(tem_tri->vex[0].z));
			fscanf(file, "%*s %lf %lf %lf", &(tem_tri->vex[1].x), &(tem_tri->vex[1].y), &(tem_tri->vex[1].z));
			fscanf(file, "%*s %lf %lf %lf", &(tem_tri->vex[2].x), &(tem_tri->vex[2].y), &(tem_tri->vex[2].z));
			//Add(tem_tri,TRUE); // ���������Ƭ
			temp_vertex.push_back(tem_tri);
		}
	}
	fclose(file);//  �ر��ļ�
	return true;
}

//Serialize ���л���д�ĵ��еļ���ģ������
void	CSTLModel::Serialize(CArchive& ar)
{
	CEntity::Serialize(ar); // ���ȴ�ȡ��������
	m_TriList.Serialize(ar); // ���л���������

	if(ar.IsStoring()){
		// ���ĵ��ж�ȡ���ݺ�CSTLModel�����������Ѿ������˸ı�
		// ��Ҫ���ñ�־���Ը��°��ݺ�
		m_bModified = TRUE;
	}
}

// ʹ��OPenGL��ͼģ�ͣ�������ģ���е�����������Ƭ
void	CSTLModel::Draw(COpenGLDC* pDC)
{
	if(!m_bVisible)	return; //�����������ģʽ�������κλ���
	
	if(m_bHighlight)
		pDC->Highlight(TRUE); // ������ڸ�����ģʽ��ʹ�ø�������ɫ����
	else
		pDC->SetMaterialColor(m_color);//����ģʽ�£�ʹ�ö�����Ĳ�����ɫ

	// ��ǰ�Ƿ���ѡ��ģʽ
	if(pDC->IsSelectionMode()){
		// ��thisָ��ֵ��Ϊ��ǰ��������ƣ������ƶ�ջ����д����
		pDC->LoadName((UINT)this);
	}

	// �˴���������ÿ��ģ�Ͷ��������϶���ת������ʹ��
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	glScalef(m_Scale, m_Scale, m_Scale);

	// �����Զ������
	// ���û�ͼ��������ģ�ͻ���
	for (int i = 0;i < m_TriList.GetSize();i++) {
		m_TriList[i]->Draw(pDC,m_Mode); // ���û���ģʽm_Mode
	}

}

void CSTLModel::SetScale(float scale) // ����
{
	m_Scale = scale;
}

void CSTLModel::SetMouseRo(GLfloat xAngle, GLfloat yAngle) // ��ת
{
	m_xAngle = xAngle;
	m_yAngle = yAngle;

}

void CSTLModel::SetMode(int mode)
{
	m_Mode = mode;
}


// ���ģ���е�����������Ƭ�������ģ�����ݵĴ洢�ռ�
void	CSTLModel::Clear()
{
	for (int i = 0; i < m_TriList.GetSize(); i++) {
		if (m_TriList[i] != NULL)
		{
			delete m_TriList[i];
			m_TriList[i] = NULL;
		}
	}
	
	m_TriList.RemoveAll();

	m_bModified = TRUE;
}

BOOL	CSTLModel::IsEmpty()
{
	return m_TriList.GetSize() == 0;
}

////////////////////�߼�����ģ����Cpart//////////////////////
CPart::CPart()
{
}

CPart::~CPart()
{
	RemoveAllEntity();
}

//draw
void CPart::Draw(COpenGLDC* pDC)
{
	for (int i = 0;i < m_EntList.GetSize();i++)
		
		m_EntList[i]->Draw(pDC);
}

//serialize
void CPart::Serialize(CArchive& ar)
{
	CEntity::Serialize(ar);

	m_EntList.Serialize(ar); // ����ģ����CObArray��Serialize()����

	if(ar.IsStoring()){
		// ���ĵ��ж�ȡ���ݺ�CPart�����������Ѿ������˸ı�
		// ��Ҫ���ñ�־���Ը��°��ݺ�
		m_bModified = TRUE;
	}
}

//operation
void CPart::AddEntity(CEntity* ent)
{
	m_EntList.Add(ent);
	m_bModified = TRUE;
}

void CPart::RemoveEntity(CEntity* ent)
{
	for(int i=0;i<m_EntList.GetSize();i++){
		if(ent == m_EntList[i]){
			m_EntList.RemoveAt(i);
			m_bModified = TRUE;
			break;
		}
	}
}

void CPart::RemoveAllEntity()
{
	for (int i = 0; i < m_EntList.GetSize(); i++) {
		if (m_EntList[i] != NULL)
		{
			delete m_EntList[i];
			m_EntList[i] = NULL;
		}
	}
		
	m_EntList.RemoveAll();
	m_bModified = TRUE;
}

//attrib accessing
BOOL CPart::IsEmpty()
{
	return m_EntList.GetSize() == 0 ;
}

UINT	CPart::GetEntitySize()
{
	return m_EntList.GetSize();
}

CEntity* CPart::GetEntity(UINT i)
{
	ASSERT(i<m_EntList.GetSize());
	return m_EntList[i];
}

void CPart::UpdateBox()
{
	if(m_pBox){
		delete m_pBox;
		m_pBox = NULL;
	}

	CBox3D box;
	for(int i=0;i<m_EntList.GetSize();i++){
		if(m_EntList[i]->GetBox(box)){
			if(m_pBox)
				*m_pBox += box;
			else{
				m_pBox = new CBox3D();
				*m_pBox = box;
			}
		}
	}
	m_bModified = FALSE;
}




