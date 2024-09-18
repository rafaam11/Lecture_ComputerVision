#include <iostream>
#include <math.h>

#define ROW 512
#define COL 512

unsigned char readimage[ROW*COL], writeimage[ROW*COL], buffer[ROW*COL];


// Binary Image Conversion
void binarization(int thres)
{
	int i, j;

	for (i = 0; i<ROW; i++) {
		for (j = 0; j<COL; j++) {

			if (readimage[i*COL + j] > thres) {
				buffer[i*COL + j] = 255;
			}
			else {
				buffer[i*COL + j] = 0;
			}
		}
	}

}

// Change Brightness
void changeintensity(int val)
{
	int i, j;
	int temp;

	for (i = 0; i<ROW; i++) {
		for (j = 0; j<COL; j++) {

			temp = (int)readimage[i*COL + j] + val;
			if (temp < 0) {
				temp = 0;
			}
			if (temp > 255) {
				temp = 255;
			}

			buffer[i*COL + j] = temp;

		}
	}

}


int main()
{
	char readfilename[50] = "hiroshimayaki_grayscale.bmp";
	char writefilename[50] = "after_imaging.bmp";
	char header[2048];
	
	FILE *fpread, *fpwrite;
	fpread = fopen(readfilename, "rb");
	fpwrite = fopen(writefilename, "wb");
	
	if(fpread==NULL||fpwrite==NULL) { printf("\nFile Open Error"); return 0;}
	
	fread(header,1,1078,fpread); // 이미지가 헤더 정보에 의해 수직으로 뒤집혀졌다. (upside down)
	fread(readimage,1,ROW*COL,fpread);
	
	binarization(100);
	// changeintensity(0);
	
	fwrite(header,1,1078,fpwrite);
	fwrite(buffer,1,ROW*COL,fpwrite);
	
	fclose(fpread);
	fclose(fpwrite);
	
	return 0;	
 
}







