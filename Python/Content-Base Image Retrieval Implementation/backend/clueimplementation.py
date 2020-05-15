# Author: Jonathan Flores
# Date: November 25, 2019
# Course: CPSC 4660

# import the necessary packages
import numpy as np
import scipy.spatial.distance
from sklearn.cluster import SpectralClustering
from recursivenormalizedcuts import RecursiveNormalizedCuts
import cv2
from PIL import Image

import heapq

class CLUEIMPLEMENTATION:
	def __init__(self, _features, baseline):
		# store our feature index of images
		self.features = _features
		self.results = baseline

	def clue(self, queryFeatures, dataset, k = 200, max_clusters = 10, T = 0.9, min_cluster_size = 2):

                ret_it = self.results

                # Spectral clustering of top results
                tree = RecursiveNormalizedCuts(max_clusters, T, min_cluster_size)
                ret = []
                for j in xrange(0, k):
                        (score, imageName) = ret_it[j]
                        ret.append(imageName)
                tree.fit([(imageName, self.features[imageName]) for imageName in ret[:k]])
                
                clusters = tree.clusters()
                # initialize our dictionary of results
		final_results = {}
                # Ask user to select relevant clusters
                selected_clusters = tree.sort_items_by_centroid_distance()

                # Ask user to select relevant clusters
                # Put images from the selected clusters first
                offset = 0
                clusterCounter = 1
                #selected_clusters.sort()
                for c in selected_clusters:
                        print('')
                        print "Start of the Cluster: %d" % (clusterCounter)
                        print c
                        print('')
                        print "End of the Cluster: %d" % (clusterCounter) 
                        length = len(c)
                        for j in range(length):
                                path = dataset + "/%s" % (c[j])
                                img = Image.open(path)
                                width_org, height_org = img.size
                                factor = 2
                                width = int(width_org * factor)
                                height = int(height_org * factor)
                                img1 = img.resize((width, height), Image.NEAREST)
                                img1.save('Results/Cluster{}/Result{}.jpg'.format(clusterCounter, offset))
                                offset = offset + 1
                        offset = 0
                        clusterCounter = clusterCounter + 1
                        
                print('')
                print("Please check the result folder to see all cluster, then select the best one")
                selection = input ("Enter the number of the best cluster: ")
                length = len(selected_clusters[int(selection) - 1])
                for j in range(length):
                        result = (selected_clusters[int(selection) - 1][j])
                        final_results[result] = self.features[result]
                        
		return final_results
