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
	int tem = len / 100;
	for(int i = 0 ; i < tem ; i++)
	{
		int p1 = rand() % len,p2 = rand() % len;
		if(p1 > p2)
		{
			int t = p1;
			p1 = p2;
			p2 = t;
		}
		for(int i = len - 1 ; i > p1 ; i--)
			expr[i] = expr[i - 1];
		expr[p1] = '(';
		len++;
		for(int i = len - 1 ; i > p2 ; i--)
			expr[i] = expr[i - 1];
		expr[p2] = ')';
		len++;
	 } 
	for(int i = 0 ; i < len ; i++)
	{
		fprintf(fp , "%c" , expr[i]);
	}
	fclose(fp);
	return 0;
 }
