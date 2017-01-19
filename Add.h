/**
* @file Add.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief Functions for adding contents to stored database tree. Provides textbased user interface.
*
*
*/
#pragma once

#ifndef __Add_h__
#define __Add_h__

#include "Structures.h"

/// Insert shelf into the list or add it's amount to the existing shelf
/// \param shelfs a pointer to the list of shelfs
/// \param shelf a pointer to the shelf for add
/// \returns the index number where in the list of shelfs the shelf was placed
int add_shelf(list_t *shelfs, shelf_t *shelf);

/// Read new shelf input and check if it not exists already in the database, and take corresponding action
/// \param shelf a pointer to the shelf where readed data will be stored
/// \param goods_db a pointer to the database of contents in form of a tree
/// \param print special string to print before word shelf, strings NEW and THE are currently used with this function
/// \param last_action a pointer to the list of previous actions
void read_and_verify_shelf(shelf_t *shelf, tree_t *goods_db, char *print, content_t *content);

/// Add content to the database and/or the shelf, add new action node in last_action list.
/// After use of current function the content input has to be checked, if the shelf list is set to NULL, then it is not linked to the database tree. Also shelf input has to be checked according to the description for add_shelf function.
/// \param goods_db a pointer to the database of contents in form of a tree
/// \param input a pointer of inputting content
/// \param shelf a pointer of inputting shelf
/// \param last_action a pointer to the list of previous actions
void add_item(tree_t *goods_db, content_t *input, shelf_t *shelf, list_t *last_action);

/// Handle the user input of a content and/or input of a shelf, ask the user to confirm its choise, and take corresponding action
/// \param goods_db a pointer to the database of contents in form of a tree
/// \param last_action a pointer to the list of previous actions
void add_goods(tree_t *goods_db, list_t *last_action);

#endif