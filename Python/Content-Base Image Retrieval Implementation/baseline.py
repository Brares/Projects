# Author: Jonathan Flores
# Date: November 25, 2019
# Course: CPSC 4660

# Usage using the whole databasa COREL 10K
# python baseline.py --dataset images1 --query queries/5_504.jpg

# Usage using the subset of COREL 10K
# python baseline.py --dataset images --query queries/5_504.jpg

# import the necessary packages
from backend.rgbhistogram import RGBHistogram
from backend.searcher import Searcher
import sys
import numpy as np
import argparse
import cPickle
import cv2
from PIL import Image
import os

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-d", "--dataset", required = True,
	help = "Path to dataset of images")
ap.add_argument("-q", "--query", required = True,
	help = "Path to query image")
args = vars(ap.parse_args())

# Select the correct CPICKLE File
cpickleFile = "index.cpickle"
dataset = args["dataset"]
if (dataset == "images1"):
        cpickleFile = "index10.cpickle"

# Delete results from previous retrievals
path = "Results/"
for image_file_name in os.listdir(path):
        if image_file_name.endswith(".jpg"):
                os.remove(path + image_file_name)
path = "Results/thumbnails/"
for image_file_name in os.listdir(path):
        if image_file_name.endswith(".jpg"):
                os.remove(path + image_file_name)
for j in xrange(1, 11):
      path = "Results/Cluster" + "%d/" % (j)
      for image_file_name in os.listdir(path):
            if image_file_name.endswith(".jpg"):
                os.remove(path + image_file_name)
print ("Previous results deleted")

# Size of thumbnails
size = (277,187)

# load the query image and show it
img = Image.open(args["query"])
width_org, height_org = img.size
factor = 2
width = int(width_org * factor)
height = int(height_org * factor)
img1 = img.resize((width, height), Image.NEAREST)
img1.save('Results/Query.jpg')
queryImage = cv2.imread("Results/Query.jpg")
cv2.imshow("Query", queryImage)

print "query: %s" % (args["query"])

# describe the query in the same way that we did in
# index.py -- a 3D RGB histogram with 8 bins per
# channel
desc = RGBHistogram([8, 8, 8])
queryFeatures = desc.describe(queryImage)

# load the index perform the search
index = cPickle.loads(open(cpickleFile).read())
searcher = Searcher(index)
results = searcher.search(queryFeatures)

# loop over the top ten results
imagesList = []
for j in xrange(0, 10):
	# grab the result (we are using row-major order) and
	# load the result image
	(score, imageName) = results[j]
	path = dataset + "/%s" % (imageName)
	print "\t%d. %s : %.3f" % (j + 1, imageName, score)
	img = Image.open(path)
	width_org, height_org = img.size
        factor = 2
        width = int(width_org * factor)
        height = int(height_org * factor)
        img1 = img.resize((width, height), Image.NEAREST)
        img1.save('Results/Result{}.jpg'.format(j + 1))
        imagesList.append('Results/Result{}.jpg'.format(j + 1))

images1 = [ Image.open(i) for i in imagesList ]
counter = 0
imagesList2 = []
for i in images1:
        i.thumbnail(size)
        i.save('Results/thumbnails/Thumbnail{}.jpg'.format(counter + 1))
        imagesList2.append('Results/thumbnails/Thumbnail{}.jpg'.format(counter + 1))
        counter += 1
images = [ Image.open(i) for i in imagesList2 ]
widths, heights = zip(*(i.size for i in images))

total_width = max(widths) * 5
max_height = max(heights) * 2

new_im = Image.new('RGB', (total_width, max_height))

x_offset = 0
y_offset = 0
i = 0
for im in images:
        if i == 5:
                x_offset = 0
                y_offset = max(heights)
        new_im.paste(im, (x_offset,y_offset))
        x_offset += im.size[0]
        i += 1
new_im.save('Results/Result.jpg')

# show the results
result = cv2.imread("Results/Result.jpg")
cv2.imshow("Results 1-10", result)
cv2.waitKey(0)
