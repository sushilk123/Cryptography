#include<stdio.h>
int main ()
{	
	unsigned int p[16] = {15,11,7,3,2,14,10,6,5,1,13,9,8,4,0,12};
	unsigned long int n=0xab78,d=0,i;
	printf("Input of P - layer: %lx",n);
	for(i=0;i<16;i++)
	{
		d|=((n>>i)&0x1)<<p[i];
	}
	printf("\nOutput of P - layer: %lx",d);
}
