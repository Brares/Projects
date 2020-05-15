#ifndef COMMENT_H
#define COMMENT_H

/**
 * @author Jonathan Flores
 * @date 2019-12-01
 * Copyright 2019
*/

#include "string"

class Comment {
 public:
  /**
  * @brief Default constructor for a class
  */
  Comment();
  /**
  *@brief Comment constructor when not given a creator
  *@param _text - The comment as string
  */
  Comment(std::string _text);
  /**
  *@brief Comment constructor when both text and creator are given
  *@param _text - The comment as string
  *@param _creator - The id of the creator
  */
  Comment(std::string _text, int _creator);
  /**
  *@brief Get function returns the comment as a string
  */
  std::string getText();
  /**
  *@brief Get function returns the id of the creator
  */
  int getCreator();
  /**
  *@brief Setting the text of the comment
  *@param _text - The input string of the comment
  */
  void setText(std::string _text);
  /**
  *@brief Setting the creator of a comment
  *@param _creator - The creator id
  */
  void setCreator(int _creator);

 private:
  /**
  *@brief The text of the comment
  */
  std::string text;
  /**
  *@brief The creator of the comment
  */
  int creator;
};

#endif // COMMENT_H
