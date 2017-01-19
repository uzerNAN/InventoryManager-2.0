/**
* @file Remove.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief Functions for removing content from stored database tree.
*
*
*/
#pragma once

#ifndef __Remove_h__
#define __Remove_h__

#include "Structures.h"

/// Remove chosen shelf and content if needed, and add new action in action list
/// \param goods_db pointer to database of contents in form of a tree
/// \param index the number of chosen index in the database
/// \param shelf_i the number of shelf in the content's list of shelfs
/// \param last_action a pointer to the list of previous actions
void remove_item(tree_t *goods_db, int index, int shelf_i, list_t *last_action);

/// Ask user to confirm the remove or cancel command, read user's command, and take corresponding action
/// \param goods_db pointer to database of contents in form of a tree
/// \param index the number of chosen index in the database
/// \param shelf_i the number of shelf in the content's list of shelfs
/// \param last_action a pointer to the list of previous actions
/// \returns user's chosen command
DO verify_and_remove_item(tree_t *goods_db, int index, int shelf_i, list_t *last_action);

/// Show content alternatives from the database, ask if user to pick index number or cancel, read user input, and take corresponding action
/// \param goods_db pointer to database of contents in form of a tree
/// \param last_action a pointer to the list of previous actions
void remove_goods(tree_t *goods_db, list_t *last_action);

#endif