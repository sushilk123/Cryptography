#include<LPC21xx.h>
void txbyte(char rx1);
char rxbyte(void);
unsigned long long int sbox(unsigned long long int );
unsigned long long int player(unsigned long long int );
unsigned char s[16]={0xc,5,6,0xb,9,0,0xa,0xd,3,0xe,0xf,8,4,7,1,2};
unsigned char p[64]={ 0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55,8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63};
int main()
{
unsigned char i,j,m;
unsigned long long int p,temp,k[2];
PINSEL0=0x05;
U0LCR=0x9A;
U0DLL=0x61;
U0DLM=0x00;
U0LCR=0x1A;
txbyte(' ');
txbyte('P');
txbyte('-');
		for(j=0;j<=15;j++)
		{
			m=rxbyte();
			txbyte(m);
			if(m>0x2F&&m<0x3A)
			{
				temp=m-0x30;
			}
			if(m>=97&&m<=102)
				{
					temp=m-87;
				}
				p+=(temp&0xF)<<((15-j)*4);
				}
txbyte(' ');
txbyte('K');
txbyte('-');
for(i=0;i<2;i++)
	{
		for(j=0;j<=15;j++)
		{
			m=rxbyte();
			txbyte(m);
			if(m>0x2F&&m<0x3A)
			{
				temp=m-0x30;
			}
			if(m>=97&&m<=102)
				{
					temp=m-87;
				}
				k[i]+=(temp&0xF)<<((7-j)*4);
				}
			}
for(i=0;i<32;i++)
	{
	p=p^k[1]; // a is input i.e. plain text and Ex-or with k[0] subkey
	p=sbox(p);// apply S-box 	
	p=player(p);// Apply P-Layer	     	
		temp=k[1];
		k[1]= (temp<<61)|(k[0]>>(64-61));
		k[0]= (k[0]<<61)|(temp>>(64-61));
		temp=0;
	for(j=0;j<2;j++)
	{ 
			temp|= s[(k[0]>>((j+14)*4))&0xf]<<j*4;
	}
     k[0] = (k[0]&0x00ffffffffffffff)|(temp<<56); 
	
	temp=(k[1]>>62)|((k[0]&0x07)<<2);
	temp=temp^(i+1);
	k[1]=((k[1])&0x3FFFFFFFFFFFFFFF)|(temp<<62);
	k[0]=((k[0])&0xFFFFFFFFFFFFFFF8)|(temp>>2);
	}
	txbyte(' ');
	txbyte('C');		
  txbyte('-');
	for(i=0;i<=15;i++)
			{
				temp=(p>>((15-i)*4))&0xF;
				if(temp<10)
				{
					txbyte(0x30+temp);
				}
				else
					txbyte(87+temp);
			}
}
void txbyte(char rx1)
{
while(!(U0LSR & 0x20));
U0THR=rx1;
}
char rxbyte()
{
unsigned char rx;
while(!(U0LSR & 0x01));
rx=U0RBR;
return(rx);
}
unsigned long long int sbox(unsigned long long int in)
{
	unsigned char i;
	unsigned long long int temp=0,temp1=0;
	for(i=0;i<32;i=i+4)
	{
		temp |= s[(in >> i) &0xf] << i;
		temp1 |=s[(in >> (i+32)) &0xf] << i;
	}
	 return (temp1<<32|(temp&0xffffffff));
}
unsigned long long int player(unsigned long long int b)
{
	unsigned char i;
	unsigned long long int c=0;
	for(i=0;i<64;i++)
	{
		c |=((b>>i) & 0x1) << p[i];
	}
	return(c);
}
