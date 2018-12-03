// charsRecognition.cpp: implementation of the CharsRecognition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo1.h"
#include "charsRecognition.h"
#include "Structure.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

charsRecognition::charsRecognition()
{
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

charsRecognition::charsRecognition(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
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
	
}

charsRecognition::~charsRecognition()
{

}

charsRecognition::HprojX()
{
	unsigned char*	lpSrc;				// ָ��Դͼ���ָ��	
	LONG	i;							// ѭ������
	LONG	j;	
	//����ͼ��ÿ�����ֽ���,�Ҷ�ͼ��Ϊ1�ֽ�/����
	int pixelByteIn=1;
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;
   	int *iProjX=new int[m_imgHeight];
	for(i=0;i<m_imgHeight;i++){
		iProjX[i]=0;
	}
	for(i=0;i<m_imgHeight;i++){		
		for(j=0; j<m_imgWidth;j++){
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+j;	
			if((*lpSrc)==0)	(iProjX[i])++;
		}
	}
	h *ProjX=new h;
	for(i=0;i<m_imgHeight;i++){
	    if(iProjX[i]==0)
			continue;
		else{
		    ProjX->m_iX1=i;
		    while(iProjX[i]!=0)	i++;
			ProjX->m_iX2 =i-1;
			ProjX->m_iH=ProjX->m_iX2-ProjX->m_iX1+1;
			m_ProjX.push_back(*ProjX);
		}
	}
	delete ProjX;
}

int charsRecognition::LineCluster()
{
	vector <cluster> clustering;
	cluster *newCluster=new cluster;
    for(list <h> ::iterator it=m_ProjX.begin();it!=m_ProjX.end();++it){
		if(clustering.empty()){
			(*newCluster).first=(*it).m_iH ;
			(*newCluster).second=1;
		    clustering.push_back(*newCluster);
		}
		else{
			for(vector <cluster> ::iterator itv=clustering.begin();itv!=clustering.end();++itv){
				if(abs((*itv).first-(*it).m_iH)<=(*it).m_iH/8){   ////�����д�����8�ȽϺã�
					(*itv).second++;
					break;
				}
			}
			if(itv==clustering.end()){						
				(*newCluster).first=(*it).m_iH ;
				(*newCluster).second=1;
			    clustering.push_back(*newCluster);
			}
		}
	}
	delete newCluster;
	int i=0,j=0;
	for(vector <cluster> ::iterator ite=clustering.begin();ite!=clustering.end();++ite){
	    if((*ite).second>i){
			i=(*ite).second;
			j=(*ite).first;//�����ظ�������и�
		}
	}
	return j;
}

charsRecognition::MergeProjX(int lWm)
{
	list <h>::iterator itx1=m_ProjX.begin();
	for(list <h>::iterator itx=m_ProjX.begin();itx!=m_ProjX.end();++itx){
		if(itx1==itx){
			itx->m_ias=0;
			continue;
		}
		itx->m_ias=itx->m_iX1-itx1->m_iX2 ;
		itx1->m_ibs=itx->m_ias;
	    itx1=itx;
	}
	itx1->m_ibs=0;
	///////////////////���еĺϲ�///////////////////
	list<h>::iterator it2=m_ProjX.begin();
	h *newX=new h;
	itx=m_ProjX.begin();
    for(;itx!=m_ProjX.end();++itx){    
	    if((double)itx->m_ias <(double)lWm/3.1){
			newX->m_ias=it2->m_ias;
			newX->m_ibs=itx->m_ibs;
			newX->m_iH=itx->m_iX2-it2->m_iX1+1;
			newX->m_iX1=it2->m_iX1;
			newX->m_iX2=itx->m_iX2;
			++itx;
			m_ProjX.erase(it2,itx);
			m_ProjX.insert(itx,*newX);
			--itx;
			it2=itx;
		}
		it2=itx;
	}
	delete newX;
}

charsRecognition::CutImage(int lWm)
{
	
	unsigned char*	lpSrc;				// ָ��Դͼ���ָ��	
	LONG	i;							// ѭ������
	LONG	j;	
	//����ͼ��ÿ�����ֽ���,�Ҷ�ͼ��Ϊ1�ֽ�/����
	int pixelByteIn=1;
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;
	Position pImagePos;
	pImagePos.m_bottom =(m_ProjX.back()).m_iX2;
	pImagePos.m_top=(m_ProjX.front()).m_iX1;
    ///////////////////////////��ͼ�����Ե
    i=0,j=0;
	do{
		if(i>m_imgHeight-1){
			j++;
			i=0;
		}
		if(j>m_imgWidth-1)	break;
		lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+j;	
		i++;
	}while(*lpSrc==(BYTE)255);
	pImagePos.m_left=j;
	///////////////////////////��ͼ���ұ�Ե
    i=0,j=m_imgWidth-1;
	do{
		if(i>m_imgHeight-1){
			j--;
			i=0;
		}
		if(j<0)	break;
		lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+j;	
		i++;
	}while(*lpSrc==(BYTE)255);
	pImagePos.m_right=j;
    LONG lProjY=0;
	LONG lCountL=0;   //��¼�б�
	LONG lCountS=0;   //��¼ÿ�е��ַ���
	LONG lSum=0;      //��¼ÿ���ַ����ܸ߶�
	///�п�������������������ʽ��ź͹�ʽ�ľ��롢���к����ص���Ŀ
    double dLWidth=0,dLI=0,dRI=0,dld=0,NBP=0;
	LONG m,n,k;
	CFtChinese *newfChinese=new CFtChinese;
	int *ProjY=new int[pImagePos.m_right-pImagePos.m_left+1];
	Position pos;  //��¼�ֶε���С����
    for(list<h>::iterator itx=m_ProjX.begin();itx!=m_ProjX.end();++itx){
		NBP=0;
		lCountL++;
		for(k=0;k<pImagePos.m_right-pImagePos.m_left+1;k++)	ProjY[k]=0;
		for(j=pImagePos.m_left;j<=pImagePos.m_right;j++){		
		    for(i=itx->m_iX1;i<=itx->m_iX2;i++){
				// ָ��DIB��i�У���j�����ص�ָ��
				lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+j;	
				if((*lpSrc)==(BYTE)0){
					//////////////////////////�����зֺ�������
					lProjY=RoundCut(j,*itx,lWm);//lWm(��ֱ������)
					/////////////////����С����
					pos.m_bottom=itx->m_iX2 ;
					pos.m_left=j;
					pos.m_right=lProjY;
					pos.m_top=itx->m_iX1;
			        ///////////////////////////��������С���κ���
			        GetMinRect(pos);
					newfChinese->i_row =lCountL;
					newfChinese->m_type=Chinese;
					newfChinese->m_pos=pos;
					m_fChinese.push_back(*newfChinese);
					lCountS++;    ///��¼ÿ�е��ַ���
					lSum+=(newfChinese->m_pos.m_bottom-newfChinese->m_pos.m_top);
					j=lProjY;
					break;
				}
			}
		}
    }
    delete newfChinese;
}

LONG charsRecognition::RoundCut(LONG iy,h ix,int iW)
{
	unsigned char*	lpSrc;				// ָ��Դͼ���ָ��	
	LONG	i;							// ѭ������
	LONG	j;	
	//����ͼ��ÿ�����ֽ���,�Ҷ�ͼ��Ϊ1�ֽ�/����
	int pixelByteIn=1;
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;
	int *iProjY=new int[iW+1];
	for(i=0;i<iW+1;i++)	iProjY[i]=0;
	for(i=ix.m_iX1;i<=ix.m_iX2;i++){
		lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+iy+iW;	
		if((*lpSrc)==(BYTE)0)	iProjY[iW]++;	    
	}
	if(iProjY[iW]!=0){
		j=iW;
		while(iProjY[j]!=0&&j>0){
			j--;
			for(i=ix.m_iX1;i<=ix.m_iX2;i++){
				lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+j+iy;	
				if((*lpSrc)==(BYTE)0)	iProjY[j]++;	 
			}
		}
		//////// j is the result of the cutting
		if(j!=0){
			delete iProjY;
			return j+iy;   
		}
	}
	else{
		j=iW;
		while(iProjY[j]==0&&j>0){
			j--;
			for(i=ix.m_iX1;i<=ix.m_iX2;i++){
				lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+j+iy;
				if((*lpSrc)==(BYTE)0)	iProjY[j]++;	 
			}
		}
		delete iProjY;
		return iy+j;		
	}
}

charsRecognition::GetMinRect(Position &pos)
{
	unsigned char*	lpSrc;				// ָ��Դͼ���ָ��	
	LONG	i;							// ѭ������
	LONG	j;	
	//����ͼ��ÿ�����ֽ���,�Ҷ�ͼ��Ϊ1�ֽ�/����
	int pixelByteIn=1;
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;
	i=pos.m_top ;
	j=pos.m_left-1 ;
	do{
		j++;
		if(j>pos.m_right){
		    j=pos.m_left;
			i++;
		}
		lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+j;
	}while((*lpSrc)==(BYTE)255&&i<=pos.m_bottom );
	pos.m_top =i;
	i=pos.m_bottom;
	j=pos.m_left -1;
	do{
		j++;
		if(j>pos.m_right){
		    j=pos.m_left;
			--i;
		}
		lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-i)+j;
	}while((*lpSrc)==(BYTE)255&&i>=pos.m_top);
	pos.m_bottom=i;
}

charsRecognition::BlockNormalization()
{
	int i=0,j=0;
	for(list<CFtChinese>::iterator it=m_fChinese.begin();
	    it!=m_fChinese.end();++it){
		Norm(*it);
		for(i=0,j=0;j<48;++j)	it->m_iImage[i][j]=0;
		for(i=47,j=0;j<48;++j)	it->m_iImage[i][j]=0;
		for(i=0,j=0;i<48;++i)	it->m_iImage[i][j]=0;
		for(i=0,j=47;i<48;++i)	it->m_iImage[i][j]=0;
		Thinning(48,*it);
	}
}

//���ֹ�һ�� ��С48
charsRecognition::Norm(CFtChinese &itx)
{
	unsigned char*	lpSrc;				// ָ��Դͼ���ָ��	
	LONG	i;							// ѭ������
	LONG	j;	
	//����ͼ��ÿ�����ֽ���,�Ҷ�ͼ��Ϊ1�ֽ�/����
	int pixelByteIn=1;
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;
	Position pos;
	pos.m_bottom=itx.m_pos.m_bottom;
	pos.m_left=itx.m_pos.m_left;
	pos.m_right=itx.m_pos.m_right;
	pos.m_top=itx.m_pos.m_top;
	int iImage[48*48];
	for(i=0;i!=48*48;i++)	iImage[i]=0;
	Normalization(pos,48,iImage);
	for(i=0;i<48;i++){
	    for(j=0;j<48;j++){
		    itx.m_iImage[i][j]=iImage[48*i+j];//д��һ������
		}
	}
}

///////////////////////////////////////////////////////////////////////////
////////////////     ��һ�����ź���   SWHΪ��һ��ÿ�е�������Ŀ
///////////////////////////////////////////////////////////////////////////
charsRecognition::Normalization(Position &pos,int SWH,int *iImage)
{

	unsigned char*	lpSrc;				// ָ��Դͼ���ָ��	
	LONG	i;							// ѭ������
	LONG	j;	
	//����ͼ��ÿ�����ֽ���,�Ҷ�ͼ��Ϊ1�ֽ�/����
	int pixelByteIn=1;
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;
    float fPercent;
	int iWr=pos.m_right-pos.m_left +1,iHr=pos.m_bottom-pos.m_top+1;
	int iXf=0,iYf=0,iX=0,iY=0;//iXfΪԭͼ������iXΪ��һ������
	if(iWr>iHr)	fPercent=(float)iWr/(float)SWH;
	else	fPercent=(float)iHr/(float)SWH;
	if(fPercent>1){
		for(iXf=pos.m_top;iXf<=pos.m_bottom ;iXf++)
			for(iYf=pos.m_left ;iYf<=pos.m_right ;iYf++){
				lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-iXf)+iYf;
			    if(*lpSrc==(BYTE)0){
					iX=MyRound((iXf-pos.m_top)/fPercent);
					iY=MyRound((iYf-pos.m_left)/fPercent);
					iImage[iX*SWH+iY]=1;             //����ǰ��ɫ
				}
			}
	}
	else{
		for(iX=0;iX<SWH;iX++)
			for(iY=0;iY<SWH;iY++){
				iXf=MyRound(iX*fPercent+pos.m_top) ;
				iYf=MyRound(iY*fPercent+pos.m_left);
				lpSrc = m_pImgData+lineByteIn*(m_imgHeight-1-iXf)+iYf;
			    if(iXf>pos.m_bottom ||iXf<pos.m_top ||iYf>pos.m_right ||iYf<pos.m_left )
					continue;
				if(*lpSrc==(BYTE)0){
				    iImage[iX*SWH+iY]=1;             //����ǰ��ɫ
				}
			}
	}
}


//////////////////////////////////////////////////////////////////////////
////////////////////       GAϸ���㷨          ����
////////////////////////////////////////////////////////////////////////
///*//һ�����ؿ�
charsRecognition::Thinning(int SWH,CFtChinese &it)
{
    int i=0,j=0;
    bool flag=true;
	bool a1=false,b1=false,c1=false,d1=false;
	bool a2=false,b2=false,c2=false,d2=false;
	int NP=0,TP=0;
//	goto thinning;
	while(flag){
		flag=false;
		//���
		for(i=1;i<SWH-1;++i){
			for(j=1;j<SWH-1;++j){
				if(it.m_iImage[i][j]!=1)	continue;
				if(it.m_iImage[i-1][j-1]==1||it.m_iImage[i-1][j-1]==11)	NP++;
				if(it.m_iImage[i-1][j]==1||it.m_iImage[i-1][j]==11)	NP++;
				if(it.m_iImage[i-1][j+1]==1||it.m_iImage[i-1][j+1]==11)	NP++;
				if(it.m_iImage[i][j-1]==1||it.m_iImage[i][j-1]==11)	NP++;
				if(it.m_iImage[i][j+1]==1||it.m_iImage[i][j+1]==11)	NP++;
				if(it.m_iImage[i+1][j-1]==1||it.m_iImage[i+1][j-1]==11)	NP++;
				if(it.m_iImage[i+1][j]==1||it.m_iImage[i+1][j]==11)	NP++;
				if(it.m_iImage[i+1][j+1]==1||it.m_iImage[i+1][j+1]==11)	NP++;
				if(NP>=2 && NP<=6)	a1=true;
				else	a1=false;
				if(it.m_iImage[i-1][j]==0&&(it.m_iImage[i-1][j+1]==1||it.m_iImage[i-1][j+1]==11))	TP++;
				if(it.m_iImage[i-1][j+1]==0&&(it.m_iImage[i][j+1]==1||it.m_iImage[i][j+1]==11))	TP++;
				if(it.m_iImage[i][j+1]==0&&(it.m_iImage[i+1][j+1]==1||it.m_iImage[i+1][j+1]==11))	TP++;
				if(it.m_iImage[i+1][j+1]==0&&(it.m_iImage[i+1][j]==1||it.m_iImage[i+1][j]==11))	TP++;
				if(it.m_iImage[i+1][j]==0&&(it.m_iImage[i+1][j-1]==1||it.m_iImage[i+1][j-1]==11))	TP++;
				if(it.m_iImage[i+1][j-1]==0&&(it.m_iImage[i][j-1]==1||it.m_iImage[i][j-1]==11))	TP++;
				if(it.m_iImage[i][j-1]==0&&(it.m_iImage[i-1][j-1]==1||it.m_iImage[i-1][j-1]==11))	TP++;
				if(it.m_iImage[i-1][j-1]==0&&(it.m_iImage[i-1][j]==1||it.m_iImage[i-1][j]==11))	TP++;
				if(TP==1)	b1=true;
				else	b1=false;
				if(it.m_iImage[i-1][j]==0||it.m_iImage[i-1][j]==2||
					it.m_iImage[i][j+1]==0||it.m_iImage[i][j+1]==2||
					it.m_iImage[i+1][j]==0||it.m_iImage[i+1][j]==2)
					c1=true;                  //����2��Ϊ���ڿ׶�����ʹ��ϸ���㷨
				else
					c1=false;
				if(it.m_iImage[i][j-1]==0||it.m_iImage[i][j-1]==2||
					it.m_iImage[i][j+1]==0||it.m_iImage[i][j+1]==2||
					it.m_iImage[i+1][j]==0||it.m_iImage[i+1][j]==2)
					d1=true;
				else
					d1=false;
				if(a1 && b1 && c1 && d1){
					it.m_iImage[i][j]=11;
					flag=true;
				}
	        	NP=0,TP=0;
			}
		}
        //ɾ�����
		for(i=1;i<SWH-1;++i){
			for(j=1;j<SWH-1;++j){
				if(it.m_iImage[i][j]==11)
					it.m_iImage[i][j]=0;
			}
		}
        //���
		for(i=1;i<SWH-1;++i){
		    for(j=1;j<SWH-1;++j){
				if(it.m_iImage[i][j]!=1)	continue;
				if(it.m_iImage[i-1][j-1]==1||it.m_iImage[i-1][j-1]==11)	NP++;
				if(it.m_iImage[i-1][j]==1||it.m_iImage[i-1][j]==11)	NP++;
				if(it.m_iImage[i-1][j+1]==1||it.m_iImage[i-1][j+1]==11)	NP++;
				if(it.m_iImage[i][j-1]==1||it.m_iImage[i][j-1]==11)	NP++;
				if(it.m_iImage[i][j+1]==1||it.m_iImage[i][j+1]==11)	NP++;
				if(it.m_iImage[i+1][j-1]==1||it.m_iImage[i+1][j-1]==11)	NP++;
				if(it.m_iImage[i+1][j]==1||it.m_iImage[i+1][j]==11)	NP++;
				if(it.m_iImage[i+1][j+1]==1||it.m_iImage[i+1][j+1]==11)	NP++;
				if(NP>=2 && NP<=6)	a2=true;
				else	a2=false;
				if(it.m_iImage[i-1][j]==0&&(it.m_iImage[i-1][j+1]==1||it.m_iImage[i-1][j+1]==11))	TP++;
				if(it.m_iImage[i-1][j+1]==0&&(it.m_iImage[i][j+1]==1||it.m_iImage[i][j+1]==11))	TP++;
				if(it.m_iImage[i][j+1]==0&&(it.m_iImage[i+1][j+1]==1||it.m_iImage[i+1][j+1]==11))	TP++;
				if(it.m_iImage[i+1][j+1]==0&&(it.m_iImage[i+1][j]==1||it.m_iImage[i+1][j]==11))	TP++;
				if(it.m_iImage[i+1][j]==0&&(it.m_iImage[i+1][j-1]==1||it.m_iImage[i+1][j-1]==11))	TP++;
				if(it.m_iImage[i+1][j-1]==0&&(it.m_iImage[i][j-1]==1||it.m_iImage[i][j-1]==11))	TP++;
				if(it.m_iImage[i][j-1]==0&&(it.m_iImage[i-1][j-1]==1||it.m_iImage[i-1][j-1]==11))	TP++;
				if(it.m_iImage[i-1][j-1]==0&&(it.m_iImage[i-1][j]==1||it.m_iImage[i-1][j]==11))	TP++;
				if(TP==1)	b2=true;
				else 	b2=false;
				if(it.m_iImage[i-1][j]==0||it.m_iImage[i-1][j]==2||
					it.m_iImage[i][j+1]==0||it.m_iImage[i][j+1]==2||
					it.m_iImage[i][j-1]==0||it.m_iImage[i][j-1]==2)
					c2=true;
				else
					c2=false;

				if(it.m_iImage[i-1][j]==0||it.m_iImage[i-1][j]==2||
					it.m_iImage[i][j-1]==0||it.m_iImage[i][j-1]==2||
					it.m_iImage[i+1][j]==0||it.m_iImage[i+1][j]==2)
					d2=true;
				else
					d2=false;
				if(a2 && b2 && c2&& d2){
					it.m_iImage[i][j]=11;
					flag=true;
				}
		        NP=0,TP=0;
			}
		}
		//ɾ�����
		for(i=1;i<SWH-1;++i){
			for(j=1;j<SWH-1;++j){
				if(it.m_iImage[i][j]==11)
					it.m_iImage[i][j]=0;
			}
		}
	}
}

charsRecognition::GetCrudeFeature()
{
	//Position pos;
	int i,j;
	double p1=0,p2=0;
	for(list<CFtChinese>::iterator it=m_fChinese.begin();it!=m_fChinese.end();++it){
        for(i=0;i<48;i++){
		    for(j=0;j<48;j++){
			    if(it->m_iImage[i][j]==1)
					it->m_iSumBlack++;
			}
		}
		Density();
        CrossMesh(*it);
		CrossPeriphery(*it);
	}
}

charsRecognition::Density()
{
	for (list<CFtChinese>::iterator itt=m_fChinese.begin();itt!=m_fChinese.end();++itt){
  		//������һ����Χ(ֻ�̶ܹ���ʽ��һ���ֺ�)_��������Ҫ�޸�
		//�����ظ����ֺŲ�ͬ��С����
 		itt->m_iDensity=(double)itt->m_iSumBlack/(double)2304;
	}
}

//���δ���Χ
//ϸ������
//������
charsRecognition::CrossMesh(CFtChinese &it)
{
    LONG i,j,m,n;
	double sum=0;
	int count=0;
	it.m_iFtCrude[count]=0;
	for(i=0;i<8;i++){
	    for(j=0;j<8;j++){
			count++;
			sum=0;
		    for(m=i*6;m<(i+1)*6;m++){				
			    for(n=j*6;n<(j+1)*6;n++){
				    if(it.m_iImage[m][n]==1)
						sum++;
				}
			}
			it.m_iFtCrude[count]=sum/(double)(it.m_iSumBlack);
		}
	}
}

//����Χ
charsRecognition::CrossPeriphery(CFtChinese &it)
{
	double sum1[6],sum2[6];
	double p1,p2;
    int k, i,j,m,n;
	int count=65;
    //ˮƽ������
	for(k=0;k<8;k++){
		for(i=0;i<6;i++)	sum1[i]=0;
		for(i=0;i<6;i++)	sum2[i]=0;
		p1=0;
		p2=0;
	    for(i=6*k;i<6*(k+1);i++){
		    for(j=0;j<=47;j++){
			    if(it.m_iImage[i][j]==0){
				    sum1[i-6*k]++;
				}
				else{
				    while(j<=47&&it.m_iImage[i][j]==1){
					    j++;
					}
					while(j<=47&&it.m_iImage[i][j]==0){
					    j++;
						sum2[i-6*k]++;
					}
					if(j>=47)	sum2[i-6*k]=0;
					break;
				}
			}
		}
		for(m=0;m<6;m++){
		    p1+=sum1[m];
		}
		for(n=0;n<6;n++){
		    p2+=sum2[n];
		}
		it.m_iFtCrude[count]=p1/(double)(48*48);
		count++;
		it.m_iFtCrude[count]=p2/(double)(48*48);
		count++;
	}
	//��ֱ�����ϵ���
	for(k=0;k<8;k++){
		for(i=0;i<6;i++)	sum1[i]=0;
		for(i=0;i<6;i++)	sum2[i]=0;
		p1=0;
		p2=0;
		for(j=k*6;j<6*(k+1);j++){
		    for(i=0;i<48;i++){
			    if(it.m_iImage[i][j]==0){
				    sum1[j-k*6]++;
				}
				else{
				    while(i<48&&it.m_iImage[i][j]==1){
						i++;
					}
					while(i<48&&it.m_iImage[i][j]==0){
					    i++;
						sum2[j-k*6]++;
					}
					if(i>=47)	sum2[j-k*6]=0;
					break;
				}
			}
		}
		for(m=0;m<6;m++){
		    p1+=sum1[m];
		}
		for(n=0;n<6;n++){
		    p2+=sum2[n];
		}
		it.m_iFtCrude[count]=p1/(double)(48*48);
		count++;
		it.m_iFtCrude[count]=p2/(double)(48*48);
		count++;
	}
	//ˮƽ����������
	for(k=0;k<8;k++){
		for(i=0;i<6;i++)	sum1[i]=0;
		for(i=0;i<6;i++)	sum2[i]=0;
		p1=0;
		p2=0;
		for(i=6*k;i<6*(k+1);i++){
		    for(j=47;j>=0;--j){
			    if(it.m_iImage[i][j]==0){
				    sum1[i-6*k]++;
				}
				else{
				    while(j>=0&&it.m_iImage[i][j]==1){
					    --j;
					}
					while(j>=0&&it.m_iImage[i][j]==0){
					    --j;
						sum2[i-6*k]++;
					}
					if(j<=0)	sum2[i-6*k]=0;
					break;
				}
			}
		}
		for(m=0;m<6;m++){
		    p1+=sum1[m];
		}
		for(n=0;n<6;n++){
		    p2+=sum2[n];
		}
		it.m_iFtCrude[count]=p1/(double)(48*48);
		count++;
		it.m_iFtCrude[count]=p2/(double)(48*48);
		count++;
	}
	///////��ֱ�����µ���
	for(k=0;k<8;k++){
		for(i=0;i<6;i++)
			sum1[i]=0;
		for(i=0;i<6;i++)
			sum2[i]=0;
		p1=0;
		p2=0;
		for(j=k*6;j<6*(k+1);++j){
		    for(i=47;i>=0;--i){
			    if(it.m_iImage[i][j]==0){
				    sum1[j-k*6]++;
				}
				else{
				    while(i>=0&&it.m_iImage[i][j]==1){
						--i;
					}
					while(i>=0&&it.m_iImage[i][j]==0){
					    --i;
						sum2[j-k*6]++;
					}
					if(i<=0)
						sum2[j-k*6]=0;
					break;

				}
			}
		}
		for(m=0;m<6;m++){
		    p1+=sum1[m];
		}
		for(n=0;n<6;n++){
		    p2+=sum2[n];
		}
		it.m_iFtCrude[count]=p1/(double)(48*48);
		count++;
		it.m_iFtCrude[count]=p2/(double)(48*48);
		count++;
	}
}

charsRecognition::CrudeMatchChinese()
{
    double c0=0.071257,c1=0.08439,c2=0.101897,c3=0.114387,c4=0.131032;
	for (list<CFtChinese>::iterator itc=m_fChinese.begin();itc!=m_fChinese.end();++itc){	
		CrudeMatch(*itc);		
	}
}


extern double InitChineseCrude[870][129];

BOOL charsRecognition::CrudeMatch(CFtChinese &it)
{
	int i,j,m,n,k;
    int count;
	double tempIndex,tempE;
	match eLm0[552+1],eLp0[552+1];
	for(m=0;m<10;++m){
		Lp[m].index=0;
		Lp[m].e=1;
		Lm[m].e=1;
		Lm[m].index=0;
	}
	for(m=0;m<20;++m){
		L[m].index=0;
		L[m].e=1;
	}
	for(m=0;m<=552;++m){
		eLm0[m].e=0;
		eLp0[m].e=0;
	}
	for(i=0;i<552;++i){
		for(j=0;j<=64;j++){//����
			eLm0[i].e+=(it.m_iFtCrude[j]-InitChineseCrude[i][j])*(it.m_iFtCrude[j]-InitChineseCrude[i][j]);
			eLm0[i].index=i;
		}
		while(j<129){//��Χ
			eLp0[i].e +=(it.m_iFtCrude[j]-InitChineseCrude[i][j])*(it.m_iFtCrude[j]-InitChineseCrude[i][j]);
			eLp0[i].index=i;
			++j;
		}
	}
	////ѡ��С��10��
	for(m=0;m<10;++m){
		for(n=0;n<552;++n){					
			for(k=0;k<=m;++k){
				if(eLp0[n].index==Lp[k].index){
					++n;
					k=-1;
				}
			}
			if(eLp0[n].index !=Lp[m].index && eLp0[n].e <=Lp[m].e){
				Lp[m].e=eLp0[n].e;
				Lp[m].index=eLp0[n].index;
			}
		}
	}
	//eLm
	for(m=0;m<10;++m){
		for(n=0;n<552;++n){
			for(k=0;k<=m;++k){
				if(eLm0[n].index==Lm[k].index){
					++n;
					k=-1;
				}
			}
			if(eLm0[n].index!=Lm[m].index && eLm0[n].e<=Lm[m].e){
				Lm[m].e=eLm0[n].e;
				Lm[m].index=eLm0[n].index;
			}
		}
	}
    /////�ϲ������
	int flag;
	count=0;
	for(m=0;m<10;++m){
		flag=0;
		for(n=0;n<10;++n){
			if(Lm[m].index==Lp[n].index){
				L[count].e=Lm[m].e+0.4*Lp[n].e;   ////�����ɱ�
				Lp[n].index=0;
				L[count].index=Lm[m].index;
				flag=1;
				break;
			}
		}
		if(flag==0){
			L[count].e=Lm[m].e+0.4*Lp[4].e;
			L[count].index=Lm[m].index;
		}
		count++;
	}
	for(m=0;m<10;++m){
		if(Lp[m].index==0){
			continue;
		}
		else{
			L[count].e=0.4*Lp[m].e+Lm[4].e;     ////�����ɱ�
			L[count].index=Lp[m].index;
			count++;
		}					
	}
	for(m=0;m<count;++m){
		for(n=m;n<count-1;++n){
			if(L[n].e>L[n+1].e){
				tempE=L[n].e;
				tempIndex=L[n].index;
				L[n].e=L[n+1].e;
				L[n].index=L[n+1].index;
				L[n+1].index=tempIndex;
				L[n+1].e=tempE;
			}
		}
	}
	it.m_dIndex=L[0].index;    
	it.e=L[0].e;			
	it.m_type=Chinese;
	return TRUE;
}

charsRecognition::DrawRect()
{
	unsigned char*	lpSrc;				// ָ��Դͼ���ָ��	
	LONG	i;							// ѭ������
	LONG	j;	
	//����ͼ��ÿ�����ֽ���,�Ҷ�ͼ��Ϊ1�ֽ�/����
	int pixelByteIn=1;
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;
	//��ֵ����,ÿ����λ��Ϊ8����
	m_nBitCountOut=8;
	//��ɫ����
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	//������ɫ������,���ɻҶ�ͼ�����ɫ��
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}
	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	//���ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;
	//�������ͼ��λͼ���ݻ�����
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];
	memcpy(m_pImgDataOut,m_pImgData,lineByteOut*m_imgHeight);
	for(list<CFtChinese>::iterator it=m_fChinese.begin();it!=m_fChinese.end();++it){ 
		if (it->m_type==Chinese){
			i=it->m_pos.m_top -1;
	        for(j=it->m_pos.m_left ;j<=it->m_pos.m_right ;++j){
				lpSrc = m_pImgDataOut+lineByteOut*(m_imgHeight-1-i)+j;
	    		*lpSrc=(BYTE)0;
		   	}
	    	i=it->m_pos.m_bottom+1;
	    	for(j=it->m_pos.m_left ;j<=it->m_pos.m_right ;++j){
	    		lpSrc = m_pImgDataOut+lineByteOut*(m_imgHeight-1-i)+j;
	    		*lpSrc=(BYTE)0;
			}
		    j=it->m_pos.m_left-1 ;
	    	for(i=it->m_pos.m_top;i<=it->m_pos.m_bottom ;++i){
		    	lpSrc = m_pImgDataOut+lineByteOut*(m_imgHeight-1-i)+j;
		    	*lpSrc=(BYTE)0;
			}
	    	j=it->m_pos.m_right+1;
    		for(i=it->m_pos.m_top ;i<=it->m_pos.m_bottom ;++i){
		    	lpSrc = m_pImgDataOut+lineByteOut*(m_imgHeight-1-i)+j;
		    	*lpSrc=(BYTE)0;
		    }
		}
	}
}
