#include <iostream>
using namespace std;
#define ROW 256
#define COL 256

unsigned char readimage[ROW][COL], writeimage[ROW][COL], 
void tmatching(unsigned char in[][COL],int *maxi, int *maxj)
{
	
	int i,j,k,m;
	double sum=0,max=255*81;
	int tp[9][9] = {{230,230,230,230,230,230,230,230,230},
					{230,230,230,230,230,230,230,230,230},
					{230,230,230,150,150,150,230,230,230},
					{230,230,150,150,150,150,150,230,230},
					{230,230,150,150,150,150,150,230,230},
					{230,230,150,150,150,150,150,230,230},
					{230,230,230,150,150,150,230,230,230},
					{230,230,230,230,230,230,230,230,230},
					{230,230,230,230,230,230,230,230,230}};
	for(i=4;i<ROW-4;i++)
		for(j=4;j<COL-4;j++) {
			sum =0;
			for(k=-4;k<=4;k++)
				for(m=-4;m<=4;m++) 
					sum += in[i+k][j+m] * tp[k+4][m+4];
					if(sum>max) { 
						max = sum;
						*maxi = i; 
						*maxj = j;
					}
		}
}
