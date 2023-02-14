#include <opencv2/opencv.hpp>
#include <stdio.h>
#include<vector>
using namespace cv;
using namespace std; 

//BGR2HSV
//BGR2LAB

#define HSV_ 0
#define LAB_ 1

#define piracicaba 2

Mat src;
char window_name[4] = "aaa";
int B, A, L, H, S, V;
int color_space;

static void onMouse(int event, int x, int y, int f, void* vet)
{
	vector<Vec3b>* vet_colors = (vector<Vec3b>*) vet;
	Mat image = src.clone();
	Vec3b rgb; 
	Mat Lab;
	Mat RGB; 
	Vec3b hsv;
	Vec3b lab;
	Mat HSV;

	if(event == EVENT_LBUTTONDOWN)
	{
		rgb = image.at<Vec3b>(y,x);

		RGB=image(Rect(x,y,1, 1));

		if(color_space == LAB_)
		{
			cvtColor(RGB, Lab, COLOR_BGR2Lab); 
			lab = Lab.at<Vec3b>(0, 0);
			L = lab.val[0];
			A = lab.val[1];
			B = lab.val[2];
			vet_colors->push_back(lab);
		}
		if(color_space == HSV_)
		{
			cvtColor(RGB, HSV, COLOR_BGR2HSV); 
			hsv = HSV.at<Vec3b>(0, 0);
			H = hsv.val[0];
			S = hsv.val[1];
			V = hsv.val[2];
			vet_colors->push_back(hsv);
		}
                           
	}

	if(event == EVENT_RBUTTONDOWN)
	{
		int max_[3];
		int min_[3];
		int min = 0;
		int max = 256; 
		if(color_space == HSV_)
		{
			cout<<"HSV Colors: "<<endl;
			for(int i = 0; i<vet_colors->size(); i++)
			{
				cout<<vet_colors->at(i)<<" ";
			}
			cout<<endl;
			cout<<"Range HSV colors"<<endl;
			for(int j = 0; j<3; j++)
			{
				min = 256; max = -1;
				for(int i = 0; i<vet_colors->size(); i++)
				{
					if(vet_colors->at(i).val[j] < min)
					{
						min = vet_colors->at(i).val[j];
					}

					if(vet_colors->at(i).val[j] > max)
					{
						max = vet_colors->at(i).val[j];
					}
				}

				cout<<j<<" - max: " << max << " min: " <<min<<endl;
				max_[j] = max;
				min_[j] = min;
			}
		}

		else if(color_space == LAB_)
		{
			cout<<endl<<"Lab Colors: "<<endl;
			for(int i = 0; i<vet_colors->size(); i++)
			{
				cout<<vet_colors->at(i)<<" ";
			}
			cout<<endl; 

			cout<<"Range Lab colors"<<endl;
			for(int j = 0; j<3; j++)
			{
				min = 256; max = -1;
				for(int i = 0; i<vet_colors->size(); i++)
				{
					if(vet_colors->at(i).val[j] < min)
					{
						min = vet_colors->at(i).val[j];
					}

					if(vet_colors->at(i).val[j] > max)
					{
						max = vet_colors->at(i).val[j];
					}
				}

				cout<<j<<" - max: " << max << " min: " <<min<<endl;
				max_[j] = max;
				min_[j] = min;
			}
		}

		Mat nimage;
		cvtColor(image, nimage, COLOR_BGR2Lab);
		// image = src.clone(); 

		for(int i = 0; i<nimage.cols; i++)
		{
			for(int j =0; j<nimage.rows; j++)
			{
					Vec3b col = nimage.at<Vec3b>(j, i);

					if(col.val[0] < min_[0] - piracicaba || col.val[0] > max_[0] + piracicaba)
					{
						nimage.at<Vec3b>(j,i).val[0] = 0;
						nimage.at<Vec3b>(j,i).val[1] = 0;
						nimage.at<Vec3b>(j,i).val[2] = 0;
					}
					if(col.val[1]< min_[1] - piracicaba || col.val[1] > max_[1] + piracicaba)
					{
						nimage.at<Vec3b>(j,i).val[0] = 0;
						nimage.at<Vec3b>(j,i).val[1] = 0;
						nimage.at<Vec3b>(j,i).val[2] = 0;

					}
					if(col.val[2] < min_[2] - piracicaba|| col.val[2] > max_[2]+ piracicaba)
					{
						nimage.at<Vec3b>(j,i).val[0] = 0;
						nimage.at<Vec3b>(j,i).val[1] = 0;
						nimage.at<Vec3b>(j,i).val[2] = 0;
					}

			}
		}

		cvtColor(nimage, image, COLOR_Lab2BGR);
		src = image.clone();
	}

	char name[30];
	sprintf(name, "L=%d", L);
	putText(image, name, Point(150, 40), FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 2, 8, false);
	sprintf(name, "a=%d", A);
	putText(image, name, Point(250, 40), FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 2, 8, false);
	sprintf(name, "b=%d", B);
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
	color_space = LAB_; 
	vector<Vec3b> vet_colors;
	setMouseCallback(window_name, onMouse, (void*)&vet_colors);
	waitKey(0);

	imshow(window_name, src);
	waitKey(0);

	return 0;
}
