# Program By Jonathan Flores
# Assigment 3 - Question 5 - CPSC 4310

import string
import gensim
import pandas as pd
import numpy as np
import numpy.linalg as LA
import re
from nltk.corpus import brown
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
from nltk.stem.snowball import SnowballStemmer
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from gensim import models
from gensim import utils
from gensim import corpora
from gensim import similarities
from gensim.corpora import Dictionary
from gensim.models import Word2Vec, KeyedVectors, WordEmbeddingSimilarityIndex
from gensim.parsing.porter import PorterStemmer
from gensim.parsing.preprocessing import remove_stopwords
from gensim.similarities import SoftCosineSimilarity, SparseTermSimilarityMatrix

#word2vec = Word2Vec(all_words, min_count=2)
stopwords = stopwords.words('english')
symbols = "!\"#$%&()*+-./:;<=>?@[\]^_`{|}~\n"
lemmatizer = WordNetLemmatizer()
stemmer = SnowballStemmer("english", ignore_stopwords=True)

def cleanDocument(document):
    document = [w.lower() for w in document if w.lower() not in stopwords]    #Remove stopwords and convert everything lower case
    document = [w for w in document if w.lower() not in string.punctuation]   #Remove punctuation
    for i in symbols:
        document = np.char.replace(document, i, ' ')  #Remove \n
    document = [w.strip() for w in document]  #Remove empty spaces and other puntuations
    document = [w for w in document if w != ""] #Remove empty strings
    document = [lemmatizer.lemmatize(w) for w in document] #lemmatization
    document = [stemmer.stem(w) for w in document]
    
    return document
def get_mean_vector(model, words):
    word_vecs = []
    for word in words:
        try:
            vec = model[word]
            word_vecs.append(vec)
        except KeyError:
            pass
    vector = np.mean(word_vecs, axis=0)
    return vector

menu = {}
menu['1'] = "Compute similarity within clusters"
menu['2'] = "Compute similarity between clusters"
menu['3'] = "Exit"

while True:
    options = menu.keys()
    #options.sort()
    for entry in options:
        print (entry, menu[entry])
    selection = input("Please Select: ")
    total = 0
    if selection == '3':
        break;
    print("\nLoading Model for Word2Vec")
    model = gensim.models.Word2Vec(brown.sents())   # Default MODEL IN GENSIM
    print("\nModel loaded")
    if selection == '1':        #TF-IDF representation within clusters
        dat = []
        answerWord2Vec = []
        for n in brown.categories():
            print("\n\nDividing each category into 2 documents: ", n)
            rawWords = brown.words(categories = n)
            cutOff = len(rawWords)/2
            counter = 0
            textA = ""
            textB = ""
            for w in rawWords:                  #It is super slow
                if counter < cutOff:
                    textA = textA + " " + w     #Separete the category into two documents
                else:
                    textB = textB + " " + w
                counter+=1
            
            documentA = textA.split(' ')
            documentB = textB.split(' ')
            documentA = cleanDocument(documentA)
            documentB = cleanDocument(documentB)
            dat.append(documentA)
            dat.append(documentB)
			
            #Vec2Word Representation Using Gensic
            vecA = get_mean_vector(model, documentA) #get the centroid of the document
            vecB = get_mean_vector(model, documentB) #get the centroid of the document
            a = np.array(vecA)
            b = np.array(vecB)
            dot = np.dot(a,b)
            norma = np.linalg.norm(a)
            normb = np.linalg.norm(b)
            cos = dot / (norma * normb)             #Calculate the cosine with the Word2Vec representation
            answerWord2Vec.append(cos)
            print("Documents processed...")
            
        #Calculate the TFIDF Matrix
        dictionary = corpora.Dictionary(dat)
        corpus = [dictionary.doc2bow(text) for text in dat]
        tfidf = models.TfidfModel(corpus)
        corpus_tfidf = tfidf[corpus]
        index = similarities.MatrixSimilarity(corpus_tfidf)

        #Sklearn representation
        data = []
        for doc in dat:
            data1 = ""
            for word in doc:
                if word not in stopwords and len(word) > 1:
                    data1 = data1 + " " + word
            data.append(data1)
        vectorizer = TfidfVectorizer()
        vectors = vectorizer.fit_transform(data).toarray()

        cx = lambda a, b : round(np.inner(a, b)/(LA.norm(a)*LA.norm(b)), 3)

        #Gensim SoftCosineSimilarity
        termsim_index = WordEmbeddingSimilarityIndex(model.wv)
        dictionary = Dictionary(dat)
        bow_corpus = [dictionary.doc2bow(document) for document in dat]
        similarity_matrix = SparseTermSimilarityMatrix(termsim_index, dictionary)  # construct similarity matrix
        docsim_index = SoftCosineSimilarity(bow_corpus, similarity_matrix)

        cat = brown.categories()
        for x in range(0,len(cat)*2,2):
            print("\n\nCluster: ", cat[x//2])
            print("\nTF-IDF Representation using Gensim")
            answer = index[corpus_tfidf[x]]
            print("Cosine Similarity: ",answer[x+1])

            print("\n\nTF-IDF Representation Using Sklearn")
            a = vectors[x]
            b = vectors[x+1]
            cos = cx(a,b)
            print("Cosine Similarity: ",cos)

            print("\n\nWord2Vec representation Using Gensim")
            print("Cosine Similarity: ",answerWord2Vec[x//2])

            print("\n\nWord2Vec representation Using Gensim and SoftCosineSimilarity")
            #Vec2Word Representation Using Gensic
            query = 'graph trees computer'.split()  # make a query
            sims = docsim_index[bow_corpus[x]]
            print("Cosine Similarity: ", sims[x+1])

    if selection == '2':
        print("\nComputing TD-IDF and Word2Vec matrix...\n")
        cat = brown.categories()
        dat = []
        for x in range(0,len(cat)):
            documentA = brown.words(categories=cat[x])
            documentA = cleanDocument(documentA)
            dat.append(documentA)

        #Calculate the TFIDF Matrix
        dictionary = corpora.Dictionary(dat)
        corpus = [dictionary.doc2bow(text) for text in dat]
        tfidf = models.TfidfModel(corpus)                       #TF-IDF Matrix
        corpus_tfidf = tfidf[corpus]
        index = similarities.MatrixSimilarity(corpus_tfidf)     #Calculate similarity

        #Sklearn representation
        data = []
        for doc in dat:
            data1 = ""
            for word in doc:
                if word not in stopwords and len(word) > 1:
                    data1 = data1 + " " + word
            data.append(data1)
        vectorizer = TfidfVectorizer()
        vectors = vectorizer.fit_transform(data).toarray()
        cx = lambda a, b : round(np.inner(a, b)/(LA.norm(a)*LA.norm(b)), 3)

        #Gensim SoftCosineSimilarity
        termsim_index = WordEmbeddingSimilarityIndex(model.wv)
        dictionary = Dictionary(dat)
        bow_corpus = [dictionary.doc2bow(document) for document in dat]
        similarity_matrix = SparseTermSimilarityMatrix(termsim_index, dictionary)  # construct similarity matrix
        docsim_index = SoftCosineSimilarity(bow_corpus, similarity_matrix)
        
        cat = brown.categories()
        for x in range(0,len(cat)):
            for y in range(x+1, len(cat)):
                print("\n\nClusters: ",cat[x], "and",cat[y])
                print("\nTF-IDF Representation using Gensim")
                answer = index[corpus_tfidf[x]]
                print("Cosine Similarity: ",answer[y])

                print("\n\nTF-IDF Representation Using Sklearn")
                a = vectors[x]
                b = vectors[y]
                cos = cx(a,b)
                print("Cosine Similarity: ",cos)

                print("\n\nWord2Vec representation Using Gensim and mean_vector")
                #Vec2Word Representation Using Gensic
                vecA = get_mean_vector(model, dat[x]) #get the centroid of the document
                vecB = get_mean_vector(model, dat[y]) #get the centroid of the document
                a = np.array(vecA)
                b = np.array(vecB)
                dot = np.dot(a,b)
                norma = np.linalg.norm(a)
                normb = np.linalg.norm(b)
                cos = dot / (norma * normb)             #Calculate the cosine with the Word2Vec representation
                print("Cosine Similarity: ",cos)

                print("\n\nWord2Vec representation Using Gensim and SoftCosineSimilarity")
                #Vec2Word Representation Using Gensic
                query = 'graph trees computer'.split()  # make a query
                sims = docsim_index[bow_corpus[x]]
                print("Cosine Similarity: ", sims[y])
    print(' ')
    print(' ')
