#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct link
{
	void *value; /**< any value pointer */
	struct link *next; /**< next link node */
} link_t;

typedef struct list
{
	int length; /**< length of the list */
	int iter; /**< iteration index of link node 'curr' */
	struct link *head; /**< first link node of the list */
	struct link *curr; /**< iteration link node */
} list_t;

const size_t ALLOC_LINK = sizeof(link_t);
const size_t ALLOC_LIST = sizeof(list_t);

void link_new( link_t **link, void *value, link_t *next ){
	*link = (link_t *)malloc(ALLOC_LINK);	
	(*link)->value = value;
	(*link)->next = next;
}

void list_init(list_t *list){
	list->iter = 0;
	list->length = 0;
	list->head = NULL;
	list->curr = NULL;
}
void list_new(list_t **list){
	*list = (list_t *)malloc(ALLOC_LIST);
	list_init(*list);
}

int list_length(list_t *list){
	return list->length;
}

void list_append(list_t *list, void *elem){
	while(list->curr != NULL && (list->curr)->next != NULL){ 
		list->iter++; 
		list->curr = (list->curr)->next;
	}
	link_new(((list->curr != NULL) ? &((list->curr)->next) : &(list->curr)), elem, NULL);
	list->length++;
	//list->iter = 1 + list->iter;
	if(list->head == NULL){
		list->head = list->curr;
	}
}

void list_prepend(list_t *list, void *elem){
	link_t *link = NULL;//= list->next;
	//list->next = NULL;
	link_new(&(link), elem, list->head);
	list->length++;
	list->iter++;
	list->head = link;
	if(list->curr == NULL){
		list->curr = list->head;
		list->iter = 0;
	}
	link = NULL;
	//swap_elem_value(list, list->next);
	//*(list->length) = (*(list->length)) + 1;
}

int neg_to_pos_length(int list_length, int the_int){
	if(the_int < 0){
		the_int = the_int+list_length;
	}
	return the_int;
}

bool list_insert(list_t *list, int indx, void *elem){
	bool success = true;
	link_t *next = NULL;
	int index = neg_to_pos_length(list->length, indx);
	switch(index){
	case 0 :
		list_prepend(list, elem);
		break;
	default :
		if(list->length > index || list->curr == NULL ){
			if(list->iter >= index){
				list->curr = list->head;
				list->iter = 0;
			}
			while(list->curr != NULL && (list->curr)->next != NULL && (list->iter+1) < index){
				
				list->curr = (list->curr)->next;
				list->iter++;
			
			}
				
			if(list->curr != NULL){
				next = (list->curr)->next;
				(list->curr)->next = NULL;
				link_new( &((list->curr)->next), elem, next );
				next = NULL;
				list->length++;
			} else {
				success = false;
			}
			
		} else if(list->length == index){
			list_append(list, elem);
		} else {
			success = false;
		}
		break;
	}
	return success;
}

bool list_remove(list_t *list, int indx, void **elem){
	bool success = true;
	//void *value = NULL;
	int index = neg_to_pos_length(list->length, indx), i = 1;
	link_t *to_remove;
	
	switch(index){
	case 0 :
		to_remove = list->head;
		if(to_remove->next){
			list->head = to_remove->next;
			to_remove->next = NULL;

			if (list->iter) {
				list->iter--;
			} else {
				list->curr = list->head;
			}
		}
		else{
			list->head = NULL;
			list->curr = NULL;
		}
		break;
	default :
		if(list->iter >= index){
			list->curr = list->head;
			list->iter = 0;
		}
		while(list->curr != NULL && (list->curr)->next != NULL && (list->iter+1) < index){ 
			list->curr = (list->curr)->next; 
			list->iter++; 
		}
		if(list->curr != NULL && (list->curr)->next != NULL){
			to_remove = (list->curr)->next;
			(list->curr)->next = to_remove->next;
			to_remove->next = NULL;
		}
		else{
			success = false;
		}
		break;
	}
	switch(success){
	case true :
		if(to_remove->value != NULL){
			*elem = to_remove->value;
			to_remove->value = NULL;
		}
		list->length--;
		free(to_remove);
		to_remove = NULL;

		break;
	default :
		break;
	}
	return success;
}

void *list_get(list_t *list, int indx){
	void *out = NULL;
	int index = neg_to_pos_length(list->length, indx);
	if(list->iter >= index || list->curr == NULL){
		list->iter = 0;
		list->curr = list->head;
	}
	while(list->curr != NULL && (list->curr)->next != NULL && list->iter < index){ 
		list->curr = (list->curr)->next; 
		list->iter++;
	}
	if(list->curr != NULL){
		out = (list->curr)->value;
	}
	return out;
}