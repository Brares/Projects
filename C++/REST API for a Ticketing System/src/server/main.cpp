/**
 * @author Jonathan Flores
 * @date 2019-12-01
 * Copyright 2019
*/

#include <restbed>
#include <nlohmann/json.hpp>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Issue.h>
#include <User.h>
#include <Comment.h>

// Response header to prevent a cross-site validation problem
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

// Response header to close connection
#define CLOSE_CONNECTION { "Connection", "close" }

/// Global Variable holding all the Issues
std::vector<Issue> issues;
/// Global Variable holding all the Users
std::vector<User> users;
/// Global Variable holding the next available Issue ID
int issuesCounter = 1;
/// Global Variable holding the next available User ID
int userCounter = 1;

/**
* Read a string containing a Status Issue
* Return status enum
*/
Issue::StatusIssue ReadStatusIssue(const std::string &status) {
    Issue::StatusIssue statusIssue;
    if (status == "New")
        statusIssue = Issue::New;
    if (status == "Assigned")
        statusIssue = Issue::Assigned;
    if (status == "Fixed")
        statusIssue = Issue::Fixed;
    if (status == "WontFix")
        statusIssue = Issue::WontFix;
    return statusIssue;
}

/**
* Read a string containing a Type Issue
* Return type enum
*/
Issue::TypeIssue ReadTypeOfIssue(const std::string &type) {
    Issue::TypeIssue typeIssue;
    if (type == "Feature")
        typeIssue = Issue::Feature;
    if (type == "Bug")
        typeIssue = Issue::Bug;
    if (type == "Task")
        typeIssue = Issue::Task;
    return typeIssue;
}

/**
* Read a string containing a Priority Issue
* Return priority enum
*/
Issue::Priority ReadPriorityOfIssue(const std::string &priority) {
    Issue::Priority priorityIssue;
    if (priority == "Low")
        priorityIssue = Issue::Low;
    if (priority == "Normal")
        priorityIssue = Issue::Normal;
    if (priority == "High")
        priorityIssue = Issue::High;
    return priorityIssue;
}

/**
* Read a string containing an OS Issue
* Return os enum
*/
Issue::OS ReadOSIssue(const std::string &tmp) {
    Issue::OS os;
    if (tmp == "Windows")
        os = Issue::Windows;
    if (tmp == "Mac")
        os = Issue::MACOS;
    if (tmp == "Linux")
        os = Issue::Linux;
    return os;
}

/**
* Read a string containing a Component Issue
* Return component enum
*/
Issue::Component ReadComponentOfIssue(const std::string &tmp) {
    Issue::Component comp;
    if (tmp == "Hardware")
        comp = Issue::Hardware;
    if (tmp == "Software")
        comp = Issue::Software;
    return comp;
}

/**
* Read a string containing a Type Of User
* Return userType enum
*/
User::UserType ReadUserType(const std::string &tmp) {
    User::UserType type;
    if (tmp == "Employee")
        type = User::Employee;
    if (tmp == "Client")
        type = User::Client;
    return type;
}

/**
* Check if the User ID exist
* @param _userID User ID to be checked
* Return the index of the User. Otherwise -1
*/
int CheckUserExists(int _userID) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getID() == _userID)
            return i;
    }
    return -1;
}

/**
* Check if the Username is already being used
* @param _userName Username to be checked
* Return the index of the User. Otherwise -1
*/
int CheckUserNameExists(const std::string &_userName) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getName() == _userName)
            return i;
    }
    return -1;
}

/**
* Check if the Issue ID exist
* @param _issueID Issue ID to be checked
* Return the index of the Issue. Otherwise -1
*/
int CheckIssueExists(int _issueID) {
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getID() == _issueID)
            return i;
    }
    return -1;
}

/**
* Save the state of the server
* @param _fileName name of file to save the state of the server
*/
void saveServer(std::string _fileName,
                const std::shared_ptr<restbed::Session >& session) {
    nlohmann::json resultJSON;
    std::string fileName = _fileName;
    std::ofstream save(fileName.c_str());
    save << issuesCounter << std::endl << userCounter << std::endl <<
    issues.size() << std::endl << users.size() << std::endl;
    for (int i = 0; i < users.size(); i++) {
        save << users[i].getID() << std::endl << users[i].getName()
        << std::endl << users[i].getStringUserType() << std::endl;
    }
    for (int i = 0; i < issues.size(); i++) {
        save << issues[i].getID() << std::endl
        << issues[i].getTitle() << std::endl
        << issues[i].getDescription() << std::endl
        << issues[i].getStrStatusIssue() << std::endl << issues[i].getCreator()
        << std::endl << issues[i].getAssignedTo() << std::endl
        << issues[i].getStrTypeIssue() << std::endl << issues[i].getStrPriority()
        << std::endl << issues[i].getStrOS() << std::endl << issues[i].getStrComponent()
        << std::endl;
        std::vector<Comment> comments;
        comments = issues[i].getComments();
        save << comments.size() << std::endl;
        for (int j = 1; j <comments.size(); j++) {
            save << comments[j].getText() << std::endl <<
            comments[j].getCreator() << std::endl;
        }
    }
    resultJSON["Status"] = "Server Saved";
    std::string response = resultJSON.dump();
    session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
}

/**
* Load the state of the server
* @param _fileName name of file to load the state of the server
*/
void loadServer(std::string _fileName,
                const std::shared_ptr<restbed::Session >& session) {
    std::string fileName = _fileName;
    std::ifstream load(fileName.c_str());
    if (load.good() == false) {
        nlohmann::json resultJSON;
        resultJSON["Status"] = "File not found";
        std::string response = resultJSON.dump();
        session->close(restbed::OK, response,
                { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                               CLOSE_CONNECTION });
    }
    load >> issuesCounter >> userCounter;
    int issuesSize, usersSize;
    load >> issuesSize >> usersSize;
    std::vector<User> tmpUsers;
    for (int i = 0; i < usersSize; i++) {
        int id;
        std::string name, userType;
        load >> id >> name >> userType;
        User tmp(name, ReadUserType(userType));
        tmp.setID(id);
        tmpUsers.push_back(tmp);
    }
    users = tmpUsers;
    std::vector<Issue> tmpIssues;
    for (int i = 0; i < issuesSize; i++) {
        int id, creator, assignedTo;
        int counter = 0;
        std::string title, description;
        std::string status, type, priority, os, component;
        std::string line;
        load >> id;
        while (std::getline(load, line)) {
            counter++;
            title = line;
            if (counter == 2) {break;}
        }
        counter = 0;
        while (std::getline(load, line)) {
            counter++;
            description = line;
            if (counter == 1) {break;}
        }
        load >> status >> creator >> assignedTo >> type
        >> priority >> os >> component;
        Issue tmp;
        tmp.setID(id);
        tmp.setTitle(title);
        tmp.setDescription(description);
        Comment tmpComment(description, creator);
        tmp.setDescription(tmpComment);
        tmp.setStatusIssue(ReadStatusIssue(status));
        tmp.setCreator(creator);
        tmp.setAssignedTo(assignedTo);
        tmp.setTypeIssue(ReadTypeOfIssue(type));
        tmp.setPriority(ReadPriorityOfIssue(priority));
        tmp.setOS(ReadOSIssue(os));
        tmp.setComponent(ReadComponentOfIssue(component));
        int numComments;
        load >> numComments;
        for (int i = 1; i < numComments; i++) {
            counter = 0;
            std::string text;
            int creatorComment;
            while (std::getline(load, line)) {
            counter++;
            text = line;
            if (counter == 2) {break;}
            }
            load >> creatorComment;
            Comment tmpComm(text, creatorComment);
            tmp.addComment(tmpComm);
        }
        tmpIssues.push_back(tmp);
    }
    issues = tmpIssues;
    nlohmann::json resultJSON;
    resultJSON["Status"] = "Server Loaded";
    std::string response = resultJSON.dump();
    session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
}

/**
* Create an Issue from a POST request
* @param newIssue from the parse method
* return the issueID of the new Issue as a JSON Object
*/
void createIssue(Issue newIssue,
                 const std::shared_ptr<restbed::Session >& session) {
    if (CheckUserExists(newIssue.getCreator()) == -1 ||
            users.size() == 0) {
            std::string resultStr = "The User Creator does not exist";
            nlohmann::json resultJSON;
            resultJSON["issueID"] = resultStr;
            std::string response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            issuesCounter--;
            return;
    }
    issues.push_back(newIssue);
    int result = issues.back().getID();
    std::string resultStr = std::to_string(result);
    nlohmann::json resultJSON;
    resultJSON["issueID"] = resultStr;
    std::string response = resultJSON.dump();

    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Create a User from a POST request
* @param newUser from the parse method
* return the userID of the new User as a JSON Object
*/
void createUser(User newUser,
                const std::shared_ptr<restbed::Session >& session) {
    if (CheckUserNameExists(newUser.getName()) != -1) {
        nlohmann::json resultJSON;
        resultJSON["userID"] = "Username already exists";
        std::string response = resultJSON.dump();
        session->close(restbed::OK, response,
        {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        userCounter--;
        return;
    }
    users.push_back(newUser);
    int result = users.back().getID();
    std::string resultStr = std::to_string(result);
    nlohmann::json resultJSON;
    resultJSON["userID"] = resultStr;
    std::string response = resultJSON.dump();

    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Create a Comment from a POST request
* @param comment from the parse method
* @param issueID ID of the issue where the comment is going to be added
* return the issueID and a message Comment Added as a JSON Object
*/
void createComment(Comment comment, int issueID,
                   const std::shared_ptr<restbed::Session >& session) {
    int issueIndex = CheckIssueExists(issueID);
    if (issueIndex < 0 || issues.size() == 0) {
        std::string resultStr = "The Issue does not exist";
        nlohmann::json resultJSON;
        resultJSON["commentID"] = resultStr;
        std::string response = resultJSON.dump();
        session->close(restbed::OK, response,
        {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                     CLOSE_CONNECTION });
        return;
    }
    if (CheckUserExists(comment.getCreator()) == -1 || users.size() == 0) {
        std::string resultStr = "The User ID for Creator does not exist";
        nlohmann::json resultJSON;
        resultJSON["commentID"] = resultStr;
        std::string response = resultJSON.dump();
        session->close(restbed::OK, response,
        {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        return;
    }
    issues[issueIndex].addComment(comment);
    std::string resultStr = std::to_string(issueID) +
    ". Comment added";
    nlohmann::json resultJSON;
    resultJSON["commentID"] = resultStr;
    std::string response = resultJSON.dump();
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Update an Issue from a POST request
* @param newIssue from the parse method
* Return a message saying Issue Updated or an error as a JSON Object
*/
void updateIssue(Issue newIssue,
                const std::shared_ptr<restbed::Session >& session) {
    if (CheckUserExists(newIssue.getAssignedTo()) == -1 ||
            users.size() == 0) {
            std::string resultStr = "The User AssignedTo does not exist";
            nlohmann::json resultJSON;
            resultJSON["Status"] = resultStr;
            std::string response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            return;
    }
    if (CheckUserExists(newIssue.getCreator()) == -1 ||
            users.size() == 0) {
            std::string resultStr = "The User Creator does not exist";
            nlohmann::json resultJSON;
            resultJSON["Status"] = resultStr;
            std::string response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            return;
    }

    int issueIndex = CheckIssueExists(newIssue.getID());
    if (issueIndex < 0 || issues.size() == 0) {
        std::string resultStr = "The Issue does not exist";
        nlohmann::json resultJSON;
        resultJSON["Status"] = resultStr;
        std::string response = resultJSON.dump();
        session->close(restbed::OK, response,
        {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                     CLOSE_CONNECTION });
        return;
    }
    issues[issueIndex] = newIssue;
    nlohmann::json resultJSON;
    resultJSON["Status"] = "Issue Updated";
    std::string response = resultJSON.dump();
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Update a User from a POST request
* @param newUser from the parse method
* Return a message saying User Updated or an error as a JSON Object
*/
void updateUser(User newUser,
                const std::shared_ptr<restbed::Session >& session) {
    int index = CheckUserNameExists(newUser.getName());
    if (index != -1 && users[index].getID() != newUser.getID()) {
        nlohmann::json resultJSON;
        resultJSON["Status"] = "Username already exists";
        std::string response = resultJSON.dump();
        session->close(restbed::OK, response,
        {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        return;
    }
    index = CheckUserExists(newUser.getID());
    if ( index == -1 ||
            users.size() == 0) {
            std::string resultStr = "The User ID does not exist";
            nlohmann::json resultJSON;
            resultJSON["Status"] = resultStr;
            std::string response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            issuesCounter--;
            return;
    }
    users[index] = newUser;
    nlohmann::json resultJSON;
    resultJSON["Status"] = "User Updated";
    std::string response = resultJSON.dump();
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Update a Comment from a POST request
* @param comment from the parse method
* @param issueID ID of the issue containing the comment
* @param _commentID ID of the comment to be updated
* Return a message saying Comment Updated or an error as a JSON Object
*/
void updateComment(Comment comment, int issueID, int _commentID,
                   const std::shared_ptr<restbed::Session >& session) {
    int issueIndex = CheckIssueExists(issueID);
    if (issueIndex < 0 || issues.size() == 0) {
        std::string resultStr = "The Issue does not exists";
        nlohmann::json resultJSON;
        resultJSON["Status"] = resultStr;
        std::string response = resultJSON.dump();
        session->close(restbed::OK, response,
        {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                     CLOSE_CONNECTION });
        return;
    }
    if (CheckUserExists(comment.getCreator()) == -1 || users.size() == 0) {
        std::string resultStr = "The User ID for Creator does not exist";
        nlohmann::json resultJSON;
        resultJSON["Status"] = resultStr;
        std::string response = resultJSON.dump();
        session->close(restbed::OK, response,
        {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        return;
    }

    issues[issueIndex].updateComment(comment, _commentID - 1);
    nlohmann::json resultJSON;
    resultJSON["Status"] = "Comment Updated";
    std::string response = resultJSON.dump();
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Get a list of All issues or just one Issue
* @param _id ID of the issue to be returned
* If ID = -1 means to return a list with all the issues
* If ID exits, the Issue information is returned as an JSON Object
*/
void getIssues(int _id,
                const std::shared_ptr<restbed::Session >& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    std::string response = "[";
    if (_id == -1) {
        for (int i = 0; i < issues.size(); i++) {
        resultJSON["ID"] = std::to_string(issues[i].getID());
        resultJSON["title"] = issues[i].getTitle();
        resultJSON["description"] = issues[i].getDescription();
        resultJSON["statusIssue"] = issues[i].getStrStatusIssue();
        resultJSON["assignedTo"] = std::to_string(issues[i].getAssignedTo());
        resultJSON["Creator"] = std::to_string(issues[i].getCreator());
        resultJSON["typeIssue"] = issues[i].getStrTypeIssue();
        resultJSON["priority"] = issues[i].getStrPriority();
        resultJSON["os"] = issues[i].getStrOS();
        resultJSON["component"] = issues[i].getStrComponent();
        response = response + resultJSON.dump();
        if (i != issues.size() -1)
            response = response + ", ";
    }
    } else {
        int index = CheckIssueExists(_id);
         if (index == -1 || issues.size() == 0) {
            std::string resultStr = "The Issue does not exist";
            nlohmann::json resultJSON;
            std::string response = "[";
            resultJSON["issueID"] = resultStr;
            response = response + resultJSON.dump();
            response = response + "]";
            session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        } else {
            resultJSON["ID"] = std::to_string(issues[index].getID());
            resultJSON["title"] = issues[index].getTitle();
            resultJSON["description"] = issues[index].getDescription();
            resultJSON["statusIssue"] = issues[index].getStrStatusIssue();
            resultJSON["assignedTo"] = std::to_string(issues[index].getAssignedTo());
            resultJSON["Creator"] = std::to_string(issues[index].getCreator());
            resultJSON["typeIssue"] = issues[index].getStrTypeIssue();
            resultJSON["priority"] = issues[index].getStrPriority();
            resultJSON["os"] = issues[index].getStrOS();
            resultJSON["component"] = issues[index].getStrComponent();
            response = response + resultJSON.dump();
        }
    }
    response = response + "]";
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Get a list of All Issues with certain priority
* @param _priority Priority of the Issues
* Returns all the Issues with the specified priority
*/
void searchByPriority(const std::string &_priority,
                const std::shared_ptr<restbed::Session >& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    std::string response = "[";
    std::vector<Issue> tmpIssues;
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getStrPriority() == _priority) {
            tmpIssues.push_back(issues[i]);
        }
    }
    for (int i = 0; i < tmpIssues.size(); i++) {
        if (tmpIssues[i].getStrPriority() == _priority) {
            resultJSON["ID"] = std::to_string(tmpIssues[i].getID());
            resultJSON["title"] = tmpIssues[i].getTitle();
            resultJSON["description"] = tmpIssues[i].getDescription();
            resultJSON["statusIssue"] = tmpIssues[i].getStrStatusIssue();
            resultJSON["assignedTo"] = std::to_string(tmpIssues[i].getAssignedTo());
            resultJSON["Creator"] = std::to_string(tmpIssues[i].getCreator());
            resultJSON["typeIssue"] = tmpIssues[i].getStrTypeIssue();
            resultJSON["priority"] = tmpIssues[i].getStrPriority();
            resultJSON["os"] = tmpIssues[i].getStrOS();
            resultJSON["component"] = tmpIssues[i].getStrComponent();
            response = response + resultJSON.dump();
            if (i != tmpIssues.size() -1)
                response = response + ", ";
        }
    }
    response = response + "]";
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Get a list of All Issues with certain status
* @param _status Status of the Issues
* Returns all the Issues with the specified status
*/
void searchByStatus(const std::string &_status,
                const std::shared_ptr<restbed::Session >& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    std::string response = "[";
    std::vector<Issue> tmpIssues;
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getStrStatusIssue() == _status) {
            tmpIssues.push_back(issues[i]);
        }
    }
    for (int i = 0; i < tmpIssues.size(); i++) {
        if (tmpIssues[i].getStrStatusIssue() == _status) {
            resultJSON["ID"] = std::to_string(tmpIssues[i].getID());
            resultJSON["title"] = tmpIssues[i].getTitle();
            resultJSON["description"] = tmpIssues[i].getDescription();
            resultJSON["statusIssue"] = tmpIssues[i].getStrStatusIssue();
            resultJSON["assignedTo"] = std::to_string(tmpIssues[i].getAssignedTo());
            resultJSON["Creator"] = std::to_string(tmpIssues[i].getCreator());
            resultJSON["typeIssue"] = tmpIssues[i].getStrTypeIssue();
            resultJSON["priority"] = tmpIssues[i].getStrPriority();
            resultJSON["os"] = tmpIssues[i].getStrOS();
            resultJSON["component"] = tmpIssues[i].getStrComponent();
            response = response + resultJSON.dump();
            if (i != tmpIssues.size() -1)
                response = response + ", ";
        }
    }
    response = response + "]";
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Get a list of All Issues with certain type
* @param _type Type of the Issues
* Returns all the Issues with the specified type
*/
void searchByType(const std::string &_type,
                const std::shared_ptr<restbed::Session >& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    std::string response = "[";
    std::vector<Issue> tmpIssues;
    for (int i = 0; i < issues.size(); i++) {
        if (issues[i].getStrTypeIssue() == _type) {
            tmpIssues.push_back(issues[i]);
        }
    }
    for (int i = 0; i < tmpIssues.size(); i++) {
        if (tmpIssues[i].getStrTypeIssue() == _type) {
            resultJSON["ID"] = std::to_string(tmpIssues[i].getID());
            resultJSON["title"] = tmpIssues[i].getTitle();
            resultJSON["description"] = tmpIssues[i].getDescription();
            resultJSON["statusIssue"] = tmpIssues[i].getStrStatusIssue();
            resultJSON["assignedTo"] = std::to_string(tmpIssues[i].getAssignedTo());
            resultJSON["Creator"] = std::to_string(tmpIssues[i].getCreator());
            resultJSON["typeIssue"] = tmpIssues[i].getStrTypeIssue();
            resultJSON["priority"] = tmpIssues[i].getStrPriority();
            resultJSON["os"] = tmpIssues[i].getStrOS();
            resultJSON["component"] = tmpIssues[i].getStrComponent();
            response = response + resultJSON.dump();
            if (i != tmpIssues.size() -1)
                response = response + ", ";
        }
    }
    response = response + "]";
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Get a list of All Users or just one User
* @param _id ID of the User to be returned
* If ID = -1 means to return a list with all Users
* If ID exits, the User information is returned as an JSON Object
*/
void getUsers(int _id,
                const std::shared_ptr<restbed::Session >& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    std::string response = "[";
    if (_id == -1) {
        for (int i = 0; i < users.size(); i++) {
        resultJSON["userID"] = std::to_string(users[i].getID());
        resultJSON["userName"] = users[i].getName();
        resultJSON["userType"] = users[i].getStringUserType();
        response = response + resultJSON.dump();
        if (i != users.size() -1)
            response = response + ", ";
        }
    } else {
        int index = CheckUserExists(_id);
        if (index == -1 || users.size() == 0) {
            std::string resultStr = "The User does not exist";
            nlohmann::json resultJSON;
            std::string response = "[";
            resultJSON["userID"] = resultStr;
            response = response + resultJSON.dump();
            response = response + "]";
            session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        } else {
            resultJSON["userID"] = std::to_string(users[index].getID());
            resultJSON["userName"] = users[index].getName();
            resultJSON["userType"] = users[index].getStringUserType();
            response = response + resultJSON.dump();
        }
    }
    response = response + "]";
    session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
    if (_id == -1) {
        for (int i = 0; i < users.size(); i++) {
        resultJSON["userID"] = std::to_string(users[i].getID());
        resultJSON["userName"] = users[i].getName();
        resultJSON["userType"] = users[i].getStringUserType();
        response = response + resultJSON.dump();
        if (i != users.size() -1)
            response = response + ", ";
        }
    } else {
        int index = CheckUserExists(_id);
        if (index == -1 || users.size() == 0) {
            std::string resultStr = "The User does not exist";
            nlohmann::json resultJSON;
            std::string response = "[";
            resultJSON["userID"] = resultStr;
            response = response + resultJSON.dump();
            response = response + "]";
            session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        } else {
            resultJSON["userID"] = std::to_string(users[index].getID());
            resultJSON["userName"] = users[index].getName();
            resultJSON["userType"] = users[index].getStringUserType();
            response = response + resultJSON.dump();
        }
    }
    response = response + "]";
    session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
}

/**
* Get a list of All Comments or just one comment from an Issue
* @param _issueID ID of the Issue that contain the Comments
* @param _commentID ID of the comment to be returned
* If commentID = -1 means to return a list with all comments
* If ID exits, the Comment information is returned as an JSON Object
*/
void getComments(int _issueID, int _commentID,
                const std::shared_ptr<restbed::Session >& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    std::string response = "[";
    int index = CheckIssueExists(_issueID);
    if (index== -1 || issues.size() == 0) {
        std::string resultStr = "The Issue does not exist";
        nlohmann::json resultJSON;
        std::string response = "[";
        resultJSON["issueID"] = resultStr;
        response = response + resultJSON.dump();
        response = response + "]";
        session->close(restbed::OK, response,
        { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        return;
    }
    std::vector<Comment> comments = issues[index].getComments();
    if (_commentID == -1) {
        for (int i = 0; i < comments.size(); i++) {
            resultJSON["commentID"] = std::to_string(i + 1);
            resultJSON["text"] = comments[i].getText();
            resultJSON["creator"] = std::to_string(comments[i].getCreator());
            response = response + resultJSON.dump();
            if (i != comments.size() -1)
                response = response + ", ";
            }
    } else {
        if (comments.size() < _commentID || comments.size() == 0) {
            std::string resultStr = "The Comment ID does not exist";
            nlohmann::json resultJSON;
            std::string response = "[";
            resultJSON["commentID"] = resultStr;
            response = response + resultJSON.dump();
            response = response + "]";
            session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
        } else {
            resultJSON["commentID"] = std::to_string(_commentID);
            resultJSON["text"] = comments[_commentID-1].getText();
            resultJSON["creator"] = std::to_string(comments[_commentID-1].getCreator());
            response = response + resultJSON.dump();
        }
    }
    response = response + "]";
    session->close(restbed::OK, response,
            { ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
}

/**
* Method to parse a POST Method requesting a Deletion
* @param session The request session.
* @param data Data from the POST Request
* Check for the operation string and do the work according
* to the request. Return a Status message
*/
void parsetodelete(const char* data,
           const std::shared_ptr<restbed::Session >& session) {
    char* data_mutable = const_cast<char*>(data);
    char* operation = strtok_r(data_mutable, "^", &data_mutable);
    std::string result = "NO OPERATION FOUND";
    nlohmann::json resultJSON;
    std::string response;
    std::string tmp = operation;
    if ("deleteuser" == tmp) {
        char* id = strtok_r(nullptr, "^", &data_mutable);
        int index = CheckUserExists(std::stoi(id));
        if (index == -1 || users.size() == 0) {
            resultJSON["Status"] = "User ID does not exist";
            response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            return;
        } else {
            users.erase(users.begin() + index);
            result = "User Deleted";
        }
    }
    if ("deleteissue" == tmp) {
        char* id = strtok_r(nullptr, "^", &data_mutable);
        int index = CheckIssueExists(std::stoi(id));
        if (index == -1 || issues.size() == 0) {
            resultJSON["Status"] = "Issue ID does not exist";
            response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            return;
        } else {
            issues.erase(issues.begin() + index);
            result = "Issue Deleted";
        }
    }
    if ("deletecomment" == tmp) {
        char* issueID = strtok_r(nullptr, "^", &data_mutable);
        char* commentID = strtok_r(nullptr, "^", &data_mutable);
        int index = CheckIssueExists(std::stoi(issueID));
        if (index == -1 || issues.size() == 0) {
            resultJSON["Status"] = "Issue ID does not exist";
            response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            return;
        }
        std::vector<Comment> comments = issues[index].getComments();
        int _commentID = std::stoi(commentID);
        if (comments.size() < _commentID || comments.size() == 0) {
            resultJSON["Status"] = "Comment ID does not exist";
            response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            return;
        }
        if (_commentID == 1) {
            resultJSON["Status"] = "Description cannot be deleted";
            response = resultJSON.dump();
            session->close(restbed::OK, response,
            {ALLOW_ALL, { "Content-Length", std::to_string(response.length())},
                           CLOSE_CONNECTION });
            return;
        }
        int indexComment = _commentID - 1;
        comments.erase(comments.begin() + indexComment);
        result = "Comment Deleted";
        issues[index].setComments(comments);
    }
    resultJSON["Status"] = result;
    response = resultJSON.dump();
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* Parse the data to correct form
* @param session The request session.
* @param data Data from the POST Request
* Reads the operation and parse the data, then call the
* the next function to finish the work
*/
void parse(const char* data,
           const std::shared_ptr<restbed::Session >& session) {
    char* data_mutable = const_cast<char*>(data);
    char* operation = strtok_r(data_mutable, "^", &data_mutable);
    std::string tmp = operation;
    if ("createissue" == tmp) { /// Reads data and create Issue
       char* title = strtok_r(nullptr, "^", &data_mutable);
       char* description = strtok_r(nullptr, "^", &data_mutable);
       char* creator = strtok_r(nullptr, "^", &data_mutable);
       std::string type = strtok_r(nullptr, "^", &data_mutable);
       std::string priority = strtok_r(nullptr, "^", &data_mutable);
       std::string OS = strtok_r(nullptr, "^", &data_mutable);
       std::string component = strtok_r(nullptr, "^", &data_mutable);

       Issue tmpIssue(title, description,
       std::stoi(creator), ReadTypeOfIssue(type), ReadPriorityOfIssue(priority),
       ReadOSIssue(OS), ReadComponentOfIssue(component));

       tmpIssue.setID(issuesCounter);
       Comment tmpComment(description, std::stoi(creator));
       tmpIssue.setDescription(tmpComment);
       tmpIssue.setAssignedTo(0);
       issuesCounter++;
       createIssue(tmpIssue, session);
       return;
    }
    if ("createuser" == tmp) { /// Reads data and create User
        char* username = strtok_r(nullptr, "^", &data_mutable);
        std::string type = strtok_r(nullptr, "^", &data_mutable);
        User tpmUser(username, ReadUserType(type));
        tpmUser.setID(userCounter);
        userCounter++;
        createUser(tpmUser, session);
        return;
    }
    if ("createcomment" == tmp) { /// Reads data and create Comment
        char* issueID = strtok_r(nullptr, "^", &data_mutable);
        char* creator = strtok_r(nullptr, "^", &data_mutable);
        char* comment = strtok_r(nullptr, "^", &data_mutable);
        Comment tmpComment(comment, std::stoi(creator));
        createComment(tmpComment, std::stoi(issueID), session);
        return;
    }
    if ("updateuser" == tmp) { /// Reads data and Update User
        char* id = strtok_r(nullptr, "^", &data_mutable);
        char* username = strtok_r(nullptr, "^", &data_mutable);
        std::string type = strtok_r(nullptr, "^", &data_mutable);
        User tmpUser(username, ReadUserType(type));
        tmpUser.setID(std::stoi(id));
        updateUser(tmpUser, session);
    }
    if ("updateissue" == tmp) { /// Reads data and Update Issue
       char* id = strtok_r(nullptr, "^", &data_mutable);
       char* title = strtok_r(nullptr, "^", &data_mutable);
       char* description = strtok_r(nullptr, "^", &data_mutable);
       std::string status = strtok_r(nullptr, "^", &data_mutable);
       char* assignedTo = strtok_r(nullptr, "^", &data_mutable);
       char* creator = strtok_r(nullptr, "^", &data_mutable);
       std::string type = strtok_r(nullptr, "^", &data_mutable);
       std::string priority = strtok_r(nullptr, "^", &data_mutable);
       std::string OS = strtok_r(nullptr, "^", &data_mutable);
       std::string component = strtok_r(nullptr, "^", &data_mutable);

       Issue tmpIssue(title, description,
       std::stoi(creator), ReadTypeOfIssue(type), ReadPriorityOfIssue(priority),
       ReadOSIssue(OS), ReadComponentOfIssue(component));

       tmpIssue.setID(std::stoi(id));
       Comment tmpComment(description, std::stoi(creator));
       tmpIssue.setDescription(tmpComment);
       tmpIssue.setAssignedTo(std::stoi(assignedTo));
       tmpIssue.setStatusIssue(ReadStatusIssue(status));
       updateIssue(tmpIssue, session);
       return;
    }
    if ("updatecomment" == tmp) { /// Reads data and Update Comment
        char* issueID = strtok_r(nullptr, "^", &data_mutable);
        char* commentID = strtok_r(nullptr, "^", &data_mutable);
        char* creator = strtok_r(nullptr, "^", &data_mutable);
        char* comment = strtok_r(nullptr, "^", &data_mutable);
        Comment tmpComment(comment, std::stoi(creator));
        updateComment(tmpComment, std::stoi(issueID), std::stoi(commentID),
                      session);
        return;
    }
    if ("delete" == tmp) { /// Reads delete operation and call ParseDelete
        parsetodelete(data_mutable, session);
    }
    nlohmann::json resultJSON;
    resultJSON["Status"] = "NOT OPERATION FOUND";
    std::string response = resultJSON.dump();

    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
                   std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* POST request callback function.
* After getting the data, a parse function is called to know what to do
*/
void post_request(const std::shared_ptr<restbed::Session >&
                  session, const restbed::Bytes & body) {
    const char* data = reinterpret_cast<const char*>(body.data());
    parse(data, session);
}

/**
* Handle a POST request.
* @param session The request session.
*/
void post_method_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    size_t content_length = request->get_header("Content-Length", 0);
    session->fetch(content_length, &post_request);
}

/**
* Handle a GET request.
* @param session The request session.
* After reading the operation, call the next function to continue the work
*/
void get_method_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();

    std::string tmp = request->get_query_parameter("op").c_str();
    if (tmp == "getissues") {
        int id = -1;
        if (request->has_query_parameter("id"))
            id = stoi(request->get_query_parameter("id"));
        getIssues(id, session);
    }
    if (tmp == "getusers") {
        int id = -1;
        if (request->has_query_parameter("id"))
            id = stoi(request->get_query_parameter("id"));
        getUsers(id, session);
    }
    if (tmp == "getcomments") {
        int commentID = -1;
        int issueID = -1;
        if (request->has_query_parameter("issueID"))
            issueID = stoi(request->get_query_parameter("issueID"));
        if (request->has_query_parameter("commentID"))
            commentID = stoi(request->get_query_parameter("commentID"));
        getComments(issueID, commentID, session);
    }
    if (tmp == "saveserver") {
        std::string fileNam = request->get_query_parameter("filename").c_str();
        saveServer(fileNam, session);
    }
    if (tmp == "loadserver") {
        std::string fileNam = request->get_query_parameter("filename").c_str();
        loadServer(fileNam, session);
    }
    if (tmp == "searchpriority") {
        std::string priority = request->get_query_parameter("priority").c_str();
        searchByPriority(priority, session);
    }
    if (tmp == "searchstatus") {
        std::string status = request->get_query_parameter("status").c_str();
        searchByStatus(status, session);
    }
    if (tmp == "searchtype") {
        std::string type = request->get_query_parameter("type").c_str();
        searchByType(type, session);
    }
}

/**
* Main function
*/
int main(const int, const char**) {
    // Setup service and request handlers
    auto resource = std::make_shared<restbed::Resource>();
    resource->set_path("/disirrest");
    resource->set_method_handler("POST", post_method_handler);
    resource->set_method_handler("GET", get_method_handler);

    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(1234);

    // Publish and start service
    restbed::Service service;
    service.publish(resource);

    service.start(settings);
    return EXIT_SUCCESS;
}
