/*
* @author Ionesio Junior
*/

#include <cstdlib>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

/*bool checkNeighbors(const cv::Mat &img,uchar *ptr){
	
}*/
void Test(cv::Mat &img){
	for(int y = 2 ; y < img.rows - 2;y++){
		uchar **ptrs = (uchar**) calloc(5,sizeof(uchar*));
		
		for(int i = -2,j = 0;i <= 2;i++,j++){
			ptrs[j] = img.ptr(2 - i) + 2;
		}	
		
		for(int x = 2;x < img.cols - 2;x++){
			uchar pVal = *ptrs[2];
			if(pVal == 0){
				bool above = *(ptrs[0] - 2) && *(ptrs[0] - 1) && *ptrs[0] && *(ptrs[0] + 1) && *(ptrs[0] + 2);
				bool left = *(ptrs[1] - 2) && *(ptrs[2] - 2) && *(ptrs[3] - 2);
				bool right = *(ptrs[1] + 2) && *(ptrs[2] + 2) && *(ptrs[3] + 2);
				bool bottom = *(ptrs[4] -2) && *(ptrs[4] -1) && *(ptrs[4]) && *(ptrs[4] +1) && *(ptrs[4] + 2);
				bool result = above && left && right && bottom;
				if(result){	
					*(ptrs[1] - 1) = 0;
					*ptrs[1] = 0;
					*(ptrs[1] + 1) = 0;
					*(ptrs[2] - 1) = 0;
					*ptrs[2] = 0;
					*(ptrs[2 + 1]) = 0;
					*(ptrs[3] - 1) = 0;
					*(ptrs[3] + 1) = 0;
					*ptrs[3] = 0;
					for(int i = 0 ; i < 5;i++){
						ptrs[i] += 2;
					}
				}
			}
			for(int i = 0 ; i < 5;i++){
				ptrs[i]++;	
			}
		}
	}
}

int main(int argc,char** argv){
	cv::VideoCapture cap;
	if(!cap.open(0)){
		return 0;	
	}else{
		while(1){
			cv::Mat frame;
			cap >> frame;
			cv::medianBlur(frame,frame,7);
			cv::cvtColor(frame,frame,CV_BGR2GRAY);
			cv::Laplacian(frame,frame,CV_8U,5);
			cv::threshold(frame,frame,80,255,1);
			Test(frame);
			cv::imshow("Test",frame);
			cv::waitKey(1);
		}
	}
	return 0;
}
