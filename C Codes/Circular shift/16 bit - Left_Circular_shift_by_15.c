#include<stdio.h>
int main()
{
 	unsigned int a=0xcccf;
 	printf("Input= %x",a);
	a= (((a<<15) | (a>>(16-15))) &0xffff);
	printf("\n Left Circular shifted by 15= %x",a);
}
