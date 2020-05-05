#include<stdio.h>
int main()
{
 	unsigned long int a=0xcccf1234;
 	printf("Input= %x",a);
	a= (((a>>16) | (a<<(32-16))) &0xffffffff);
	printf("\n Right Circular shifted by 16= %lx",a);
}
