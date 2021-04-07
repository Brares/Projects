const functions = require("firebase-functions");

const app = require('express')();

const { getAllPosts, createAPost } = require('./handlers/posts');
const { signup, login, uploadImage, addUserDetails} = require('./handlers/users');

const FBAuth = require('./utilities/FBAuth');

//Posts Functions
app.get('/posts', getAllPosts);
app.post('/post', FBAuth, createAPost);

//User Functions
app.post('/signup', signup);
app.post('/login', login);
app.post('/user/image', FBAuth, uploadImage);
app.post('/user', FBAuth, addUserDetails);


exports.api = functions.https.onRequest(app);