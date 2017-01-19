/**
* @file Pallet.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief A text based system to create a list of buying items from the database. Provides textbased user interface.
*
*
*/
#pragma once

#ifndef __Pallet_h__
#define __Pallet_h__

#include "Structures.h"

/// Show the list of indexes in the pallet
/// \param pallet a pointer to the tree, used as pallet
void show_pallet_receipt(tree_t *pallet);

/// Add items from the pallet to the database
/// \param goods_db a pointer to the tree, used as database
/// \param pallet a pointer to the tree, used as pallet
void add_pallet(tree_t *goods_db, tree_t *pallet);

/// Show the index list, allow collect items from the database and save the pallet or cancel and add collected pallet back
/// \param goods_db a pointer to the tree, used as database
/// \param last_action a pointer o the list of actions
void pack_pallet(tree_t *goods_db, list_t *last_action);

#endif