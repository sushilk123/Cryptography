#include<stdio.h>
int permutation(unsigned int a);
int sbox_func(unsigned int p);
int circular_shift_1(unsigned int q);
int circular_shift_2(unsigned int r);
int main()
{
	unsigned long long int x=0x0000000000000000;
	unsigned long long int x0=0x00000000, d=0x00000000;
	unsigned  long long int x2,x3;
	unsigned int f,w1,w2,u1,y1,v1,z1,p1,i;
	//unsigned int y,s1;
	printf("Input String is %llx",x);
	//for(i=0; i<4; i++)
	//{
	
	//d=x&0x00000000ffffffff;
	//x0=((x&0xffffffff00000000)>>32);
	f=permutation(d);
	printf("\nAfter Permutation:-%x",f);
	w2=f&0x0ffff;
	w1=(f&0xffff0000)>>16;
	printf("\nWf1:-%x",w1);// Value of Wf1 16- bit value
	printf("\nWf2:-%x",w2);// Value of Wf2 16-bits value
	u1=sbox_func(w1);
	printf("\nU1:-%x",u1);    // The value of U after substitution method 16-bit
	y1=circular_shift_1(u1);
	printf("\nCircular Shift of U1:-%x",y1);// The output of the Y1 after circular shift of U, Y1 is 16-bit
	v1=sbox_func(w2);
	printf("\nV1:-%x",v1);   // The value of V after substitution method 16-bit
	z1=circular_shift_2(v1);
	printf("\nCircular Shift of V1:-%x",z1);// The output of the Z1 after circular shift of V, Z1 is 16-bit
	p1=(y1<<16)|z1;
	printf("\nOutput of Fiestal Network:-%x",p1);// P1 is the output of the Fiestal Network
	x2=p1^x0;
	printf("\nOutput @ X2 terminal :-%x",x2);// X2=P1 xor with input bit stream
	x3=(d<<32)|x2;
	
	x0=d;
	d = x2;
//	y=sbox_func(s1);
	printf("\nCipher Text is :- %llx",x3);// Output Cipher text
//	printf("\n------------------------Round %d---------------\n",i);
	//}
	
//	printf("\n No. of Active S-Box:-%x",s1);
}
int permutation(unsigned int a)
{
	unsigned int y,x,b,c;
	y=((a&0x00ff0000)>>16);
	x=(a&0x0000ff00)|y;
	b=((a&0x000000ff)<<16)|x;
	c=(a&0xff000000)|b;
	return(c);
}
int sbox_func(unsigned int p)
{
	unsigned int sbox[16]= {2,0xe,0xf,5,0xc,1,9,0xa,0xb,4,6,8,0,7,3,0xd};
	unsigned int i,j[6],z,m=0;
	for(i=0;i<16;i=i+4)
	{
		z = sbox[((p>>(12-i))&0xf)]<<(12-i);
		m=m|z;
	}
	return(m);
}
int circular_shift_1(unsigned int q)
{
	q= q^(((q<<1) | (q>>(16-1))) &0xffff)^(((q<<5) | (q>>(16-5))) &0xffff)^(((q<<9) | (q>>(16-9))) &0xffff)^(((q<<12) | (q>>(16-12))) &0xffff);
	return(q);
}
int circular_shift_2(unsigned int r)
{
	r= r^(((r<<4) | (r>>(16-4))) &0xffff)^(((r<<7) | (r>>(16-7))) &0xffff)^(((r<<11) | (r>>(16-11))) &0xffff)^(((r<<15) | (r>>(16-15))) &0xffff);
	return(r);
}

