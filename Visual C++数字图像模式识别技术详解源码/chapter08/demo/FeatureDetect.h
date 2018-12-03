// FeatureDetect.h: interface for the FeatureDetect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEATUREDETECT_H__07B031B4_F2C2_4C25_BE7D_FE9272432868__INCLUDED_)
#define AFX_FEATUREDETECT_H__07B031B4_F2C2_4C25_BE7D_FE9272432868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"
class FeatureDetect : public ImageDib
{
public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;
	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;
	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;
	//����ͼ��λͼ����ָ��
	unsigned char * m_pImgDataIn;

		//����
	double FeatureLocalCalmRD;	//�ֲ�ƽ���ԣ�45�ȷ���
	double FeatureLocalCalmLD;	//�ֲ�ƽ���ԣ�135�ȷ���
	double FeatureLocalCalmV;	//�ֲ�ƽ���ԣ�90�ȷ���ȷ���
	double FeatureLocalCalmH;	//�ֲ�ƽ���ԣ�0�ȷ���
	double FeatureCorrelationRD;	//����ԣ�45�ȷ���
	double FeatureCorrelationLD;	//����ԣ�135�ȷ���
	double FeatureCorrelationV;		//����ԣ�90�ȷ���
	double FeatureCorrelationH;		//����ԣ�0�ȷ���
	double FeatureInertiaQuadratureRD;	//���Ծأ�45�ȷ���
	double FeatureInertiaQuadratureLD;	//���Ծأ�135�ȷ���
	double FeatureInertiaQuadratureV;	//���Ծأ�90�ȷ���
	double FeatureInertiaQuadratureH;	//���Ծأ�0�ȷ���
	double FeatureEntropyRD;	//�أ�45�ȷ���
	double FeatureEntropyLD;	//�أ�135�ȷ���
	double FeatureEntropyV;		//�أ�90�ȷ���
	double FeatureEntropyH;		//�أ�0�ȷ���
	double FeatureEnergyRD;		//������45�ȷ���
	double FeatureEnergyLD;		//������135�ȷ���
	double FeatureEnergyV;		//������90�ȷ���
	double FeatureEnergyH;		//������0�ȷ���
	int FilterWindowWidth;	//���������Ĵ�С��ͨ����ͼ�񻮷ֳ����ɸ���������
	
	int distance;	//���룬���ݲ�ͬ��Ӧ��ѡȡ	
	int GrayLayerNum;	//�Ҷȷּ�
	int** PMatrixRD;	//45�ȷ����ϵĻҶȹ��־���
	int** PMatrixLD;	//135�ȷ����ϵĻҶȹ��־���
	int** PMatrixV;		//90�ȷ����ϵĻҶȹ��־���
	int** PMatrixH;		//0�ȷ����ϵĻҶȹ��־���
private:
	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;
	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;
	//���ͼ����ɫ����
	int m_nColorTableLengthOut;
public:
	//���������Ĺ��캯��
	FeatureDetect();
	//�������Ĺ��캯��
	FeatureDetect(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);
	//��������
	~FeatureDetect();
	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();

	void ComputeMatrix(BYTE **LocalImage, int LocalImageWidth);
	void ComputeFeature(double &FeatureEnergy, double &FeatureEntropy, 
	double &FeatureInertiaQuadrature, double &FeatureCorrelation, 
	double &FeatureLocalCalm, int** pMatrix, int dim);

};

#endif // !defined(AFX_FEATUREDETECT_H__07B031B4_F2C2_4C25_BE7D_FE9272432868__INCLUDED_)
