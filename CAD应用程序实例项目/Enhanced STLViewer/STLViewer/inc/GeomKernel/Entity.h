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
	CPoint3D  vex[3]; // ������Ƭ�������� 
	CVector3D normal; // ������Ƭ��ʧ����

public:
	//constructor && destructor
	CTriChip(); // ���캯��
	CTriChip(const CPoint3D& v0,const CPoint3D& v1,
			 const CPoint3D& v2,const CVector3D& norm);
	virtual ~CTriChip(); // ��������

	//display
	virtual void Draw(COpenGLDC* pDC); // ��ʾ����

	//serialize
	virtual void Serialize(CArchive& ar); // ���л���ȡ
	
	//operator
	const CTriChip& operator=(const CTriChip&); // ����������

};


//tessellated model
class AFX_EXT_CLASS CSTLModel: public CEntity
{
	DECLARE_SERIAL(CSTLModel)  // ���л�����
//attribs
public:

	CTypedPtrArray<CObArray,CTriChip*>	m_TriList; // ����Ƭ����������Ϣ
	GLfloat m_xAngle = 0.0f;
	GLfloat m_yAngle = 0.0f;
	GLfloat m_xPos = 0.0f;
	GLfloat m_yPos = 0.0f;
	
	float m_Scale = 1.0f;
	void SetScale(float scale);
	void SetMouseRo(GLfloat xAngle, GLfloat yAngle);

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
	
	void	Add(CTriChip* tri); // ��������Ƭ��
	BOOL	LoadSTLFile(LPCTSTR file); // ����STL�ļ�
	void	Clear(); // �����������

	//attrib accessing
	BOOL	IsEmpty(); // �ж�ģ���Ƿ�Ϊ��

protected:
	virtual void UpdateBox(); // ���¼�����ݺгߴ�
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
