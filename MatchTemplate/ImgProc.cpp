#include "ImgProc.hpp"

// 1 - Calcular Histogramas
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<double> ImgProc::computeImgGlobalHist(Mat img, int nBins){
	vector<double> vHist;
	vHist.assign(nBins, 0);
	
	int binSize = 256/nBins;
	
	for(int i = 0; i < img.rows; i++){
		for(int j = 0; j < img.cols; j++){
			int value = img.at<uchar>(i,j);
			int index  = value/binSize;
			vHist[index] = vHist[index] + 1;
		}
	}
	
	double soma = 0;
	for(int i = 0; i < nBins; i++){
		soma = soma + vHist[i];
	}
	
	for(int i = 0; i < nBins; i++){
		vHist[i] = vHist[i]/soma;
	}
	
	return vHist;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 2 - Distancia Euclidiana entre Histogramas
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double 	ImgProc::computeEuclideanDist(vector<double>Vhist1 , vector<double> Vhist2){
	double dist = 0;	
	for(int i = 0; i < Vhist1.size(); i++){ 		
		dist = pow(Vhist1[i] - Vhist2[i], 2.0) + dist;
	}
	dist = sqrt(dist);
	return dist;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 3 - Distancia Euclidiana entre Matrizes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ImgProc::computeEuclideanDist(Mat img1,Mat img2){
	double dist = 0;	
	for(int i = 0; i < img1.rows; i++){ 
		for(int j = 0; j < img1.cols; j++){ 	
			dist = pow(img1.at<uchar>(i,j) - img2.at<uchar>(i,j) , 2.0) + dist;
		}
	}
	dist = sqrt(dist);
	return dist;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 4- Método responsável por checar se as matrizes coincidem em algum ponto.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImgProc::Match(Mat img1 , Mat img2){	
	//Decompondo RGB
	Mat imgColor = img1;		
	vector<Mat> bgr_Img1;
	split(img1 , bgr_Img1);
	vector<Mat> bgr_Img2;
	split(img2 , bgr_Img2);	
	img1 = bgr_Img1[0];// Pegando a matriz do tom azul da imagem
	img2 = bgr_Img2[0];// Pegando a matriz do tom azul do template
	
	Point p1 , p2;	
	double dist = 0;
	double menordist = DBL_MAX;
	
	for(int i = 0; i < img1.rows - img2.rows; i++){ 
		for(int j = 0; j < img1.cols - img2.cols; j++){ 
			Rect rect = Rect(j, i, img2.cols, img2.rows); 
			Mat img3 = img1(rect);  
			dist = computeEuclideanDist(img2,img3); // Calcula a distancia euclidiana entre matrizes
			if (dist <= menordist){ 
				menordist = dist; 
				p1 = Point(j,i);
				p2 = Point( j + img2.cols , i + img2.rows );
			}
		}
	}
	exibirImagem(p1,p2,imgColor);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 5- Método responsável por checar se os histogramas coincidem.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImgProc::MatchHistogram(Mat img1 , Mat img2,int nBins){	
	//Decompondo RGB
	Mat imgColor = img1;		
	vector<Mat> bgr_Img1;
	split(img1 , bgr_Img1);
	vector<Mat> bgr_Img2;
	split(img2 , bgr_Img2);	
	img1 = bgr_Img1[1];// Pegando a matriz do tom verde da imagem
	img2 = bgr_Img2[1];// Pegando a matriz do tom verde do template	


	vector<double> vHistTemp = computeImgGlobalHist(img2,nBins);	
	vector<double> vHistImg3;	
	Point p1 , p2;	
	double dist = 0;
	double menordist = DBL_MAX;

	for(int i = 0; i < img1.rows - img2.rows; i++){ 
		for(int j = 0; j < img1.cols - img2.cols; j++){ 
			Rect rect = Rect(j, i, img2.cols, img2.rows); 
			Mat img3 = img1(rect);
			vHistImg3 = computeImgGlobalHist(img3,nBins);  
			dist = computeEuclideanDist(vHistTemp,vHistImg3); // Calcula a distancia euclidiana entre histogramas
			if (dist <= menordist){ 
				menordist = dist; 
				p1 = Point(j,i);
				p2 = Point( j + img2.cols , i + img2.rows );
			}
		}
	}
	exibirImagem(p1,p2,imgColor);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 6- Metodo de exibição da imagem marcada
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImgProc::exibirImagem(Point p1, Point p2 , Mat img){
	rectangle(img, p1,p2, CV_RGB(255, 255, 0), 3, 8, 0); 
	cout << "Pressione qualquer tecla para fechar a imagem."<<endl;	
	imshow("imgPanel", img); 
	waitKey(-1);
	exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 7 - Gerar matriz de Imagens
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mat ImgProc::gerarMatriz(char* argv){	
	string imgName(argv);
	return imread(imgName.c_str(), IMREAD_COLOR);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











