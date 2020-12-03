In order to run this implementation of CLUE, you will need a few pre-requisites:

- Python 2.7
- Numpy (pip install numpy)
- OpenCV (pip install opencv-python)
- Image (pip install image)
- Scipy (pip install scipy)
- Sklearn (pip install sklearn)

There are two datasets:

	images: Contains a subset of COREL 10k. There are 10 categories with 100 images each. There are 1,000 images in total.

	images1: is the whole dataset of COREL 10K. There are 100 categories with 100 images each. There are 10,000 images in total.

Backend Folder: Contains important python files. The python files at the root use the files in the backend folder. 

Queries Folder: The queries images that are going to be used. There are already a few here just to test each category.

Results Folder: After running baseline.py or clueretrieval.py, the image results are going to be displayed here. There are 10 folders inside,
Cluster 1 to Cluster 10. Once you run cluretrieval.py, the images of each cluster are going to appear in each folder.

baseline.py: It does an image retrieval, but only compares the color similarity. It looks for images with similar colors than the query image. Then it displays
the ones with less distance or that have similar colors.

clueretrieval: It does the same as the baseline, but after comparing the colors, it separates the 200 nearest neighbours to the query image into different
clusters. 


TO RUN THE PROGRAM:

To run the baseline with the whole COREL 10K dataset:
python baseline.py --dataset images1 --query queries/90_9076.jpg

To run the baseline with the subset of COREL 10K dataset:
python baseline.py --dataset images --query queries/90_9076.jpg

To run the CLUE implementation with the whole COREL 10K dataset
python clueretrieval.py --dataset images1 --query queries/90_9076.jpg

To run the CLUE implementation with the subset of COREL 10K dataset
python clueretrieval.py --dataset images --query queries/90_9076.jpg