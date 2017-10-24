#include "ImgProc.hpp"

int main(int argc, char* argv[]){	
	// Declarando variaveis
	Mat img1, img2;
	ImgProc imp;
	string resp;
	
	//Teste para verificar a validade dos argumentos
	if(argc < 2){
		cout<<"Entrada incorreta. \n Exemplo de execução: ./Run imgName1 imgName2"<<endl;
		return 0;
	}

	
	//Gerando Matrizes
	img1 = imp.gerarMatriz(argv[1]);	
	img2 = imp.gerarMatriz(argv[2]);	
	
	//Teste para verificar se a imagem foi carregada.
	if(img1.empty() || img2.empty()){
		cout<<"Não foi possível carregar as imagens"<<endl;
		exit(0);
	}
	
	
	//Tipo de analise
	cout << "Deseja analisar por histogramas ou matrizes? ";
	cin >> resp;
	
	if (resp == "histogramas"){
		int nBins;
		cout <<"Digite o numero de bins: ";
		cin >> nBins;
		cout << "Aguarde..."<<endl;
		imp.MatchHistogram(img1 ,img2, nBins); // Busca template da imagem pela comparação entre histogramas	
	}
	else if (resp == "matrizes"){
		cout << "Aguarde..."<<endl;		
		imp.Match(img1,img2); // Busca template da imagem pela comparação entre matrizes
	}
	else{
		cout << "Especificação errada. (Ex: histogramas , matrizes)"<<endl;	
	}
	
	
	return 0;
}


















