#include<stdio.h>
int main ()
{
	unsigned int p[32] = {16,17,18,19,20,21,22,23,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,24,25,26,27,28,29,30,31};
	unsigned long int n=0xab789a35,d=0,i;
	printf("Input of P - layer: %lx",n);
	for(i=0;i<32;i++)
	{
		d|=((n>>i)&0x1)<<p[i];
	}
	printf("\nOutput of P - layer: %lx",d);
}
