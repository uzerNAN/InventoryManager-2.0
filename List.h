/**
* @file List.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief Functions for printing indexes from stored database tree. Provides textbased user interface.
*
*
*/
#pragma once

#ifndef __List_h__
#define __List_h__

#include "Structures.h"

/// Print a list of content indexes from database with predetermined limit of indexes per page, read user input, and take corresponding action
/// \param goods_db a pointer to the database of contents in form of a tree
/// \param what a special reason to print out in question-line, those are defined as special : REMOVE, EDIT and PACK
/// \param page_index a pointer to integer that defined as the index of  start page (starting from 0 as first page)
/// \returns chosen index number or -1 as cancel
int list_items(tree_t *goods_db, DO what, int *page_index);

/// Print a list of shelfs, read user input, and take corresponding action
/// \param shelfs a pointer to the list of shelfs
/// \returns chosen index number or -1 as cancel
int list_shelfs(list_t *shelfs);

/// Show content alternatives from the database, ask if user to pick index number or cancel, read user input, and take corresponding action
/// \param goods_db a pointer to the database of contents in form of a tree
void list_goods(tree_t *goods_db);

#endif