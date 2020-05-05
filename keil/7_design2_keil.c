#include<lpc21xx.h>

void tx(unsigned int c); //function that transmit char (user see on uart terminal)
char rx(void); // function that receive anything

unsigned char s[16] = {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd};
unsigned int sbox(unsigned int c)
{
	unsigned int i,z=0;
	for (i=0;i<32;i=i+4)
	{
		z |= s[((c>>(28-i))&0xf)]<<(28-i);
	 } 
	 return (z);
}

int main()
 {
   unsigned long int t;
	unsigned long long int temp=0,k[2]={0x00,0x00};//k[1]=lsb,k[0]=msb
	unsigned long int data[2]={0x00,0x00};
	unsigned int j1,i1,m;
	
	
	PINSEL0 = 0x05; // configuration for tx and rx in pinsel
	U0LCR = 0x83; // configure the line control register
	U0DLL = 0x61;
	U0DLM = 0x00;// config baud rate 9600 (calculate in bps ---> convert into hex --> then load into DLL & DLM)
	U0LCR = 0x03; // lock baud rate by resetting baud rate bit in U0LCR register	 
	
	//______________Enter Plain Text 64 bit from UART___________________________
	
	tx('P');
	tx('-');		
		for (j1=0; j1<2; j1++)
		{
			//k[j1] =0;
				for (i1=0;i1<=7;i1++)
				{
					m = rx();
					tx(m);
			 
					if (m>0x2F && m<0x3a)   //from 0 to 9-----0x30-0x39
					{
						temp = m-0x30;
					}	
					if(m>=0x61 && m<=0x66)  //from a to f------0x61-0x66
					{
						temp = m-87;
					}
					data[j1] += (temp & 0xf) << ((7-i1)*4); 
				}	
		}
			
	//______________Enter Key Value 128 bit from UART___________________________			
			
		tx(' ');
		tx('K');
		tx('-'); 
		for (j1=0; j1<2; j1++)
		{
			//k[j1] =0;
				for (i1=0;i1<=15;i1++)
				{
					m = rx();
					tx(m);
			 
					if (m>0x2F && m<0x3a)
					{
						temp = m-0x30;
					}	
					if(m>=0x61 && m<=0x66)
					{
						temp = m-87;
					}
					k[j1] += (temp & 0xf) << ((15-i1)*4); 
				}	
		}
//_______________Main Design Logic Starts from here___________________
		
	for(j1=0; j1<31; j1++)
	{
    temp=0;
    data[0]=sbox(data[0]);
    data[0]=(((data[0]<<11)|(data[0]>>(32-11))&0xffffffff));
    data[1]=(data[0]^data[1]^(k[1]&(0x00000000ffffffff)));
    //t1=pbox(data[1]);
   //t1=(((data[1]<<7)|(data[1]>>(32-7))&0xffffffff));
    data[0]=(data[1]^data[0]);


     t=0;
  	t=data[1];
    data[1]=data[0];
    data[0]=t;
		
//key scheduling:
			temp=k[1];
		k[1]= (temp<<13)|(k[0]>>(64-13));
		k[0]= (k[0]<<13)|(temp>>(64-13));
		
		//Sbox	
      m=0;
				for(i1=0; i1<2; i1++)
		{
			m|=(s[(k[1]>>(i1*4))&0XF]<<i1*4)&0xff;
		}
	
		k[1] &= (0Xffffffffffffff00);  
		k[1] |= ((m&0xFF));
		
		//RC xor	
		temp = (((k[1]&0XF800000000000000)>>(64-5))^(0x1f&j1));
		k[1] &= 0X07FFFFFFFFFFFFFF;
		k[1] |= temp<<(64-5);
	}
		
//_______________Output Data print on UART________________________

	 tx(' ');
	 tx('c');
	 tx('-');
for(j1=2; j1>0; j1--)
{
	for (i1=0; i1<=7; i1++)
	{
		temp=(data[j1-1]>>(7-i1)*4)&0xf;	
			if(temp<10)
			tx(0x30+temp);
			else
			tx(87+temp);
	}
}
	
	
//__________________________________________________________________	 
	
	
}
//Functin to Transmit the characters
void tx(unsigned int c)
{
 while(!(U0LSR & 0x20)); // check the transmitter data available bit in U0LSR
 U0THR = c; // if data is available it will transmit by jumping from above line (while !)
}
 char rx(void)
{
	unsigned char m;
	while(!(U0LSR & 0x01)); // check the transmitter data available bit in U0LSR
  m = U0RBR; // if data is available it will transmit by jumping from above line (while !)
  return(m);
}

