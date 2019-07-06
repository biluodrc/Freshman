#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const int max = 1000 + 200;  //���ʽ����󳤶ȣ����Լ��仯�� 

char expr[max - 200];  //�������200�����ţ���ֻ��max - 200�����������
char sample[4] = {'+' , '-' , '*' , '/'};  //�Ӽ��˳�

int main(void)
{
	FILE *fp = fopen("expr.in" , "w");

	srand(time(0));
	int len = rand() % (max - 200);  //���һ������ĳ��ȣ������ʽ�г�ȥ���ŵĳ���
	for(int i = 0 ; i < len - 1 ; i++)
	{
		int rd1 = rand() % 10;  //���ѡ������
		int rd2 = rand() % 4;  //���ѡ�����
		if(i % 2 == 0)  //������һ���ǳ��ؼ��ĵط���������������0
		{
			expr[i] = rd1 + '0';
			if(expr[i - 1] == '/')
				expr[i] = '1'; 
		} 
		else 
		{
			expr[i] = sample[rd2];
		}
	}
	expr[len - 1] = '0' + (rand() % 10 );
	for(int i = 0 ; i < len ; i++)
	{
		fprintf(fp , "%c" , expr[i]);
	}
	fclose(fp);
	return 0;
 }
