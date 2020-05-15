# Program By Jonathan Flores
# Assigment 1 - CPSC 4310

from nltk.corpus import brown
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
from nltk.stem.snowball import SnowballStemmer
stopwords = stopwords.words('english')
lemmatizer = WordNetLemmatizer()
stemmer = SnowballStemmer("english", ignore_stopwords=True)
menu = {}
menu['1'] = "Display results with Stopwords"
menu['2'] = "Display results without Stopwords"
menu['3'] = "Display results without Stopwords and Lemmatization"
menu['4'] = "Display results without Stopwords and Stemming"
menu['5'] = "Exit"

while True:
    options = menu.keys()
    for entry in options:
        print (entry, menu[entry])
    selection = input("Please Select: ")
    total = 0
    if selection == '5':
        break;
    for n in brown.categories():
        words = brown.words(categories=n)
        noStopwords = [w for w in words if w.lower() not in stopwords]
        if selection == '1':
            count = len(words)
            vocabulary = len(set(words))
            total = total + vocabulary
            print('Category: ' + n)
            datastring = "\tWord Tokens with Stopwords: " + str(count)
            print(datastring)
            datastring = "\tWord Types: with Stopwords: " + str(vocabulary)
            print(datastring)
        elif selection == '2':
            count = len(noStopwords)
            vocabulary = len(set(noStopwords))
            total = total + vocabulary
            print('Category: ' + n)
            datastring = "\tWord Tokens without Stopwords: " + str(count)
            print(datastring)
            datastring = "\tWord Types: without Stopwords: " + str(vocabulary)
            print(datastring)
        elif selection == '3':
            lemmas = [lemmatizer.lemmatize(w) for w in noStopwords]
            count = len(lemmas)
            vocabulary = len(set(lemmas))
            total = total + vocabulary
            print('Category: ' + n)
            datastring = "\tWord Tokens without Stopwords and Lemmatization: " + str(count)
            print(datastring)
            datastring = "\tWord Types: without Stopwords and Lemmatization: " + str(vocabulary)
            print(datastring)
        elif selection == '4':
            stems = [stemmer.stem(w) for w in noStopwords]
            count = len(stems)
            vocabulary = len(set(stems))
            total = total + vocabulary
            print('Category: ' + n)
            datastring = "\tWord Tokens without Stopwords and Stemming: " + str(count)
            print(datastring)
            datastring = "\tWord Types: without Stopwords and Stemming: " + str(vocabulary)
            print(datastring)
        else:
            print('Unknown Option Selected!')
            break;
    print(' ')
    print('Total Vocabulary: ' + str(total))
    print(' ')
    print(' ')
