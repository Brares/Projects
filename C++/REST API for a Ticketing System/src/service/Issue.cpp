/**
 * @author Jonathan Flores
 * @date 2019-12-01
 * Copyright 2019
*/

#include "string"
#include "vector"
#include "Issue.h"

Issue::Issue() {
}

Issue::Issue(std::string _title, std::string _comment,
             int _creator,
             TypeIssue _type, Priority _priority, OS _os, Component _comp) {
    title = _title;
    Comment tmpcomment(_comment);
    comments.push_back(tmpcomment);
    description = tmpcomment;
    statusIssue = Issue::New;
    //assignedTo = _assignedTo;
    creator = _creator;
    typeIssue = _type;
    priority = _priority;
    os = _os;
    component = _comp;
}

Issue::~Issue() {
}
// take a input string turn it into a comment
// then put it in the comment vector
void Issue::addComment(std::string _comment) {
    Comment comment(_comment);
    comments.push_back(comment);
}
// take a comment object push it into comment vector
void Issue::addComment(Comment _comment) {
    comments.push_back(_comment);
}

int Issue::getID() {
    return ID;
}

std::string Issue::getTitle() {
    return title;
}

std::string Issue::getDescription() {
    return description.getText();
}

Issue::StatusIssue Issue::getStatusIssue() {
    return statusIssue;
}

std::string Issue::getStrStatusIssue() {
    std::string result;
    if (statusIssue == New)
        result = "New";
    if (statusIssue == Assigned)
        result = "Assigned";
    if (statusIssue == Fixed)
        result = "Fixed";
    if (statusIssue == WontFix)
        result = "WontFix";
    return result;
}

int Issue::getAssignedTo() {
    return assignedTo;
}

int Issue::getCreator() {
    return creator;
}
//create a new comment object and put the index comment in it.
Comment Issue::getAComment(int index) {
    Comment tmp;
    tmp = comments[index];
    return tmp;
}

std::vector<Comment> Issue::getComments() {
    return comments;
}

Issue::TypeIssue Issue::getTypeIssue() {
    return typeIssue;
}

std::string Issue::getStrTypeIssue() {
    std::string result;
    if (typeIssue == Feature)
        result = "Feature";
    if (typeIssue == Bug)
        result = "Bug";
    if (typeIssue == Task)
        result = "Task";
    return result;
}

Issue::Priority Issue::getPriority() {
    return priority;
}

std::string Issue::getStrPriority() {
    std::string result;
    if (priority == Low)
        result = "Low";
    if (priority == Normal)
        result = "Normal";
    if (priority == High)
        result = "High";
    return result;
}

Issue::OS Issue::getOS() {
    return os;
}

std::string Issue::getStrOS() {
    std::string result;
    if (os == Windows)
        result = "Windows";
    if (os == MACOS)
        result = "Mac";
    if (os == Linux)
        result = "Linux";
    return result;
}

Issue::Component Issue::getComponent() {
    return component;
}

std::string Issue::getStrComponent() {
    std::string result;
    if (component == Software)
        result = "Software";
    if (component == Hardware)
        result = "Hardware";
    return result;
}

void Issue::setID(int _id) {
    ID = _id;
}

void Issue::setTitle(std::string _title) {
    title = _title;
}
//the description is the comment at [0]
void Issue::setDescription(std::string _description) {
    Comment tmp(_description);
    description = tmp;
    if (comments.size() > 0)
        comments[0] = tmp;
    else
        comments.push_back(tmp);
}

void Issue::setDescription(Comment _comment) {
    if (comments.size() == 0) {
        comments.push_back(_comment);
        description = _comment;
    } else {
        comments[0] = _comment;
        description = _comment;
    }
}

void Issue::setStatusIssue(StatusIssue _statusIssue) {
    statusIssue = _statusIssue;
}

void Issue::setAssignedTo(int _userID) {
    assignedTo = _userID;
}

void Issue::setCreator(int _userID) {
    creator = _userID;
}

void Issue::setTypeIssue(TypeIssue _typeIssue) {
    typeIssue = _typeIssue;
}

void Issue::setPriority(Priority _priority) {
    priority = _priority;
}

void Issue::setOS(OS _os) {
    os = _os;
}

void Issue::setComponent(Component _component) {
    component = _component;
}

void Issue::updateComment(Comment _comment, int index) {
    comments[index] = _comment;
}

void Issue::setComments(std::vector<Comment> _comments) {
    comments = _comments;
}
