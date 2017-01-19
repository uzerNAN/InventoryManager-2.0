/**
* @file LinkedList.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief Simple Linked List that can have any pointer as the input.
*
*
*/
#pragma once

#ifndef __LinkedList_h__
#define __LinkedList_h__

#include <stdbool.h>

typedef struct link link_t;
typedef struct list list_t;

/// Length of the list
/// \param list a pointer of the list
/// \returns the length of the inputted list
int list_length(list_t *list);

/// Insert elem pointer after the list
/// \param list pointer to the list
/// \param elem the pointer for element to insert
void list_append(list_t *list, void *elem);

/// Insert elem pointer before the list
/// \param list pointer to the list
/// \param elem the pointer for element to insert
void list_prepend(list_t *list, void *elem);

/// Insert elem pointer to the list at given index
/// \param list pointer to the list
/// \param indx index place in the list for insertion
/// \param elem the element to insert
/// \returns true if succeeded, else false
bool list_insert(list_t *list, int indx, void *elem);

/// Remove an element from a list.
/// \param list  pointer to the list
/// \param index the index to be removed
/// \param elem a pointer to where the element can be stored
/// \returns true if succeeded, else false
bool list_remove(list_t *list, int indx, void **elem);

/// Search function for linked list
/// \param list pointer to the list
/// \param indx index to search for
/// \returns pointer stored at given index or NULL if there is no such index in the list
void *list_get(list_t *list, int indx);

/// Create new list
/// \param list a pointer of a pointer where new list will be stored
void list_new( list_t **list );

#endif