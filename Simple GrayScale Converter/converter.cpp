/*
* @author : Ionesio Junior
*/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <cstdlib>
#include <iostream>

void generateGrayScaleImage(cv::Mat *emptyImg,cv::Mat bgr[]);

int main(int argc,char * argv[]){
	if(argc < 2){
		std::cout << "Wrong input, Ex: ./Run imagename.extension" << std::endl;
		return 0;
	}
	
	cv::Mat img = cv::imread(argv[1]);
	
	if(img.empty()){
		std::cout << "Sofware can't load image!" << std::endl;
		return 0;
	}
	
	//Split 3 channels image to 3(1 channel) matrix (Blue,green,red)
	cv::Mat bgr[3];
	cv::split(img,bgr);
	
	//Empty gray scale image
	cv::Mat grayImg = cv::Mat::zeros(img.rows,img.cols,CV_8UC1);

	generateGrayScaleImage(&grayImg,bgr); //Or simple "cv::cvtColor(image,grayImg,COLOR_BGR2GRAY) ->opencv method"
	
	cv::imwrite("gray_scale_image.jpg",grayImg);
	return 0;
}

//Fill empty gray scale image with avarage of BGR matrix
void generateGrayScaleImage(cv::Mat *emptyImg,cv::Mat bgr[]){
        for(int rows = 0 ; rows < emptyImg->rows;rows++){
                for(int cols = 0 ; cols < emptyImg->cols;cols++){
                        emptyImg->at<uchar>(rows,cols) = ( bgr[0].at<uchar>(rows,cols)  //Blue matrix
							  + bgr[1].at<uchar>(rows,cols) //Green matrix
							  + bgr[2].at<uchar>(rows,cols)  ) / 3; //Red matrix
                }
        }
}
