Given 2 text documents, the program computes the similarity between the 2
documents using the cosine similarity measure with:

(a) TF-IDF representation
(b) Word2Vec representation

It uses the Brown corpus to compute the similarity within the cluster and
between clusters.

To run my program you need the following imports:
Python 3.6
import string
import gensim
import pandas as pd
import numpy as np
import numpy.linalg as LA
import re
