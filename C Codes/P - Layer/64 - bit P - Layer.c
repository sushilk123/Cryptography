#include<stdio.h>
int main ()
{
	unsigned int p[64]={ 0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23,
	 39, 55,8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63};
	unsigned long long int n=0xab789a3512345678,d=0,i;
	printf("Input of P - layer: %llx",n);
	for(i=0;i<64;i++)
	{
		d|=((n>>i)&0x1)<<p[i];
	}
	printf("\nOutput of P - layer: %llx",d);
}
