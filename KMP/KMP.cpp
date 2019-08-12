#include<stdio.h>
#include<string.h>
#include<stdlib.h> 


void dealNext(char *p , int *next)
{
	int len = strlen(p);
	memset(next , 0 , sizeof(next));
	for (int i = 1 ; i < len ; i++)
	{
		if (p[i] == p[next[i - 1]])
			next[i] = next[i - 1] + 1;
		else
			next[i] = 0;
	}
	for (int i = 1 ; i < len ; i++)
		next[i] = next[i - 1];
	next[0] = -1;
}


int KMP(char *s , char *p)  //��ģʽ��pȥƥ��Ŀ�괮s���ɹ������±꣬ʧ�ܷ���-1 
{
	int i , j;  //iΪs���±�������jΪp���±����� 
	i = j = 0;
	int slen = strlen(s) , plen = strlen(p);
	int *next = (int*)malloc(sizeof(int) * plen);
	dealNext(p , next);
	
	while (i < slen && j < plen)
	{
		if (j == -1 || s[i] == p[j])  //�����ͷƥ��p�͵�ǰ�ַ�������ͬ������� 
		{
			i++; j++;
		}
		else
		{
			j = next[j];  //ʹ��ħ�� 
		}
	 } 
	
	if (j == plen)
		return i - j;
	else
		return -1; 
}


int main(void)
{
	char s[100] = "abceeabceg";
	char p[100] = "abceg";
	int flag = KMP(s , p);
	if (flag != -1)
		printf("Success��%d" , flag);
	else
		printf("Fail");
	
	return 0;
 } 
