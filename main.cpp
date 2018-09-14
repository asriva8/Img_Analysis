#include <stdio.h>
#include <opencv2/opencv.hpp>
# include <vector>
# include "ImgAnalysis.h"

using namespace cv;

// Following method of enum for switch case is borrowed from https://stackoverflow.com/questions/3019153/how-do-i-use-an-enum-value-on-a-switch-statement-in-c
enum Operation
{
  EXIT = 0,
  FIND_REGION = 1, 
  FIND_PERIMETER = 2, 
  DISPLAY_IMAGE = 3,
  DISPLAY_PIXELS = 4,
  SAVE_PIXELS = 5,
  FIND_SMOOTH_PERIMETER = 6,
  DISPLAY_SMOOTH_PIXELS = 7,
  SAVE_SMOOTH_PIXELS = 8
};




int print_message()
{ int operation;
  std::cout<<"\n\nChoose one of the following operations to perform"<<std::endl<<std::endl;
  std::cout<< "EXIT			-> 0"<<std::endl;
  std::cout<< "FIND_REGION		-> 1"<<std::endl;
  std::cout<< "FIND_PERIMETER		-> 2"<<std::endl;
  std::cout<< "DISPLAY_INPUT_IMAGE	-> 3"<<std::endl;
  std::cout<< "DISPLAY_PIXELS		-> 4"<<std::endl;
  std::cout<< "SAVE_PIXELS		-> 5"<<std::endl;
  std::cout<< "FIND_SMOOTH_PERIMETER	-> 6"<<std::endl;
  std::cout<< "DISPLAY_SMOOTH_PIXELS	-> 7"<<std::endl;
  std::cout<< "SAVE_SMOOTH_PIXELS	-> 8"<<std::endl;
  std::cout<<std::endl;

  std::cin>>operation;
  return operation;
}


void zero_mat (cv::Mat & mat)
{

	int nRows =  mat.rows;
	int nCols =  mat.cols;
	int i,j;
	uchar *p;
	for (i = 0; i < nRows; ++i) {
		p = mat.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j) {
			p[j] = 0;
		}
	}

}


int main(int argc, char **argv) {


	if (argc != 2) {
	printf("usage: Opencv_Test <Image_Path> <Output_Path>\n");
	return -1;
	}

	Mat image;

	image = imread(argv[1], 1);
	if (!image.data) {
		printf("No image data (warning: OpenCV recognize files by extensions)\n");
		return -1;
	}


	int nRows =  image.rows;
	int nCols =  image.cols;
	int i,j;
	Mat Filled_Image(nRows, nCols, CV_8UC1);
	zero_mat(Filled_Image);
	Mat border_img(nRows, nCols, CV_8UC1);
	zero_mat(border_img);
	Mat Filled_Image_smooth(nRows, nCols, CV_8UC1);
	zero_mat(Filled_Image_smooth);
	Mat border_img_smooth(nRows, nCols, CV_8UC1);
	zero_mat(border_img_smooth);

	std::vector<Point> border;


	Image_Analysis Image(image);
	int similarity_param =0;
	int XPixel = 0;
	int YPixel = 0;
	std::string s_region, s_border;

	int operation = print_message();

	while (operation!=EXIT)
	{
	   switch(operation)
	   {
  		case EXIT:
    		std::cout << "Exiting!\n";
    		break;
  		case FIND_REGION:
    		std::cout << "Finding Region\n";
		std::cout<<"Please enter the similarity parameter (greater than 0 and less than 255 (around 30)) = \n";
		std::cin>> similarity_param;
		std::cout<<"Please enter X index of the pixel (greater equal than 0 and less than "<<nRows<<") = \n";
		std::cin>> XPixel;
		std::cout<<"Please enter Y index of the pixel (greater equal than 0 and less than "<<nCols<<") = \n";
		std::cin>> YPixel;
		zero_mat(Filled_Image);
		Image.Find_Region(Filled_Image, XPixel, YPixel, similarity_param);
    		break;
  		case FIND_PERIMETER:
    		std::cout << "Finding Perimeter\n";
		zero_mat(border_img);
		Image.Find_Perimeter(Filled_Image, border_img, border);
    		break;
  		case DISPLAY_IMAGE:
    		std::cout << "Displaying Image\n";
		Image.Display_Image ("Input");
    		break;
  		case DISPLAY_PIXELS:
    		std::cout << "Displaying Pixels\n";
		Image.Display_Pixels(Filled_Image, border_img, "filled_region", "border_region");
    		break;
  		case SAVE_PIXELS:
		std::cout<<"Name of the output region-filled image with extension? \n";
		std::cin>>s_region;
		std::cout<<"Name of the output image showing border of the image with extension? \n";
		std::cin>>s_border;
    		std::cout << "Saving Pixels\n";
		imwrite(s_region, Filled_Image);
		imwrite(s_border, border_img);
		//Image.Save_Pixels(Filled_Image, border_img);
		break;
  		case FIND_SMOOTH_PERIMETER:
    		std::cout << "Finding Smooth Perimeter\n";
		Filled_Image_smooth = Filled_Image;
		zero_mat(border_img_smooth);
		Image.Find_Smooth_Perimeter(Filled_Image_smooth, border_img_smooth, border);
    		break;
		case DISPLAY_SMOOTH_PIXELS:
    		std::cout << "Displaying Pixels\n";
		Image.Display_Pixels(Filled_Image_smooth, border_img_smooth,"filled_region_smooth", "border_region_smooth");
    		break;
  		case SAVE_SMOOTH_PIXELS:
		std::cout<<"Name of the output smooth region-filled image with extension? \n";
		std::cin>>s_region;
		std::cout<<"Name of the output image showing smooth border of the image with extension? \n";
		std::cin>>s_border;
    		std::cout << "Saving Pixels\n";
		imwrite(s_region, Filled_Image_smooth);
		imwrite(s_border, border_img_smooth);
		break;
  		default:
    		std::cout << "Invalid Selection\n";    		
	   }
	   operation = print_message();
	}


	return 0;
}



