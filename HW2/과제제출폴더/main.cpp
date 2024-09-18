#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
void template_matching();
int main()
{
	template_matching();

	return 0;
}

void template_matching()
{
	Mat img = imread("3-a_binary.bmp", IMREAD_COLOR);
	Mat templ1 = imread("1-a_binary-1.bmp", IMREAD_COLOR);
	Mat templ2 = imread("2-a_binary-1.bmp", IMREAD_COLOR);
	Mat templ3 = imread("3-a_binary-1.bmp", IMREAD_COLOR);

	if (img.empty() || templ1.empty() || templ2.empty() || templ3.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}


	/* templ을 scaling & rotate시키는 코드
	double scale = 0.5;
	while ( scale < 1.5 ) { // templ을 scaling 시키는 코드
		
		// templ을 rotate시키는 코드
		for (int angle = 0; angle < 360; angle += 10) {
		
		}
		scale += 0.1
	}
	*/

	img = img + Scalar(50, 50, 50);
	Mat res, res_norm;
	// img가 templ1과 얼마나 겹치는지 확인
	matchTemplate(img, templ1, res, TM_CCOEFF_NORMED);
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);
	double maxv1;
	Point maxloc;
	minMaxLoc(res, 0, &maxv1, 0, &maxloc);
	cout << "maxv1: " << maxv1 << endl;

	// img가 templ2와 얼마나 겹치는지 확인
	matchTemplate(img, templ2, res, TM_CCOEFF_NORMED);
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);
	double maxv2;
	minMaxLoc(res, 0, &maxv2, 0, &maxloc);
	cout << "maxv2: " << maxv2 << endl;

	// img가 templ3과 얼마나 겹치는지 확인
	matchTemplate(img, templ3, res, TM_CCOEFF_NORMED);
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);
	double maxv3;
	minMaxLoc(res, 0, &maxv3, 0, &maxloc);
	cout << "maxv3: " << maxv3 << endl;

	if (maxv1 >= 0.9) cout << endl << "This is 1" << endl;
	if (maxv2 >= 0.9) cout << endl << "This is 2" << endl;
	if (maxv3 >= 0.9) cout << endl << "This is 3" << endl;

	waitKey();
	destroyAllWindows();

}