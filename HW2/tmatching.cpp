#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>

#define ROW 512
#define COL 512
#define winROW_1a 95
#define winCOL_1a 177
#define winROW_2a 186
#define winCOL_2a 249
#define winROW_3a 192
#define winCOL_3a 216

using namespace std;

unsigned char img_1a_tp[winROW_1a*winCOL_1a];
unsigned char img_2a_tp[winROW_2a*winCOL_2a];
unsigned char img_3a_tp[winROW_3a*winCOL_3a];
unsigned char img_1a_bn[ROW*COL];
unsigned char img_2a_bn[ROW*COL];
unsigned char img_3a_bn[ROW*COL];
unsigned char img_case[ROW*COL];
unsigned char buff2_1a_tp[winROW_1a][winCOL_1a];
unsigned char buff2_2a_tp[winROW_2a][winCOL_2a];
unsigned char buff2_3a_tp[winROW_3a][winCOL_3a];
unsigned char buff2_1a_bn[ROW][COL];
unsigned char buff2_2a_bn[ROW][COL];
unsigned char buff2_3a_bn[ROW][COL];
unsigned char buff2_case[ROW][COL];

int main()
{
	
	char readfilename_1a_tp[30] = "1-a_binary-1.bmp";	
	char readfilename_2a_tp[30] = "2-a_binary-1.bmp";	
	char readfilename_3a_tp[30] = "3-a_binary-1.bmp";
	char readfilename_1a_bn[30] = "1-a_binary.bmp";	
	char readfilename_2a_bn[30] = "2-a_binary.bmp";	
	char readfilename_3a_bn[30] = "3-a_binary.bmp";
	char readfilename_case[30] = "case_binary.bmp";
	
	FILE *fpread_1a_tp, *fpread_2a_tp, *fpread_3a_tp, *fpread_1a_bn, *fpread_2a_bn, *fpread_3a_bn, *fpread_case;
	fpread_1a_tp = fopen(readfilename_1a_tp, "rb");
	fpread_2a_tp = fopen(readfilename_2a_tp, "rb"); 
	fpread_3a_tp = fopen(readfilename_3a_tp, "rb");
	fpread_1a_bn = fopen(readfilename_1a_bn, "rb");
	fpread_2a_bn = fopen(readfilename_2a_bn, "rb"); 
	fpread_3a_bn = fopen(readfilename_3a_bn, "rb");
	fpread_case = fopen(readfilename_case, "rb");
	fread(img_1a_tp, 1, winROW_1a*winCOL_1a , fpread_1a_tp);
	fread(img_2a_tp, 1, winROW_2a*winCOL_2a , fpread_2a_tp);
	fread(img_3a_tp, 1, winROW_3a*winCOL_3a , fpread_3a_tp);
	fread(img_1a_bn, 1, ROW*COL , fpread_1a_bn);
	fread(img_2a_bn, 1, ROW*COL , fpread_2a_bn);
	fread(img_3a_bn, 1, ROW*COL , fpread_3a_bn);
	fread(img_case, 1, ROW*COL , fpread_case);
	for (int i = 0 ; i < winROW_1a ; i++) for (int j = 0 ; j < winCOL_1a ; j++) { buff2_1a_tp[i][j] = img_1a_tp[i*winCOL_1a+j]; }
	for (int i = 0 ; i < winROW_2a ; i++) for (int j = 0 ; j < winCOL_2a ; j++) { buff2_2a_tp[i][j] = img_2a_tp[i*winCOL_2a+j]; }
	for (int i = 0 ; i < winROW_3a ; i++) for (int j = 0 ; j < winCOL_3a ; j++) { buff2_3a_tp[i][j] = img_3a_tp[i*winCOL_3a+j]; }
	for (int i = 0 ; i < ROW ; i++) for (int j = 0 ; j < COL ; j++) {
		buff2_1a_bn[i][j] = img_1a_bn[i*COL+j];
		buff2_2a_bn[i][j] = img_2a_bn[i*COL+j];
		buff2_3a_bn[i][j] = img_3a_bn[i*COL+j];
		buff2_case[i][j] = img_case[i*COL+j];
	}
	
	
	
	int a;
	int b;
	
	
	// 1인지 확인  
	for(int i=47 ; i<ROW-47 ; i++)
		for(int j=88 ; j<COL-88 ; j++) {
			
			
			
			for(int k=-47 ; k<=47 ; k++) {
				for(int m=-88 ; m<=88 ; m++) {
					a = buff2_1a_tp[k+47][m+88] / 255;
					b = buff2_case[i+k][j+m] / 255;
					std::cout << a;
					
					
				}
				std::cout << endl;	
			}
			
		
			
		}
		
			

		
	fclose(fpread_1a_tp);
	fclose(fpread_2a_tp);
	fclose(fpread_3a_tp);
	fclose(fpread_1a_bn);
	fclose(fpread_2a_bn);
	fclose(fpread_3a_bn);
	fclose(fpread_case);
	
	
}
