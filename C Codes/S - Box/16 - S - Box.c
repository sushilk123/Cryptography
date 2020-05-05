#include<stdio.h>
int main()
{
	unsigned long long int i,z1=0,z2=0,c=0xebf5f0cb1234ab73,z=0;
	unsigned long long int s[16] = {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd};

	for (i=0;i<64;i=i+4)
	{
		z |= s[((c>>(60-i))&0xf)]<<(60-i);
	//	z1 |= s[((c>>(i*4))&0xf)]<<(i*4);
	//	z2 |= s[(c>>((i+8)*4)&0xf)]<<(i*4);
	//	z = ((z2<<32)&0xffffffff00000000)|(z1 & 0xffffffff);
	}
	 printf("\nS - Box Output : - %llx",z);
}
