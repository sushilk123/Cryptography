#include<stdio.h>

int main ()
{
	unsigned long int n=0x12345678,d=0,i;
	printf("Input of P - layer: %lx",n);
	n = ((n & 0xff000000)>>8)|((n & 0x00ff0000)<<8)|((n & 0x0000ff00)>>8)|((n & 0x000000ff)<<8);
	printf("\nOutput of P - layer: %lx",n);
}
