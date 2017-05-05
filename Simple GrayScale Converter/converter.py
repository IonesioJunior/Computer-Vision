import sys,os
import cv2
import numpy as np
import matplotlib.pyplot as plt

__author__ = "Ionesio Junior"



def plotHistogramGraphic(img,grayimg):
	''' Plot a normal histogram of channel 
		
	   Args:
		img(Mat[3]) : 3 channel image(RGB)
		grayImg(Mat[1]) : 1 channel image(GRAY)
	'''
        grayHistogram = np.histogram(grayimg[:,:,0],256)
        blueHistogram = np.histogram(img[:,:,0],256)
        greenHistogram = np.histogram(img[:,:,1],256)
        redHistogram = np.histogram(img[:,:,2],256)
        y = range(256)
	plt.plot(y,grayHistogram[0],'k-',y,blueHistogram[0],'b-',y,greenHistogram[0],'g-',y,redHistogram[0],'r-')
        plt.savefig('./Graphics/Histogram.png')
	plt.clf()	

def plotValuesAvarageGraphic(valuesMatrix,index):
	''' Plot and save graphic of color distribution in all image pixels by channel
	
	    Args:
		valuesMatrix[channels[] ] : matrix of pixel values by channels(rows)
		index(int) : index of channel (0-blue/1-green/2-red/3-gray)
	'''
	if(type(index) != int and (index > 4 or index < 0)):
		print "Wrong index,try again."
		exit()
	colorline = ['b-','g-','r-','k-']
	figname = ['1-blue.png','2-green.png','3-red.png','4-gray.png']

	x = range(1,len(valuesMatrix[0]) + 1);
	plt.plot(x,valuesMatrix[i],colorline[i]);
	plt.savefig("./Graphics/" + figname[index])


if __name__ == "__main__":
	if(len(sys.argv) != 2):
		print "Wrong input. Ex: python grayscaleconverter.py imagename.extension"
		exit()
	img = cv2.imread(sys.argv[1])
	gray = np.zeros((img.shape[0],img.shape[1],1),np.uint8)
	valuesMatrix = [[] for i in range(4)]
	for i in range(len(gray)):
		for j in range(len(gray[1])):
			avarageValue = int((int(img[i,j,0]) + int(img[i,j,1]) + int(img[i,j,2])) / 3)
			gray[i,j,0] = np.uint8(avarageValue)
			if(i == j and i % 5 == 0):
				valuesMatrix[0].append(img[i,j,0])
				valuesMatrix[1].append(img[i,j,1])
				valuesMatrix[2].append(img[i,j,2])
				valuesMatrix[3].append(avarageValue)

	plotHistogramGraphic(img,gray)
	for i in range(4):
		plotValuesAvarageGraphic(valuesMatrix,i)
	
	cv2.imwrite('gray_scale_image.jpg',gray)
