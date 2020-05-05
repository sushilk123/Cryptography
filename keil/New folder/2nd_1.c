#include<lpc21xx.h>

//Define Clock settings
#define PCLK			15000000            
#define BAUDRATE	9600	 //Set Baud Rate here
void tx(unsigned int c); //function that transmit char (user see on uart terminal)
char rx(void); // function that receive anything


void  delay_ms(unsigned char time)	   //This Function is used to cause delay between LED ON and OFF events
{  
 unsigned int  i, j;
 for (j=0; j<time; j++)
  for(i=0; i<8002; i++);
}

//Function to Initialize the UART0
void  Init_UART0(void)					//This function setups UART0
{  
   unsigned int Baud16;
   U0LCR = 0x83;		            // DLAB = 1
   Baud16 = (PCLK /(16*BAUDRATE));  
   U0DLM = Baud16 >>8;							
   U0DLL = Baud16 ;						
   U0LCR = 0x03;
}
	
/*
unsigned long int pbox(unsigned long long int c)
{unsigned int p[32]={20,16,28,24,17,21,25,29,22,18,30,26,19,23,27,31,11,15,3,7,14,10,6,2,9,13,1,5,12,8,4,0};
	unsigned long int d=0;
  unsigned int i;

   for(i=0;i<32;i++)
   {
   	d|=((c>>i)&0x01)<<p[i];
   }
   return d;
}

*/
unsigned long int sbox(unsigned long int c,unsigned int byte)
{ 
unsigned int i,s[16]= {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd};
unsigned long int z=0;
	byte=byte*4;
				for(i=0;i<byte;i=i+4)
	{   
			z|=(s[((c>>((byte-4)-i))&0xf)]<<((byte-4)-i));
	}
return(z);
}

int main()
 {
   unsigned long int t=0;
	unsigned long long int temp=0,k[2]={0x00,0x00};//k[1]=lsb,k[0]=msb
	unsigned long int data[2]={0x00,0x00};
    //unsigned long long int z;
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
		
	for(i1=0; i1<31; i1++)
	{
    temp=0;t=0;
    data[0]=sbox(data[0],8);
    data[1]=(((data[1]<<3)|(data[1]>>(32-3))&0xffffffff));
		
    t=data[1];
    data[1]=data[0];
    data[0]=t;
   // data[0]=sbox(data[0],8);
    data[1]=(((data[1]>>5)|(data[1]<<(32-5))&0xffffffff));
    data[0]=(data[0]^(k[1]>>32));
    data[1]=(data[1]^data[0]^(k[1]&(0x00000000ffffffff)));
    /*t=0;
	t=data[1];
    data[1]=data[0];
    data[0]=t;*/
		//key scheduling:
			temp=k[1];
		k[1]= (temp<<13)|(k[0]>>(64-13));
		k[0]= (k[0]<<13)|(temp>>(64-13));
		
		//Sbox	
+
m=0;
			m=sbox(k[1],2);
	
		k[1] &= (0Xffffffffffffff00);  
		k[1] |= ((m&0xFF));
		
		//RC xor	
		temp = (((k[1]&0XF800000000000000)>>(64-5))^(0x1f&i1));
		k[1] &= 0X07FFFFFFFFFFFFFF;
		k[1] |= temp<<(64-5);
	}
		
//_______________Output Data print on UART________________________

	 tx(' ');
	 tx('C');
	 tx('-');
	for(j1=0;j1<2;j1++){
	for (i1=0; i1<=7; i1++)
	{
		temp=(data[j1]>>(7-i1)*4)&0xf;	
			if(temp<10)
			tx(0x30+temp);
			else
			tx(87+temp);
	}
 temp =0;
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

