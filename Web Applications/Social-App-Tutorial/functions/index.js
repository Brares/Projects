const functions = require("firebase-functions");
const admin = require('firebase-admin');

const app = require('express')();

admin.initializeApp();

const firebaseConfig = {
    apiKey: "AIzaSyChj5Ers8FRTvOLok75BIIm8BXw3UTcI70",
    authDomain: "socialapptutorial-1fee5.firebaseapp.com",
    databaseURL: "https://socialapptutorial-1fee5.firebaseio.com",
    projectId: "socialapptutorial-1fee5",
    storageBucket: "socialapptutorial-1fee5.appspot.com",
    messagingSenderId: "812381089663",
    appId: "1:812381089663:web:e3ad18c9ce755f3acab44a",
    measurementId: "G-L0YF3FRSNS"
  };

const firebase = require('firebase');
const { user } = require("firebase-functions/lib/providers/auth");
firebase.initializeApp(firebaseConfig);

const db = admin.firestore();

app.get('/posts', (req, res) => {
    admin
        .firestore()
        .collection('posts')
        .orderBy('createdAt', 'desc')
        .get()
        .then((data) => {
        let posts = [];
        data.forEach((doc) => {
            posts.push({
                postId: doc.id,
                body: doc.data().body,
                user: doc.data().user,
                createdAt: doc.data().createdAt                
            });
        });
        return res.json(posts);
    })        
    .catch((err) => console.error(err));
});

const isEmail = (email) => {
    const emailRegEx = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    if (email.match(emailRegEx)) return true;
    else return false;
};

const isEmpty = (string) => {
    if (String(string).trim() === '') return true;
    else return false;
};

//Create a Post
app.post('/post', (req, res) => {
    if(req.method !== 'POST') {
        return res.status(400).json({ error: 'Method not allowed' });
    }
    const newPost = {
        body: req.body.body,
        user: req.body.user,
        createdAt: new Date().toISOString()
    };

    admin.firestore()
        .collection('posts')
        .add(newPost)
        .then(doc => {
            res.json({ message: `document ${doc.id} created successfully` });
        })
        .catch((err) => {
            res.status(500).json({ error: 'Something went wrong' });
            console.error(err);
        });
});

//Sign Up route
app.post('/signup', (req, res) => {
    const newUser = {
        email: req.body.email,
        password: req.body.password,
        confirmPassword: req.body.confirmPassword,
        username: req.body.username
    };

    let errors = {};

    if (isEmpty(newUser.email)) {
        errors.email = 'Must not be empty';
    } else if (!isEmail(newUser.email)) {
        errors.email = 'Must be a valid Email';
    }

    if (isEmpty(newUser.password)) errors.password = "Must not be empty";
    if (newUser.confirmPassword !== newUser.password) errors.confirmpassword = "Password must match";
    if (isEmpty(newUser.username)) errors.username = "Must not be empty";

    if (Object.keys(errors).length > 0 ) return res.status(400).json(errors);

    let token, userId;
    db.doc(`/users/${newUser.username}`).get()
        .then(doc => {
            if (doc.exists) {
                return res
                    .status(400)
                    .json({ usename: 'this username already exists'});
            } else {
                return firebase
                    .auth()
                    .createUserWithEmailAndPassword(newUser.email, newUser.password);
            }
        })
        .then(data => {
            userId = data.user.uid;
            return data.user.getIdToken();
        })
        .then(idToken => {
            token = idToken;
            const userCredentials = {
                username: newUser.username,
                email: newUser.email,
                createdAt: new Date().toISOString(),
                userId
            };
            return db.doc(`users/${newUser.username}`).set(userCredentials);
        })
        .then(() => {
            return res.status(201).json({ token });
        })
        .catch((err) => {
            console.error(err);
            if (err.code === 'auth/email-already-in-use') {
                return res
                .status(400)
                .json({ email: 'Email is already in use'});
            } else {
                return res
                .status(500)
                .json({ error: err.code});
            }
        });
});

//Login

app.post('/login', (req, res) => {
    const user = {
        email: req.body.email,
        password: req.body.password
    };

    let errors = {};

    if (isEmpty(user.email)) errors.email = "Must not be empty"; 
    if (isEmpty(user.password)) errors.password = "Must not be empty"; 

    if (Object.keys(errors).length > 0) return res.status(400).json(errors);

    firebase
        .auth()
        .signInWithEmailAndPassword(user.email, user.password)
        .then(data => {
            return data.user.getIdToken();
        })
        .then(token => {
            return res.json({token});
        })
        .catch(err => {
            console.error(err);
            if (err.code === 'auth/user-not-found') { 
                return res
                .status(403)
                .json({ general: 'User does not exist' });
            } else if (err.code === 'auth/wrong-password') {
                return res
                .status(403)
                .json({ general: 'Wrong credentials, please try again' });
            } else {
                return res
                .status(500)
                .json({ error: err.code });
            }
        });
});
exports.api = functions.https.onRequest(app);