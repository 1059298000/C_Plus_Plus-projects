//ģ��ƥ���㷨
#define N  10;   //��Ʒ���
#define K  25;   //����ά��

double LeastDistance()
{
	double min=10000000000;
	number_no number_no;
	for(int n=0;n<N;n++)
	{
		for(int i=0;i<pattern[n].number;i++)
		{
			if(match(pattern[n].feature[i],testsample)<min)
			{
				//ƥ�����Сֵ
				min=match(pattern[n].feature[i],testsample);
				number_no.number=n;//ģ�����
				number_no.no=i;//ģ�����
			}
		}
	}
	return number_no;//�����������������
}

double match(double a[], double b[])
{
	double count=0.0;
	for(int i=0;i<K;i++)
	{
		count+=(a[i]-b[i])*(a[i]-b[i]);
	}
	return count;
}
