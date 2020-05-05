// We have to change just sbox then difference distribution table will form
#include<stdio.h>

int main()
{
	
	int A=10,B=11,C=12,D=13,E=14,F=15;
  //unsigned int sbox[16] =  {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd}; // SBox for LiCi
//  unsigned char sbox[16] = {2,9,7,0xE,1,0xC,0xA,0,4,3,8,0xD,0xF,0x6,0x5,0xB}; // S-Box for ANU
   //unsigned int sbox[16] = {0xc,5,6,0xb,9,0,0xa,0xd,3,0xe,0xf,8,4,7,1,2}; // S-Box for present
  unsigned int sbox[16] = {3, 0xF, 0xE,1, 0, 0xA, 5, 8, 0xC, 4, 0xB, 2, 9, 7, 6, 0xD}; // S box for DOT

	int y1,y2,x2,x1,delx,dely,c,i,j1,j2;
	int count[16][16]={0};
printf("Difference Distribution Table \n \n");
for(delx=0;delx<16;delx++)
{
	for(x1=0;x1<16;x1++)
	{
		x2=x1^delx;
		y2=sbox[x2];
		y1=sbox[x1];
		dely=y1^y2;
		count[delx][dely]++;
	}
	
}
printf("   0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F\n");
printf("_________________________________________________________________\n");
c=4;	
for(delx=0;delx<16;delx++)
{
printf("%x |",delx);
	for(dely=0;dely<16;dely++)
	{
		printf("%d | ",count[delx][dely]);
	
	if((count[delx][dely]>c) &delx!=0 &dely!=0)
		{
			c=count[delx][dely];
		}
	}
	printf("\n");
}
printf("\nVALUES AT wt(delI)=wt(delO)=1 \n%d %d %d %d \n%d %d %d %d \n%d %d %d %d \n%d %d %d %d",count[1][1],count[1][2],count[1][4],count[1][8],count[2][1],count[2][2],count[2][4],count[2][8],count[4][1],count[4][2],count[4][4],count[4][8],count[8][1],count[8][2],count[8][4],count[8][8]);
printf("\nMAXIMUM PROBABILITY=%d",c);

getch();
}
