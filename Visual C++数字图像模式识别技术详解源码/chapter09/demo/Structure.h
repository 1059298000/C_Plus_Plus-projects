////Structure.h//
//���������е��������ݽṹ����ͽṹ�����

#ifndef STRUCTURE_H
#define STRUCTURE_H
//����c++
#include <vector>
#include <list>
#include <string>

using namespace std;

#define pi 3.1415927
const int Swh=24;                            //�ַ���һ����С28
const int Feature=13;//22                        //���ֵ�������//���¸�����С
const int SUMCHINESE=3768;                   //һ��������������Ҫ�����������壩
//const int SUMCHINESE=40;
const int SUMCHAR=567;                      //�ַ���������
//������ͨ��
const int CHARHOLE0=362;                    //�ַ�0�׶���
const int CHARHOLE1=141;                     //�ַ�1�׶���
const int CHARHOLE2=53;                     //�ַ�2�׶���
const int CHARHOLE3=11;                      //�ַ�3�׶���+����3�׶���
//const double REFUSE=0.025;                   //���־�ʶ��


//��ʽ������
struct h
{
	int m_iX1;//��������
	int m_iX2;
	int m_iH;//�и�
	int m_ias;//���м��
	int m_ibs;//���м��	
};

///����������������з֣�
struct cluster
{
	int first;//�߶�
	int second;//����
	int third;//��ֵ
};

///λ�����������������ͨ�ýṹ��
class Position
{
public:
	int m_left;
	int m_top;
	int m_bottom;
	int m_right;

	Position():m_left(0),m_top(0),m_bottom(0),m_right(0){}

};


//�ĵ��и�����������һ����,��ÿ���������һ���ַ�������������������
enum Type{Chinese,Formular};//Type t=0/1/2

struct coordinate 
{
	int x;
	int y;
};//�����ַ�������λ��


//�����ַ�
class CFtChinese
{
public:	
	Type m_type;//ȷ���Ƿ�Ϊ����
	Position m_pos;
	int m_iImage[48][48];//���ֹ�һ����С48���ɵ���������������//��һ����С�ɱ�32
    //////////////////////////////////////////////////////////////////////////
    //string m_Chinese;//ԭ�ַ��޷���ȡ
	//////////////////////////////////////////////////////////////////////////
	//features
	double m_iFtCrude[129];//�������������ɱ䣩
	//double m_iCenter[129];//��������
    //double m_iFtPer[78];//ϸ������(65)
	int m_iHole;

	//double m_dIndex;
	int m_dIndex;
	int m_iCrude;
	double e;
	
	int m_iSumBlack;
	double m_iDensity;
	int i_row;
	//mine
	//int m_storke;//�ʻ��ܶ�����
	//int m_wavelet;//С��
	//enum Font{Song,FangSong,Hei,Kai};//����ѡ����ѡ�����壬��ʶ��
	list<coordinate> m_FtXY;//��������������
    //CFtFormular m_Formular;//������
	CFtChinese()
	{
		for (int i=0;i!=48;++i)
		{
			for (int j=0;j!=48;++j)
			{
				m_iImage[i][j]=0;
			}
		}
		m_iSumBlack=0;
		m_iDensity=0.0;
	}

};
//�ַ�����
class CFtCharacter
{
public:
   int m_iSinF;//��������ֵ
   int m_iInFX;//��Ƕ����ֵ
   int m_iInFY;//��Ƕ�����ַ�����ţ��кţ�
   Position m_pos;//�ַ�����

   //////////////////////////////////////////////////////////////////////////
   //string m_Char;//ԭ�ַ��޷���ȡ
   //////////////////////////////////////////////////////////////////////////
   
   //features
   int m_iMiddleX;//��һ����������X
   int m_iMiddleY;//��һ����������Y
   int m_iCenterX;//����X����
   int m_iCenterY;//����Y����

   //int m_projectX;//ͶӰ����X
   //int m_projectY;//ͶӰ����Y
   double m_dRationWH;//�߿��
   int m_iHole;//�׶���
   int m_iFeature[Feature];//��������
   int m_iImage[Swh][Swh];//��һ��ģ��
   int m_iIndex;//���������е���ţ�������Ҫд�룩
   //ʶ�����
   int m_iType;//�ַ�������һ�������ַ���ʶ��֮�󣬽ṹ������
   //�����1 ������2 ������3 ���±���4�� ������5 ������6 ��������7�� ��ͨ��8 ������9 �ϲ���0
   int m_iType2;   //up=1 center=2 down=3 �������=4 �ϲ��ͱ��=5

   CFtCharacter()
   {
	   for (int i=0;i!=Swh;++i)
	   {
		   for (int j=0;j!=Swh;++j)
		   {
			   m_iImage[i][j]=0;
		   }
	   }
   }
   //overload
   bool operator<(CFtCharacter &item)
   {
	   if (m_iMiddleY<item.m_iMiddleY)
	   {
		   return TRUE;
	   }
	   else
		   return FALSE;
   }
   
};
///*
class CFtCharactor
{
public:
   int m_iSinF;//��������ֵ
   int m_iInFX;//��Ƕ����ֵ
   int m_iInFY;//��Ƕ�����ַ�����ţ��кţ�
   Position m_pos;//�ַ�����

   //////////////////////////////////////////////////////////////////////////
   //string m_Char;//ԭ�ַ��޷���ȡ
   //////////////////////////////////////////////////////////////////////////
   
   //features
   int m_iMiddleX;//��һ����������X
   int m_iMiddleY;//��һ����������Y
   int m_iCenterX;//����X����
   int m_iCenterY;//����Y����

   //int m_projectX;//ͶӰ����X
   //int m_projectY;//ͶӰ����Y
   double m_dRationWH;//�߿��
   int m_iHole;//�׶���
   int m_iFeature[Feature];//��������
   int m_iImage[Swh][Swh];//��һ��ģ��
   int m_iIndex;//���������е���ţ�������Ҫд�룩
   //ʶ�����
   int m_iType;//�ַ�������һ�������ַ���ʶ��֮�󣬽ṹ������
   //�����1 ������2 ������3 ���±���4�� ������5 ������6 ��������7�� ��ͨ��8 ������9 �ϲ���0
   int m_iType2;   //up=1 center=2 down=3 �������=4 �ϲ��ͱ��=5

   CFtCharactor()
   {
	   for (int i=0;i!=Swh;++i)
	   {
		   for (int j=0;j!=Swh;++j)
		   {
			   m_iImage[i][j]=0;
		   }
	   }
   }
   //overload
   bool operator<(CFtCharactor &item)
   {
	   if (m_iMiddleY<item.m_iMiddleY)
	   {
		   return TRUE;
	   }
	   else
		   return FALSE;
   }
   
};//*/

class CCharInit
{
public:
	int m_iCenterX;                           //����X����
	int m_iCenterY;                           //����Y����
	double m_dRatioWH;                        //��߱�
	int m_iFeature[Feature];                  //��������
	int m_iIndex;	                          //����
	int m_iType;		                      //�����ַ�����𣨽ṹ����ʹ�ã� 
	//�����1 ������2 ������3 (�±���4) ������5 ������6 (������7) ��ͨ��8 ������9 �ϲ���0
	int m_iType2;		                      // up=1  center=2  down=3 ������ţ�4 �ϲ��ͱ�ţ�5

};//�������ַ���
//��ʽ�У���λ,�зִ������⣩
struct CFtFormular
{
	int iRow;//�к�
	double HT;//��һ���и�
	double AS;//���м��=�����еľ���/�ж�ƽ����
	double BS;//���м��=�����еľ���/�ж�ƽ����
	double LI;//������=��߾�/�п�
	double RI;//������=�ұ߾�/�п�
	double LD;//��ʽ��ź͹�ʽ�ľ����һ��=��ʽ��ź͹�ʽ�ľ���/�ж�ƽ����
	double DE;//�ܶ�=��������ص���Ŀ/������������

	//CFtChinese m_Chinese;//����
};
//////////////////////////////////////////////////////////////////////////
//algorithms �Ľṹ
//����,�ַ�
class match
{
public:
	int index;
	double e;
	int InitChar;
};//ƥ���㷨

//Layout Analyse
enum Type2{Table,Image};
class layoutStru
{
public:
	Position m_pos;
	double area;
    
	Type2 m_type2;
	
};

//�ı���
/*class CText
{
public:
   int m_BL;//�������к�
   Position t_pos;

   CFtChinese *p_Chines;
   CFtCharacter *p_Char;

};*/
//����
class CForm
{
public:
	Position m_Fpos;
	double area;

	CFtChinese *p_Chinese;
	//�������
};
//ͼ�ο�
class CImage
{
public:
	Position b_pos;
    //ѹ��ͼ������
};

//�ַ��ṹ����
class StruAna
{
public:
	Position m_pos;
	int m_iMiddleY;//��ֱ�����ϵ�
	int m_iMiddleX;//ˮƽ�����ϵ�
	int m_iIndex;
	int m_iType;
	int m_iType2;
};
//////////////////////////////////////////////////////////////////////////
typedef struct{
	int Value;
	int Dist;
	int AngleNumber;
}	MaxValue;//�ṹ��(Hough)
//////////////////////////////////////////////////////////////////////////
class Number
{
public:
   int m_value;
   int m_count;

   Number():m_value(0),m_count(0){}

};//�������
class Line 
{
public:
	int line1;
	int line2;
	int line;

	Line():line1(0),line2(0),line(0){}
};

#endif