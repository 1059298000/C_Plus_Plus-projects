
// FeatureReuseDoc.h : CFeatureReuseDoc ��Ľӿ�
//

#pragma once
#include "TriMesh\include\TriMesh.h"
#include "OpenGL\OpenGLDC.h"
#include <malloc.h>    // ��� malloc.h �� crtdbg.h ˳���µ� Debug Assertion Failed, "Corrupted pointer passed to _freea" ��
#include <crtdbg.h>

#include "TriChip.h"
#include "tetgen.h"
#include "Section.h"


class CFeatureReuseDoc : public CDocument
{
protected: // �������л�����
	CFeatureReuseDoc();
	DECLARE_DYNCREATE(CFeatureReuseDoc)

// ����
public:
	vector<TriMesh*>		meshes;
	int								Current_mesh;					//��ǰ������ģ��

// ����
public:
	TriMesh *mesh;
	CTriChip tem_tri;  // ������ʱָ��CTriChip����

	tetgenio v_tetIN;
	tetgenio v_tetOUT;

	vector<CPoint3D> vertices;
	vector<CPoint3D>  faces;

	// .node�ļ�
	vector<CTriChip> temp_vertex; // ���ڶ������ݻ��������������������ж����ڵĶ���һһ����
	vector<CTriChip> m_TriList;

	vector<CPoint3D> node; // �������
	// .face�ļ�
	vector<CPoint3D> triface; // ����������
	vector<int> trifacemarker; // ��������
	//.ele�ļ� 
	vector<int> tetrahedronattribute; // ����������
	vector<CPoint4D> tetrahedron; // ���ڴ洢�������ĸ��ǵ����������
	 // .edge�ļ�
	vector<int> edge; // ������ı�
	vector<int> edgemarker; // ������ı߱��


	GLfloat m_xAngle;
	GLfloat m_yAngle; // ������ת�Ƕ�
	CPoint m_MouseDownPoint;
	float m_Scale;

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

	virtual BOOL				OnOpenDocument(LPCTSTR lpszPathName);
	bool								IsTextFile(const char * strFileName);					 //�ж�һ���ļ��Ƿ�Ϊ�ı��ļ�
	void								split(char **arr, char *str, const char *del);		//�ַ��ָ���ļ򵥶����ʵ��;
	void								DrawModel(COpenGLDC* pDC);							// ����ģ�ͺ���

	TriMesh::BBox			getbox();																		   // ��ȡ���ݺ�

// ʵ��
public:


	bool inputStl_to_Tetgen(); // Ϊtetgen�⴫��STLģ�͵��ʷֲ���

	bool Dissection(); // �ʷֺ���

	bool Input_to_CTriChip(); // �ʷ����� ����CTriChip����

	bool Load_Stl_Points(LPCTSTR m_stlfile, TriMesh *themesh, int fn);// �Զ����ȡstl���ݵ㺯��

	void SetMode(int mode); // ���û���ģʽ
	void SetArrows(bool b);  // ����ʸ����ͷ

	void Set_cloudPicture(bool b); // ���ò�ɫ��ͼ״̬

	void SetScale(float scale); // ��̬�������ű�������
	void SetMouseRotate(GLfloat xAngle, GLfloat yAngle); // ��̬������ת�Ƕ�

	virtual ~CFeatureReuseDoc();

public:
	bool read_txt(string f); // ���������ı���ȡ����

	int m_Mode; // ����ģʽ״̬������������Ϊ0��1��2, 3
	bool is_PrintArrows; // �Ƿ���ʾʸ����ͷ
	bool is_Draw_cloudPicture; // �Ƿ���ʾ��ɫ��ͼ
	int stage;  // �����������ν׶�
	int counts;
	int delta; // ��̬��ʾģʽ��ѭ������

	static int steps; // �����������ν׶�����
	vector<Section> sections; // ÿ���׶ε�ģ��״̬����
	vector<int> num_faces;
	void SetStage(int m_stage); // ���ù���ģ����ʾ�׶�
	void SetDelta(int m_delta); // ���ù���ģ�Ͷ�̬��ʾѭ������
	void SetCounter(int counter); // ���ö�̬��ʾʱ�ļ�ʱ��




	typedef struct 
	{
		double x, y; // ������
		double strain; // ��߳�ֵ1
		double stress; // ��߳�ֵ2
		double index; // ��������
	}DPoint;  // �Զ����ά��ṹ��

	typedef struct
	{
		DPoint point[3];  // ���ڱ���������Ƭ�����������Ϣ
		bool is_used = false; // �Ƿ�������ֵ��
		bool is_Original = false; // ��ֵ�ߵ���ʼ������Ƭ���
		bool is_edge = false; // �߽�������Ƭ��־
		bool flag1 = false; // ���ڱ��������Ƭ1��2�����ڱ��Ƿ�Ϊ�߽��
		bool flag2 = false; // ���ڱ��������Ƭ2��3�����ڱ��Ƿ�Ϊ�߽��
		bool flag3 = false; // ���ڱ��������Ƭ3��1�����ڱ��Ƿ�Ϊ�߽��
	}Trigon; // ������Ƭ�ṹ��

	typedef struct
	{
		double x, y;
		double H; // �߳�ֵ
		bool is_begin = false;
		bool is_end = false;
		vector<CPoint2D> m_lines; // ��ͷ����β���ڵı߽�ߵ������˵�

	}Dcontour;  // ��ֵ�߽ڵ�ṹ��


	//typedef struct
	//{
	//	double y;
	//	vector<double> rank; // ��ɫ�ȼ�
	//	vector<double> x_Set; // ɨ�������ֵ�߽���ĺ�����
	//}Scanner;  // ɨ���߽ṹ��


	int Ncolor;      // ��ɫ����
	vector<int> Dc;
	vector<double>  delta_Set;
	vector<double>  Max_x, Min_x, Max_y, Min_y;							// ���н׶εĹ��������½���������Ͻ�����
	vector<double>  stress_Max, stress_Min;										// ���н׶εĹ��������߳�ֵ����С�߳�ֵ 
	
	vector<vector<Scanner>> Scanner_TotalSet;								// ���н׶ε�ɨ���߼���

	int findNumOfTrigon_Edge(vector<Trigon> vec);						// Ѱ�ұ�Ե������ĸ���

																		
	bool CFeatureReuseDoc::isAllUsed(vector<Trigon> vec); // �ж������漯��vec���е��������Ƿ��Ѿ��ù���

	bool CFeatureReuseDoc::findSame(vector<Dcontour> Dcontour_Set, Trigon rigon); // Ѱ���Ƿ�����ͬ��������Ƭ

	vector<vector<double>> stress_TotalSet;										// ���н׶εĸ߳�ֵ����

	vector<vector<vector<Dcontour>>> Dcontour_TotalSet;		// ���н׶εĵ�ֵ�߼���

	vector<vector<Trigon>>  ContourTriArr;											// ���е�ֵ�ߵ�������Ƭ����

	vector<vector<Trigon>> Trigon_Edge_Set;									// ���б�Ե������Ƭ�ļ���

	vector<vector<CPoint2D>>  BorderLine_Set;								// ���ڱ������н׶εı�Ե����

	vector<vector<vector<CPoint3D>>>  NonClosedRegion_Set;				// ���ڱ������н׶εĿ����ߵķ������
	vector<vector<vector<CPoint3D>>>  ClosedRegion_Set;						// ���ڱ������н׶εı����ߵķ������

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void SetTitle(LPCTSTR lpszTitle);
};