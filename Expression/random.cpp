#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const int max = 1000 + 200;  //表达式的最大长度（可自己变化） 

char expr[max - 200];  //最后生成200个括号，故只有max - 200个数字与符号
char sample[4] = {'+' , '-' , '*' , '/'};  //加减乘除

int main(void)
{
	FILE *fp = fopen("expr.in" , "w");

	srand(time(0));
	int len = rand() % (max - 200);  //获得一个随机的长度，即表达式中除去括号的长度
	for(int i = 0 ; i < len - 1 ; i++)
	{
		int rd1 = rand() % 10;  //随机选择数字
		int rd2 = rand() % 4;  //随机选择符号
		if(i % 2 == 0)  //这里有一个非常关键的地方：被除数不能是0
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
