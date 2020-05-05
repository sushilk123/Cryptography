#include<lpc21xx.h>

//Define Clock settings
#define PCLK			15000000            
#define BAUDRATE	9600	 //Set Baud Rate here

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
				
//Functin to Transmit the characters
void  Tx_byte(unsigned char data)	   //A function to send a byte on UART0
{  
   U0THR = data;				    
   while( (U0LSR&0x40)==0 );	    
}

//Functin to Receive the characters
unsigned char  Rx_byte( )	   //A function to send a byte on UART0
{     
  while((U0LSR&0x01)==0);
   	return U0RBR; 
	    
}

//Functin to Transmit the string
void  Tx_string(const unsigned char *str)	 //A function to send a string on UART0
{  
   while(1)
   {  
      if( *str == '\0' ) break;
      Tx_byte(*str++);	    
   }
}
/*unsigned long long int pbox(unsigned long long int c)
{ int i;
  unsigned long long int d=0,a[]={20,16,28,24,17,21,25,29,22,18,30,26,19,23,27,31,11,15,3,7,14,10,6,2,9,13,1,5,12,8,4,0};
  	for(i=0;i<32;i++)
	{
	d|=((c>>i)&0x1)<<a[i];
	 }
return d;
}

unsigned long long int sbox(unsigned long long int c,unsigned int byte)
{ 
byte=byte*4;
unsigned long long int i,s[16]={2,9,7,0xe,1,0xc,0xa,0,4,3,8,0xd,0xf,0x6,0x5,0xb};
unsigned long long int z=0;
				for(i=0;i<byte;i=i+4)
	{   
			z|=(s[((c>>((byte-4)-i))&0xf)]<<((byte-4)-i));
	}
return(z);
}*/





int  main(void)
{  
	unsigned char m,temp,rx_data[20], i;

	unsigned int k,l;
	unsigned long long int data;
	PINSEL0 = 0x00000005; // Enable UART0 Rx and Tx pins
  Init_UART0();
	
	//plain_text:
	Tx_byte('p');
	Tx_byte('-');
	for(k=0;k<=15;k++)
	{  m=Rx_byte();
		Tx_byte(m);
		if(m>0x2f&&m<0x3a)
		{
			temp=m-0x30;
		}
		if(m>=0x61&&m<=0x66)
		{
       temp=m-87;
    }
		data+=(temp&0xF)<<((15-k)*4);
	}
//key:
	Tx_byte(' ');
	Tx_byte('k');
	Tx_byte('-');
	
	for(k=0;k<2;k++)
	{  
		for(l=0;l<=15;l++)
		{
			m=Rx_byte();
		Tx_byte(m);
		if(m>0x2f&&m<0x3a)
		{
			temp=m-0x30;
		}
		if(m>=0x61&&m<=0x66)
		{
       temp=m-87;
   
 }
		data+=(temp&0xF)<<((15-k)*4);
	}
}
	
	
	
	
while(1);
}

	/*UART0_SendStr("Send 10 Characters\n\r ");
  
	for (i=0; i<10; i++)
	{	
 		rx_data[i]=UART0_RecievedByte();
  } 
	
	rx_data [10]= 0; // To make received string as ASCIIZ string
	UART0_SendStr("\n\rTransmitted Characters are:");
	UART0_SendStr(rx_data);
	UART0_SendStr("\n\rRx Tx test complete\n\r");*/

