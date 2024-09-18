#include <iostream>
#include <math.h>

#define ROW 512
#define COL 512
double pi = 3.1415926535;
double realx[ROW*COL];
double real2[ROW][COL];
double real_dft1[ROW*COL];
double real_dft2[ROW][COL];
double real_idft2[ROW][COL];
double imagx[ROW*COL];
double imag2[ROW][COL];
double imag_dft1[ROW*COL];
double imag_dft2[ROW][COL];
double imag_idft2[ROW][COL];
double temp[ROW][COL];
unsigned char gimage[ROW*COL];
unsigned char gimage2[ROW][COL];
unsigned char cimage[ROW*COL*3];


void changetogray(double cimage[], double gimage[])
{
	int i, j;
	int temp;
	
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			
			temp = int(0.114 * int(cimage[(i * COL + j) * 3]) + 0.587 * int(cimage[(i * COL + j) * 3 + 1]) + 0.299 * int(cimage[(i * COL + j) * 3 + 2]));
			// convert intensity of R, G, B for each pixel to intensity of grayscale 
			
			gimage[i * COL + j] = temp;
			// store the converted intensity of each pixel to the buff_R2G
		}
}

void changeto24(double gimage[], double cimage[])
{
	int i, j;
	int temp;
	
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			
			temp = int(gimage[i * COL + j]);
			cimage[(i * COL + j) * 3] = 0.114 * temp;
			cimage[(i * COL + j) * 3 + 1] = 0.587 * temp;
			cimage[(i * COL + j) * 3 + 2] = 0.299 * temp;
		}
	
	
}

void dft(int N, double real1[], double imag1[], double rx[], double ix[])
{ 
	int i,k;
	double sum_real_real, sum_real_imag, sum_imag_real, sum_imag_imag;
	
	for(k=0;k<N;k++) {
		sum_real_real = 0;
		sum_real_imag = 0;
		sum_imag_real = 0;
		sum_imag_imag = 0;
		
		for (i = 0; i < N; i++) {
			sum_real_real += rx[i] * cos(2.0*pi*k*i/N);
			sum_real_imag += -rx[i] * sin(2.0*pi*k*i/N);
			sum_imag_real += ix[i] * cos(2.0*pi*k*i/N);
			sum_imag_imag += -ix[i] * sin(2.0*pi*k*i/N);
		}
		real1[k] = sum_real_real-sum_imag_imag;
		imag1[k] = sum_real_imag+sum_imag_real;
	}
}

void dft2(double rdft2[][COL], double idft2[][COL], double r2[][COL], double i2[][COL])
{ 
	int i,j;
	for (j=0; j < COL; j++) {
		for (i=0; i < ROW; i++) {
			realx[i] = r2[i][j]; imagx[i] = i2[i][j];
		}
		dft(ROW,real_dft1,imag_dft1,realx,imagx);
		for (i=0; i < ROW; i++) {
			rdft2[i][j]=real_dft1[i]; idft2[i][j]=imag_dft1[i];
		}
	}
	
	for (i=0; i < ROW; i++) {
		for (j=0; j < COL; j++) {
			realx[j]=rdft2[i][j]; imagx[j]=idft2[i][j];
		}
		dft(COL,real_dft1,imag_dft1,realx,imagx);
		for (j=0; j < COL; j++) {
			rdft2[i][j]=real_dft1[j]; idft2[i][j]=imag_dft1[j];
		}
	}
}

void idft2(double rdft2[][COL], double idft2[][COL], double r2[][COL], double i2[][COL])
{
	int i,j;
	for (j=0; j < COL; j++) 
		for (i=0; i < ROW; i++) 
			i2[i][j] *=(-1.0); // complex conjugate
		dft2(rdft2,idft2,r2,i2);
		
	for (j=0; j < COL; j++) 
		for (i=0; i < ROW; i++) 
			idft2[i][j] *=(-1.0); // complex conjugate
			
	for (j=0; j < COL; j++) 
		for (i=0; i < ROW; i++) { 
			rdft2[i][j] = rdft2[i][j]/(ROW*COL);
			idft2[i][j] = idft2[i][j]/(ROW*COL);
		}	
}

void lowpass(double rdft2[][COL], double idft2[][COL], int th)
{
	int i,j;
	for (j=0; j < COL; j++) 
		for (i=0; i < ROW; i++) 
			if((ROW/2-i)*(ROW/2-i)+(COL/2-j)*(COL/2-j) > th*th ) 
				rdft2[i][j] = idft2[i][j] = 0;
}

void highpass(double rdft2[][COL], double idft2[][COL], int th)
{
	int i,j;
	for (j=0; j < COL; j++) 
		for (i=0; i < ROW; i++) 
			if((ROW/2-i)*(ROW/2-i)+(COL/2-j)*(COL/2-j) < th*th) 
				rdft2[i][j]= idft2[i][j] =0;
}

void erosion(unsigned char image[])
{
	unsigned char buffer[ROW*COL];
	int i,j,k,l,count;
	int str[25]= { 0, 0, 1, 0, 0, 
				   0, 1, 1, 1, 0, 
				   1, 1, 1, 1, 1,
				   0, 1, 1, 1, 0,
				   0, 0, 1, 0, 0 };
	int str_size = 5;
	int str_area = 13;
	int imgbackground = 255;
	
	for(i=0;i<ROW-str_size/2;i++)
		for(j=0;j<COL-str_size/2;j++) {
			count = 0;
			for(k= 0 ; k<str_size ; k++)
				for(l= 0 ; l<str_size ; l++)
					if(str[k*str_size+l]!=0) 
					if(image[(i+k)*COL+(j+l)]!=imgbackground) count++;
			if(count==str_area)
				buffer[(i+str_size/2)*COL+(j+str_size/2)] = 255-imgbackground;
			else 
				buffer[(i+str_size/2)*COL+(j+str_size/2)] = imgbackground;
	} 
	for(i=0;i<ROW;i++) for(j=0;j<COL;j++) image[i*COL+j] = buffer[i*COL+j];
}

void labeling(int i0, int j0, unsigned char readimage[], int background)
{
	int i,j,l,m;
	int i1, j1, num, nnum;
	long pel_count,maxarea;
	int cm[8] = { 0,-1,-1,-1, 0, 1, 1, 1 };
	int cn[8] = { 1, 1, 0,-1,-1,-1, 0, 1 };
	
	unsigned int seed_x[100000],seed_y[100000];
	unsigned int nseed_x[100000],nseed_y[100000];
	
	pel_count = 0;
	num = 1;
	buffer[i0*COL+j0] = objectct;
	seed_x[1] = i0; seed_y[1] = j0;
	
	while(num != 0) {
		for(l = 1, nnum = 0; l <= num; l++) {
			i = seed_x[l]; j = seed_y[l];
			for(m = 0; m < 8; m += 2) {
				i1 = i + cm[m]; j1 = j + cn[m];
				if((i1 >= 0) && (i1 < ROW) && (j1 >= 0) && (j1 < COL))
					if(readimage[int(i1*COL+j1)]!=background && buffer[i1*COL+j1] !=objectct) {
						pel_count++; nnum++; 
						buffer[i1*COL+j1] = objectct;
						nseed_x[nnum] = i1; nseed_y[nnum] = j1;
					}
			}
		}
		for(l = 1; l <= nnum; l++) {
			seed_x[l] = nseed_x[l];
			seed_y[l] = nseed_y[l];
		}
		num = nnum;
	}
	area[objectct]= pel_count; /* to extract the largest object */
	if(pel_count>maxarea) { 
		largestobject = objectct; maxarea = pel_count; 
	}
}



int main()
{
	char readfilename[30] = "earth_gray.bmp";
	char writefilename[30] = "testdft2020.bmp";
	char header[2048];
	int i,j,k,a,x,y,z;
	
	FILE *fpread,*fpwrite;
	fpread = fopen(readfilename,"rb");
	fpwrite = fopen(writefilename,"wb");
	
	if(fpread==NULL||fpwrite==NULL) { printf("\nFile Open Error"); return 0; }
	
	/* In case of 8 bits grayscale bmp with file size of ROW*COL*1 */
	// fread(header,1,1078,fpread); // Be careful that image has been vertically inversed
	// fread(gimage,1,ROW*COL,fpread);
	/* In case of 24 bits color bmp with file size of ROW*COL*3 */
	fread(header,1,54,fpread); // Be careful that image has been vertically inversed 
	fread(cimage,3,ROW*COL,fpread);
	changetogray(cimage,gimage);
	
	// centering
	for(i=0;i<ROW;i++) for(j=0;j<COL;j++) gimage2[i][j]=gimage[i*COL+j];
	
	for (j=0; j < COL; j++) 
		for (i=0; i < ROW; i++) {
			if((i+j)%2 != 0) real2[i][j]= (-1.0)*(double) gimage2[i][j];
			else real2[i][j]= (1.0)*(double) gimage2[i][j];
		imag2[i][j] = 0;
	}
	
	dft2(real_dft2,imag_dft2,real2,imag2);
	lowpass(real_dft2,imag_dft2,128);
	idft2(real_idft2,imag_idft2,real_dft2,imag_dft2);
	
	// Region Selection
	thresholding(gimage,0,128,0);
	erosion(gimage); 
	int background = 255;
	for(i=0;i<ROW;i++) for(j=0;j<COL;j++) buffer[i*COL+j] = 255;
	
	for(i=0;i<ROW;i++)
		for(j=0;j<COL;j++) {
			if((gimage[i*COL+j]!=background)&&buffer[i*COL+j]==255) { 
				objectct++;
				labeling(i,j,gimage,background);
			}
		}
		for(i=0;i<ROW;i++) for(j=0;j<COL;j++) { 
		if(buffer[i*COL+j] == largestobject ) gimage[i*COL+j] = 255-background; 
		else gimage[i*COL+j] = background; 
		}
	dilation(gimage);
	
	// DFT
	for (i=0; i < ROW; i++) {
		for (j=0; j < COL; j++) { 
			/* to save the results of DFT */
			temp[i][j] = sqrt(real_dft2[i][j]*real_dft2[i][j]+imag_dft2[i][j]*imag_dft2[i][j]);
			temp[i][j]/=100.0;
			/* to save the results of IDFT */
			// if((i+j)%2 != 0) temp[i][j]= (-1.0)*real_idft2[i][j];
			// else temp[i][j] = real_idft2[i][j];
			if(temp[i][j] > 255) temp[i][j] = 255;
			if(temp[i][j] < 0) temp[i][j] = 0;
			gimage2[i][j] = (unsigned char)temp[i][j];
		}
	}
	
	for(i=0;i<ROW;i++) for(j=0;j<COL;j++) gimage[i*COL+j]=gimage2[i][j];
	
	/* In case of 8 bits grayscale bmp with file size of ROW*COL*1 */
	// fwrite(header,1,1078,fpwrite);
	// fwrite(gimage,1,ROW*COL,fpwrite);
	/* In case of 24 bits color bmp with file size of ROW*COL*3 */ 
	changeto24bit(gimage,cimage); 
	fwrite(header,1,54,fpwrite);
	fwrite(cimage,3,ROW*COL,fpwrite);
	fclose(fpread);
	fclose(fpwrite);
	return 0;
	}
