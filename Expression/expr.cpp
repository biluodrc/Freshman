#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stack>
using namespace std; 

char s[100000];  
char back[100000];  

int pre(char sym)
{
	if(sym == '(')
		return 1;
	else if(sym == '+' || sym == '-')
		return 2;
	else if(sym == '*' || sym == '/')
		return 3;
	else
		return 4;
}

int main(void)
{
	stack<char> sym;
	FILE *fp = fopen("expr.in" , "r");
	int cnt = 0;  
	int p = 0;  
	while(!feof(fp))
		fscanf(fp , "%c" , &s[cnt++]);
	for(int i = 0 ; i < cnt ; i++)  
	{ 
		if(s[i] >= '0' && s[i] <= '9')
		{
//			while(s[i] <= '9' && s[i] >= '0')  //这个是处理多位数的四则运算，但转换出来的后缀表达式会有一些问题，
//				back[p++] = s[i++];  //故是个待优化的点：可以将后缀表达式的元素构成一个结构体，也可以用空格来间隔每一个元素 
			back[p++] = s[i];
		}
		else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')')  //防止输入的不合法 
		{
			if(sym.empty())
			{
				sym.push(s[i]);
			}
			else if(s[i] == ')')
			{
				while(1)
				{
					char tem = sym.top();
					sym.pop();
					if(tem == '(')
						break;
					back[p++] = tem;
				}
			}
			else if(s[i] == '(')
				sym.push(s[i]);
			else
			{
				while(1)
				{
					if(sym.empty())
					{
						sym.push(s[i]);
						break;
					}
					char top = sym.top();
					if(pre(top) >= pre(s[i]))
					{
						back[p++] = top;
						sym.pop();
					}
					else
					{
						sym.push(s[i]);
						break;
					}
				}
			}
		}
	}
	while(!sym.empty())
	{
		back[p++] = sym.top();
		sym.pop();
	}
//	for(int i = 0 ; i < p ; i++)  //测试后缀表达式是否完成 
//		printf("%c" , back[i]);
	stack<int> num; 
	//printf("ppp%d   " , p);
	for(int i = 0 ; i < p ; i++)
	{
//		printf("%d %c" , i , back[i]);
		if(back[i] >= '0' && back[i] <= '9')
			num.push(back[i] - '0');
		else
		{
			int b = num.top();  //注意这里用的是b a而不是 a b 
			num.pop();
			int a = num.top();
			num.pop();
			if(back[i] == '+')
				num.push(a + b);
			else if(back[i] == '-')
				num.push(a - b);
			else if(back[i] == '*')
				num.push(a * b);
			else if(back[i] == '/')  //非常关键：被除数不能是0，这个是我原先在自己写的随机测试数据中没有注意到的 
				num.push(a / b); 
		}
	}	
	printf("The answer is %d" , num.top());
}
