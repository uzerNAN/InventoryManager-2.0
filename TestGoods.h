/**
* @file TestGoods.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief Inserts pre-defined database to the database tree.
*
*
*/
#pragma once

#ifndef __TestGoods_h__
#define __TestGoods_h__

#include "AVLTree.h"
#include "LinkedList.h"

/// Insert pre-defined database to the database tree
/// \param goods_db a pointer to the tree, used as database
/// \param last_action a pointer to the list of changes in the database
void insert_test_goods(tree_t *goods_db, list_t *last_action);

#endif