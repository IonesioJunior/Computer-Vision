import sys,os
import cv2
import numpy as np
import matplotlib.pyplot as plt



def threshold(img,limit = 127,Type = 0):
	mask = np.zeros(img.shape,np.uint8)
	if(Type == 0 or Type == 1):
		return binaryThreshold(img,mask,limit,Type)
	elif(Type == 2):
		return truncate(img,mask,limit)
	elif(Type == 3 or Type == 4):
		return thresholdToZero(img,mask,limit,Type)


def binaryThreshold(img,mask,limit,Type):
	for i in range(len(mask)):
		for j in range(len(mask[0])):
			if(img[i,j] <= limit and Type == 0): #Normal binary threshold
				mask[i,j] = np.uint8(255)
			if(img[i,j] > limit and Type == 1): #Inverted binary threshold
				mask[i,j] = np.uint8(255)
	return mask

def truncate(img,mask,limit):
	for i in range(len(mask)):
		for j in range(len(mask[0])):
			if(img[i,j] <= limit):
				mask[i,j] = img[i,j]
			else:
				mask[i,j] = limit
	return mask

def thresholdToZero(img,mask,limit,Type):
	for i in range(len(mask)):
		for j in range(len(mask[0])):
			if(Type == 3):
				if(img[i,j] > limit):
					mask[i,j] = img[i,j]
				else:
					mask[i,j] = 0
			else:
				if(img[i,j] > limit):
					mask[i,j] = 0
				else:
					mask[i,j] = img[i,j]
	return mask

if __name__ == "__main__":
	if(len(sys.argv) != 4):
		print "Wrong input, Ex: python thresholding.py imagename.extesion  limit thresholding type"
		exit()
	imgnames = ['binary.jpg','invertedbinary.jpg','truncate.jpg','toZero.jpg','invertedToZero.jpg']
	img = cv2.imread(sys.argv[1],0)
	result = threshold(img,int(sys.argv[2]),int(sys.argv[3]))
	cv2.imwrite('./Results/' + imgnames[int(sys.argv[3])],result)
	
