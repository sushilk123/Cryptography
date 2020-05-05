#include<stdio.h>
int main()
{
	unsigned long int i,z=0,c=0xebf5f0cb;
	unsigned int s[16] = {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd};

	for (i=0;i<32;i=i+4)
	{
		z |= s[((c>>(28-i))&0xf)]<<(28-i);
	}
	 printf("\nS - Box Output : - %lx",z);
}
