#include <cstdlib>
#include <iostream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

int main(int argc,char** argv){
	cv::VideoCapture cap;
	if(!cap.open(0)){
		return 0;
	}else{
		std::cout << "Qual tipo de filtro deseja aplicar?" << std::endl;
		std::cout << "1 - MedianBlur + Laplacian" << std::endl;
		std::cout << "2 - MedianBlur + Laplacian + Thresholding" << std::endl;
		int x = 0;
		std::cin >> x;
		while(1){
			cv::Mat frame;
			cap >> frame;
			if(frame.empty()){
				std::cout << "Error!" << std::endl;
			}else{
				cv::Mat gray;
				cv::cvtColor(frame,gray,CV_BGR2GRAY);
				cv::medianBlur(gray,gray,7);
				cv::Laplacian(gray,gray,CV_8U,5);
				if(x == 1){
					cv::imshow("Image",gray);	
					cv::waitKey(1);
				}else{
					cv::Mat mask;
					cv::threshold(gray,mask,80,255,1);
					cv::imshow("Image",mask);	
					cv::waitKey(1);
				}
                                                                                                                                                           			     }
		}
	}
}
