#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>

#define ROW 512
#define COL 512

using namespace std;

unsigned char grayimg[ROW*COL];
unsigned char img_1a[ROW*COL*3];
unsigned char img_1b[ROW*COL*3];
unsigned char img_1c[ROW*COL*3];
unsigned char img_1d[ROW*COL*3];
unsigned char img_2a[ROW*COL*3];
unsigned char img_2b[ROW*COL*3];
unsigned char img_2c[ROW*COL*3];
unsigned char img_2d[ROW*COL*3];
unsigned char img_3a[ROW*COL*3];
unsigned char img_3b[ROW*COL*3];
unsigned char img_3c[ROW*COL*3];
unsigned char img_3d[ROW*COL*3];
unsigned char buff_R2G_1a[ROW*COL];
unsigned char buff_R2G_1b[ROW*COL];
unsigned char buff_R2G_1c[ROW*COL];
unsigned char buff_R2G_1d[ROW*COL];
unsigned char buff_R2G_2a[ROW*COL];
unsigned char buff_R2G_2b[ROW*COL];
unsigned char buff_R2G_2c[ROW*COL];
unsigned char buff_R2G_2d[ROW*COL];
unsigned char buff_R2G_3a[ROW*COL];
unsigned char buff_R2G_3b[ROW*COL];
unsigned char buff_R2G_3c[ROW*COL];
unsigned char buff_R2G_3d[ROW*COL];
unsigned char buff_binar_1a[ROW*COL];
unsigned char buff_binar_1b[ROW*COL];
unsigned char buff_binar_1c[ROW*COL];
unsigned char buff_binar_1d[ROW*COL];
unsigned char buff_binar_2a[ROW*COL];
unsigned char buff_binar_2b[ROW*COL];
unsigned char buff_binar_2c[ROW*COL];
unsigned char buff_binar_2d[ROW*COL];
unsigned char buff_binar_3a[ROW*COL];
unsigned char buff_binar_3b[ROW*COL];
unsigned char buff_binar_3c[ROW*COL];
unsigned char buff_binar_3d[ROW*COL];
unsigned char img_md[ROW*COL], img_md2[ROW][COL], buff_md[ROW*COL], buff_md2[ROW][COL];


void RGB_to_Gray (unsigned char img[], unsigned char buff_R2G[], double a, double b, double c)
{
	int i, j;
	int temp;
	
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			
			temp = int(c * int(img[(i * COL + j) * 3]) + b * int(img[(i * COL + j) * 3 + 1]) + a * int(img[(i * COL + j) * 3 + 2]));
			
			buff_R2G[i * COL + j] = temp;
			
		}
}

void median(unsigned char out[][COL], unsigned char image[][COL],int size)
{
	int i,j;
	int k, l, gray;
	int first, search, temp, count;
	int *med = new int[size*size];
	
	for(i = (int)(size/2) ; i < ROW - (int)(size/2) ; i++)
		for (j = (int)(size/2) ; j < COL - (int)(size/2) ; j++) {
			count = 0;
				for (k = -1*(int)(size/2) ; k <= (int)(size/2) ; k++)
					for (l = -1*(int)(size/2) ; l <= (int)(size/2) ; l++)
						med[count++] = image[i+k][j+l];
			for (first = 0 ; first < size*size - 1 ; first++)
				for(search = first + 1 ; search < size*size ; search++)
					if (med[search] > med[first]) {
						temp = med[search];
						med[search] = med[first];
						med[first] = temp;
					}
		out[i][j] = med[(int)(size*size/2)];	
		}
	delete [] med;
}

void binarization(unsigned char buff_R2G[], unsigned char buff_binar[], int val) 
{
	int i, j;
	int temp;
	for (i=0; i<ROW; i++)
		for (j = 0; j < COL; j++){
			temp = (int)buff_R2G[i * COL + j]; 
			if (temp < val) temp = 0;
			if (temp >= val) temp =255;
			buff_binar[i * COL + j] = temp;
		
		}
}


int main()
{ 
	// Read & Write할 파일이름 지정  
	char readfilename_grayscale[30] = "earth_gray_512.bmp";				
	char readfilename_1a[30] = "1-a_512.bmp";
	char readfilename_1b[30] = "1-b_512.bmp";	
	char readfilename_1c[30] = "1-c_512.bmp";	
	char readfilename_1d[30] = "1-d_512.bmp";	
	char readfilename_2a[30] = "2-a_512.bmp";	
	char readfilename_2b[30] = "2-b_512.bmp";	
	char readfilename_2c[30] = "2-c_512.bmp";	
	char readfilename_2d[30] = "2-d_512.bmp";	
	char readfilename_3a[30] = "3-a_512.bmp";	
	char readfilename_3b[30] = "3-b_512.bmp";	
	char readfilename_3c[30] = "3-c_512.bmp";	
	char readfilename_3d[30] = "3-d_512.bmp";				
	char writefilename_1a[30] = "1-a_binary.bmp";		
	char writefilename_1b[30] = "1-b_binary.bmp";
	char writefilename_1c[30] = "1-c_binary.bmp";
	char writefilename_1d[30] = "1-d_binary.bmp";
	char writefilename_2a[30] = "2-a_binary.bmp";
	char writefilename_2b[30] = "2-b_binary.bmp";
	char writefilename_2c[30] = "2-c_binary.bmp";
	char writefilename_2d[30] = "2-d_binary.bmp";
	char writefilename_3a[30] = "3-a_binary.bmp";
	char writefilename_3b[30] = "3-b_binary.bmp";
	char writefilename_3c[30] = "3-c_binary.bmp";
	char writefilename_3d[30] = "3-d_binary.bmp";
	
	// File Open & Read 
	char header_gray[1078];										
	char header_color[54];							
	FILE *fpread_grayscale, *fpread_1a, *fpread_1b, *fpread_1c, *fpread_1d, *fpread_2a, *fpread_2b, *fpread_2c, *fpread_2d, *fpread_3a, *fpread_3b, *fpread_3c, *fpread_3d, 
	*fpwrite_1a, *fpwrite_1b, *fpwrite_1c, *fpwrite_1d, *fpwrite_2a, *fpwrite_2b, *fpwrite_2c, *fpwrite_2d, *fpwrite_3a, *fpwrite_3b, *fpwrite_3c, *fpwrite_3d;	
	fpread_grayscale = fopen(readfilename_grayscale, "rb");					
	fpread_1a = fopen(readfilename_1a, "rb");
	fpread_1b = fopen(readfilename_1b, "rb"); 
	fpread_1c = fopen(readfilename_1c, "rb"); 
	fpread_1d = fopen(readfilename_1d, "rb"); 
	fpread_2a = fopen(readfilename_2a, "rb"); 
	fpread_2b = fopen(readfilename_2b, "rb"); 
	fpread_2c = fopen(readfilename_2c, "rb"); 
	fpread_2d = fopen(readfilename_2d, "rb"); 
	fpread_3a = fopen(readfilename_3a, "rb"); 
	fpread_3b = fopen(readfilename_3b, "rb"); 
	fpread_3c = fopen(readfilename_3c, "rb"); 
	fpread_3d = fopen(readfilename_3d, "rb"); 				
	fpwrite_1a = fopen(writefilename_1a, "wb");
	fpwrite_1b = fopen(writefilename_1b, "wb");	
	fpwrite_1c = fopen(writefilename_1c, "wb");	
	fpwrite_1d = fopen(writefilename_1d, "wb");	
	fpwrite_2a = fopen(writefilename_2a, "wb");	
	fpwrite_2b = fopen(writefilename_2b, "wb");	
	fpwrite_2c = fopen(writefilename_2c, "wb");	
	fpwrite_2d = fopen(writefilename_2d, "wb");	
	fpwrite_3a = fopen(writefilename_3a, "wb");	
	fpwrite_3b = fopen(writefilename_3b, "wb");	
	fpwrite_3c = fopen(writefilename_3c, "wb");	
	fpwrite_3d = fopen(writefilename_3d, "wb");	
	fread(header_gray, 1, 1078, fpread_grayscale);		
	fread(grayimg, 1, ROW * COL, fpread_grayscale);
	fread(img_1a, 3, ROW * COL, fpread_1a);
	fread(img_1b, 3, ROW * COL, fpread_1b);
	fread(img_1c, 3, ROW * COL, fpread_1c);
	fread(img_1d, 3, ROW * COL, fpread_1d);
	fread(img_2a, 3, ROW * COL, fpread_2a);
	fread(img_2b, 3, ROW * COL, fpread_2b);
	fread(img_2c, 3, ROW * COL, fpread_2c);
	fread(img_2d, 3, ROW * COL, fpread_2d);
	fread(img_3a, 3, ROW * COL, fpread_3a);
	fread(img_3b, 3, ROW * COL, fpread_3b);
	fread(img_3c, 3, ROW * COL, fpread_3c);
	fread(img_3d, 3, ROW * COL, fpread_3d);
	
	
	// grayscaling  (24bit -> 8bit 이미지로 ) 
	RGB_to_Gray(img_1a, buff_R2G_1a, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_1b, buff_R2G_1b, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_1c, buff_R2G_1c, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_1d, buff_R2G_1d, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_2a, buff_R2G_2a, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_2b, buff_R2G_2b, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_2c, buff_R2G_2c, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_2d, buff_R2G_2d, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_3a, buff_R2G_3a, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_3b, buff_R2G_3b, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_3c, buff_R2G_3c, 0.299, 0.114, 0.587);
	RGB_to_Gray(img_3d, buff_R2G_3d, 0.299, 0.114, 0.587);
	
	
	// Median filter for 2-c salt-pepper image
	for (int i = 1 ; i < ROW-1 ; i++) for (int j = 1 ; j < COL-1 ; j++) img_md2[i][j] = buff_R2G_2c[i*COL+j];
	median(buff_md2, img_md2, 11);
	for (int i = 1 ; i < ROW-1 ; i++) for (int j = 1 ; j < COL-1 ; j++) buff_md[i*COL+j] = buff_md2[i][j];	
	
	// binarization (8bit -> binary 이미지로) 
	binarization(buff_R2G_1a,buff_binar_1a,70);
	binarization(buff_R2G_1b,buff_binar_1b,180);
	binarization(buff_R2G_1c,buff_binar_1c,70);
	binarization(buff_R2G_1d,buff_binar_1d,75);
	binarization(buff_R2G_2a,buff_binar_2a,70);
	binarization(buff_R2G_2b,buff_binar_2b,75);
	binarization(buff_md,buff_binar_2c,50);
	binarization(buff_R2G_2d,buff_binar_2d,30);
	binarization(buff_R2G_3a,buff_binar_3a,70);
	binarization(buff_R2G_3b,buff_binar_3b,100);
	binarization(buff_R2G_3c,buff_binar_3c,50);
	binarization(buff_R2G_3d,buff_binar_3d,50);
	
	// Binary-imagefile Writing
	fwrite(header_gray, 1, 1078, fpwrite_1a);	
	fwrite(header_gray, 1, 1078, fpwrite_1b);
	fwrite(header_gray, 1, 1078, fpwrite_1c);
	fwrite(header_gray, 1, 1078, fpwrite_1d);
	fwrite(header_gray, 1, 1078, fpwrite_2a);
	fwrite(header_gray, 1, 1078, fpwrite_2b);
	fwrite(header_gray, 1, 1078, fpwrite_2c);
	fwrite(header_gray, 1, 1078, fpwrite_2d);
	fwrite(header_gray, 1, 1078, fpwrite_3a);
	fwrite(header_gray, 1, 1078, fpwrite_3b);
	fwrite(header_gray, 1, 1078, fpwrite_3c);
	fwrite(header_gray, 1, 1078, fpwrite_3d);
	fwrite(buff_binar_1a,1, ROW * COL, fpwrite_1a);
	fwrite(buff_binar_1b,1, ROW * COL, fpwrite_1b);
	fwrite(buff_binar_1c,1, ROW * COL, fpwrite_1c);
	fwrite(buff_binar_1d,1, ROW * COL, fpwrite_1d);
	fwrite(buff_binar_2a,1, ROW * COL, fpwrite_2a);
	fwrite(buff_binar_2b,1, ROW * COL, fpwrite_2b);
	fwrite(buff_binar_2c,1, ROW * COL, fpwrite_2c);
	fwrite(buff_binar_2d,1, ROW * COL, fpwrite_2d);
	fwrite(buff_binar_3a,1, ROW * COL, fpwrite_3a);
	fwrite(buff_binar_3b,1, ROW * COL, fpwrite_3b);
	fwrite(buff_binar_3c,1, ROW * COL, fpwrite_3c);
	fwrite(buff_binar_3d,1, ROW * COL, fpwrite_3d);	
	
	
	// File Closing
	fclose(fpread_grayscale);
	fclose(fpread_1a);
	fclose(fpread_1b);
	fclose(fpread_1c);
	fclose(fpread_1d);
	fclose(fpread_2a);
	fclose(fpread_2b);
	fclose(fpread_2c);
	fclose(fpread_2d);
	fclose(fpread_3a);
	fclose(fpread_3b);
	fclose(fpread_3c);
	fclose(fpread_3d);
	fclose(fpwrite_1a);
	fclose(fpwrite_1b);
	fclose(fpwrite_1c);
	fclose(fpwrite_1d);
	fclose(fpwrite_2a);
	fclose(fpwrite_2b);
	fclose(fpwrite_2c);
	fclose(fpwrite_2d);
	fclose(fpwrite_3a);
	fclose(fpwrite_3b);
	fclose(fpwrite_3c);
	fclose(fpwrite_3d);
	
	return 0;	
	
}



