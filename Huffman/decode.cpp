#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{  //Huffman树中的节点
	int c;  //叶节点就保存字符的ASCII码，枝节点就为-1
	int frqt;  //节点的频率，在译码时这个就没有用了
	struct node *left , *right;
}; 

int config[100000];  //配置文件内容
int sum , code_sum;  //原文件字符数，出现字符种类数
char code[256][20];  //编码
struct node *root;  //Huffman树根
char compression[100000];  //压缩文件内容
char binary[100000];  //转化的二进制表示

void cvt2code(int num , int len , char *code)
{
	while(num)
	{
		len--;
		code[len] = '0' + num % 2;
		num /= 2;
	}
	while(len)
	{
		code[--len] = '0';
	}
}

void DFS(struct node *now , char *code , int code_char , int place)
{
	if(code[place] == '\0')
	{
		now->c = code_char;
		return;
	}
	else
	{
		if(code[place] == '0')
		{
			if(now->left == NULL)
			{
				now->left = (struct node*)malloc(sizeof(struct node));
				now->left->left = now->left->right = NULL;
			} 
			now->c = -1; 
			DFS(now->left , code , code_char , place + 1);
		}
		else
		{
			if(now->right == NULL)
			{
				now->right = (struct node*)malloc(sizeof(struct node));
				now->right->left = now->right->right = NULL;
			}
			now->c = -1;
			DFS(now->right , code , code_char , place + 1);
		}
	}
}

void cvt2Binary(int c , char *bin)
{
	c = c > 0 ? c : c + 256;
	for(int i = 7 ; i >= 0 ; i--)
	{
		bin[i] = c % 2 + '0';
		c /= 2;
	}
}

char cvt2char(int &p , struct node *now)
{
	if(now->c != -1)
	{
		return now->c;
	}
	else
	{
		if(binary[p++] == '0')
			return cvt2char(p , now->left);
		else
			return cvt2char(p , now->right);
	}
}

int main(void)
{ 
	//读入并处理配置文件
	FILE *fp_config = fopen("Huffman.config" , "rb"); 
	fread(config , sizeof(int) , 100000 , fp_config);
	sum = config[0];
	code_sum = config[1];
	for(int i = 1 ; i <= code_sum ; i++)
	{
		int code_char = config[3 * i - 1] , code_len = config[3 * i] , code_num = config[3 * i + 1];
		cvt2code(code_num , code_len , code[code_char]);
	}
	
	//生成Huffman树
	root = (struct node*)malloc(sizeof(struct node));
	root->left = root->right = NULL;
	for(int i = 0 ; i < 256 ; i++)
		if(strcmp(code[i] , "") != 0)
		{
			DFS(root , code[i] , i , 0);
		}	
	
	//读入并处理压缩文件
	FILE *fp_compression = fopen("Huffman.compressed" , "rb");
	fread(compression , sizeof(char) , 100000 , fp_compression);
	for(int i = 0 ; i < strlen(compression) ; i++)
	{
		cvt2Binary(compression[i] , &binary[8 * i]);
	}

	//得出原文件
	int p = 0;
	for(int i = 0 ; i < sum -  1 ; i++)
	{
		char c = cvt2char(p , root);
		printf("%c" , c);
	}

	return 0;
}
