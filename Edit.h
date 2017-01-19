/**
* @file Edit.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief Functions for edit contents in stored database tree. Provides textbased user interface.
*
*
*/
#pragma once

#ifndef __Edit_h__
#define __Edit_h__

#include "Structures.h"

/// Edit given shelf place and/or amount of given shelf
/// \param goods_db a pointer to the database of contents in form of a tree
/// \param content a pointer to the content that contains items name and the shelf list 
/// \param shelf_i index position of the shelf in the shelf list of the given content
int edit_shelf_and_amount(tree_t *goods_db, content_t *content, int shelf_i);

/// Edit content from the tree at the given index position
/// \param goods_db a pointer to the database of contents in form of a tree
/// \param index the index number of content 
/// \param last_action a pointer to the list of previous actions
/// \returns index position of edited content item
int edit_item(tree_t *goods_db, int index, list_t *last_action);

/// List content names and let the user to choose which content has to be edited, read user input and take corresponding action
/// \param goods_db a pointer to the database of contents in form of a tree
/// \param last_action a pointer to the list of previous actions
void edit_goods(tree_t *goods_db, list_t *last_action);

#endif