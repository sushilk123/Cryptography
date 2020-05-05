#include<stdio.h>
int main()
{
	unsigned long long int i,z=0,c=0xebf5f0cb12345678;
	unsigned int s[16] = {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd};

	for (i=0;i<64;i=i+4)
	{
		z |= s[((c>>(60-i))&0xf)]<<(60-i);
	}
		 printf("\nS - Box Output : - %lx",((z>>32)&0xffffffff));

	 printf("\nS - Box Output : - %lx",z);
}
