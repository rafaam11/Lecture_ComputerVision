#include <iostream>
#include <math.h>

#define ROW 512
#define COL 512

unsigned char cimage[ROW*COL*3], cbuffer[ROW*COL*3];


// Change to grayscale image from color image
void changetogray(double a, double b, double c)
{
	int i, j;
	int temp;
	
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			
			temp = int(c * int(cimage[(i * COL + j) * 3]) + b * int(cimage[(i * COL + j) * 3 + 1]) + a * int(cimage[(i * COL + j) * 3 + 2]));
			// convert intensity of R, G, B for each pixel to intensity of grayscale 
			
			cbuffer[i * COL + j] = temp;
			// store the converted intensity of each pixel to the buff_R2G
		}
}

	

int main()
{
	char readfilename_color[100] = "hiroshimayaki.bmp";						// original color image
	char readfilename_gray[100] = "earth_Grayscale.bmp"; 					// 그레이스케일 헤더를 뽑아오기위해 불러줌  
	char writefilename_RGB_to_Gray[100] = "after_imaging.bmp";			// grayscale image converted from original color image by RGB_to_Gray function
		char header_gray[1078];											// header of original gray image1078
		char header_color[54];											// header of original color image54
	
		FILE *fpread_color, *fpwrite_RGB_to_Gray, *fpread_gray;
		
		fpread_gray = fopen(readfilename_gray, "rb");
		fpread_color = fopen(readfilename_color, "rb"); 					// open "original_color.bmp"
		fpwrite_RGB_to_Gray = fopen(writefilename_RGB_to_Gray, "wb");		// open "generated_gray.bmp"	
	
	if (fpread_color == NULL || fpwrite_RGB_to_Gray == NULL) {printf("\nFile Open Error"); return 0; }
	
	fread(header_gray,1,1078,fpread_gray);
	fread(header_color, 1, 54, fpread_color);		// read header with 1 bit and 54 size from "original_color.bmp" and store to header_color 
	fread(cimage, 3, ROW * COL, fpread_color);	// read pixel data with 3 bit and ROW*COL size from "original_color.bmp" and store to color_image
	
	
	changetogray(0.3, 0.2, 0.5);						// run RGB_to_Gray with weighting factor of r=0.3, g=0.2, b=0.5

	
	fwrite(header_gray, 1, 1078, fpwrite_RGB_to_Gray);		// write header with 1 bit and 1078 size from header_gray to fpwrite_RGB_to_Gray
	fwrite(cbuffer,1, ROW * COL, fpwrite_RGB_to_Gray);		// write converted pixel data with 1 bit and 1078 size from buff_R2G to fpwrite_RGB_to_Gray
	
	
	fclose(fpread_color);
	fclose(fpwrite_RGB_to_Gray);
	
	return 0;
 
}



