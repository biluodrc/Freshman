#include<stdio.h>

char s[100000];

char change(char c)
{
	if(c == '¡£')
		return '.';
	if(c == '£¬')
		return ',';
	if(c == '£¡')
		return '!';
	if(c == '£»')
		return ';';
	if(c == '£º')
		return ':';
	if(c == '¡°')
		return '"';
	if(c == '¡¶')
		return '<';
	if(c == '¡·')
		return '>';
	if(c == '¡¾')
		return '[';
	if(c == '¡¿')
		return ']';
	if(c == '¡¢')
		return '\\';
	if(c == '£¨')
		return '(';
	if(c == '£©')
		return ')';
}

int main(void)
{
	FILE *fp = fopen("source.txt" , "r");
	int cnt = 0;
	while(!feof(fp))
	{
		fscanf(fp , "%c" , &s[cnt]);
		s[cnt] = change(s[cnt]);
		cnt++;
	}
	fclose(fp);
	fp = fopen("source.txt" , "w");
	for(int i = 0 ; i < cnt ; i++)
	{
		printf("%c" , s[i]);
		fprintf(fp , "%c" , s[i]);
	} 
	return 0;
}
