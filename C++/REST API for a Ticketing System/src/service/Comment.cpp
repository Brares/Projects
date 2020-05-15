/**
 * @author Jonathan Flores
 * @date 2019-12-01
 * Copyright 2019
*/

#include "string"
#include "Comment.h"

Comment::Comment() {
}

Comment::Comment(std::string _text) {
    text = _text;
}

Comment::Comment(std::string _text, int _creator) {
    text = _text;
    creator = _creator;
}

std::string Comment::getText() {
    return text;
}

int Comment::getCreator() {
    return creator;
}

void Comment::setText(std::string _text) {
    text = _text;
}

void Comment::setCreator(int _creator) {
    creator = _creator;
}
