const { db } = require('../utilities/admin');

exports.getAllPosts = (req, res) => {
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
};

exports.createAPost = (req, res) => {
    if(isEmpty(req.body.body)) {
        return res.status(400).json({ error: 'Body must not be empty' });
    }
    const newPost = {
        body: req.body.body,
        username: req.user.username,
        createdAt: new Date().toISOString()
    };

    db.collection('posts')
        .add(newPost)
        .then(doc => {
            res.json({ message: `document ${doc.id} created successfully` });
        })
        .catch((err) => {
            res.status(500).json({ error: 'Something went wrong' });
            console.error(err);
        });
};