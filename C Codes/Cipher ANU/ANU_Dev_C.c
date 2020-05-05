#include<stdio.h>

 unsigned long int shiftleft(unsigned long int,unsigned char);
 unsigned long int sbox_(unsigned long int);
 unsigned long int shiftright(unsigned long int,unsigned int );
 unsigned long int player(unsigned long long int);
 
 unsigned char sbox[16] = {2,9,7,0xE,1,0xC,0xA,0,4,3,8,0xD,0xF,0x6,0x5,0xB};
unsigned char p[32] = {20,16,28,24,17,21,25,29,22,18,30,26,19,23,27,31,11,15,3,7,14,10,6,2,9,13,1,5,12,8,4,0};

int main()
{
	unsigned int m;
	unsigned long int msb_32bit=0x00,lsb_32bit=0x00,s_box1,s_box2,bn,bn1,sub_key[1],c,r,i1,j1,i,j[2]; 
 	unsigned long long int temp,k[2]={0x00,0x00};
 	
 	for(r=0;r<25;r++)
	{	
//_____________________________________
	c = shiftleft(msb_32bit,3);
 	 s_box1 = sbox_(c);
 	 c = shiftright(msb_32bit,8);
  	s_box2 = sbox_(c);
 	bn = player(msb_32bit);
//___________________________________	
	sub_key[0] = (k[1]&0XFFFFFFFF);	
		temp=k[1];
	k[1]= (temp<<13)|(k[0]>>(64-13));
	k[0]= (k[0]<<13)|(temp>>(64-13));
	//k[1] = K_UP1;
	//k[0] = K_UP2;

		for(i=0; i<2; i++)
		{
			j[i]=sbox[(k[1]>>(i*4))&0XF];
		}
		k[1] &= (0Xffffffffffffff00);  

		for(i=0;i<2;i++)
			{
				k[1] |= ((j[i]&0xf)<<(i*4));
			}  
				temp = (((k[1]&0XF800000000000000)>>(64-5))^(0x1f&r));
				k[1] &= 0X07FFFFFFFFFFFFFF;
				k[1] |= temp<<(64-5);
		temp =  (s_box1^s_box2^lsb_32bit^sub_key[0]);
//_____________________________________________________________			
		//	bn1=0;
      bn1 =  player(temp);
//______________________________________________________________
	 msb_32bit = bn1;
   lsb_32bit = bn;
   
   printf("\n Cipher Text= %lx %lx\n",msb_32bit,lsb_32bit);
   printf("\n---------------------------Round %d---------------------\n",r);
}   
}

unsigned long int shiftleft(unsigned long int msb_32bit,unsigned char i)
{
	unsigned long int a,b,tempr;
	a = msb_32bit<<i;
	tempr = msb_32bit>>(32-i);
	b = a|tempr;
	return(b);
}

 unsigned long int sbox_(unsigned long int c)
{

	unsigned long int a=0,i,j[33],b=0;
	for (i=0;i<32;i=i+4)     
	{
	 j[b]= sbox[((c>>(28-i)&0xf))];
	 a |= ((((j[b])&0xf)<<(28-i)));
	 b++;
	}
	return(a);
}

unsigned long int shiftright(unsigned long int msb_32bit,unsigned int i)
{
	unsigned long int a,b,tempr;
	a = msb_32bit>>i;
	tempr = msb_32bit<<(32-i);
	b = a|tempr;
	return(b);
}

 unsigned long int player(unsigned long long int tempr)
 {
 	unsigned int i, b=0;
	 
    for (i=0; i<32;i++)
     {
 		 b |= ((tempr>>i)&0x1)<<p[i];
		 }
	  	 return(b);
 }

