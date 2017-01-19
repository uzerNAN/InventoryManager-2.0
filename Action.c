//#include "Strings.h"
#include "InputReader.h"
#include "Add.h"
#include "Pallet.h"


typedef struct act
{
	char *name;
	union {
		shelf_t *shelf;
		content_t *item;
	};
} act_t;

typedef struct action
{
	DO type;
	union {
		act_t *goods;
		tree_t *pallet;
	};
} action_t;

const size_t ALLOC_ACT = sizeof(act_t);
const size_t ALLOC_ACTION = sizeof(action_t);

void new_action(action_t **action, bool goods) {
	*action = (action_t *)malloc(ALLOC_ACTION);
	if (goods) {
		(*action)->goods = NULL;
	}
	else {
		(*action)->pallet = NULL;
	}
}

void new_act(act_t **action, bool item) {
	*action = (act_t *)malloc(ALLOC_ACT);
	(*action)->name = NULL;
	if (item) {
		(*action)->item = NULL;
	}
	else {
		(*action)->shelf = NULL;
	}
}

void put_action_pallet(list_t *last_action, tree_t *pallet) {
	action_t *action = NULL;
	new_action(&action, false);

	action->type = PACK;
	action->pallet = pallet;

	list_prepend(last_action, action);
	action = NULL;
}

void put_action_goods(list_t *last_action, DO type, char *name, shelf_t *shelf, content_t *item) {
	action_t *action = NULL;
	//list_t * shelfs = NULL;
	new_action(&action, true);
	new_act(&(action->goods), (item != NULL));

	action->type = type;
	if (name) {
		new_string(&(action->goods->name), NAME_LENGTH);
		copy_string(action->goods->name, name, NAME_LENGTH);
	}
	if (shelf) {
		action->goods->shelf = shelf;
		//new_shelf(&(action->goods->shelf));
		//copy_shelf(action->goods->shelf, shelf);
	}
	if (item) {
		action->goods->item = item;
		/*new_content(&(action->goods->item));
		list_new(shelfs);
		set_content_shelfs(action->goods->item, shelfs);
		copy_content(action->goods->item, item);*/

	}
	list_prepend(last_action, action);
	//action->goods = NULL;

	//free(action);
	action = NULL;
}

void undo_last_action(tree_t *goods_db, list_t *last_action) {
	char SPACE[] = "  ";
	int i;//, shelf_size;
				//char *shelf_string = NULL;
	content_t *content = NULL;
	shelf_t *shelf_curr = NULL;
	list_t *shelfs = NULL;
	action_t *action = (action_t *)list_get(last_action, 0);

	switch (action->type) {
	case ADD:
		content = (content_t *)tree_search(goods_db, action->goods->name);
		i = get_shelf_index(get_content_shelfs(content), action->goods->shelf);
		shelf_curr = (shelf_t *)list_get(get_content_shelfs(content), i);

		show_content_shelf(content, action->goods->shelf);
		
		printf("%sDo you want to remove this item?\n", SPACE);
		printf("%sConfirm your choise by typing Remove or Cancel : ", SPACE); // %s%s\n  %s%s : 
		switch (read_command(UNDO_ADD, NULL)) {
		case REMOVE:
			if (yes_no_question("Are you sure you want to remove this item permanently?") == YES) {
				if (get_shelf_amount(shelf_curr) > get_shelf_amount(action->goods->shelf)) {
					set_shelf_amount(shelf_curr, get_shelf_amount(shelf_curr) - get_shelf_amount(action->goods->shelf));
					shelf_curr = NULL;
					//shelf_undo = NULL;
				}
				else {
					shelf_curr = NULL;
					//shelf_undo = NULL;
					if (list_length(get_content_shelfs(content)) > 1) {
						list_remove(get_content_shelfs(content), i, &shelf_curr);
						free_shelf(&shelf_curr);
					}
					else {
						int index_pos = tree_index_pos_search(goods_db, action->goods->name);
						tree_remove(goods_db, index_pos, &content);
						free_content(&content);
					}
				}
				free_string(&(action->goods->name), NAME_LENGTH);

				free_shelf(&(action->goods->shelf));

				free(action->goods);
				action->goods = NULL;

			}
		case CANCEL:
			content = NULL;
			shelf_curr = NULL;
			break;
		}
		break;
	case EDIT:
		content = (content_t *)tree_search(goods_db, action->goods->name);
		print_side_by_side(content, action->goods->item, "BEFORE", "AFTER");
		printf("%sDo you want to edit this item?\n", SPACE);
		printf("%sConfirm your choise by typing Edit or Cancel : ", SPACE);
		switch (read_command((READ)UNDO_EDIT, NULL)) {
		case EDIT:
			if (yes_no_question("Are you sure you want to apply changes for this item?") == YES) {
				if (tree_index_compare(get_content_name(content), get_content_name(action->goods->item))) {
					int index_pos = tree_index_pos_search(goods_db, get_content_name(content));
					tree_remove(goods_db, index_pos, &content);
					clone_content(content, action->goods->item);
					tree_insert(goods_db, get_content_name(content), content);
				}
				else {
					clone_content(content, action->goods->item);
				}

				free_content(&(action->goods->item));

				free_string(&(action->goods->name), NAME_LENGTH);

				//action->goods->item = NULL;
				free(action->goods);
				action->goods = NULL;

			}
		case CANCEL:
			content = NULL;
			break;
		}
		break;
	case REMOVE:
		content = action->goods->name ? tree_search(goods_db, action->goods->name) : NULL;
		if (!content) {
			show_goods(action->goods->item, 0);
		}
		else {
			show_content_shelf(content, action->goods->shelf);
		}
		printf("%sDo you want to add this item?\n", SPACE);
		printf("%sConfirm your choise by typing Add or Cancel : ", SPACE);
		switch (read_command(UNDO_REMOVE, NULL)) {
		case ADD:
			if (yes_no_question("Are you sure you want to add this item?") == YES) {
				if (!content) {
					tree_insert(goods_db, get_content_name(action->goods->item), action->goods->item);
					action->goods->item = NULL;
				}
				else {
					free_string(&(action->goods->name), NAME_LENGTH);

					add_shelf(get_content_shelfs(content), action->goods->shelf);
					//free(action->goods->shelf);
					action->goods->shelf = NULL;

					content = NULL;
				}

				free(action->goods);
				action->goods = NULL;
			}
			break;
		case CANCEL:
			content = NULL;
			break;
		}
		break;
	case PACK:

		show_pallet_receipt(action->pallet);

		printf("\n%sDo you want to return this items and add them back to the inventory?", SPACE);
		printf("\n%sConfirm your choise by typing Add or Cancel : ", SPACE);
		switch (read_command(UNDO_PACK, NULL)) {
		case ADD:
			if (yes_no_question("Are you sure you want to return this pallet?") == YES) {
				add_pallet(goods_db, action->pallet);
				//free(action->pallet);
				action->pallet = NULL;
			}
		case CANCEL:
			break;
		}
		break;
	}

	list_remove(last_action, 0, &action);
	free(action);
	action = NULL;
	
	//return goods_db;
}

void free_action_list(list_t **actions) {
	action_t *elem = NULL;
	while (list_length(*actions)) {
		list_remove(*actions, 0, &elem);
		switch (elem->type) {
		case PACK:
			free_content_tree(&(elem->pallet));
			break;
		case ADD:
			free_string(&(elem->goods->name), NAME_LENGTH);
			free_shelf(&(elem->goods->shelf));
			free(elem->goods);
			elem->goods = NULL;
			break;
		case EDIT:
			free_string(&(elem->goods->name), NAME_LENGTH);
			free_content(&(elem->goods->item));
			free(elem->goods);
			elem->goods = NULL;
			break;
		case REMOVE:
			if (elem->goods->name) {
				free_string(&(elem->goods->name), NAME_LENGTH);
				free_shelf(&(elem->goods->shelf));
			}
			else {
				free_content(&(elem->goods->item));
			}
			free(elem->goods);
			elem->goods = NULL;
			break;
		}
		free(elem);
		elem = NULL;
		
	}
	free(*actions);
	*actions = NULL;
}

