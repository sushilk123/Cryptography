#include<stdio.h>
int main()
{
 	unsigned int a=0xab;
 	printf("Input= %x",a);
	a= (((a<<4) | (a>>(8-4))) &0xff);
	printf("\n Left Circular shifted by 4= %x",a);
}
