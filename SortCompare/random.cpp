#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(void)
{
	FILE *fp1 = fopen("1000.txt" , "w");
	FILE *fp2 = fopen("10000.txt" , "w");
	FILE *fp3 = fopen("100000.txt" , "w");
	FILE *fp4 = fopen("1000000.txt" , "w");
	long cnt = 1000;
	srand(time(0));
	while(cnt--)
	{
		fprintf(fp1 , "%d " , rand());
	}
	cnt = 10000;
	while(cnt--)
	{
		fprintf(fp2 , "%d " , rand());
	}
	cnt = 100000;	
	while(cnt--)
	{
		fprintf(fp3 , "%d " , rand());
	}
	cnt = 1000000;	while(cnt--)
	{
		fprintf(fp4 , "%d " , rand());
	}
	fclose(fp1);fclose(fp2);fclose(fp3);fclose(fp4);
}
