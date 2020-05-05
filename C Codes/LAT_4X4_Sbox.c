#include<stdio.h>
int main()
{
 int A1 = 10, B = 11, C1 = 12, D = 13, E = 14, F = 15, z;
// unsigned int Sbox[16] = {3,0xf,0xe,1,0,0xa,5,8,0xc,4,0xb,2,9,7,6,0xd}; // S-Box for LiCi
//unsigned int Sbox[16] = {0xc, 5, 6, 0xb, 9, 0, 0xa, 0xd, 3, 0xe, 0xf, 8, 4, 7, 1, 2}; // S-Box for present
//unsigned char Sbox[16] = {2,9,7,0xE,1,0xC,0xA,0,4,3,8,0xD,0xF,0x6,0x5,0xB}; // S-Box for ANU
unsigned char Sbox[16] = {3, 0xF, 0xE,1, 0, 0xA, 5, 8, 0xC, 4, 0xB, 2, 9, 7, 6, 0xD};
//unsigned char Sbox[16] = {0xE, 4, 0xB, 1, 7, 9, 0xC, 0xA, 0xD, 2, 0, 0xF, 8, 5, 3, 6};
  
 int i, j, k1, k2, l1, l2, c1, c2;
 
 int x[4][16] = {{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},        //X1
 			 {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1},			 //X2	
			 {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1},			 //X3
 			 {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}};		 //X4
 
 int y[4][16];
 int a[4],b[4],A[16];
 int RHS[16];//={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 int LHS[16];//={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int count_lat[16][16];
 float C[16][16];

//printf("\nSBOX="); 
//printf("\n");
printf(" Linear Approximation Table\n\n");
	for(i=0;i<16;i++)
	 {
	 	 
	 	for(j=0;j<4;j++)
	 	{
	 		y[3-j][i]=(Sbox[i]>>j)&1;			//form in Y1 Y2 Y3 Y4
	 	//	printf("%d ",y[j][i]);
	 	}
	 	
	 }
	
	for(i=0;i<4;i++)
	 {
	 	for(j=0;j<16;j++)
	 	{
//	 		printf("%d ",y[i][j]);
	 	}
//		printf("\n"); 	
	 }
//-------------------------------------------------------------------- 
for(l2=0;l2<16;l2++)
{
for(l1=0;l1<16;l1++)
{
	for(i=0;i<16;i++)
	{
	
	  RHS[i]=0;
 	  LHS[i]=0;
 	}
// 	printf("\nINPUT A=");
	for(i=0;i<4;i++)
	{
		a[i]=(l1>>(3-i))&1;
//		printf("%d",a[i]);
	}
	
//	printf("\nOUTPUT B=");
	for(i=0;i<4;i++)
	{
		b[i]=(l2>>(3-i))&1;
//		printf("%d",b[i]);
	}
	k1=0;
	k2=0;
	for(i=0;i<4;i++)
	{
		//-----------RHS--------------//
		if(a[i]==1)
		{
			k1++;
			
			for(j=0;j<16;j++)
			{
				RHS[j]^=x[i][j];
			}
		}

		else if(k1==0)
		{
			for(j=0;j<16;j++)
			{
				RHS[j]=0;
			}
		}
		//--------LHS----------------//	
		if(b[i]==1)
		{
			k2++;
			
			for(j=0;j<16;j++)
			{
				LHS[j]^=y[i][j];
			}
		}
		
		else if(k2==0)
		{
			for(j=0;j<16;j++)
			{
				LHS[j]=0;
			}
		}
	}
	
//	printf("\n");
	count_lat[l2][l1]=0;
	for(i=0;i<16;i++)
	{
//		printf("RHS=%d LHS=%d",RHS[i],LHS[i]);
	
		if(RHS[i]==LHS[i])
		{
			count_lat[l2][l1]++;
		}
//		printf("\n");
	} 
}
//printf("\n");
}
//while(1)
{
//printf("INPUT=");
//scanf("%d",&l2);
printf("    0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F\n");
printf("___________________________________________________________________\n");
c1=4;
c2=-4;
for(l1=0;l1<16;l1++)
{
printf(" %x |",l1);

for(l2=0;l2<16;l2++)
{

	count_lat[l2][l1]-=8;
	if(count_lat[l2][l1] > c1 & l2!=0 & l1!=0)
	{
		c1=count_lat[l2][l1];
	}
		if(count_lat[l2][l1] < 0 & count_lat[l2][l1] < c2 )
	{
		c2=count_lat[l2][l1];
	}
//	count_lat[l2][l1]/=16;
	printf("%2d| ",count_lat[l2][l1]);
}
printf("\n");
}
printf("\n MAXIMUM VALUE IN LAT\ +ve = %d -ve = %d",c1,c2);
}
printf("\n\n VALUES AT wt(INPUTMASK)=wt(OUTPUTMASK)=1 \n%2d %2d %2d %2d \n%2d %2d %2d %2d \n%2d %2d %2d %2d \n%2d %2d %2d %2d",count_lat[1][1],count_lat[2][1],count_lat[4][1],count_lat[8][1],count_lat[1][2],count_lat[2][2],count_lat[4][2],count_lat[8][2],count_lat[1][4],count_lat[2][4],count_lat[4][4],count_lat[8][4],count_lat[1][8],count_lat[2][8],count_lat[4][8],count_lat[8][8]);
z=0;
for(l2=1;l2<9;l2=l2*2)
{
	for(l1=1;l1<9;l1=l1*2)
	{
				
		if(count_lat[l1][l2] !=0)
		{
			z++;
				
		}
	}
	
}
printf("\nCARLC=\%d",z);

getch();	
}
