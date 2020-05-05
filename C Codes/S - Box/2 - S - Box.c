#include<stdio.h>
int main()
{
	unsigned int i,z=0,c=0xab;
	unsigned int s[16] = {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd};

	for (i=0;i<=4;i=i+4)
	{
		z |= s[((c>>(4-i))&0xf)]<<(4-i);
	}
	 printf("\nS - Box Output : - %lx",z);
}
