/*
* @author Ionesio Junior
*/
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>

int main(int argc,char** argv){
	//Load video file
	cv::VideoCapture cap(argv[1]);
	if(!cap.isOpened()){
		std::cerr << "Error!" << std::endl;
		return 0;
	}else{
		double fps = cap.get(CV_CAP_PROP_FPS); // get frames per second  of the video (others alternatives -> CV_CAP_PROP_POS_MSEC - miliseconds position / CV_CAP_PROP_POS_FRAMES - index of next frame)
		cv::namedWindow("Test",CV_WINDOW_AUTOSIZE);
					//CV_WINDOW_NORMAL -> the user can resize window size
					//CV_AUTOSIZE -> The window size is automatically adjusted to fitvthe displayed image()
					//CV_OPENGL -> The window will be created with OpenGL support

		while(1){
			cv::Mat frame;
			if(!cap.read(frame)){		
				std::cout << "Can't read this video!" << std::endl;
			}else{
				cv::imshow("test",frame);
				std::cout << cv::waitKey(30)  << std::endl;
				if(cv::waitKey(30) == 1048603){ //Wait for esc press
					break;
				}
			}
		}
			
	}
	return 0;
}
