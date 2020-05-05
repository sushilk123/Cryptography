#include<stdio.h>
unsigned long long int sbox(unsigned long long int);
unsigned long long int player(unsigned long long int);
unsigned int P[64]={ 0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55,8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63};
unsigned int s[16]= {6,3,0xa,5,0xc,8,1,0xb,0,0xd,9,0xe,0xf,2,7,4};
int main()
{
	unsigned long long int a=0x1234567890abcdef,a1,a2;
	printf("Plain Text:- %llx\n",a);
	a=sbox(a);
	printf("\nS-box Output:- %llx\n",a);
	a=player(a);
	printf("\nP - Layer Output:- %llx\n",a);
	a1 = ((a>>32)&0xffffffff); // MSB 32 - bit
	a2 = (a & 0xffffffff); // LSB 32 - bit
	
	a1= (((a1>>16) | (a1<<(32-16))) &0xffffffff);
	a2= (((a2<<8) | (a2>>(32-8))) &0xffffffff);
	
	printf("\nMSB 32 - bit Right Circular Shifting by 16: %lx\n",a1);
	printf("\nLSB 32 - bit Left Circular Shifting by 8: %lx\n",a2);
	
	a = ((a1<<32)&0xffffffff00000000)|(a2);
	
	printf("\nCipher Text:- %llx\n",a);
}
unsigned long long int sbox(unsigned long long int c)
{
	unsigned long long int i,z=0,z1=0,z2=0;
	for (i=0;i<8;i++)
	{
		z1 |= s[((c>>(i*4))&0xf)]<<(i*4);
		z2 |= s[(c>>((i+8)*4)&0xf)]<<(i*4);
		
	}
	z = ((z2<<32)&0xffffffff00000000)|(z1 & 0xffffffff);
	 return (z);
}
unsigned long long int player(unsigned long long int b)
{
	unsigned long long int c=0,i;
	for(i=0;i<64;i++)
	{
		c |=((b>>i) & 0x1) << P[i];
	}
	return(c);
}
