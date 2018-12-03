// Entity.h: interface for the CEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITY_H__BE769D85_6C72_43F4_88FB_5521CA66FC8E__INCLUDED_)
#define AFX_ENTITY_H__BE769D85_6C72_43F4_88FB_5521CA66FC8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\inc\GeomCalc\cadbase.h"

#include "gl/gl.h"

#include "gl/glu.h"

#define GLUT_DISABLE_ATEXIT_HACK
#include <gl\glut.h>

#include "gl/glaux.h"
#pragma comment(lib, "glaux")// ����ӵ����������ó����޷�ʶ����ⲿ����
#pragma comment(lib, "legacy_stdio_definitions") // ǿ�Ƽ��ݾɵĴ��룬����ͨ��

#include "tetgen.h"
#include <vector>
#include <stdlib.h>

#define COND_READ(cond, where, len) do { if ((cond) && !fread((void *)&(where), (len), 1, f)) return false; } while (0)

using namespace std;

class COpenGLDC;
class AFX_EXT_CLASS CEntity : public CObject  
{
	// ���ζ���Ļ������Ա���
protected:
	BOOL		m_bModified; // �Ƿ��޸Ĺ�
	CBox3D*		m_pBox; // ָ��һ����С���ݺ�
	UINT		m_id; // �������ID��
	CString		m_name;  // ��������ַ���ʶ��Ϣ
	COLORREF	m_color; // ���������ɫ
	BOOL		m_bVisible;
	BOOL		m_bHighlight;

public:
	//constructor and destructor
	CEntity();
	virtual ~CEntity();

	//display
	virtual void Draw(COpenGLDC* pDC)=0; // ��ʾ�����壨���麯�������ڽӿڣ�

	//serialize
	virtual	void Serialize(CArchive& ar); // ���л���ȡ	

	//attrib accessing 
	BOOL		GetBox(CBox3D& box);	// ��ȡ���ݺ�
	
	void		SetID(UINT nID);		// ����ID��
	UINT		GetID();				// ��ȡID��
	
	void		SetName(LPCTSTR name);	// �����ַ���ʶ��Ϣ
	CString		GetName();				// ��ȡ�ַ���ʶ��Ϣ
	
	void		SetColor(COLORREF color); // ������ɫ
	COLORREF	GetColor();				  // ��ȡ��ɫ

	void		SetVisible(BOOL bVisible);
	BOOL		IsVisible();

	void		SetHighlight(BOOL bHighlight);
	BOOL		IsHighlight();

protected:
	virtual		void UpdateBox()=0; // ���¼�����ݺеĳߴ磨�����⺯����

};


//triangle chip
class AFX_EXT_CLASS CTriChip:public CObject
{

	DECLARE_SERIAL(CTriChip) // ���л�����
public:
	//attribs
	CPoint3D  vex[3]; // Ĭ��STL�������� 
	CVector3D normal; // Ĭ��STL�����淨ʧ����

	CPoint3D  tri[3]; // ������Ƭ�������� 
	CPoint3D  fourFace[4]; //�������ĸ��ǵ����� 

public:
	//constructor && destructor
	CTriChip(); // ���캯��

	CTriChip::CTriChip(const CPoint3D& v0, const CPoint3D& v1, const CPoint3D& v2);

	CTriChip(const CPoint3D& v0,const CPoint3D& v1,
			 const CPoint3D& v2,const CVector3D& norm);

	CTriChip::CTriChip(const CPoint3D & v0, const CPoint3D & v1, const CPoint3D & v2, const CPoint3D & v3,
		const CPoint3D & v4, const CPoint3D & v5, const CPoint3D & v6);

	virtual ~CTriChip(); // ��������

	//display
	virtual void Draw(COpenGLDC* pDC,int b); // ��ʾ����


	//serialize
	virtual void Serialize(CArchive& ar); // ���л���ȡ
	
	//operator
	const CTriChip& operator=(const CTriChip&); // ����������

};


//tessellated model
class AFX_EXT_CLASS CSTLModel: public CEntity
{
	DECLARE_SERIAL(CSTLModel)  // ���л�����
public:
	tetgenio v_tetIN;
	tetgenio v_tetOUT;

	int m_Mode; // ����ģʽ״̬������������Ϊ0��1��2


	vector<CPoint3D> vertices;
	vector<CPoint3D>  faces;

	CTriChip* tem_tri;  // ������ʱָ��CTriChip����

	CTypedPtrArray<CObArray,CTriChip*>	m_TriList; // ����Ƭ����������Ϣ

	// .node�ļ�
	vector<CTriChip*> temp_vertex; // ���ڶ������ݻ��������������������ж����ڵĶ���һһ����

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

	GLfloat m_xAngle = 0.0f;
	GLfloat m_yAngle = 0.0f;
	float m_Scale = 1.0f; // ���ű���

	void SetScale(float scale); // �����������ű���
	void SetMouseRo(GLfloat xAngle, GLfloat yAngle); // ����������ת�Ƕ�

	void SetMode(int mode); // ���û���ģʽ����

	bool Dissection();  // �ʷֺ���
	bool CSTLModel::Input_to_CTriChip(); // �����ʷ����ݵ�CTriChip������

public:
	//constructor && destructor
	CSTLModel(); // ���캯��
	virtual ~CSTLModel(); // ��������

	//display
	void	Draw(COpenGLDC* pDC); // ��ʾ����

	//serialize
	void	Serialize(CArchive& ar); // ���л���ȡ

	//		operation
	const   CSTLModel& operator=(const CSTLModel&); // ��=������������
	
	void	Add(CTriChip* tri);
	bool IsTextFile(const char * strFileName);
	// ��������Ƭ��
	BOOL	LoadSTLFile(LPCTSTR file,int mode); // ����STL�ļ�

	bool  CSTLModel::ReadBinFile(LPCTSTR stlfile);



	void	Clear(); // �����������

	//attrib accessing
	BOOL	IsEmpty(); // �ж�ģ���Ƿ�Ϊ��

protected:
	virtual void UpdateBox(); // ���¼�����ݺгߴ�

public:
	bool inputStl_to_Tetgen(); // ����ȡ��stl�ļ����ݴ���v_tetIN���������ʷ����������������
	bool Load_Stl_Points(LPCTSTR m_stlfile); // �Զ����ȡstl���ݵ㺯��

};

class AFX_EXT_CLASS CPart : public CEntity // ��CEntity����
{
//attribs

protected:
	CTypedPtrArray<CObArray,CEntity*> m_EntList; // ����Ԫ�ض���ָ����

public:
	//constructor && destructor
	CPart();
	virtual ~CPart();

	//draw
	virtual void Draw(COpenGLDC* pDC); // ��ʾ����

	//serialize
	virtual void Serialize(CArchive& ar); // ���л���ȡ����

	//operation
	void	AddEntity(CEntity* ent); // ��Ӽ����庯��
	void	RemoveEntity(CEntity* ent); // �ͷŵ�һ������Ĵ洢�ռ亯��
	void	RemoveAllEntity(); // �ͷ����м�����Ĵ洢�ռ亯��

	//attrib accessing
	BOOL	IsEmpty(); // �ж�ģ���Ƿ�Ϊ�յĺ���

	UINT		GetEntitySize(); // ��ȡģ���ڼ�������������ĺ���
	CEntity*	GetEntity(UINT i); // ��ȡģ�ͼ��������Ϊi�ļ�����ĺ���

protected:
	virtual void	UpdateBox(); // ���¼������м���ģ��������ݺеĺ���
};
#endif // !defined(AFX_ENTITY_H__BE769D85_6C72_43F4_88FB_5521CA66FC8E__INCLUDED_)
