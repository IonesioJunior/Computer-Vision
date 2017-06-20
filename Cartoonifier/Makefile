INC = -I/usr/local/include/ -I /usr/local/include/opencv2/
LIBPATH = -L/usr/local/lib/
LIBS =  -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_imgproc


#alvo de compilação: Run

#para gerar Run é necessário verificar se houve alterações em funcoes.o ou Run.cpp
Default:
	g++ main.cpp -o Run $(INC) $(LIBS) $(LIBPATH) 

clean:
	rm *.o Run
