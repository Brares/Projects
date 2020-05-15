# Author: Jonathan Flores
# Date: November 25, 2019
# Course: CPSC 4660

# USAGE
# python retrieval.py --query queries/5_504.jpg

# THIS FILE WAS JUST FOR TESTING. DO NOT RUN IT. IT IS HERE JUST TO SHOW EXTRA WORK

# import the necessary packages
from backend.rgbhistogram import RGBHistogram
from backend.searcher import Searcher
from backend.clueimplementation import CLUEIMPLEMENTATION
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
import scipy.spatial.distance
from sklearn.cluster import SpectralClustering
import sys
import numpy as np
import argparse
import cPickle
import cv2
from PIL import Image
import os

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-q", "--query", required = True,
	help = "Path to query image")
args = vars(ap.parse_args())

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
query = cv2.imread(args["query"])
queryFeatures = desc.describe(query)

features = []
labels = []
# load the index perform the search
index = cPickle.loads(open("index.cpickle").read())
#[(imageName, self.features[imageName]) for imageName in ret[:k]]
searcher = Searcher(index)
baseline = searcher.search(queryFeatures)
it = []
for j in xrange(0,200):
    (score, imageName) = baseline[j]
    it.append(imageName)
feat = [(imageName, index[imageName]) for imageName in it[:200]]
X = np.array(([f for id, f in feat]))
affinity = scipy.spatial.distance.pdist(X)
affinity = scipy.spatial.distance.squareform(affinity)
print affinity


#print baseline[0]

# loop over the index
##for (k, _features) in index.items():
##    features.append(_features)
##    label = k.split(os.path.sep)[-1].split("_")[0]
##    labels.append(label)
##
##(trainFeat, testFeat, trainLabels, testLabels) = train_test_split(
##	features, labels, test_size=0.25, random_state=42)
##model = KNeighborsClassifier(n_neighbors=20, metric='euclidean', 
##	n_jobs=-1)
##model.fit(trainFeat, trainLabels)
##acc = model.score(testFeat, testLabels)
##print("[INFO] histogram accuracy: {:.2f}%".format(acc * 100))
##predi = model.predict(queryFeatures)
##print predi


