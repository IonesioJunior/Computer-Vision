/*
* @author : Ionesio Junior
*/
#include <cstdlib>
#include <iostream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

std::vector<int> buildGrayScaleHistogram(cv::Mat *img){
	cv::Mat gray;
	cv::cvtColor(*img,gray,CV_BGR2GRAY);
	std::vector<int> histogram(256,0);
	for(int row = 0 ; row < gray.rows;row++){
		for(int col = 0 ; col < gray.cols;col++){
			histogram[gray.at<uchar>(row,col)]++;
		}
	}
	return histogram;
}
std::vector<std::vector<int> > buildColoredHistogram(cv::Mat *img){
	cv::Mat bgr[3];
	cv::split(*img,bgr);
	std::vector<int> blue_histogram(256,0);
	std::vector<int> green_histogram(256,0);
	std::vector<int> red_histogram(256,0);

        for(int row = 0 ; row < img->rows;row++){
                for(int col = 0 ; col < img->cols;col++){
			blue_histogram[bgr[0].at<uchar>(row,col)]++;
			green_histogram[bgr[1].at<uchar>(row,col)]++;
                        red_histogram[bgr[2].at<uchar>(row,col)]++;
                }
        }
	std::vector<std::vector<int> >  result;
	result.push_back(blue_histogram);
	result.push_back(green_histogram);
	result.push_back(red_histogram);
	return result;
}

int main(int argc,char* argv[]){
	if(argc != 3){
		std::cout << "Wrong input. Ex: ./Run imagename.extension (0 or 1)" << std::endl;
		return 0;
	}
	
	cv::Mat img = cv::imread(argv[1]);
	if(std::atoi(argv[2]) == 0) std::vector<int> result = buildGrayScaleHistogram(&img);
	else
		std::vector<std::vector<int> > result = buildColoredHistogram(&img);
	return 0;
}
