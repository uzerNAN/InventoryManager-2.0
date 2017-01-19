//#include "Strings.h"
#include "InputReader.h"
#include "Action.h"
#include "List.h"

void remove_item(tree_t *goods_db, int index, int shelf_i, list_t *last_action) {
	shelf_t *shelf = NULL;
	content_t *item = (content_t *)tree_search(goods_db, tree_index_search(goods_db, index));
	if (list_length(get_content_shelfs(item))>1) {
		list_remove(get_content_shelfs(item), shelf_i, &shelf);
		//free(shelf);
		if (last_action != NULL) {
			put_action_goods(last_action, REMOVE, get_content_name(item), shelf, NULL);
		}
		else {
			free(shelf);
		}
		shelf = NULL;
	}
	else {
		int index_pos = tree_index_pos_search(goods_db, get_content_name(item));
		tree_remove(goods_db, index_pos, &item);
		if (last_action != NULL) {
			put_action_goods(last_action, REMOVE, NULL, NULL, item);
		}
		else {
			free_content_shelfs(item);
			free(item);
		}
	}
	item = NULL;
	//return goods_db;
}

DO verify_and_remove_item(tree_t *goods_db, int index, int shelf_i, list_t *last_action) {
	DO choise;
	shelf_t *shelf = NULL;
	content_t *item = (content_t *)tree_search(goods_db, tree_index_search(goods_db, index));
	//if(item != NULL){
	show_goods(item, shelf_i);
	item = NULL;
	char SPACE[] = "  ";
	printf("%sConfirm your choise by typing Remove or Cancel : ", SPACE);
	switch (choise = read_command(DELETE, NULL)) {
	case REMOVE:
		if (yes_no_question("Are you sure you want to remove item(s) from this shelf?") == YES) {
			remove_item(goods_db, index, shelf_i, last_action);
		}
		break;
	case CANCEL:
		break;
	}
	//}
	return choise;
}

void remove_goods(tree_t *goods_db, list_t *last_action) {
	int chosen_index, chosen_shelf, page_index = 0;
	DO list_alt = AGAIN;
	do {
		if (tree_size(goods_db) > 0) {
			chosen_index = list_items(goods_db, REMOVE, &page_index);
			switch (chosen_index) {
			case -1:
				list_alt = CANCEL;
				break;
			default:
				chosen_shelf = list_shelfs(get_content_shelfs((content_t *)tree_search(goods_db, tree_index_search(goods_db, chosen_index))));
				if (verify_and_remove_item(goods_db, chosen_index, chosen_shelf, last_action) == CANCEL) {
					list_alt = AGAIN;
				}
				break;
			}
		}
	} while (list_alt == AGAIN);
	//return goods_db;
}