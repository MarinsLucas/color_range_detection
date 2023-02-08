#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;
using namespace std; 

//BGR2HSV
//BGR2LAB

Mat src;
char window_name[4] = "aaa";
static void onMouse(int event, int x, int y, int f, void* )
{
	Mat image = src.clone();
	Vec3b rgb = image.at<Vec3b>(y,x);

	Mat Lab;
	Mat RGB=image(Rect(x,y,1, 1));
	cvtColor(RGB, Lab, COLOR_BGR2Lab); 

	Vec3b hsv = Lab.at<Vec3b>(0, 0);
	int B = hsv.val[0];
	int G = hsv.val[1];
	int R = hsv.val[2];

	Mat HSV;
	cvtColor(RGB, HSV, COLOR_BGR2HSV); 

    hsv = HSV.at<Vec3b>(0, 0);
	int H = hsv.val[0];
	int S = hsv.val[1];
	int V = hsv.val[2];

	char name[30];
	sprintf(name, "B=%d", B);
	putText(image, name, Point(150, 40), FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 2, 8, false);
	sprintf(name, "G=%d", G);
	putText(image, name, Point(250, 40), FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 2, 8, false);
	sprintf(name, "R=%d", R);
	putText(image, name, Point(350, 40), FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 2, 8, false);
	sprintf(name, "H=%d", H);
	putText(image, name, Point(450, 40), FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 2, 8, false);
	sprintf(name, "S=%d", S);
	putText(image, name, Point(550, 40), FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 2, 8, false);
	sprintf(name, "V=%d", V);
	putText(image, name, Point(650, 40), FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 2, 8, false);
	
	imshow(window_name, image);
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		printf("usage: DisplayImage.out <Image_Path>\n");
		return -1;
	}
	
	src = imread(argv[1], 1);
	if (!src.data) {
		printf("No image data \n");
		return -1;
	}

	namedWindow(window_name, WINDOW_AUTOSIZE);
	imshow(window_name, src);
	setMouseCallback(window_name, onMouse, 0);
	waitKey(0);
	return 0;
}
