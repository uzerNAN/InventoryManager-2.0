/**
* @file Structures.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief A collection of small but useful help-functions, made for use of content and shelf features, combined with list and tree.
*
*
*/
#pragma once

#ifndef __Structures_h__
#define __Structures_h__


#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "AVLTree.h"

typedef struct shelf shelf_t;

typedef struct content content_t;

extern const int NAME_LENGTH;
extern const int DESC_LENGTH;

extern const size_t ALLOC_SHELF;
extern const size_t ALLOC_CONTENT;
extern const size_t ALLOC_CHAR;

int get_int_size(int n);

void new_shelf(shelf_t **shelf);

void new_content(content_t **content);

void new_string(char **string, int size);

void free_string(char **string, int size);

void free_shelf(shelf_t **shelf);

void free_content(content_t **content);

void prepare_for_free_string(char *string, int size);

void copy_shelf(shelf_t *copy, shelf_t *shelf);

int shelf_equal(shelf_t *shelf, shelf_t * equal);

void shelf_to_string(char *s, shelf_t *shelf, int shelf_size);

void free_shelf_list(list_t *shelfs);

void free_content_shelfs(content_t *content);

int print_shelfs(list_t *shelfs);

int show_goods(content_t *content, int shelf_index);

const char *print_not_equal_string(char *string, char *not_equal);

void copy_string(char *copy, char *string, int copy_size);

void clone_content(content_t *clone, content_t *content);

void print_side_by_side(content_t *first, content_t *second, const char *first_h, const char *second_h);

void copy_shelf_list(list_t *copy, list_t *list);

void copy_content(content_t *copy, content_t *content);

void show_content_shelf(content_t *content, shelf_t *shelf);

void free_content_tree(tree_t **contents);

list_t *get_content_shelfs(content_t *content);

void set_content_shelfs(content_t *content, list_t *shelfs);

void set_shelf(shelf_t *shelf, char place, int number, int zero_at_start, int amount);

void set_shelf_place(shelf_t *shelf, char place);

void set_shelf_number(shelf_t *shelf, int number);

void set_shelf_zero_at_start(shelf_t *shelf, int zero_at_start);

int get_shelf_zero_at_start(shelf_t *shelf);

int get_shelf_amount(shelf_t *shelf);

char get_shelf_place(shelf_t *shelf);

int get_shelf_number(shelf_t *shelf);

void set_shelf_amount(shelf_t *shelf, int amount);

char *get_content_name(content_t *content);

char *get_content_description(content_t *content);

int get_content_price(content_t *content);

void set_content_price(content_t *content, int price);

int get_shelf_index(list_t *shelfs, shelf_t *shelf);

#endif