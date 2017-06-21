/*
* @author Ionesio Junior
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

void blackAndWhiteSketch(cv::Mat &img){
	cv::cvtColor(img,img,CV_BGR2GRAY);
	cv::medianBlur(img,img,7);
	cv::Laplacian(img,img,CV_8U,5);
	cv::threshold(img,img,80,255,1);
}

void colorPaintingCartoon(cv::Mat &img){
	//Turn this method more faster
	cv::Size size = img.size();
	cv::Size smallSize;
	smallSize.width = size.width / 2;
	smallSize.height = size.height / 2;
	cv::Mat smallImg = cv::Mat(smallSize,CV_8UC3);
	cv::resize(img,smallImg,smallSize,0,0,cv::INTER_LINEAR);
	cv::Mat tmp = cv::Mat(smallSize,CV_8UC3);
	unsigned short int repetitions = 7;
	for(int i = 0 ; i< repetitions;i++){
		unsigned short int ksize = 9;
		double sigmaColor = 9;
		double sigmaSpace = 7;
		cv::bilateralFilter(smallImg,tmp,ksize,sigmaColor,sigmaSpace);
		cv::bilateralFilter(tmp,smallImg,ksize,sigmaColor,sigmaSpace);
	}
	cv::resize(smallImg,img,img.size(),0,0,cv::INTER_LINEAR);
}

void evilMode(cv::Mat &img){
	cv::cvtColor(img,img,CV_BGR2GRAY);
	const int MEDIAN_BLUR_FILTER_SIZE = 7;
	cv::medianBlur(img,img,MEDIAN_BLUR_FILTER_SIZE);
	cv::Mat edges,edges2;
	cv::Scharr(img,edges,CV_8U,1,0);
	cv::Scharr(img,edges2,CV_8U,1,0,-1);
	edges += edges;
	const int EVIL_EDGE_THRESHOLD = 12;
	cv::threshold(edges,img,EVIL_EDGE_THRESHOLD,255,2);
	cv::medianBlur(img,img,3);
}
int main(int argc,char** argv){
	cv::VideoCapture cap;
	if(!cap.open(0)){
		return 0;
	}else{
                        std::cout << "Choose some filter type: " << std::endl;
                        std::cout << "1 - Black and white sketch" << std::endl;
                        std::cout << "2 - Painted Cartoon " << std::endl;
                        std::cout << "3 - Evil Mode" << std::endl;
                        int choose = 0;
                        std::cin >> choose;
		while(1){
			cv::Mat frame;
			cap >> frame;
			if(frame.empty()){
				std::cout << "Error!" << std::endl;
			}else{
				if(choose == 1){
                 			blackAndWhiteSketch(frame);
				} else if (choose == 2){
					colorPaintingCartoon(frame);
				}else if (choose  == 3){
					evilMode(frame);
				}else{
					std::cerr << "Invalid type of cartoon!" << std::endl;
					exit(1);
				}
				cv::imshow("Image",frame);
				cv::waitKey(1);
		        }
		}
	}
}
