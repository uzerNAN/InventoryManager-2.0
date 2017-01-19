/**
* @file GoodsManager.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief A system with functions of text-based menu and command handler (based on extended enum COMMAND) in order to manage content database. Provides textbased user interface.
*
*
*/
#pragma once

#ifndef __GoodsManager_h__
#define __GoodsManager_h__

#include "InputReader.h"
//#include "Strings.h"
#include "Action.h"

/// Show menu command alternatives, based on expected command values (ADD, PACK, REMOVE, EDIT, UNDO, LIST, QUIT and AGAIN)
/// \param goods_db a pointer to allocated tree, used as database
/// \param last_action a pointer to allocated list of actions that made change in the database
void show_main_menu(tree_t *goods_db, list_t *last_action);

/// Use input command to take corresponding action
/// \param what a command based on extended enum COMMAND, expected values are ADD, PACK, REMOVE, EDIT, UNDO, LIST, QUIT and AGAIN
/// \param goods_db a pointer to allocated tree, used as database
/// \param last_action a pointer to allocated list of actions that made change in the database
void manage_goods(DO what, tree_t *goods_db, list_t *last_action);

#endif