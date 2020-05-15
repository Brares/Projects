/**
 * @author Jonathan Flores
 * @date 2019-12-01
 * Copyright 2019
*/

#ifndef ISSUE_H
#define ISSUE_H

#include "string"
#include "vector"
#include "Comment.h"

class Issue {
 public:
  /**
  * @enum StatusIssue - Enum for issue status
  * @brief Issue is New, Assigned, Fixed or Will not fix
  */
  enum StatusIssue { New, Assigned, Fixed, WontFix };
  /**
  * @enum TypeIssue - Enum for issue type
  * @brief Issue is Feature, Bug or Task Type
  */
  enum TypeIssue { Feature, Bug, Task };
  /**
  * @enum Priority - Enum for issue Priority
  * @brief Issue is Low, Normal, or High Priority
  */
  enum Priority { Low, Normal, High };
  /**
  * @enum OS - Enum for issue OS
  * @brief Issue is occuring on Windows, MacOS or Linux
  */
  enum OS { Windows, MACOS, Linux };
  /**
  * @enum Component - Enum for issue component
  * @brief Issue affects Hardware or Software
  */
  enum Component { Hardware, Software };

  /**
  * @brief Default Constructor
  */
  Issue();
  /**
  * @brief Creating the issue
  * @param _title - The issue title
  * @param _comment - The description of the issue treated as a comment
  * @param _creator - The id of the creator of the issue
  * @param _type - The type of issue
  * @param _priority - The priority of the issue
  * @param _os - The os of issue
  * @param _comp - The component affected by the issue
  */
  Issue(std::string _title, std::string _comment,
        int _creator,
        TypeIssue _type, Priority _priority, OS _os, Component _comp);
  /**
  * @brief Default Destructor
  */
  virtual ~Issue();

  /**
  * @brief Adding the description (treated like a comment) to an issue
  * @param comment - The description
  */
  void addComment(std::string comment);
  /**
  * @brief Adding the comment to an issue
  * @param comment - The comment being added
  */
  void addComment(Comment comment);

  /**
  * @brief Return the user ID
  */
  int getID();

  /**
  * @brief Return the title of the issue
  */
  std::string getTitle();

  /**
  * @brief Return the description of the issue
  */
  std::string getDescription();

  /**
  * @brief Return the issue status
  */
  StatusIssue getStatusIssue();

  /**
  * @brief Return the string of Status Issue
  */
  std::string getStrStatusIssue();

  /**
  * @brief Return the issue assignee
  */
  int getAssignedTo();

  /**
  * @brief Return the creator of the issue
  */
  int getCreator();

  /**
  * @brief Return the comment of the given index
  * @param index - The index of the comment
  */
  Comment getAComment(int index);

  /**
  * @brief Return the vector of comments
  */
  std::vector<Comment> getComments();

  /**
  * @brief Return the type of the issue
  */
  TypeIssue getTypeIssue();

  /**
  * @brief Return the string of Type Issue
  */
  std::string getStrTypeIssue();

  /**
  * @brief Return the priority of the issue
  */
  Priority getPriority();

  /**
  * @brief Return the string of Priority Issue
  */
  std::string getStrPriority();

  /**
  * @brief Return the OS
  */
  OS getOS();

  /**
  * @brief Return the string of OS Issue
  */
  std::string getStrOS();

  /**
  * @brief Return the component
  */
  Component getComponent();

  /**
  * @brief Return the string of Component Issue
  */
  std::string getStrComponent();

  /**
  * @brief Setting the id of the issue
  * @param _id - The id of the issue
  */
  void setID(int _id);

  /**
  * @brief Setting the issue title
  * @param _title - The title of the issue
  */
  void setTitle(std::string _title);

  /**
  * @brief Setting the issue description
  * @param _description - The description string
  */
  void setDescription(std::string _description);

  /**
  * @brief Setting the issue description
  * @param comment - The description as a comment
  */
  void setDescription(Comment comment);

  /**
  * @brief Setting the status of the issue
  * @param _statusIssue - The status of the issue
  */
  void setStatusIssue(StatusIssue _statusIssue);

  /**
  * @brief Setting the assignee
  * @param _UserID - The id of the assignee
  */
  void setAssignedTo(int _UserID);

  /**
  * @brief Setting the creator of the issue
  * @param _UserID - The id of the creator
  */
  void setCreator(int _UserID);

  /**
  * @brief Setting the type of the issue
  * @param _typeIssue - The type of the issue
  */
  void setTypeIssue(TypeIssue _typeIssue);

  /**
  * @brief Setting the issue's priority
  * @param _priority - The priority of the issue
  */
  void setPriority(Priority _priority);

  /**
  * @brief Setting the issue OS
  * @param _os - The OS of the system
  */
  void setOS(OS _os);

  /**
  * @brief Setting the component of the issue
  * @param _component - The component the issue is affecting
  */
  void setComponent(Component _component);

  /**
  * @brief Update a Comment
  * @param _comment - The comment to be updated
  * @param index - Index of the comment
  */
  void updateComment(Comment _comment, int index);

  /**
  * @brief Set Comments
  * @param _comments - A vector of comments
  */
  void setComments(std::vector<Comment> _comments);

 private:
     /**
     *@brief issue ID
     */
    int ID;
    /**
    *@brief issue title
    */
    std::string title;
    /**
    *@brief description of the issue
    */
    Comment description;
    /**
    *@brief issue status
    */
    StatusIssue statusIssue;
    /**
    *@brief assignee ID
    */
    int assignedTo;
    /**
    *@brief assignor ID
    */
    int creator;
    /**
    *@brief vector to store the comments of an issue
    */
    std::vector<Comment> comments;
    /**
    *@brief type of the issue
    */
    TypeIssue typeIssue;
    /**
    *@brief the priority of the issue
    */
    Priority priority;
    /**
    *@brief OS
    */
    OS os;
    /**
    *@brief issue component
    */
    Component component;
};

#endif // ISSUE_H
