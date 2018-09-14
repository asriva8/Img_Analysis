#include <stdio.h>
#include <opencv2/opencv.hpp>
# include <vector>

using namespace cv;


class Image_Analysis
{ public:
	
	Image_Analysis (cv::Mat &img);
	int Display_Image(std::string const &win_name);
	int Display_Pixels(cv::Mat &filled_image, cv::Mat &border_image, std::string const &win_name1, std::string const &win_name2);
	void Find_Region (cv::Mat &dest, int x, int y, int similarity_param);
	void Find_Perimeter (cv::Mat &src, cv::Mat &dest, std::vector<Point> &border);
	void Find_Smooth_Perimeter (cv::Mat &src, cv::Mat &dest, std::vector<Point> &border);
	void createGaussianKernel (cv:: Mat &kernel, double sigma);
	void filterImage (cv::Mat &src, cv::Mat &dst, cv:: Mat &kernel);
	void thresholdImage (cv::Mat &mat);


  private:
	
	Mat image;

};


