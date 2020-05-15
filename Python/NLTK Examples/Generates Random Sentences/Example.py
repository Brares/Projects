# Jonathan Flores
# Assigment 2 Question 3
import nltk
import random
import string
from nltk import FreqDist
from nltk.corpus import brown
from nltk.util import ngrams
menu = {}
menu['1'] = "Bi-grams"
menu['2'] = "Tri-grams"
menu['3'] = "Exit"

text = []
for sentence in brown.sents(): # Compute text from the beginning only once
    text.append('<s>')
    for word in sentence:
        if word != "''":
            text.append(word)
    text.append('</s>')
bigrams = nltk.bigrams(text)
cfdBiagrams = nltk.ConditionalFreqDist(bigrams)
trigrams = nltk.trigrams(text)
condition_pairs = (((w0, w1), w2) for w0, w1, w2 in trigrams)
cfd = nltk.ConditionalFreqDist(condition_pairs)
while True:
    print("Random Sentences Generator using Shannon Visualization Method")
    options = menu.keys()
    for entry in options:
        print(entry, menu[entry])
    selection = input("Please Select: ")
    total = 0
    if selection == '3':
        break;
    result = ""
    if selection == '1':
        word = '<s>'
        print(' ')
        while word != '</s>':
            if word != '<s>':
                if word in string.punctuation or word == "''": # I did remove punctuations because the results were kind of bad with them
                    if word == '.' or word == ',':
                        result = result + word
                else:
                    result = result + " " + word
            word = random.choice(list(cfdBiagrams[word].keys()))      
        print(result)
    elif selection == '2':
        word = '<s>'
        word2 = random.choice(list(cfdBiagrams[word].keys()))
        words = tuple((word,word2))
        print(' ')
        result = result + word2
        while word != '</s>':		
            possibleWords = list(cfd[words].keys())
            if len(possibleWords) > 1:
                word = random.choice(possibleWords)
            else:
                word = possibleWords[0]
            words = tuple((word2,word))
            lastWord2 = word2
            word2 = word
            if word != '</s>':
                if word in string.punctuation: #I did not remove punctuation because there are important in this situation
                    result = result + word  
                else:
                    result = result + " " + word
        print(result) 
    else:
        print('Unknown Option Selected!')
        break;
    print(' ')


