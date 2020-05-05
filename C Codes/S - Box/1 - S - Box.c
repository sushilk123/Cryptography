#include<stdio.h>
int main()
{
	unsigned int z=0,c=0xa;
	unsigned int s[16] = {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd};
	
	z = s[c & 0xf];
	 printf("\nS - Box Output : - %lx",z);
}
