#include <stdio.h>
#include <opencv2/opencv.hpp>
# include <vector>
# include "ImgAnalysis.h"
# include <fstream>

#define PI 3.141592653

using namespace cv;

Image_Analysis::Image_Analysis(cv::Mat &img)
{
	image = img;

}

int Image_Analysis::Display_Image(std::string const &win_name)
{
	if (!image.data) {
		printf("Image is not yet loaded)\n");
		return -1;
	}	
	
	namedWindow(win_name, WINDOW_AUTOSIZE);
	imshow(win_name, image);
	waitKey(0);
return 0;
}

int Image_Analysis::Display_Pixels(cv::Mat &filled_image, cv::Mat &border_image, std::string const &win_name1, std::string const &win_name2)
{
	if ((!filled_image.data)||(!border_image.data)) {
		printf("No image data)\n");
		return -1;
	}	
	int nRows =  filled_image.rows;
	int nCols =  filled_image.cols;
	Mat filled_img_colored(nRows, nCols, CV_8UC3);
	Mat border_img_colored(nRows, nCols, CV_8UC3);
	int i,j;
	for (i = 0; i < nRows; ++i) {
		for (j = 0; j < nCols; ++j)
		{	
			filled_img_colored.ptr<Vec3b>(i)[j][0]=filled_image.ptr<uchar>(i)[j];
			filled_img_colored.ptr<Vec3b>(i)[j][1]=0;
			filled_img_colored.ptr<Vec3b>(i)[j][2]=0;
			border_img_colored.ptr<Vec3b>(i)[j][0]=border_image.ptr<uchar>(i)[j];
			border_img_colored.ptr<Vec3b>(i)[j][1]=0;
			border_img_colored.ptr<Vec3b>(i)[j][2]=0;
		}
	}

	
	
	namedWindow(win_name1, WINDOW_AUTOSIZE);
	imshow(win_name1, filled_img_colored);
	//waitKey(0);
	namedWindow(win_name2, WINDOW_AUTOSIZE);
	imshow(win_name2, border_img_colored);
	waitKey(0);
return 0;
}

void Image_Analysis::Find_Region (cv::Mat &dest, int x, int y, int similarity_param)
{
	
	
	int nRows = image.rows;
	int nCols = image.cols;
	//uchar *p = 
//std:: cout<<"x = "<< x<<"  y = "<<y<< std::endl;
	// Checking the right neighbourhood;
	if(y < nCols-1)
	{
		if (dest.ptr<uchar>(x)[y+1]==0)
		{
			if ((abs(image.ptr<Vec3b>(x)[y][0]- image.ptr<Vec3b>(x)[y+1][0])<=similarity_param) && (abs(image.ptr<Vec3b>(x)[y][1]- image.ptr<Vec3b>(x)[y+1][1])<=similarity_param) && (abs(image.ptr<Vec3b>(x)[y][2]- image.ptr<Vec3b>(x)[y+1][2])<=similarity_param) )
			{
				dest.ptr<uchar>(x)[y+1] = 255;
				Find_Region(dest, x, y+1, similarity_param);
			}
		}
	}

	// Checking the top neighbourhood;
	if (x>0)
	{
		if (dest.ptr<uchar>(x-1)[y] == 0)
		{
			if ((abs(image.ptr<Vec3b>(x)[y][0]- image.ptr<Vec3b>(x-1)[y][0])<=similarity_param) && (abs(image.ptr<Vec3b>(x)[y][1]- image.ptr<Vec3b>(x-1)[y][1])<=similarity_param) && (abs(image.ptr<Vec3b>(x)[y][2]- image.ptr<Vec3b>(x-1)[y][2])<=similarity_param) )
			{
				dest.ptr<uchar>(x-1)[y] = 255;
				Find_Region(dest, x-1, y, similarity_param);
			}
		}
	}

	// Checking the left neighbourhood;
	if (y>0)
	{
		if (dest.ptr<uchar>(x)[y-1] ==0)
		{
			if ((abs(image.ptr<Vec3b>(x)[y][0]- image.ptr<Vec3b>(x)[y-1][0])<=similarity_param) && (abs(image.ptr<Vec3b>(x)[y][1]- image.ptr<Vec3b>(x)[y-1][1])<=similarity_param) && (abs(image.ptr<Vec3b>(x)[y][2]- image.ptr<Vec3b>(x)[y-1][2])<=similarity_param) )
			{
				dest.ptr<uchar>(x)[y-1] = 255;
				Find_Region(dest, x, y-1, similarity_param);
			}
		}
	}

	// Checking the bottom neighbourhood;
	if (x<nRows-1)
	{
		if(dest.ptr<uchar>(x+1)[y] == 0)
		{
			if ((abs(image.ptr<Vec3b>(x)[y][0]- image.ptr<Vec3b>(x+1)[y][0])<=similarity_param) && (abs(image.ptr<Vec3b>(x)[y][1]- image.ptr<Vec3b>(x+1)[y][1])<=similarity_param) && (abs(image.ptr<Vec3b>(x)[y][2]- image.ptr<Vec3b>(x+1)[y][2])<=similarity_param) )
			{
				dest.ptr<uchar>(x+1)[y] = 255;
				Find_Region(dest, x+1, y, similarity_param);
			}
		}



	}
return;
}


void Image_Analysis::Find_Perimeter (cv::Mat &src, cv::Mat &dest, std::vector<Point> &border)
{
	
	// Making all elements of the destination matrix zero. Only border pixels will be set to 255.
	std::cout<<dest.size()<<"\n";
	border.clear();
	int nRows =  src.rows;
	int nCols =  src.cols;
	int i,j;
	char s_border_txt[20];
	std::ofstream borderFile;
	std::cout<<"Name of the text file to store border pixels in (should be less than 20 characters including extension)? \n";
	std::cin>>s_border_txt;
	borderFile.open(s_border_txt);
	borderFile << "BorderPoints [x,y]:\n";
	
	//uchar *ps;
	uchar p1,p2,p3,p4,p5,p6,p7,p8;
	for (i = 0; i < nRows; ++i) {
		for (j = 0; j < nCols; ++j) 
		{ //std::cout<<(int)ps[j]<<""; 
			if (src.ptr<uchar>(i)[j] == 255)
			{//std::cout<<"counter ="<<counter<<"  ";counter++;
				if((i==0)||(i==nRows-1)||(j==0)||(j==nCols-1))
				{ 
					dest.ptr<uchar>(i)[j]=255;
					borderFile << Point(i,j)<<"\n";
					border.push_back(Point(i,j));	
				}
				else
				{  // Check all 8 neighborhoods of the pixel if they have any black pixels.
					p1 = src.ptr<uchar>(i-1)[j-1];
					p2 = src.ptr<uchar>(i-1)[j];
					p3 = src.ptr<uchar>(i-1)[j+1];
					p4 = src.ptr<uchar>(i)[j-1];
					p5 = src.ptr<uchar>(i)[j+1];
					p6 = src.ptr<uchar>(i+1)[j-1];
					p7 = src.ptr<uchar>(i+1)[j];
					p8 = src.ptr<uchar>(i+1)[j+1];

					if((p1==0)||(p2==0)||(p3==0)||(p4==0)||(p5==0)||(p6==0)||(p7==0)||(p8==0))
					{dest.ptr<uchar>(i)[j]=255;
					borderFile << Point(i,j)<<"\n";
					border.push_back(Point(i,j));
					}
				}
			}
		}
	}

	borderFile.close();
	

}



void Image_Analysis::Find_Smooth_Perimeter (cv::Mat &src, cv::Mat &dest, std::vector<Point> &border)
{
	

	int n=0;
	std::cout<<"Enter the size of Gaussian Kernel (should be an odd number)\n";
	std::cin>>n;
	while (!(n%2==1))
	{
		std::cout<<"Invalid!\n";
		std::cout<<"Please enter the size of Gaussian Kernel (should be an odd number)\n";
		std::cin>>n;
	}
	std::cout<<"Enter the value of sigma (std deviation) for Gaussian Kernel\n";
	double sigma;
	std::cin>> sigma;
	cv::Mat kernel(n,n,CV_64FC1);
	createGaussianKernel (kernel, sigma);
//	std::cout<<"Kernel = "<< kernel<<std::endl;
	Mat filteredImg(src);
	filterImage(src, filteredImg,kernel);
	namedWindow("Filtered_Image", WINDOW_AUTOSIZE);
	imshow("Filtered_Image", filteredImg);
	waitKey(0);
	thresholdImage(filteredImg);
	std::cout<<"size of dest before calling find_perimeter"<<dest.size()<<"\n";
	Find_Perimeter (filteredImg, dest, border);
	std::cout<<"size of dest after calling find_perimeter"<<dest.size()<<"\n";
}



void Image_Analysis::createGaussianKernel (cv:: Mat &kernel, double sigma)
{
	int height = kernel.rows;
	int width = kernel.cols;
	int i,j;
	double *p;
	double sum = 0;
	for (i=0; i<height; ++i)
	{
		p = kernel.ptr<double>(i);
		for (j = 0; j<width; ++j)
		{
			p[j] = exp(-(i*i+j*j)/(2*sigma*sigma))/(2*sigma*sigma*PI);
			sum+=p[j];
		}
	}

		for (i=0; i<height; ++i)
	{
		p = kernel.ptr<double>(i);
		for (j = 0; j<width; ++j)
		{
			p[j] /= sum;
		}
	}

}


void Image_Analysis::filterImage (cv::Mat &src, cv::Mat &dst, cv:: Mat &kernel)
{
	int kernelheight = kernel.rows;
	int kernelwidth = kernel.cols;
	int xOffset = (kernelheight-1)/2;
	int yOffset = (kernelwidth-1)/2;

	int nRows = src.rows;
	int nCols =  src.cols;

	int i,j,k,l;
	double temp;
	for (i= xOffset; i< (nRows-xOffset); ++i)
	{
		//pi = src.ptr<uchar>(i)[2];
		for (j = yOffset; j<(nCols-yOffset); ++j)
		{
			temp = 0;
			for (k = -xOffset; k<= xOffset; ++k)
			{
				//pk = kernel.ptr<double>(k);
				for (l = -yOffset; l<= yOffset; ++l)
				{
					temp += src.ptr<uchar>(i+k)[j+l]*kernel.ptr<double>(k+xOffset)[l+yOffset];
				}
				
			}
			dst.ptr<uchar>(i)[j] = (uchar)temp;
		}
	}
}

void Image_Analysis::thresholdImage (cv::Mat &mat)
{
	int thresh;
	std::cout<<"Enter thresholding parameter (between 0 and 255)\n";
	std::cin>>thresh;
	int nRows = mat.rows;
	int nCols =  mat.cols;

	int i,j;
	double temp;
	uchar *p;
	for (i= 0; i< nRows; ++i)
	{
		p = mat.ptr<uchar>(i);
		for (j = 0; j<nCols; ++j)
		{
			if (p[j]<=(uchar)thresh)
			{
				p[j]=0;
			}
			else 
			{
				p[j]=255;
			}
		}
	}

}


