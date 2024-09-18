#include <iostream>
#include <math.h>

#define ROW 512
#define COL 512

unsigned char hw_img[ROW*COL*3], my_grayimg[ROW*COL], buff_R2G[ROW*COL], buff_histo[ROW*COL], buff_md[ROW*COL], buff_md2[ROW][COL], buff_sb[ROW*COL];
unsigned char hw_img_histo[ROW*COL], hw_img_md[ROW*COL], hw_img_md2[ROW][COL], hw_img_sb[ROW*COL];


void RGB_to_Gray (double a, double b, double c)
{
	int i, j;
	int temp;
	
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			
			temp = int(c * int(hw_img[(i * COL + j) * 3]) + b * int(hw_img[(i * COL + j) * 3 + 1]) + a * int(hw_img[(i * COL + j) * 3 + 2]));
			
			buff_R2G[i * COL + j] = temp;
			
		}
}

void histogram(unsigned char readimg[])
{
	int i, j, r;
	int temp;
	unsigned int histo[256];
	double pdf[256], cdf[256], s;
	
	for (i = 0 ; i < 256 ; i++) histo[i] = 0;
	
	for (i = 0 ; i < ROW ; i++)
		for (j = 0 ; j < COL ; j++)
			histo[(int)readimg[i*COL + j]]++;
	
	for ( i = 0 ; i < 256 ; i++) {
		pdf[i] = histo[i]/(double)(ROW*COL);	
		
		if (i == 0) cdf[i] = pdf[i];
		else cdf[i] = cdf[i-1] + pdf[i];
		
	}
	
	for (i = 0 ; i < ROW ; i++)
		for (j = 0 ; j < COL ; j++)  {
			r = readimg[i*COL + j];
			s = 255.0*cdf[r];
			buff_histo[i*COL + j] = int(s+0.5);
			
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

void sobel1d(unsigned char out[], unsigned char in[]) {
int i, j, k, m;
int sumx = 0, sumy = 0, val = 0;

int xwin[3][3] = {{-1,0,1},{-2,0,2}, {-1,0,1}};
int ywin[3][3] = {{-1,-2,-1},{0,0,0}, {1,2,1}};

for (i = 1 ; i < ROW-1 ; i++)
	for (j = 1 ; j < COL-1 ; j++) {
		sumx = sumy = 0;
		for (k=-1 ; k <= 1 ; k++)
			for (m = -1 ; m <= 1 ; m++) {
				sumx += in[(i+k)*COL+(j+m)]*xwin[k+1][m+1];
				sumy += in[(i+k)*COL+(j+m)]*ywin[k+1][m+1];
			}	
		
	val = 2.0*(abs(sumx)+abs(sumy));	
	if(val>255) val = 255;
	out[i*COL+j] = val;
		
	}
}

int main()
{
	// grayscaling  (24bit -> 8bit 이미지로 바꿈 )  
	char readfilename_my[100] = "earth_gray.bmp";				
	char readfilename_hw[100] = "noisebsc.bmp";					
	char writefilename_grayscaling[100] = "noisebsc_after_grayscaling.bmp";		
	char header_gray[1078];										
	char header_color[54];									
	FILE *fpread_my, *fpread_hw, *fpwrite_grayscaling;	
	fpread_my = fopen(readfilename_my, "rb");					
	fpread_hw = fopen(readfilename_hw, "rb"); 				
	fpwrite_grayscaling = fopen(writefilename_grayscaling, "wb");		
	if (fpread_my == NULL|| fpread_hw == NULL || fpwrite_grayscaling == NULL) {printf("\nFile Open Error"); return 0; }
	fread(header_gray, 1, 1078, fpread_my);	
	fread(header_color, 1, 54, fpread_hw);	
	fread(my_grayimg, 1, ROW * COL, fpread_my);	
	fread(hw_img, 3, ROW * COL, fpread_hw);
	RGB_to_Gray(0.299, 0.114, 0.587);	
	fwrite(header_gray, 1, 1078, fpwrite_grayscaling);	
	fwrite(buff_R2G,1, ROW * COL, fpwrite_grayscaling);		
	fclose(fpread_my);
	fclose(fpread_hw);
	fclose(fpwrite_grayscaling);
	
	
	// histogram(밝게)
	char readfilename_ht[100] = "noisebsc_after_grayscaling.bmp";								
	char writefilename_ht[100] = "noisebsc_after_histo.bmp";											
	FILE *fpread_ht, *fpwrite_ht;
	fpread_ht = fopen(readfilename_ht, "rb");							
	fpwrite_ht = fopen(writefilename_ht, "wb");
	if (fpread_ht == NULL || fpwrite_ht == NULL) {printf("\nFile Open Error"); return 0; }
	fread(header_gray,1,1078,fpread_ht);
	fread(hw_img_histo, 1, ROW * COL, fpread_ht);
	
	histogram(hw_img_histo);
	
	fwrite(header_gray, 1, 1078, fpwrite_ht);	
	fwrite(buff_histo,1, ROW * COL, fpwrite_ht);		
	fclose(fpread_ht);
	fclose(fpread_ht);
	
	
	// Median(Salt-pepper 노이즈 제거)  
	char readfilename_md[100] = "noisebsc_after_histo.bmp";								
	char writefilename_md[100] = "noisebsc_after_median.bmp";											
	FILE *fpread_md, *fpwrite_md;
	fpread_md = fopen(readfilename_md, "rb");							
	fpwrite_md = fopen(writefilename_md, "wb");
	if (fpread_md == NULL || fpwrite_md == NULL) {printf("\nFile Open Error"); return 0; }
	fread(header_gray,1,1078,fpread_md);
	fread(hw_img_md, 1, ROW * COL, fpread_md);
	
	for (int i = 1 ; i < ROW-1 ; i++) for (int j = 1 ; j < COL-1 ; j++) hw_img_md2[i][j] = hw_img_md[i*COL+j];
	median(buff_md2, hw_img_md2, 9);
	for (int i = 1 ; i < ROW-1 ; i++) for (int j = 1 ; j < COL-1 ; j++) buff_md[i*COL+j] = buff_md2[i][j];	
	
	fwrite(header_gray, 1, 1078, fpwrite_md);	
	fwrite(buff_md,1, ROW * COL, fpwrite_md);		
	fclose(fpread_md);
	fclose(fpread_md);
	
	
	// sobel (Edge 강조)
	char readfilename_sb[100] = "noisebsc_after_median.bmp";								
	char writefilename_sb[100] = "noisebsc_after_processing.bmp";											
	FILE *fpread_sb, *fpwrite_sb;
	fpread_sb = fopen(readfilename_sb, "rb");							
	fpwrite_sb = fopen(writefilename_sb, "wb");
	if (fpread_sb == NULL || fpwrite_sb == NULL) {printf("\nFile Open Error"); return 0; }
	fread(header_gray,1,1078,fpread_sb);
	fread(hw_img_sb, 1, ROW * COL, fpread_sb);
	
	sobel1d(buff_sb, hw_img_sb);
	
	fwrite(header_gray, 1, 1078, fpwrite_sb);	
	fwrite(buff_sb, 1, ROW * COL, fpwrite_sb);		
	fclose(fpread_sb);
	fclose(fpread_sb);
	
	return 0;	
 
}



