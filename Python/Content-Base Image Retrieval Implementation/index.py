# Author: Jonathan Flores
# Date: November 25, 2019
# Course: CPSC 4660

# USAGE
# python index.py 

# import the necessary packages
from backend.rgbhistogram import RGBHistogram
import argparse
import cPickle
import glob
import cv2
import os

# initialize the index dictionary to store our our quantifed
# images, with the 'key' of the dictionary being the image
# filename and the 'value' our computed features
index = {}

# initialize our image descriptor -- a 3D RGB histogram with
# 8 bins per channel
desc = RGBHistogram([8, 8, 8])

# Change "images" for another dataset
for imagePath in glob.glob("images" + "/*.jpg"):
	# extract our unique image ID (i.e. the filename)
	j, k = os.path.split(imagePath)

	# load the image, describe it using our RGB histogram
	# descriptor, and update the index
	image = cv2.imread(imagePath)
	features = desc.describe(image)
	index[k] = features

# we are now done indexing our image -- now we can write our
# index to disk
f = open("index.cpickle", "w")
f.write(cPickle.dumps(index))
f.close()

# show how many images we indexed
print "done...indexed %d images" % (len(index))
