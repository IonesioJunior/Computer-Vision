import sys,os
import cv2
import matplotlib.pyplot as plt
import numpy as np

def grayscaleHistogram(img):
	gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        histogram = np.zeros(256,int)
	for i in range(len(img)):
	        for j in range(len(img[0])):
                       histogram[img[i,j]] = histogram[img[i,j]] + 1
        plt.plot(range(256),histogram, 'k-')
        plt.xlabel('Pixel values')
        plt.ylabel('Frequency')
        plt.title("Histogram GrayScale")
        plt.savefig('./Results/GrayHistogram.png')

def RGBHistogram(img):
	r = np.zeros(256,int)
	g = np.zeros(256,int)
	b = np.zeros(256,int)
	
	for i in range(len(img)):
		for j in range(len(img[0])):
			r[img[i,j,2]] = r[img[i,j,2]] + 1
			g[img[i,j,1]] = g[img[i,j,1]] + 1
			b[img[i,j,0]] = b[img[i,j,0]] + 1
	
	plt.plot(range(256),r,'r-',range(256),g,'g-',range(256),b,'b-')
	plt.xlabel('Pixel values')
	plt.ylabel('Frequency')
	plt.title('Histogram RGB')
	plt.savefig('./Results/RGBHistogram.png')

if __name__ == "__main__":
	if(len(sys.argv) != 3):
		print "Wrong input. Ex: python histogram.py imagename.extension  0 or 1"
		exit()

	img = cv2.imread(sys.argv[1])
	if(int(sys.argv[2]) == 0):
		grayscaleHistogram(img)
	else:
		RGBHistogram(img)
	
