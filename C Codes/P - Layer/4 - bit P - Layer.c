#include<stdio.h>

int main ()
{
	
	unsigned int p[4] = {2,3,0,1};
	unsigned int n=0xe,d=0,i;
	
	printf("Input of P - layer: %x",n);
	for(i=0;i<4;i++)
	{
		d|=((n>>i)&0x1)<<p[i];
	}
	printf("\nOutput of P - layer: %x",d);
}
