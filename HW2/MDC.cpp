#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

void averagepattern(double ap[], double p[][3])
{
	int i,j;
	for(j=0;j<3;j++) {
		ap[j]=0.0;
		for(i=0;i<5;i++)
		 	ap[j] += p[i][j]/5.0;
	}
}

double getdistance(double a[], double b[])
{
	return sqrt((a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1])+(a[2]-b[2])*(a[2]-b[2]));
}

int main()
{
	int i;
	double dn,dab;
	double normalpattern[5][3],abnormalpattern[5][3],casepattern[3][3];
	double averagenormalpattern[3],averageabnormalpattern[3];
	double decision[3];
	
	ifstream ifile("pattern.txt");
	ofstream ofile("out.txt");
	
	if(!ifile.is_open() || !ofile.is_open() ) { cout << " File Open Error "; exit(1); }
	
	for(i=0;!ifile.eof();i++) {
		for(i=0;i<5;i++) {
			ifile >> normalpattern[i][0] >> normalpattern[i][1] >> normalpattern[i][2];
		}
	
	for(i=0;i<5;i++) {
		ifile >> abnormalpattern[i][0] >> abnormalpattern[i][1] >> abnormalpattern[i][2];
	}
	
	for(i=0;i<3;i++) {
		ifile >> casepattern[i][0] >> casepattern[i][1] >> casepattern[i][2];
	}
	
	averagepattern(averagenormalpattern,normalpattern);
	averagepattern(averageabnormalpattern,abnormalpattern);
	
	for(i=0;i<3;i++) {
		dn = getdistance(averagenormalpattern,casepattern[i]);
		dab = getdistance(averageabnormalpattern,casepattern[i]);
		
		if(dn>dab) decision[i] = 1;
		else decision[i] = 0;
		
		ofile <<"Decision " << decision[i] << endl;
	}
	
	ifile.close();
	ofile.close();
	return 1;
	}
}
