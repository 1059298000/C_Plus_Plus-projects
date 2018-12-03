//������BP�㷨
CString m_result,m_result1;
int  decimal, sign;
char  buffer[200];
double x_out[InputN];				//���������ֵ
double hn_out[HN];               	//����������ֵ
double y_out[OutN];              	//���������ֵ
double y[OutN];                  	//�������������ֵ
double w[InputN][HN];            	//����㵽�������Ȩֵ
double v[HN][OutN];              	//�����㵽������Ȩֵ
double deltaw[InputN][HN];
double deltav[HN][OutN];
double hn_delta[HN];             	//�������delta
double y_delta[OutN];            	//������delta
double error;                    	//ȫ�����
double errlimit=0.001;            	//Ԥ���ȫ������
double alpha=0.1, beta=0.1;        	//Ԥ���ѧϰ����
int loop=0;                      	//ѵ������
int times=50000;                 	//Ԥ���ѵ����������
int i, j, m;
double max, min;
double sumtemp;
double errtemp;

struct{                      		//ѵ��������.
	double input[InputN];
	double teach[OutN];
}data[datanum];

//��ʼ��. ������Ȩֵ��ƫ��ϵ����Ϊ(-1,1)֮��������
for(i=0; i<InputN; i++)        		//w���������
	for(j=0; j<HN; j++){
		w[i][j] = ((double)rand()/32767.0)*2-1;
		deltaw[i][j] = 0;
	}

for(i=0; i<HN; i++)   			//v���������
	for(j=0;j<OutN;j++){		
		v[i][j] = ((double)rand()/32767.0)*2-1;
		deltav[i][j] = 0;
	}
//ѵ��.
while(loop < times){
	loop++;
	error = 0.0;
	
	for(m=0; m<datanum; m++){  	//��datanum��������������ѵ��,mΪ��������
		//�������򴫲�
		max=0.0;
		min=0.0;
		for(i=0; i<InputN; i++){ 	//�������������
			x_out[i] = data[m].input[i];
			if (max < x_out[i]) 	//�Ƚϵó�����������Сֵ
		    	max = x_out[i];
	
		if (min > x_out[i]) 
				min = x_out[i];
		}

		for(i=0; i<InputN; i++){ 	//��һ���������ֵ
			x_out[i] = (x_out[i] - min) / (max-min);
		}

		for(i=0; i<OutN; i++){  	//�������������
			y[i] = data[m].teach[i];
		}			
	
		for(i=0; i<HN; i++){    	//��������������
			sumtemp = 0.0;
			for(j=0; j<InputN; j++)
			sumtemp += w[j][i] * x_out[j];
			hn_out[i] = tanh(sumtemp);   	//���������ú���Ϊy=tanh(x)
		}
				
		for(i=0; i<OutN; i++){           	//�������������
			sumtemp = 0.0;
			for(j=0; j<HN; j++) sumtemp += v[j][i] * hn_out[j];
			y_out[i] = g(sumtemp);     	//��������ú���Ϊsigmod����
		}
	
//���򴫲�
		for(i=0; i<OutN; i++){
			errtemp = y[i] - y_out[i]; 
			y_delta[i] = errtemp * g(y_out[i]) * (1.0 - g(y_out[i]));
			error += (errtemp * errtemp);  	//����������ȫ�����
		}
		
		for(i=0; i<HN; i++){               	//�����������delta
			errtemp = 0.0;
			for(j=0; j<OutN; j++)	errtemp += y_delta[j] * v[i][j];
			hn_delta[i] = errtemp * (1.0 + hn_out[i]) * (1.0 - hn_out[i]);
		}
		
		for(i=0; i<OutN; i++){       		//����������Ȩֵ��ƫ��ϵ��
			for(j=0; j<HN; j++){
				deltav[j][i] = alpha * deltav[j][i] + beta * y_delta[i] * hn_out[j];
				v[j][i] += deltav[j][i];
			}
		}
		
		for(i=0; i<HN; i++){        	//�����������Ȩֵ��ƫ��ϵ��
			for(j=0; j<InputN; j++){
				deltaw[j][i] = alpha * deltaw[j][i] + beta * hn_delta[i] * x_out[j];
				w[j][i] += deltaw[j][i];
			}
		}
	}
		
//ȫ������ж�
	error = error/2;
	if(loop%1000==0){
	    m_result="ȫ�����Error=";
		sprintf( buffer, "%f", error);
		m_result+=buffer;
		m_result+="\r\n";
		m_result+=m_result1;
	}
	if(error < errlimit)	break;
}
