# Program By Jonathan Flores
# Assigment 4 - Question 3 - CPSC 4310

import string
import gensim
import random
import nltk
import pandas as pd
import numpy as np
from tqdm import tqdm
from nltk.corpus import brown
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
from nltk.stem.snowball import SnowballStemmer
from gensim.models import Word2Vec
from gensim.models import Doc2Vec
from gensim.corpora import Dictionary
from gensim.models.doc2vec import TaggedDocument
from gensim.utils import simple_preprocess
from sklearn import utils
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.linear_model import SGDClassifier
from sklearn.feature_extraction.text import CountVectorizer,TfidfVectorizer
from sklearn.metrics import accuracy_score, f1_score
from sklearn.neural_network import MLPClassifier
import multiprocessing
cores = multiprocessing.cpu_count()
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

def labelizeReviews(reviews, label_type):
    labelized = []
    cat = brown.categories()
    for i,v in enumerate(reviews):
        label = cat[i]
        labelized.append(LabeledSentence(v, [label]))
    return labelized

def vec_for_learning(model, tagged_docs):
    sents = tagged_docs
    targets, regressors = zip(*[(doc.tags[0], model.infer_vector(doc.words, steps=20)) for doc in sents])
    return targets, regressors

def tokenize_text(text):
    tokens = []
    print(text)
    for word in nltk.word_tokenize(sent):
        if len(word) < 2:
            continue
        tokens.append(word.lower())
    tokens = cleanDocument(tokens)
    tokens = [word.lower() for word in tokens if re.match('^[a-zA-Z]+', word)]
    print(tokens)
    return tokens

def tag_docs(docs, col):
    tagged = docs.apply(lambda r: TaggedDocument(words=simple_preprocess(r[col]), tags=[r.label]), axis=1)
    return tagged

def train_doc2vec_model(tagged_docs, window, size):
    sents = tagged_docs.values
    doc2vec_model = Doc2Vec(sents, vector_size=size, window=window, epochs=20, dm=1)
    return doc2vec_model

def vec_for_learning(doc2vec_model, tagged_docs):
    sents = tagged_docs.values
    targets, regressors = zip(*[(doc.tags[0], doc2vec_model.infer_vector(doc.words, steps=20)) for doc in sents])
    return targets, regressors

menu = {}
menu['1'] = "Logistic Repression or Single-layer perceptron"
menu['2'] = "Multi-layer neural network"
menu['3'] = "Exit"

print("\nLoading Model for Word2Vec")
model = gensim.models.Word2Vec(brown.sents())   # Default MODEL IN GENSIM
LabeledSentence = gensim.models.doc2vec.LabeledSentence
print("\nModel loaded\n\n")

while True:
    options = menu.keys()
    #options.sort()
    for entry in options:
        print (entry, menu[entry])
    selection = input("Please Select: ")
    total = 0
    if selection == '3':
        break;
    if selection == '1':
        cat = brown.categories()
        tmpS = []
        tmpC = []
        for x in range(0,len(cat)):
            for sent in brown.sents(categories=cat[x]):
                tmp = ""
                for word in sent:
                    tmp += " " + word
                tmpS.append(tmp)
                tmpC.append(cat[x])
        dat = {'sents':tmpS,
               'Category':tmpC}
        df = pd.DataFrame(dat)
        print("\nTable with the data")
        print(df)    
        
        print("\nCalculating Logistic Regresion...\n")
        train_data, test_data = train_test_split(df, test_size=0.1)

        train_tagged = train_data.apply(
            lambda r: TaggedDocument(words=simple_preprocess(r['sents']), tags=[r.Category]), axis=1)
        test_tagged = test_data.apply(
            lambda r: TaggedDocument(words=simple_preprocess(r['sents']), tags=[r.Category]), axis=1)
        model = train_doc2vec_model(train_tagged,300,3)

        y_train, X_train = vec_for_learning(model, train_tagged)
        y_test, X_test = vec_for_learning(model, test_tagged)

        logreg = LogisticRegression()
        logreg.fit(X_train, y_train)
        y_pred = logreg.predict(X_test)
        print('Testing accuracy %s' % accuracy_score(y_test, y_pred))

        print("\nCalculating Logistic Regression after mixing Data...\n")
        train_data, test_data = train_test_split(df, test_size=0.3)

        train_tagged = train_data.apply(
            lambda r: TaggedDocument(words=simple_preprocess(r['sents']), tags=[r.Category]), axis=1)
        test_tagged = test_data.apply(
            lambda r: TaggedDocument(words=simple_preprocess(r['sents']), tags=[r.Category]), axis=1)
        model = train_doc2vec_model(train_tagged,300,3)

        y_train, X_train = vec_for_learning(model, train_tagged)
        y_test, X_test = vec_for_learning(model, test_tagged)

        logreg = LogisticRegression()
        logreg.fit(X_train, y_train)
        y_pred = logreg.predict(X_test)
        print('Testing accuracy %s' % accuracy_score(y_test, y_pred))

    if selection == '2':
        cat = brown.categories()
        tmpS = []
        tmpC = []
        for x in range(0,len(cat)):
            for sent in brown.sents(categories=cat[x]):
                tmp = ""
                for word in sent:
                    tmp += " " + word
                tmpS.append(tmp)
                tmpC.append(cat[x])
        dat = {'sents':tmpS,
               'Category':tmpC}
        df = pd.DataFrame(dat)
        print("\nTable with the data")
        print(df)

        print("\nCalculating MLP...\n")
        train_data, test_data = train_test_split(df, test_size=0.1)

        train_tagged = train_data.apply(
            lambda r: TaggedDocument(words=simple_preprocess(r['sents']), tags=[r.Category]), axis=1)
        test_tagged = test_data.apply(
            lambda r: TaggedDocument(words=simple_preprocess(r['sents']), tags=[r.Category]), axis=1)
        model = train_doc2vec_model(train_tagged,300,3)

        y_train, X_train = vec_for_learning(model, train_tagged)
        y_test, X_test = vec_for_learning(model, test_tagged)

        mlp = MLPClassifier(hidden_layer_sizes=(150,100,50),max_iter=300, activation='relu',solver='adam',random_state=1)
        mlp.fit(X_train, y_train)
        y_pred = mlp.predict(X_test)
        print('MLP accuracy %s' % accuracy_score(y_test, y_pred))

        print("\nCalculating MLP after mixing Data...\n")
        train_data, test_data = train_test_split(df, test_size=0.3)

        train_tagged = train_data.apply(
            lambda r: TaggedDocument(words=simple_preprocess(r['sents']), tags=[r.Category]), axis=1)
        test_tagged = test_data.apply(
            lambda r: TaggedDocument(words=simple_preprocess(r['sents']), tags=[r.Category]), axis=1)
        model = train_doc2vec_model(train_tagged,300,3)

        y_train, X_train = vec_for_learning(model, train_tagged)
        y_test, X_test = vec_for_learning(model, test_tagged)

        mlp = MLPClassifier(hidden_layer_sizes=(150,100,50),max_iter=300, activation='relu',solver='adam',random_state=1)
        mlp.fit(X_train, y_train)
        y_pred = mlp.predict(X_test)
        print('MLP accuracy %s' % accuracy_score(y_test, y_pred))

    print(' ')
    print(' ')
