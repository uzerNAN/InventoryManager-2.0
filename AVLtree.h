/**
* @file AVLtree.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief Simple self-balancing search tree that can have any pointer as the input.
*
*
*/
#pragma once

#ifndef __AVLTree_h__
#define __AVLTree_h__

typedef struct tree tree_t;

/// Create new tree
/// \param tree a pointer of a pointer which will point to the new tree
void tree_new( tree_t **tree );

/// Get the size of the tree 
/// \param tree pointer to the allocated tree
/// \returns the number of nodes in the tree
int tree_size(tree_t *tree);

/// Compare two strings
/// \example tree_index_compare("AAA", "aaa") == 0
/// \example tree_index_compare("zaa", "aaaa") == 1
/// \param index_one first string for comparison
/// \param index_two second string for comparison
/// \returns 0 if strings are equal, -1 if second string is greater and 1 if first string is greater
int tree_index_compare(char *index_one, char *index_two);

/// Insert value at given index in the tree
/// \param tree pointer to the tree
/// \param index pointer for the string to be used as index for inserted value
/// \param value pointer to the value for insertion
/// \returns index position(0,1,..) of inserted node in the tree
int tree_insert(tree_t *tree, char *index, void *value);

/// Remove node at given index in the tree
/// \param tree pointer to the tree
/// \param index_pos index position of the node to be removed
/// \param value pointer of the pointer where the value pointer of the removed node can be stored
void tree_remove(tree_t *tree, int index_pos, void **elem);

/// Search for the value pointer in the tree
/// \param tree pointer to the tree
/// \param index index for the node to search for
/// \returns pointer stored at given index or NULL if there is no such index in the tree
void *tree_search(tree_t *tree, char *index);

/// Search for index position(0,1,..) with index string
/// \param tree a pointer to the tree
/// \param index a pointer to the index string
/// \returns index position(0,1,..) of searched node
int tree_index_pos_search(tree_t *tree, char *index);

/// Search for the index pointer in the list of indexes of the tree
/// \param tree pointer to the tree
/// \param index number of index of the node in the tree
/// \returns pointer to index string stored at given index number
char* tree_index_search(tree_t *tree, int index);

/// Print list of indexes within given limits
/// \param tree pointer to the tree
/// \param start_i first index for print
/// \param max_i amount of maximum printed indexes
/// \returns (start_i+max_i) or the size of the tree if there is no such index number as (start_i+max_i)
int tree_print_indexes(tree_t *tree, int start_i, int max_i);

#endif