#include <iostream>
#include <math.h>

#define ROW 512
#define COL 512

unsigned char gray_image[ROW*COL], color_image[ROW*COL*3], buff_binar[ROW*COL], buff_R2G[ROW*COL];



// convert original grayscale image to binary image  
void binarization(int thres)
{
	int i, j;
	int temp;
	
	for (i=0; i<ROW; i++)
		for (j = 0; j < COL; j++){
			
			temp = (int)gray_image[i * COL + j]; // store intensity of each pixel to the temp 
			
			if (temp < thres) temp = 0;  		// convert intensity to the 0(minimum intensity) if the intensity is smaller than determined threshold val
			
			if (temp >= thres) temp =255;  		// convert intensity to the 255(maximum intensity) if the intensity is larger than determined threshold val
			
			buff_binar[i * COL + j] = temp; 	 // store the converted intensity of each pixel to the buff_binar
		}
}

// convert RGB image to Grayscale image  
void RGB_to_Gray (double a, double b, double c)
{
	int i, j;
	int temp;
	
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			
			temp = int(c * int(color_image[(i * COL + j) * 3]) + b * int(color_image[(i * COL + j) * 3 + 1]) + a * int(color_image[(i * COL + j) * 3 + 2]));
			// convert intensity of R, G, B for each pixel to intensity of grayscale 
			
			buff_R2G[i * COL + j] = temp;
			// store the converted intensity of each pixel to the buff_R2G
		}
}
	

int main()
{
	char readfilename_gray[100] = "hiroshimayaki_grayscale.bmp";				// original grayscale image
	char readfilename_color[100] = "hiroshimayaki.bmp";						// original color image
	char writefilename_binarization[100] = "after_binarization.bmp";		// binary image converted from original_gray image by binarization function
	char writefilename_RGB_to_Gray[100] = "after_RGB_to_Gray.bmp";			// grayscale image converted from original color image by RGB_to_Gray function
		char header_gray[1078];											// header of original gray image1078
		char header_color[54];											// header of original color image54
	
		FILE *fpread_gray, *fpread_color, *fpwrite_binarization, *fpwrite_RGB_to_Gray;
		
		fpread_gray = fopen(readfilename_gray, "rb");						// open "original_gray.bmp"
		fpread_color = fopen(readfilename_color, "rb"); 					// open "original_color.bmp"
		fpwrite_binarization = fopen(writefilename_binarization, "wb");		// open "binarization.bmp"
		fpwrite_RGB_to_Gray = fopen(writefilename_RGB_to_Gray, "wb");		// open "generated_gray.bmp"	
	
	if (fpread_color == NULL|| fpread_gray == NULL || fpwrite_binarization == NULL || fpwrite_RGB_to_Gray == NULL) {printf("\nFile Open Error"); return 0; }
	
	// fread : 뒤에걸로부터 앞에거를 읽는다. 
	fread(header_gray, 1, 1078, fpread_gray);		// read header with 1 bit and 1078 size from "original_gray.bmp" and store to header_gray 
	fread(header_color, 1, 54, fpread_color);		// read header with 1 bit and 54 size from "original_color.bmp" and store to header_color 
	fread(gray_image, 1, ROW * COL, fpread_gray);	// read pixel data with 1 bit and ROW*COL size from "original_gray.bmp" and store to gray_image 
	fread(color_image, 3, ROW * COL, fpread_color);	// read pixel data with 3 bit and ROW*COL size from "original_color.bmp" and store to color_image
	
	
	binarization(95);								// run binarizaiton with threshold 100
	RGB_to_Gray(0.3, 0.2, 0.5);						// run RGB_to_Gray with weighting factor of r=0.3, g=0.2, b=0.5

	
	// fwrite : 앞에걸로부터 뒤에거를 쓴다. 
	fwrite(header_gray, 1, 1078, fpwrite_binarization);		// write header with 1 bit and 1078 size from header_gray to fpwrite_binarization
	fwrite(header_gray, 1, 1078, fpwrite_RGB_to_Gray);		// write header with 1 bit and 1078 size from header_gray to fpwrite_RGB_to_Gray
	fwrite(buff_binar,1, ROW * COL, fpwrite_binarization);	// write converted pixel data with 1 bit and 1078 size from buff_binar to fpwrite_binarization
	fwrite(buff_R2G,1, ROW * COL, fpwrite_RGB_to_Gray);		// write converted pixel data with 1 bit and 1078 size from buff_R2G to fpwrite_RGB_to_Gray
	
	
	fclose(fpread_gray);
	fclose(fpread_color);
	fclose(fpwrite_binarization);
	fclose(fpwrite_RGB_to_Gray);
	
	return 0;	
 
}



