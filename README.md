## Analysis of objects in an image through flood-fill algorithm



### CLASS IMAGE_ANALYSIS

class Image_Analysis
{ public:
	
	Image_Analysis (cv::Mat &img);   // constructor
	int Display_Image(std::string const &win_name);
	int Display_Pixels(cv::Mat &filled_image, cv::Mat &border_image);
	void Find_Region (cv::Mat &dest, int x, int y, int similarity_param);
	void Find_Perimeter (cv::Mat &src, cv::Mat &dest, std::vector<Point> &border);
	void Find_Smooth_Perimeter (cv::Mat &src, cv::Mat &dest, std::vector<Point> &border);
	void createGaussianKernel (cv:: Mat &kernel, double sigma);
	void filterImage (cv::Mat &src, cv::Mat &dst, cv:: Mat &kernel);
	void thresholdImage (cv::Mat &mat);


  private:
	
	Mat image;

};


### DEFINITIONS OF CLASS MEMBERS

#### Image_Analysis::Image_Analysis (cv::Mat &img)  

**cv::Mat img** image to be analyzed;

#### Image_Analysis::Find_Region (cv::Mat &dest, int x, int y, int similarity_param);<br />
**cv::Mat dest** destination matrix which is used to store and show the filled region<br />
**int x, int y** x and y index of pixel which intensity is compared with neighborhood pixels intensity.<br />
**int similarity_param** this parameter is used as a tolerance (control parameter) to consider the neighborhood pixel intensity same as current pixel intensity.<br />

##### PSEUDO CODE<br />
1. Take RGB image
2. Check the intensity of the current pixel
3. Take a similarity_parameter that is the allowed difference between two neighbourhood pixels to considered the same region.
4. Check the four direction in Right, Top, Left, Bottom sequence. (Applied the same method as in the round 1 of the programming test) (Could have checked all the 8 directions)
5. Flood filled pixels are shown as colored in the output image and save as white in the saved image.



#### Image_Analysis::Find_Perimeter (cv::Mat &src, cv::Mat &dst, std::vector<Point> &border);<br />
**cv::Mat src**  obtained by Image_Analysis::Find_Region method.<br />
**cv::Mat dst** Matrix which is used to show the border pixels of src matrix.<br />
**std::vector<Point> border** a vector of Points to store the border pixels.<br />

##### PSEUDO CODE<br />
1. Iterate through all the pixels of the src matrix
2. If pixel intensity is 255 then goto 3
3. Check all the neighborhood, if any pixel intensity is 0, make the current pixel location as border point in the dst matrix



#### Image_Analysis::Find_Smooth_Perimeter (cv::Mat &src, cv::Mat &dest, std::vector<Point> &border);<br />
**cv::Mat src** obtained by Image_Analysis::Find_Region method.<br />
**cv::Mat dst**  Matrix which is used to store smooth border pixels of src matrix.<br />
**std::vector<Point> border** a vector of Points to store the smooth border pixels.<br />

##### PSEUDO CODE <br />
1. Call the Image_Analysis::CreateGaussianKernel function.
2. Filter the image obtained from Image_Analysis::Find_Region method by calling Image_Analysis::filterImage function.
3. Finally call the Image_Analysis::Find_Perimeter function described above.

#### Image_Analysis::DISPLAY_PIXELS(cv::Mat &filled_image, cv::Mat &border_image);<br /> 
This function displays the colored image of the filled region and border obtained from FIND_* methods. <br />

**cv::Mat filled_image**  obtained from Image_Analysis::FIND_REGION Method.
**cv::Mat border_imaged**  obtained from Image_Analysis::FIND_PERIMETER method

##### PSEUDO CODE<br />
1. Convert the two single channel images intro 3 channel image.
2. Show the colored images.


### COMPILATION STEPS 

1. cmake .
2. make

### RUN PROCEDURE

1. ./ImgAnalysis "image_name_with_extension"<br />

Running the above command will display following message to the user<br />

Choose one of the following operation to perform<br />

EXIT			-> 0<br />
FIND_REGION		-> 1	[this option asks user for Similarity_parameter, xIndex and yIndex of the pixel to start "floodfilling"]<br />
FIND_PERIMETER		-> 2<br />
DISPLAY_INPUT_IMAGE	-> 3<br />
DISPLAY_PIXELS		-> 4<br />
SAVE_PIXELS		-> 5	[this option asks user for the name of output file to save Region_filled and border_image. Stores the filled region and border in white color]<br />
FIND_SMOOTH_PERIMETER	-> 6<br />


#### An Example for running operation:

**amit@amit-Lenovo-IdeaPad-Y410P:~/git/exercise-AS0434/part1$** ./ImgAnalysis test3.png


*Choose one of the following operations to perform

EXIT			-> 0<br />
FIND_REGION		-> 1<br />
FIND_PERIMETER		-> 2<br />
DISPLAY_INPUT_IMAGE	-> 3<br />
DISPLAY_PIXELS		-> 4<br />
SAVE_PIXELS		-> 5<br />
FIND_SMOOTH_PERIMETER	-> 6<br />

1
Finding Region<br />
Please enter the similarity parameter (greater than 0 and less than 255 (around 30)) = <br />
30<br />
Please enter X index of the pixel (greater equal than 0 and less than 200) = <br />
100<br />
Please enter Y index of the pixel (greater equal than 0 and less than 200) = <br />
100<br />


Choose one of the following operations to perform<br />

EXIT			-> 0<br />
FIND_REGION		-> 1<br />
FIND_PERIMETER		-> 2<br />
DISPLAY_INPUT_IMAGE	-> 3<br />
DISPLAY_PIXELS		-> 4<br />
SAVE_PIXELS		-> 5<br />
FIND_SMOOTH_PERIMETER	-> 6<br />

6
Finding Smooth Perimeter
Enter the size of Gaussian Kernel (should be an odd number)
5
Enter the value of sigma (std deviation) for Gaussian Kernel
100

Choose one of the following operations to perform

EXIT			-> 0<br />
FIND_REGION		-> 1<br />
FIND_PERIMETER		-> 2<br />
DISPLAY_INPUT_IMAGE	-> 3<br />
DISPLAY_PIXELS		-> 4<br />
SAVE_PIXELS		-> 5<br />
FIND_SMOOTH_PERIMETER	-> 6<br />

0


### REFERENCES

1. enum for switch case is borrowed from https://stackoverflow.com/questions/3019153/how-do-i-use-an-enum-value-on-a-switch-statement-in-c
2. Implementation of storing to text file--  https://stackoverflow.com/questions/8863505/simple-file-write-function-in-c
3. Creating Gaussian kernel http://www.programming-techniques.com/2013/02/gaussian-filter-generation-using-cc.html





