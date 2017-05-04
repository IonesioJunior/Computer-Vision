/*
* @author Ionesio Junior
*/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
#include <iostream>

///	Methods declaration	//////////////////////////////////
								//
cv::Mat binaryThresholding(cv::Mat *img,int limit);		//
cv::Mat invertBinaryThresholding(cv::Mat *img,int limit);	//
cv::Mat truncate(cv::Mat *img,int limit);			//
cv::Mat thresholdToZero(cv::Mat *img,int limit);		//
cv::Mat invertedThresholdToZero(cv::Mat *img,int limit);	//
cv::Mat threshold(cv::Mat *img,int limit,int type);		//
								//
//////////////////////////////////////////////////////////////////

int main(int argc,char* argv[]){
	if(argc < 4){
		std::cout << "Wrong input, Ex: ./Run  imagename.extesion threshold_type limit_pixel_value" << std::endl;
		return 0;
	}	
	
	cv::Mat image = cv::imread(argv[1],0); //Load image in grayscale (1 channel)
	int limit = std::atoi(argv[3]);
	if(image.empty()){
		std::cout << "Software can't load that image!" << std::endl;
		return 0;
	}
	
	cv::Mat thresholdImg = threshold(&image,limit,std::atoi(argv[2]));
	cv::imwrite("threshold_image.jpg",thresholdImg);
	cv::waitKey(-1);
	return 0;
}

/* 
*  Select threshold type (binary threshold by default)
*/
cv::Mat threshold(cv::Mat *img,int limit,int type){
	if(type == 1){
		return invertBinaryThresholding(img,limit);
	}else if(type == 2){
		return truncate(img,limit);
	}else if(type == 3){
		return thresholdToZero(img,limit);
	}else if(type == 4){
		return invertedThresholdToZero(img,limit);	
	}else{
		return binaryThresholding(img,limit);
	}
}

// Binary threshold algorithm
cv::Mat binaryThresholding(cv::Mat *img,int limit){
        cv::Mat emptyImg = cv::Mat::zeros(img->rows,img->cols,CV_8UC1);
	for(int rows = 0 ; rows < emptyImg.rows;rows++){
		for(int cols = 0 ; cols < emptyImg.cols;cols++){
			int pixelValue = img->at<uchar>(rows,cols);
			if(pixelValue <= limit){
				emptyImg.at<uchar>(rows,cols) = 255;
			}
		}
	}
	return emptyImg;
}

// Inverted binary threshold
cv::Mat invertBinaryThresholding(cv::Mat *img,int limit){
        cv::Mat emptyImg = cv::Mat::zeros(img->rows,img->cols,CV_8UC1);
	for(int rows = 0 ; rows < emptyImg.rows;rows++){
                for(int cols = 0 ; cols < emptyImg.cols;cols++){
                        int pixelValue = img->at<uchar>(rows,cols);
                        if(pixelValue > limit){
                                emptyImg.at<uchar>(rows,cols) = 255;
                        }
                }
        }
	return emptyImg;
}

//Truncate threshold algorithm implementation
cv::Mat truncate(cv::Mat *img,int limit){
        cv::Mat emptyImg = cv::Mat::zeros(img->rows,img->cols,CV_8UC1);
        for(int rows = 0 ; rows < emptyImg.rows;rows++){
                for(int cols = 0 ; cols < emptyImg.cols;cols++){
                        int pixelValue = img->at<uchar>(rows,cols);
                        if(pixelValue <= limit){
                                emptyImg.at<uchar>(rows,cols) = pixelValue;
                        }else{
				emptyImg.at<uchar>(rows,cols) = limit;
			}
                }
        }
        return emptyImg;
}

// Threshold to zero algorithm implementation
cv::Mat thresholdToZero(cv::Mat *img,int limit){
        cv::Mat emptyImg = cv::Mat::zeros(img->rows,img->cols,CV_8UC1);
        for(int rows = 0 ; rows < emptyImg.rows;rows++){
                for(int cols = 0 ; cols < emptyImg.cols;cols++){
                        int pixelValue = img->at<uchar>(rows,cols);
                        if(pixelValue > limit){
                                emptyImg.at<uchar>(rows,cols) = pixelValue;
                        }else{
                                emptyImg.at<uchar>(rows,cols) = 0;
                        }
                }
        }
        return emptyImg;
}

// Inverted threshold to zero
cv::Mat invertedThresholdToZero(cv::Mat *img,int limit){
        cv::Mat emptyImg = cv::Mat::zeros(img->rows,img->cols,CV_8UC1);
        for(int rows = 0 ; rows < emptyImg.rows;rows++){
                for(int cols = 0 ; cols < emptyImg.cols;cols++){
                        int pixelValue = img->at<uchar>(rows,cols);
                        if(pixelValue > limit){
                                emptyImg.at<uchar>(rows,cols) = 0;
                        }else{
                                emptyImg.at<uchar>(rows,cols) = pixelValue;
                        }
                }
        }
        return emptyImg;
}
