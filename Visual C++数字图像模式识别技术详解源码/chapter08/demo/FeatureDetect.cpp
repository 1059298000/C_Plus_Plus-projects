// FeatureDetect.cpp: implementation of the FeatureDetect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo1.h"
#include "FeatureDetect.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
FeatureDetect::FeatureDetect()
{
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	
	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

FeatureDetect::FeatureDetect(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					 unsigned char *pImgData):
ImageDib(size, nBitCount, lpColorTable, pImgData)
{
	
    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0
	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
	m_pImgDataIn=pImgData;//m_pImgData;

	PMatrixRD = NULL;	//45�ȷ����ϵĻҶȹ��־���
	PMatrixLD = NULL;	//135�ȷ����ϵĻҶȹ��־���
	PMatrixV = NULL;		//90�ȷ����ϵĻҶȹ��־���
	PMatrixH = NULL;		//0�ȷ����ϵĻҶȹ��־���

	//m_tOriPixelArray = NULL;//ԭʼλͼ����
	//m_tResPixelArray = NULL;//�ο�λͼ����
	//m_dib = new CDib();

	distance = 5;
	FilterWindowWidth = 16;
	GrayLayerNum = 8; //��ʼ����Ϊ8���ҶȲ㣬�����޸�
	//�������־����ΪGrayLayerNum��GrayLayerNum
	int i;
	PMatrixH = new int*[GrayLayerNum];
	PMatrixLD= new int*[GrayLayerNum];
	PMatrixRD= new int*[GrayLayerNum];
	PMatrixV = new int*[GrayLayerNum];
	for(i=0; i<GrayLayerNum; i++){
		PMatrixH[i] = new int[GrayLayerNum];
		PMatrixLD[i]= new int[GrayLayerNum];
		PMatrixRD[i]= new int[GrayLayerNum];
		PMatrixV[i] = new int[GrayLayerNum];
	}
}

FeatureDetect::~FeatureDetect()
{

}

////////////////////////////////////////////////////////////////////////////////////
//�������ܣ�������������
//������FeatureEnergy������
//      FeatureEntropy����
//      FeatureInertiaQuadrature�����Ծ�
//      FeatureCorrelation�����
//      FeatureLocalCalm���ֲ�ƽ��
//      pMatrix�����־���
//      dim�����־����ά��
///////////////////////////////////////////////////////////////////////////////////
void FeatureDetect::ComputeFeature(double &FeatureEnergy, double &FeatureEntropy, 
							   double &FeatureInertiaQuadrature, double &FeatureCorrelation, 
							   double &FeatureLocalCalm, int** pMatrix, int dim)
{
	int i,j;
	double **pdMatrix;
	pdMatrix = new double*[dim];
	for(i=0; i<dim; i++)
		pdMatrix[i] = new double[dim];

	int total = 0;
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			total += pMatrix[i][j];
		}
	}

	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			pdMatrix[i][j] = (double)pMatrix[i][j]/(double)total;
		}
	}
	
	FeatureEnergy = 0.0;
	FeatureEntropy = 0.0;
	FeatureInertiaQuadrature = 0.0;
	FeatureLocalCalm = 0.0;


	//�����������ء����Ծء��ֲ�ƽ��
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			//����
			FeatureEnergy += pdMatrix[i][j]*pdMatrix[i][j];

			//��
			if(pdMatrix[i][j]>1e-12){
				FeatureEntropy -= pdMatrix[i][j]*log(pdMatrix[i][j]);
			}

			//���Ծ�
			FeatureInertiaQuadrature += (double)(i-j)*(double)(i-j)*pdMatrix[i][j];

			//�ֲ�ƽ��
			FeatureLocalCalm += pdMatrix[i][j]/(1+(double)(i-j)*(double)(i-j));
		}
	}

	//����ux
	double ux = 0.0;
	double localtotal = 0.0;
	for(i=0; i<dim; i++){
		localtotal = 0.0;
		for(j=0; j<dim; j++){
			localtotal += pdMatrix[i][j];
		}
		ux += (double)i * localtotal;
	}

	//����uy
	double uy = 0.0;
	for(j=0; j<dim; j++){
		localtotal = 0.0;
		for(i=0; i<dim; i++){
			localtotal += pdMatrix[i][j];
		}
		uy += (double)j * localtotal;
	}

	//����sigmax
	double sigmax = 0.0;
	for(i=0; i<dim; i++){
		localtotal = 0.0;
		for(j=0; j<dim; j++){
			localtotal += pdMatrix[i][j];
		}
		sigmax += (double)(i-ux) * (double)(i-ux) * localtotal;
	}

	//����sigmay
	double sigmay = 0.0;
	for(j=0; j<dim; j++){
		localtotal = 0.0;
		for(i=0; i<dim; i++){
			localtotal += pdMatrix[i][j];
		}
		sigmay += (double)(j-uy) * (double)(j-uy) * localtotal;
	}

	//�������
	FeatureCorrelation = 0.0;
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			FeatureCorrelation += (double)(i-ux) * (double)(j-uy) * pdMatrix[i][j];
		}
	}
	FeatureCorrelation /= sigmax;
	FeatureCorrelation /= sigmay;
}

/////////////////////////////////////////////////////////////////////////////////////
//���ܣ����㹲�־���
//������LocalImage����������ľֲ���������ͼ��
//      LocalImageWidth���ֲ�����������
////////////////////////////////////////////////////////////////////////////////////
void FeatureDetect::ComputeMatrix(BYTE **LocalImage, int LocalImageWidth)
{
	BYTE **NewImage;
	NewImage = new BYTE*[LocalImageWidth];

	int i,j;
	for(i=0; i<LocalImageWidth; i++)
		NewImage[i] = new BYTE[LocalImageWidth];

	for(i=0; i<LocalImageWidth; i++){
		for(j=0; j<LocalImageWidth; j++){
			//�ֳ�GrayLayerNum���Ҷȼ�
			NewImage[i][j] = LocalImage[i][j] / (256/GrayLayerNum);
		}
	}

	for(i=0; i<GrayLayerNum; i++){
		//
		for(j=0; j<GrayLayerNum; j++){
			PMatrixH[i][j]  = 0;
			PMatrixLD[i][j] = 0;
			PMatrixRD[i][j] = 0;
			PMatrixV[i][j]  = 0;
		}
	}

	//����0�ȵĻҶȹ�����
	for(i=0; i<LocalImageWidth; i++){
		for(j=0; j<LocalImageWidth-distance; j++){
			PMatrixH[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[i][j+distance]] += 1;
			PMatrixH[(unsigned int)NewImage[i][j+distance]][(unsigned int)NewImage[i][j]] += 1;
		}
	}

	//����90�ȵĻҶȹ�����
	for(i=0; i<LocalImageWidth-distance; i++){
		for(j=0; j<LocalImageWidth; j++){
			PMatrixV[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[i+distance][j]] += 1;
			PMatrixV[(unsigned int)NewImage[i+distance][j]][(unsigned int)NewImage[i][j]] += 1;
		}
	}

	//����135�ȵĻҶȹ�����
	for(i=0; i<LocalImageWidth-distance; i++){
		for(j=0; j<LocalImageWidth-distance; j++){
			int newi, newj;
			newi = i+distance;
			newj = j+distance;
			PMatrixLD[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[newi][newj]] += 1;
			PMatrixLD[(unsigned int)NewImage[newi][newj]][(unsigned int)NewImage[i][j]] += 1;
		}
	}

	//����45�ȵĻҶȹ�����
	for(i=distance; i<LocalImageWidth; i++){
		for(j=0; j<LocalImageWidth-distance; j++){
			int newi, newj;
			newi = i-distance;
			newj = j+distance;
			PMatrixRD[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[newi][newj]] += 1;
			PMatrixRD[(unsigned int)NewImage[newi][newj]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
}

