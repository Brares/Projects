const { admin, db } = require('../utilities/admin');

const firebaseConfig = require('../utilities/firebaseConfig');

const firebase = require('firebase');
const { user } = require("firebase-functions/lib/providers/auth");
const { decode } = require("firebase-functions/lib/providers/https");
firebase.initializeApp(firebaseConfig);

const { validateSignUp, validateLogin } = require('../utilities/validation');
const { FILE } = require('dns');
const { ResultStorage } = require('firebase-functions/lib/providers/testLab');

exports.login = (req, res) => {
    const user = {
        email: req.body.email,
        password: req.body.password
    };

    const { valid, errors } = validateLogin(user);
    
    if(!valid) return res.status(400).json(errors);

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
};

exports.signup = (req, res) => {
    const newUser = {
        email: req.body.email,
        password: req.body.password,
        confirmPassword: req.body.confirmPassword,
        username: req.body.username
    };

    const { valid, errors } = validateSignUp(newUser);
    
    if(!valid) return res.status(400).json(errors);

    const noImg = 'noimg.png';

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
                imageUrl: `https://firebasestorage.googleapis.com/v0/b/${firebaseConfig.storageBucket}/o/${noImg}?alt=media`,
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
};

exports.uploadImage = (req, res) => {
    const BusBoy = require('busboy');
    const path = require('path');
    const os = require('os');
    const fs = require('fs');

    const busboy = new BusBoy({ headers: req.headers });

    let imageFileName;
    let imageToBeUploaded = {};

    busboy.on('file', (fieldname, file, filename, encoding, mimetype) => {
        if (mimetype !== 'image/jpg' && mimetype !== 'image/png') {
            return res.status(400).json({ error: 'Wrong file type submitted'});
        }

        const imageExtension = filename.split(".")[filename.split(".").length-1];
        imageFileName = `${Math.round(Math.random() * 1000000000000).toString()}.${imageExtension}`;
        const filepath = path.join(os.tmpdir(), imageFileName);
        imageToBeUploaded = { filepath, mimetype };

        file.pipe(fs.createWriteStream(filepath));    
    });
    busboy.on('finish', () => {
        admin.storage().bucket().upload(imageToBeUploaded.filepath, {
            resumable: false,
            metadata: {
                metadata: {
                    contentType: imageToBeUploaded.mimetype
                }
            }
        })
        .then(() => {
            const imageUrl = `https://firebasestorage.googleapis.com/v0/b/${firebaseConfig.storageBucket}/o/${imageFileName}?alt=media`;
            return db.doc(`/users/${req.user.username}`).update({ imageUrl});
        })
        .then(() => {
            return res.json({ message: 'Image uploaded successfully'});
        })
        .then(err => {
            console.error(err);
            return res.status(500).json({ error: err.code});
        });
    });
    busboy.end(req.rawBody);
};