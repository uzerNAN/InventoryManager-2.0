#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

 //int i_length = 20;

 typedef struct leaf {
	 char index[20]; /**< the unique index of a node in the tree */
	 void *value; /**< any value pointer */
	 struct leaf *right, *left; /**< child nodes */
	 int depth; /**< the height of current subtree */
 } leaf_t;

typedef struct tree
{
	list_t *indexes; /**< list of all indexes in the tree */
	leaf_t *top; /**< the top node of the tree */
} tree_t;

void leaf_copy_index(char *copy, char *index){
	int i = 0;
   for (; index[i]!='\0' && i<20; i++) {
      copy[i] = index[i];
   }
   copy[i] = '\0';
}

const size_t ALLOC_LEAF = sizeof(leaf_t);

const size_t ALLOC_TREE = sizeof(tree_t);

void tree_new(tree_t **tree){
	*tree = (tree_t *)
		malloc(ALLOC_TREE);
	(*tree)->top = NULL;
	(*tree)->indexes = NULL;
}

void leaf_new(leaf_t **leaf) {
	*leaf = (leaf_t *)
		malloc(ALLOC_LEAF);
	(*leaf)->index[0] = '\0';
	(*leaf)->value = NULL;
	(*leaf)->left = NULL;
	(*leaf)->right = NULL;
	(*leaf)->depth = 1;
}

void leaf_init( leaf_t *leaf, char *index, void *value){
	//leaf->depth = 1;
	if(index != NULL){
		leaf_copy_index(leaf->index, index);
		leaf->value = value;
	}
}

int tree_size(tree_t *tree){
	/*int out = 0;
	if(tree != NULL && tree->value != NULL){
		out = 1 + tree_size(tree->left) + tree_size(tree->right);
	}*/
	return tree->indexes ? list_length(tree->indexes) : 0;
}

// A utility function to get maximum of two integers
int max_int(int a, int b){
    return (a >= b) ? a : b;
}

int min_int(int a, int b) {
	return (a <= b) ? a : b;
}

int tree_depth(leaf_t *tree){
	return tree && tree->value ? tree->depth : 0;
}

int tree_balance_value(leaf_t *tree){
	int out = 0, r, l;
	if(tree != NULL){
		r = tree_depth(tree->right);
		l = tree_depth(tree->left);
		out = l - r;
	}
	return out;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
leaf_t *tree_rotate_right(leaf_t *tree){
    leaf_t *left = tree->left;
    leaf_t *left_right = left->right;
	//if (left_right) {
	// Perform rotation
	left->right = tree;
	tree->left = left_right;

	tree->depth = max_int(tree_depth(tree->left), tree_depth(tree->right))+1;
	left->depth = max_int(tree_depth(left->left), tree_depth(left->right))+1;
	//}
    // Return new root
    return left;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
leaf_t *tree_rotate_left(leaf_t *tree){
    leaf_t *right = tree->right;
    leaf_t *right_left = right->left;
 
	//if (right_left) {
	// Perform rotation
	right->left = tree;
	tree->right = right_left;

	tree->depth = max_int(tree_depth(tree->left), tree_depth(tree->right))+1;
	right->depth = max_int(tree_depth(right->left), tree_depth(right->right))+1;

	//}
    // Return new root
    return right;
}

int to_upper_index_char(int c){
	if(	c >= 97		&&
		c <= 122	){
		c  = c-32	;
	}
	return c;
}

int tree_index_compare(char *index_one, char *index_two){
	int equal = 0, i = 0, one = 0, two = 0;
	while (index_one[i] != '\0' && index_two[i] != '\0' && to_upper_index_char(index_one[i]) == to_upper_index_char(index_two[i])) { i++; }
	if(index_one[i] != '\0' || index_two[i] != '\0'){
		if(index_one[i] != '\0' && index_two[i] != '\0'){
			one = to_upper_index_char(index_one[i]), two = to_upper_index_char(index_two[i]);
			if(one == two){
				one = index_one[i], two = index_two[i];
			}
			if(one < two){
				equal = -1;
			}
			else if(one > two){
				equal =  1;
			}
		}
		else if (index_one[i] == '\0'){
			equal = -1;
		}
		else if (index_two[i] == '\0'){
			equal = 1;
		}
	}
	return equal;
}

int insert_new_index(list_t *indexes, char *index) {
	int i = 0, l = list_length(indexes);
	char *i_compare = NULL;
	if (l) {
		while (i < l) {
			i_compare = (char *)list_get(indexes, i);
			switch (tree_index_compare(i_compare, index)) {
			case 0:
			case -1:
				i++;
				if (i < l) {
					break;
				}
			case 1:
				list_insert(indexes, i, index);
				l = i;
				break;
			}
		}
	}
	else {
		list_insert(indexes, i, index);
	}
	return i;
}

void insert_new_leaf(leaf_t **leaf, list_t *indexes, char *index, void *value) {
	leaf_new(leaf);
	leaf_init(*leaf, index, value);
	insert_new_index(indexes, (*leaf)->index);
}


leaf_t *subtree_insert(leaf_t *tree, list_t *indexes, char *index, void *value){
	int balance_value;
	/* Normal BST rotation */
    /*if (tree == NULL){
        tree_new(&(*b_tree), index, value);
	}*/
	switch(tree_index_compare(index, tree->index)){
	case -1 :
		if(tree->left != NULL){
			tree->left  = subtree_insert(tree->left, indexes, index, value);
		} else {
			insert_new_leaf(&(tree->left), indexes, index, value);
		}
		break;
	case 1 :
		if(tree->right != NULL){
			tree->right = subtree_insert(tree->right, indexes, index, value);
		} else {
			insert_new_leaf(&(tree->right), indexes, index, value);
		}
		break;
	default :
		break;
	}
	/* 2. Update height of this ancestor node */
	tree->depth = max_int(tree_depth(tree->left), tree_depth(tree->right)) + 1;
 
	/* 3. Get the balance factor of this ancestor node to check whether
		this node became unbalanced */
	balance_value = tree_balance_value(tree);
 
	// If this node becomes unbalanced, then there are 4 cases

	// Left Case
	if (balance_value > 1){
		switch(tree_index_compare(index, tree->left->index)){
		case  1 : // Left Right Case
			tree->left = tree_rotate_left(tree->left);
		case -1 : // Left Left Case
			tree = tree_rotate_right(tree);
			break;
		default :
			break;
		}
	}
 
	// Right Case
	else if (balance_value < -1){
		switch(tree_index_compare(index, tree->right->index)){
		case  -1 : // Right Left Case
			tree->right = tree_rotate_right(tree->right);
		case 1 : // Right Right Case
			tree = tree_rotate_left(tree);
			break;
		default :
			break;
		}
	}

	

	return tree;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
leaf_t* get_leftmost_leaf(leaf_t* tree){
    leaf_t* left_leaf = tree;
 
    /* loop down to find the leftmost leaf */
    while (left_leaf->left != NULL){
        left_leaf = left_leaf->left;
	}
 
    return left_leaf;
}


int get_index_position(list_t *indexes, char *index) {
	int i = 0, l = list_length(indexes);
	bool found = false;
	while (i < l && !found) {
		if (!tree_index_compare((char *)list_get(indexes, i), index)) {
			found = true;
		}
		if (!found) {
			i++;
		}
	}
	return i;
}

int tree_insert(tree_t *tree, char *index, void *value) {
	int i = 0;
	if (tree->top) {
		tree->top = subtree_insert(tree->top, tree->indexes, index, value);
		i = get_index_position(tree->indexes, index);
	}
	else {
		if (!(tree->indexes)) {
			list_new(&(tree->indexes));
		}
		insert_new_leaf(&(tree->top), tree->indexes, index, value);
	}
	return i;
}

int tree_index_pos_search(tree_t *tree, char *index) {
	return get_index_position(tree->indexes, index);
}

void copy_leaf_data(list_t *indexes, leaf_t *leaf_1, leaf_t *leaf_2) {
	int indx_pos;
	void *elem;
	// Copy the inorder successor's data to this node
	leaf_copy_index(leaf_1->index, leaf_2->index); // <- important to handle values 
	indx_pos = get_index_position(indexes, leaf_2->index);
	list_remove(indexes, indx_pos, &elem);
	elem = NULL;
	list_insert(indexes, indx_pos, leaf_1->index);
	elem = leaf_1->value;
	leaf_1->value = leaf_2->value;
	leaf_2->value = elem;
	elem = NULL;
}
 
leaf_t *subtree_remove(leaf_t *tree, list_t *indexes, char *index, void **elem){
	leaf_t *child = NULL;
//	char *indx;
	int balance_value;
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (tree != NULL){
		// If the key to be deleted is smaller than the root's key,
		// then it lies in left subtree
		switch ( tree_index_compare(index , tree->index) ){
		case -1 :
			tree->left = subtree_remove(tree->left, indexes, index, elem);
			if(tree->left && !(tree->left->value)){
				free(tree->left);
				tree->left = NULL;
			}
			break;
		// If the key to be deleted is greater than the root's key,
		// then it lies in right subtree
		case 1 :
			tree->right = subtree_remove(tree->right, indexes, index, elem);
			if(tree->right && !(tree->right->value)){
				free(tree->right);
				tree->right = NULL;
			}
			break;
		// if key is same as root's key, then This is the node
		// to be deleted
		case 0 :
			// node with only one child or no child
			if( !(tree->left) || !(tree->right) ){
				if(tree->left){
					child = tree->left;
				}
				else if(tree->right){
					child = tree->right;
				}
				// No child case
				if(!child)
				{
					*elem = tree->value;
					tree->value = NULL;
				}
				else{ // One child case
					*elem = tree->value;
					copy_leaf_data(indexes, tree, child);
					tree->right = child->right;
					tree->left = child->left;
					child->right = NULL;
					child->left = NULL;
					
					child->value = NULL;
					free(child);
					child = NULL;
				}
			}
			else{
				// node with two children: Get the inorder successor (smallest
				// in the right subtree)
				child = get_leftmost_leaf(tree->right);
 
				copy_leaf_data(indexes, tree, child);

				child = NULL;
				// Delete the inorder successor
				tree->right = subtree_remove(tree->right, indexes, tree->index, elem);
				if(tree->right != NULL && tree->right->value == NULL){
					free(tree->right);
					tree->right = NULL;
				}
			}
			break;
		}
	//}
 
		// If the tree had child node(s)
		if (tree->value != NULL){
			
			// STEP 2: UPDATE HEIGHT
			tree->depth = max_int(tree_depth(tree->left), tree_depth(tree->right)) + 1;

			// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
			//  this node became unbalanced)
			balance_value = tree_balance_value(tree);
 
			// If this node becomes unbalanced, then there are 4 cases
			if (balance_value > 1){ 
				// Left Left Case
				if(tree_balance_value(tree->left) >= 0){
					tree = tree_rotate_right(tree);
				}
				// Left Right Case
				else{
					tree->left =  tree_rotate_left(tree->left);
					tree = tree_rotate_right(tree);
				}
			}
			else if(balance_value < -1){
				// Right Right Case
				if(tree_balance_value(tree->right) <= 0){
					tree = tree_rotate_left(tree);
				}
				// Right Left Case
				else{
					tree->right = tree_rotate_right(tree->right);
					tree = tree_rotate_left(tree);
				}
			}
		}
	}
 
    return tree;
}

void tree_remove(tree_t *tree, int index_pos, void **elem) {
	char *indx = NULL, index[20];
	if (tree->top && list_remove(tree->indexes, index_pos, &indx)) {
		leaf_copy_index(index, indx);
		indx = NULL;
		tree->top = subtree_remove(tree->top, tree->indexes, index, elem);
		if (!(tree->top->value)) {
			free(tree->top);
			tree->top = NULL;
			free(tree->indexes);
			tree->indexes = NULL;
		}
	}
}

void *tree_search(tree_t *tree, char *index){
	leaf_t *iterator = tree->top;
	int equal = 1; // a value to get in the loop if tree is not NULL
	while (iterator != NULL && equal != 0){
		equal = tree_index_compare(iterator->index, index);
		//printf("\n%s && %s | equal : %d", iterator->index, index, equal);
		switch(equal){
		case -1:
			iterator = iterator->right;
			break;
		case  1:
			iterator = iterator->left;
			break;
		default:
			break;
		}
	}
	return ( (iterator != NULL) ? iterator->value : NULL );
}

/*leaf_t *subtree_get_left(leaf_t *leaf){
	return leaf->left;
}

leaf_t *subtree_get_right(leaf_t *leaf){
	return leaf->right;
}

char *leaf_get_index(leaf_t *leaf){
	return leaf->index;
}

void *leaf_get_value(leaf_t *leaf){
	return leaf->value;
}*/

char *tree_index_search(tree_t *tree, int index){
	return (0 <= index && index < list_length(tree->indexes)) ? (char *)list_get(tree->indexes, index) : NULL;
}

int tree_print_indexes(tree_t *tree, int start_i, int max_i){
	int current_i = start_i, length_i = start_i + max_i < list_length(tree->indexes) ? start_i + max_i : list_length(tree->indexes); 


	while (current_i < length_i) {

		printf("   %d : %s\n", ++current_i, (char *)list_get(tree->indexes, current_i-1) );
		
	}

	/*if((current_i-start_i) < max_i){
		while()

		if(tree->left != NULL){
			current_i = print_indexes(tree->left, start_i, current_i, max_i);
		}
	
		if(start_i <= current_i && tree->index != NULL){
			printf("   %d : %s\n", current_i-start_i+1, tree->index);
		}
		if(tree->right != NULL){
			current_i = print_indexes(tree->right, start_i, current_i+1, max_i);
		}
		else{
			current_i = current_i+1;
		}
	}*/
	return current_i;
}

/*void tree_copy(tree_t *tree, tree_t **copy) {
	tree_new(copy);
	tree_init(*copy, tree->index, tree->value);
	if (tree->right) {
		tree_copy(tree->right, &((*copy)->right));
	}
	if (tree->left) {
		tree_copy(tree->left, &((*copy)->left));
	}
}


void tree_free(tree_t *tree) {
if (tree->left) {
tree_free(tree->left);
tree->left = NULL;
}
if (tree->right) {
tree_free(tree->right);
tree->right = NULL;
}
tree_index_prepare_for_free(tree->index, tree->i_length);
free(tree->index);
tree->index = NULL;
free(tree->value);
tree->value = NULL;
free(tree);
tree = NULL;
}

*/

