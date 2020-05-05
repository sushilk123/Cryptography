#include<stdio.h>
int main()
{
 	unsigned long int a=0xcccf1234;
 	printf("Input= %x",a);
	a= (((a<<8) | (a>>(32-8))) &0xffffffff);
	printf("\n Left Circular shifted by 15= %lx",a);
}
