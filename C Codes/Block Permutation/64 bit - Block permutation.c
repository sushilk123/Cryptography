#include<stdio.h>
int main ()
{
	unsigned long long int n=0x12345678abcdef09,d=0,i;
	//printf("Input of P - layer: %llx",n);
	d = ((n & 0xffffffff00000000)>>32)|((n & 0x00000000ffffffff)<<32);
	printf("\nOutput of P - layer: %llx",d);
}
