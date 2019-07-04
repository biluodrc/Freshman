#include<stdio.h>
int main(void)
{
	FILE *fp1 = fopen("1000.txt" , "w");
	FILE *fp2 = fopen("10000.txt" , "w");
	FILE *fp3 = fopen("100000.txt" , "w");
	FILE *fp4 = fopen("1000000.txt" , "w");

	for(long i = 1000 ; i > 0 ; i--)
		fprintf(fp1 , "%ld " , i);
	for(long i = 10000 ; i > 0 ; i--)
		fprintf(fp2 , "%ld " , i);	
	for(long i = 100000 ; i > 0 ; i--)
		fprintf(fp3 , "%ld " , i);
	for(long i = 1000000 ; i > 0 ; i--)
		fprintf(fp4 , "%ld " , i);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}
