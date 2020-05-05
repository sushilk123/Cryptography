#include<stdio.h>

int main ()
{
	unsigned int p[8] = {2,4,6,0,7,1,3,5};
	unsigned int n=0xab,d=0,i;
	printf("Input of P - layer: %x",n);
	for(i=0;i<8;i++)
	{
		d|=((n>>i)&0x1)<<p[i];
	}
	printf("\nOutput of P - layer: %x",d);
}
