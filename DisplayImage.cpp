#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <fstream> 
#include<vector>
using namespace cv;
using namespace std; 

//BGR2HSV
//BGR2LAB

#define HSV_ 1
#define LAB_ 0

Mat rawFrame;
VideoCapture cap; 
int B, A, L, H, S, V; //aux variables
string current_color_name;
string* possibilities = {"Amarelo", "Verde", "Azul", "Ciano", "Laranja", "Rosa", "Marrom", "Vermelho", "Roxo", "ColorEnemy1", "ColorEnemy2", "ColorEnemy3"};

void writeFile(int* min, int* max, int cs, int c)
{
  string straux; 
  fstream file.open("../RinobotSystem/config/colors");
  int index = -1;
  while(!file.eof())
    {
      getline(file, straux);
      if(straux.size() > 4)
      {
        index++;
      }
      if(straux == current_color_name)
      {
        file<<min[0]<<endl<<max[0]<<endl<<min[1]<<endl<<max[1]<<endl<<min[2]<<endl<<max[2];
      }
    }
  file.close();

  fstream color_space_file.open("../RinobotSystem/config/typeColors");
  for(int i =0; i<index; i++)
    {
      getline(color_space_file, straux);
    }
  color_space_file<<cs;
  color_space_file.close();
}

static void onMouseHSV(int event, int x, int y, int f, void* vet)
{
	vector<Vec3b>* vet_colors = (vector<Vec3b>*) vet;
  Mat HSVmat;
  Mat RBGmat;
  Vec3b hsv3b;

  if(event == EVENT_LBUTTONDOWN)
  {
		RGB=rawFrame(Rect(x,y,1, 1));
    cvtColor(RGB, HSVmat, COLOR_BGR2HSV); 
    hsv3b = HSVmat.at<Vec3b>(0, 0);
    H = hsv3b.val[0];
    S = hsv3b.val[1];
    V = hsv3b.val[2];
    vet_colors->push_back(hsv3b);
  }

  if(event == EVENT_RBUTTONDOWN)
	{
    int max_[3];
		int min_[3];
		int min = 0;
		int max = 256; 

    //Debug
    /*cout<<"HSV Colors: "<<endl;
    for(int i = 0; i<vet_colors->size(); i++)
    {
      cout<<vet_colors->at(i)<<" ";
    }
    cout<<endl;*/
    
    //cout<<"Range HSV colors"<<endl;
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

      //cout<<j<<" - max: " << max << " min: " <<min<<endl;
      max_[j] = max;
      min_[j] = min;
  } 
  //end debug

  writeFile(min, max, HSV_, 3);
    
  Mat nimage;
  cvtColor(rawFrame, nimage, COLOR_BGR2HSV);

  for(int i = 0; i<nimage.cols; i++)
  {
    for(int j =0; j<nimage.rows; j++)
    {
        Vec3b col = nimage.at<Vec3b>(j, i);

        if(col.val[0] < min_[0] || col.val[0] > max_[0])
        {
          nimage.at<Vec3b>(j,i).val[0] = 0;
          nimage.at<Vec3b>(j,i).val[1] = 0;
          nimage.at<Vec3b>(j,i).val[2] = 0;
        }
        if(col.val[1]< min_[1] || col.val[1] > max_[1])
        {
          nimage.at<Vec3b>(j,i).val[0] = 0;
          nimage.at<Vec3b>(j,i).val[1] = 0;
          nimage.at<Vec3b>(j,i).val[2] = 0;

        }
        if(col.val[2] < min_[2]|| col.val[2] > max_[2)
        {
          nimage.at<Vec3b>(j,i).val[0] = 0;
          nimage.at<Vec3b>(j,i).val[1] = 0;
          nimage.at<Vec3b>(j,i).val[2] = 0;
        }

    }
  }
  imshow(window_name, nimage);

}
  else
  {
    imshow(window_name, rawFrame);
  }
  
}

static void onMouseLab(int event, int x, int y, int f, void* vet)
{
  vector<Vec3b>* vet_colors = (vector<Vec3b>*) vet;
  Mat LAB;
  Mat RGB;
  Vec3b lab3b;

  if(event == EVENT_LBUTTONDOWN)
  {
		RGB=rawFrame(Rect(x,y,1, 1));
    cvtColor(RGB, Lab, COLOR_BGR2Lab); 
    lab3b = Lab.at<Vec3b>(0, 0);
    L = lab3b.val[0];
    A = lab3b.val[1];
    B = lab3b.val[2];
    vet_colors->push_back(lab3b);
  }

  if(event == EVENT_RBUTTONDOWN)
	{
    int max_[3];
		int min_[3];
		int min = 0;
		int max = 256; 

    //Debug
    /*cout<<"Lab Colors: "<<endl;
    for(int i = 0; i<vet_colors->size(); i++)
    {
      cout<<vet_colors->at(i)<<" ";
    }
    cout<<endl;*/
    
    //cout<<"Range Lab colors"<<endl;
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

      //cout<<j<<" - max: " << max << " min: " <<min<<endl;
      max_[j] = max;
      min_[j] = min;
  } 
  //end debug

  writeFile(min, max, LAB_, 3);

  Mat nimage;
  cvtColor(rawFrame, nimage, COLOR_BGR2Lab);

  for(int i = 0; i<nimage.cols; i++)
  {
    for(int j =0; j<nimage.rows; j++)
    {
        Vec3b col = nimage.at<Vec3b>(j, i);

        if(col.val[0] < min_[0] || col.val[0] > max_[0])
        {
          nimage.at<Vec3b>(j,i).val[0] = 0;
          nimage.at<Vec3b>(j,i).val[1] = 0;
          nimage.at<Vec3b>(j,i).val[2] = 0;
        }
        if(col.val[1]< min_[1] || col.val[1] > max_[1])
        {
          nimage.at<Vec3b>(j,i).val[0] = 0;
          nimage.at<Vec3b>(j,i).val[1] = 0;
          nimage.at<Vec3b>(j,i).val[2] = 0;

        }
        if(col.val[2] < min_[2]|| col.val[2] > max_[2)
        {
          nimage.at<Vec3b>(j,i).val[0] = 0;
          nimage.at<Vec3b>(j,i).val[1] = 0;
          nimage.at<Vec3b>(j,i).val[2] = 0;
        }

    }
  }
  imshow(window_name, nimage);

}
  else
  {
    imshow(window_name, rawFrame);
  }
  
}

void updateRawFrame()
{
    if( cap.isOpened() )
    {

        // se a câmera ta aberta
        cap.read(rawFrame);

        //cout << "Got the frame" << endl;

    }else
    {
        // se a câmera não ta aberta
        cout << "Unable to get the frame" << endl;
    }



}

void openCamera()
{
    int id = getCameraId();

    cap.open(id);
    cap.set(3,640);
    cap.set(4,480);
    if( cap.isOpened() )
    {
        // abriu a câmera
        cout << "Camera opened succefully" << endl;

    }else
    {
        // não conseguiu abrir a câmera
        cout << "Unable to open the camera" << endl;
    }
    //CAMERA NOVA
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G') );
    //CAMERA NOVA
}

void closeCamera()
{
    cap.release();

    if( cap.isOpened() )
    {
        // abriu a câmera
        cout << "Unable to close the camera" << endl;

    }else
    {
        // não conseguiu abrir a câmera
        cout << "Camera closed succefully" << endl;
    }
}

int main(int argc, char** argv)
{
  char window_name[18] = "Color calibration";
  int color_space;
  if(argc == 1)
  {
    cout<<"[ERROR]: Color space not informed:"<<endl;
    cout<<"$ ./color_calibration.exe --<color_space_value>"<<endl;
    return 0;
  }
  //Flag do espaço de cor 
  if((string)argv[1] == "--lab")
  {
    cout<<"Color space selected: Lab"<<endl;
    color_space = LAB_;
  }else if((string)argv[1] == "--hsv3b")
  {
    cout<<"Color space selected: HSV"<<endl;
    color_space = HSV_;
  }else
  {
    cout<<"[ERROR]: Color space not informed:"<<endl;
    cout<<"$ ./color_calibration.exe --<color_space_value>"<<endl;
    return 0;
  }

  openCamera();
  namedWindow(window_name, WINDOW_AUTOSIZE);
	vector<Vec3b> vet_colors;
  bool gettingColors = true;
  
  while(gettingColors)
  {
    cout<<"Digite a cor: Amarelo, Ciano, Rosa, Verde, Azul, Laranja, Roxo, Marrom, Vermelho, ColorEnemy1, ColorEnemy2, ColorEnemy3"<<endl;
    cin>>current_color_name;

    gettingColors = false;
    for(int i = 0; i<possibilities.size(); i++)
    {
      if(current_color_name == possibilities[i])
      {
        gettingColors = true;
        break;
      }
    }

    if(gettingColors == false)
      cout<<"Nome da cor inválida: fim do programa"<<endl;
    
   while(gettingColors)
    {
        updateRawFrame();
        for(auto it=vet_colors.begin() ; it != vet_colors.end() ; ++it) //every frame it draw the points clickeds in the image
        {
            circle(rawFrame, *it, 0.1, Scalar(0,0,255), 2);
        }

        imshow(window_name, rawFrame);
        setMouseCallback(window_name, color_space == HSV_ ? onMouseHSV : onMouseLab , (void*)&points);
      
        if((waitKey(1) == 27)
        {
            break;
        }
    }
  destroyWindow(window_name);
  
  }

  closeCamera();
	return 0;
}
