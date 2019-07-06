#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stack>
using namespace std; 

char s[100000];  
char back[100000];  

int pre(char sam)
{
	if(sam == '(')
		return 1;
	else if(sam == '+' || sam == '-')
		return 2;
	else if(sam == '*' || sam == '/')
		return 3;
	else
		return 4;
}

int main(void)
{
	stack<char> sam;
	FILE *fp = fopen("expr.in" , "r");
	int cnt = 0;  
	int p = 0;  
	while(!feof(fp))
		fscanf(fp , "%c" , &s[cnt++]);
	for(int i = 0 ; i < cnt ; i++)  
	{ 
		if(s[i] >= '0' && s[i] <= '9')
		{
//			while(s[i] <= '9' && s[i] >= '0')  //����Ǵ�����λ�����������㣬��ת�������ĺ�׺����ʽ����һЩ���⣬
//				back[p++] = s[i++];  //���Ǹ����Ż��ĵ㣺���Խ���׺����ʽ��Ԫ�ع���һ���ṹ�壬Ҳ�����ÿո������ÿһ��Ԫ�� 
			back[p++] = s[i];
		}
		else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')')  //��ֹ����Ĳ��Ϸ� 
		{
			if(sam.empty())
			{
				sam.push(s[i]);
			}
			else if(s[i] == ')')
			{
				while(1)
				{
					char tem = sam.top();
					sam.pop();
					if(tem == '(')
						break;
					back[p++] = tem;
				}
			}
			else if(s[i] == '(')
				sam.push(s[i]);
			else
			{
				while(1)
				{
					if(sam.empty())
					{
						sam.push(s[i]);
						break;
					}
					char top = sam.top();
					if(pre(top) >= pre(s[i]))
					{
						back[p++] = top;
						sam.pop();
					}
					else
					{
						sam.push(s[i]);
						break;
					}
				}
			}
		}
	}
	while(!sam.empty())
	{
		back[p++] = sam.top();
		sam.pop();
	}
//	for(int i = 0 ; i < p ; i++)  //���Ժ�׺����ʽ�Ƿ���� 
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
			int b = num.top();  //ע�������õ��� b a������ a b 
			num.pop();
			int a = num.top();
			num.pop();
			if(back[i] == '+')
				num.push(a + b);
			else if(back[i] == '-')
				num.push(a - b);
			else if(back[i] == '*')
				num.push(a * b);
			else if(back[i] == '/')  //�ǳ��ؼ���������������0���������ԭ�����Լ�д���������������û��ע�⵽�� 
				num.push(a / b); 
		}
	}	
	printf("The answer is %d" , num.top());
}