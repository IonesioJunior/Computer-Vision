#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>



using namespace cv;
using namespace std;

class ImgProc{
	public:
		Mat gerarMatriz(char* argv);
		void MatchHistogram(Mat img1 , Mat img2,int nBins);
		void Match(Mat img1 , Mat img2);
		
	private:
		vector<double> computeImgGlobalHist(Mat img, int nBins);
		double computeEuclideanDist(Mat img1, Mat img2);
     		double computeEuclideanDist(vector<double>Vhist1 , vector<double> Vhist2);
		void exibirImagem(Point p1, Point p2 , Mat img);
		void definirMenorDistancia(Point p1, Point p2,double dist, double menordist ,int i , int j , Mat img);

};
