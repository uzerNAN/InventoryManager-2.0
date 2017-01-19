/**
* @file Action.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief A system to handle "change-making actions" in the inventory system and can successfully undo those changes step by step. Provides textbased user interface. 
*
*
*/
#pragma once

#ifndef __Action_h__
#define __Action_h__

#include "Structures.h"

/// Place saved pallet first in the list of actions
/// \param last_action a pointer to allocated list of actions that made change in the database
/// \param pallet a pointer to saved pallet
void put_action_pallet(list_t *last_action, tree_t *pallet);

/// Collect the data and place it first in the list of actions 
/// \param last_action a pointer to allocated list of actions that made change in the database
/// \param type the type of action as enum COMMAND, expected values are ADD, EDIT, REMOVE or PACK
/// \param name a pointer to the index string of content in the database, NULL might be passed as well
/// \param shelf a pointer to the shelf, NULL might be passed as well
/// \param item a poiter to a content, NULL might be passed as well
void put_action_goods(list_t *last_action, DO type, char *name, shelf_t *shelf, content_t *item);

/// Pop out last made action and print it out, read user input and take corresponding action
/// \param goods_db a pointer to the tree, used as content database
/// \param last_action a pointer to allocated list of actions that made change in the database
void undo_last_action(tree_t *goods_db, list_t *last_action);

/// Free action list and all unlinked(unused) datapointers inside each node
/// \param actions a pointer to pointer of allocated list of actions that made change in the database 
void free_action_list(list_t **actions);

#endif
