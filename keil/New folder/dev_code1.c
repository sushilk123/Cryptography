#include<stdio.h>
 
unsigned long long int pbox(unsigned long long int c)
{
	unsigned long long int d=0,p[]={20,16,28,24,17,21,25,29,22,18,30,26,19,23,27,31,11,15,3,7,14,10,6,2,9,13,1,5,12,8,4,0};
	  unsigned int i;

   for(i=0;i<32;i++)
   {
   	d|=((c>>i)&0x01)<<p[i];
   }
   return d;
}

unsigned long long int s[16]={3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd};
unsigned long long int sbox(unsigned long long int c,unsigned int byte)
{ 
byte=byte*4;
unsigned long long int i;
unsigned long long int z=0;
				for(i=0;i<byte;i=i+4)
	{   
			z|=(s[((c>>((byte-4)-i))&0xf)]<<((byte-4)-i));
	}
return(z);
}


int main()
{   unsigned long long int t,lhs,rhs;//lhs=0x00000000,rhs=0x00000000;
	unsigned long long int temp=0,a=0,k[2]={0x00,0x00};//k[1]=lsb,k[0]=msb
	unsigned long int data[2]={0x000000000,0x00000000};
    unsigned long long int y,q,z,j=0;
		unsigned int j1,i1,m,r,i;
  for(i1=0; i1<31; i1++)
	{
    a=0;z=0;y=0;q=0;
    data[0]=(((data[0]<<3)|(data[0]>>(32-3))&0xffffffff));
    data[1]=(((data[1]>>7)|(data[1]<<(32-7))&0xffffffff));
    data[0]=(data[1]^data[0]^(k[1]>>32));//msb key
    data[1]=(data[1]^data[0]^(k[1]&(0x00000000ffffffff)));
   data[0]=sbox(data[0],8);
   data[1]=sbox(data[1],8);
   data[0]=pbox(data[0]);
   data[1]=pbox(data[1]);
    t=data[1];
    data[1]=data[0];
    data[0]=t;
    printf("%lx%lx\n",data[0],data[1]);
	//__________key scheduling___________________
	temp=k[1];
	k[1]=((temp<<13)|(k[0]>>(64-13)));	//128 bit left circular shift by 13
	k[0]=((k[0]<<13)|(temp>>(64-13)));	
	z=	sbox(k[1]&0x000000ff,2);
	z=(z&0x000000ff);
	k[1]=((k[1]&0xFFFFFFFFFFFFFF00)|z);
a=((k[1]>>59)^(0x1f&j));//j=ring counter
a=a<<59;
k[1]=((k[1]&0X07FFFFFFFFFFFFFF)|a);		
//printf("round & key = %d %llx%llx\n",j, k[0],k[1]);	


}}

