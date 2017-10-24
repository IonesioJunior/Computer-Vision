INC = -I/usr/local/include/ -I /usr/local/include/opencv2/
LIBPATH = -L/usr/local/lib/
LIBS =  -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_imgproc

#para saber as bibliotecas do opencv que estão faltando: pkg-config opencv --libs

#alvo de compilação: Run
all: MatchTemplate 

ImgProc.o : ImgProc.cpp ImgProc.hpp
	g++ -c ImgProc.cpp -o ImgProc.o  $(INC)

#para gerar Run é necessário verificar se houve alterações em funcoes.o ou Run.cpp
MatchTemplate: MatchTemplate.cpp ImgProc.o
	g++ ImgProc.o MatchTemplate.cpp -o MatchTemplate $(INC) $(LIBS) $(LIBPATH) 

clean:
	rm *.o MatchTemplate
