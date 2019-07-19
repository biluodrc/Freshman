#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{  //Huffman树的节点
	int c;  //c == -1时表示是树的枝节点，c ！= -1表示叶节点
	int frqt;  //当前节点的频率
	struct node *left , *right;
}; 

struct node* (ch[256]); //每种字符的频率，用于之后生成Huffman树
char code[256][100];  //每种字符的频率
int config[100000];  //写入配置文件中的内容
char bsource[100000];  //转换的二进制编码
char compression[100000];  //写入压缩文件中的内容

int cmp(const void* x , const void* y)
{
	return (*(struct node**)x)->frqt - (*(struct node**)y)->frqt;
}

void DFS(struct node *now , char tem[50] , int len)
{
	if(now->c != -1)
	{
		for(int i = 0 ; i < len ; i++) 
			code[now->c][i] = tem[i];
		code[now->c][len] = '\0';	
		return;
	}
	tem[len] = '0';
	DFS(now->left , tem , len + 1);
	tem[len] = '1';
	DFS(now->right , tem , len + 1);
}

int cvt2int(char *code)
{
	int cnt = 0 , u = 1 , ans = 0;
	while(code[cnt] != '\0')
		cnt++;
	while(cnt != 0)
	{
		cnt--;
		ans += (code[cnt] - '0') * u;
		u *= 2;
	}
	return ans;
}

char cvt2char(char *bs)
{
	char ans = 0;
	int u = 1;
	for(int i = 7 ; i >= 0 ; i--)
	{
		ans += ((bs[i] - '0') * u);
		u *= 2;
	}
	return ans;
}

int main(void)
{
	//初始化
	for(int i = 0 ; i < 256 ; i++)  
	{
		ch[i] = (struct node*)malloc(sizeof(struct node));
		ch[i]->c = i;
		ch[i]->frqt = 0;
		ch[i]->left = ch[i]->right = NULL;
	}
	
	//读入源文件 
	int sum = 0;  //源文件总字符数	
	FILE *fp = fopen("source.txt" , "r"); 
	while(!feof(fp))
	{
		char tem; 
		fscanf(fp , "%c" , &tem);
		ch[tem]->frqt++;
		sum++;
	}
	rewind(fp);
 
	//除去源文件中没有出现的字符
	int NotZero = 256;
	for(int i = 0 ; i < NotZero ; i++)
		if(ch[i]->frqt == 0)
		{
			for(int j = i ; j < NotZero - 1 ; j++)
			{
				ch[j] = ch[j + 1];
			}
			NotZero--;
			i--;
		}
	
	//生成Huffman树
	qsort(ch , NotZero , sizeof(struct node*) , cmp);
	while(NotZero != 1)
	{
		struct node *tem0 = ch[0] , *tem1 = ch[1];
		ch[0] = (struct node*)malloc(sizeof(struct node));
		ch[0]->c = -1;
		ch[0]->frqt = tem0->frqt + tem1->frqt;
		ch[0]->left = tem0;
		ch[0]->right = tem1;
		for(int j = 1 ; j < NotZero - 1 ; j++)
		{
			ch[j] = ch[j + 1];
		}
		NotZero--;
		qsort(ch , NotZero , sizeof(struct node*) , cmp);
	}

	//确定出现字符的编码
	char tem[50];
	DFS(ch[0] , tem , 0);
	int code_sum = 0;  //一共有几种字符有编码
	for(int i = 0 ; i < 256 ; i++)
		if(strcmp(code[i] , "") != 0)
		{
			code_sum++;
		}
		
	//写入配置文件
	FILE *fp_config = fopen("Huffman.config" , "wb");
	memset(config , 0 , sizeof(config));
	config[0] = sum;
	config[1] = code_sum;
	int p = 2;
	for(int i = 0 ; i < 256 ; i++)
		if(strcmp(code[i] , "") != 0)
		{
			int num = cvt2int(code[i]);
			config[p++] = i;
			config[p++] = strlen(code[i]);
			config[p++] = num;
		}
	fwrite(config , sizeof(int) , p , fp_config); 

	//写入压缩文件
	FILE *fp_huffman = fopen("Huffman.compressed" , "wb");
	int cnt = 0;
	while(!feof(fp))
	{
		char c;
		fscanf(fp , "%c" , &c);
		for(int i = 0 ; i < strlen(code[c]) ; i++)
			bsource[cnt++] = code[c][i];
	}
	if(cnt % 8 != 0)
	{
		while(cnt % 8 != 0)
			bsource[cnt++] = '0';
	}
	int cnt1 = 0;
	for(int i = 0 ; i * 8 < cnt ; i++)
	{ 
		compression[cnt1++] = cvt2char(&bsource[i * 8]);
	}
	fwrite(compression , sizeof(char) , cnt1 , fp_huffman);

	printf("压缩成功");
	return 0;	
}
