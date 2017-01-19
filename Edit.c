#include <ctype.h>
//#include "Strings.h"
#include "InputReader.h"
#include "Add.h"
#include "Action.h"
#include "List.h"


int edit_shelf(tree_t *goods_db, content_t *content, int shelf_i) {
	char *shelf_string = NULL;
	shelf_t *verifyed_shelf = NULL, *shelf = list_get(get_content_shelfs(content), shelf_i);
	int shelf_size = 1 + get_shelf_zero_at_start(shelf) + get_int_size(get_shelf_number(shelf));
	char SPACE[] = "  ";
	new_string(&shelf_string, shelf_size);
	shelf_to_string(shelf_string, shelf, shelf_size);
	printf("\n%sCurrent shelf : %s", SPACE, shelf_string);
	printf("\n%s--------------------------------------------------------------------------\n", SPACE);
	free(shelf_string);
	shelf_string = NULL;

	new_shelf(&verifyed_shelf);
	read_and_verify_shelf(verifyed_shelf, goods_db, " new ", content);
	if (shelf_equal(verifyed_shelf, shelf) != 0) {
		set_shelf_amount(verifyed_shelf, get_shelf_amount(shelf));
		copy_shelf(shelf, verifyed_shelf);

		list_remove(get_content_shelfs(content), shelf_i, &shelf);

		shelf_i = add_shelf(get_content_shelfs(content), shelf);

	}
	free(verifyed_shelf);
	verifyed_shelf = NULL;
	shelf = NULL;
	return shelf_i;
}

void edit_shelf_amount(shelf_t *shelf) {
	char SPACE[] = "  ";
	printf("\n%sCurrent amount : %d", SPACE, get_shelf_amount(shelf));
	printf("\n%s--------------------------------------------------------------------------", SPACE);
	printf("\n%sType in new amount of the items\n%s [0-9]+ : ", SPACE, SPACE);
	set_shelf_amount(shelf, read_integer(AMOUNT, -1));
}

int edit_shelf_and_amount(tree_t *goods_db, content_t *content, int shelf_i) {
	char *shelf_string = NULL;
	shelf_t *shelf = (shelf_t *)list_get(get_content_shelfs(content), shelf_i);
	int shelf_size = 1 + get_shelf_zero_at_start(shelf) + get_int_size(get_shelf_number(shelf));
	char SPACE[] = "  ";
	new_string(&shelf_string, shelf_size);
	shelf_to_string(shelf_string, shelf, shelf_size);
	printf("\n%s :  %s  : \n\n", SPACE, get_content_name(content));
	printf("%s %-10s%s\n", SPACE, "SHELF", shelf_string);
	printf("%s %-10s%d\n\n", SPACE, "AMOUNT", get_shelf_amount(shelf)); //%s%-15s%d%s
	printf("%sFor edit type Shelf, Amount or Cancel : ", SPACE);
	switch (read_command(EDIT_SHELF, NULL)) {
	case SHELF:

		shelf_i = edit_shelf(goods_db, content, shelf_i);
		
		break;
	case AMOUNT:
		edit_shelf_amount(shelf);
		break;
	case CANCEL:
		shelf_i = -1;
		break;
	}
	free(shelf_string);
	shelf_string = NULL;
	shelf = NULL;
	return shelf_i;
}



int edit_content(tree_t *goods_db, int index, bool need_save, char *first_char, bool *again, bool *done) {
	char *r_string = NULL;
	char SPACE[] = "  ";
	content_t *item = tree_search(goods_db, tree_index_search(goods_db, index));
	int i = list_length(get_content_shelfs(item)), index_pos = index;
	switch (read_command(EDIT_MENU, first_char)) {
	case NAME: // \n%s%s%s : %s%s
		new_string(&r_string, NAME_LENGTH);
		//copy_string(edit_name, name, NAME_LENGTH);
		do {
			copy_string(r_string, get_content_name(item), NAME_LENGTH);

			printf("\n%sCurrent name : %s\n", SPACE, r_string);
			printf("%s--------------------------------------------------------------------------\n", SPACE);
			if (*again) {
				printf("\n%sThis product name is already taken, please try another one.\n\n", SPACE);
				*again = false;
			}
			printf("%sType in new name of the item\n%s [UP TO 20 CHARACTERS] : ", SPACE, SPACE);

			read_string(r_string, NAME, NAME_LENGTH);

			if (tree_index_compare(get_content_name(item), r_string) != 0) {
				if (tree_search(goods_db, r_string) == NULL) {
					index_pos = tree_index_pos_search(goods_db, get_content_name(item));
					tree_remove(goods_db, index_pos, &item);
					index_pos = tree_insert(goods_db, r_string, item);
					copy_string(get_content_name(item), r_string, NAME_LENGTH);
				}
				else {
					*again = true;
				}
			}
		} while (*again);

		prepare_for_free_string(r_string, NAME_LENGTH);
		free(r_string);
		r_string = NULL;
		break;
	case DESCRIPTION:
		printf("\n%sCurrent description : %s\n", SPACE, get_content_description(item));
		printf("%s--------------------------------------------------------------------------\n", SPACE);
		printf("%sType in new description of the item\n%s [UP TO 100 CHARACTERS] : ", SPACE, SPACE);
		read_string(get_content_description(item), DESCRIPTION, DESC_LENGTH);
		break;
	case PRICE:
		printf("\n%sCurrent price : %0.2f\n", SPACE, ((float)get_content_price(item)) / 100.0f);
		printf("%s--------------------------------------------------------------------------\n", SPACE);
		printf("%sType in new calculated price\n%s [0-9]+ (ORE) : ", SPACE, SPACE);
		set_content_price(item, read_integer(PRICE, -1));
		break;
	case SHELF:
		switch (i) {
		case 1:

			edit_shelf(goods_db, item, 0);

			break;
		default:
			*again = true;
			break;
		}
		break;
	case AMOUNT:
		switch (i) {
		case 1:

			edit_shelf_amount((shelf_t *)list_get(get_content_shelfs(item), 0));

			break;
		default:
			*again = true;
			break;
		}
		break;
	case CANCEL:
		if (!need_save) {
			*done = true;
		}
		break;
	case AGAIN:
		*again = true;
		break;
	default:
		break;
	}
	return index_pos;
	//return goods_db;
}

int edit_item(tree_t *goods_db, int index, list_t *last_action) {
	bool done = false, need_save = false, again = false;
	int i = 0, shelf_i, shelf_j = 0, index_pos = index;
	char first_char;
	list_t *shelfs = NULL;
	char SPACE[] = "  ";

	content_t *origin = NULL, *item = (content_t *)tree_search(goods_db, tree_index_search(goods_db, index));
	new_content(&origin);
	list_new(&(shelfs));
	set_content_shelfs(origin, shelfs);
	shelfs = NULL;
	copy_content(origin, item);
	while (!done) {
		do {

			i = show_goods(item, (list_length(get_content_shelfs(item)) > 1) ? -1 : 0);

			if (again && shelf_j >= 0) {
				switch (i) {
				case 1:
					printf("%s Incorrect input.\n%s Type NAME, DESCRIPTION, PRICE, SHELF, AMOUNT or CANCEL.\n", SPACE, SPACE);
					break;
				default:
					printf("%s Incorrect input.\n%s Type NAME, DESCRIPTION, PRICE, CANCEL or index of shelf [1-%d].\n", SPACE, SPACE, i);
					break;
				}
				again = false;
			}
			else {
				if (shelf_j < 0) {
					shelf_j = 0;
				}
				if (again) {
					again = false;
				}
			}

			printf("%sChoose from the alternatives in the menu or Cancel : ", SPACE);
			first_char = getchar();
			if (last_action != NULL && i > 1 && isdigit(first_char)) {
				shelf_i = read_integer(EDIT, first_char - 48) - 1;
				if ( shelf_i >= 0 && shelf_i < list_length(get_content_shelfs(item)) ) {
					shelf_j = edit_shelf_and_amount(goods_db, item, shelf_i);
					again = !( need_save = (shelf_j >= 0) );
				}
				else {
					again = true;
				}
			}
			else {

				index_pos = edit_content(goods_db, index_pos, need_save, &first_char, &again, &done);

				if (!again && !done) {
					done = !( need_save = ( last_action != NULL ) );
				}
			}
		} while (again);
		if (!done) {
			if( !( done = !need_save ) ) {
				do {
					print_side_by_side(origin, item, "BEFORE", "AFTER");
					printf("%sDo you want to save the changes?\n%sConfirm your choise by typing Save, Edit or Cancel : ", SPACE, SPACE); // %s%s\n  %s%s : 
					switch (read_command(CHANGES, NULL)) {
					case SAVE:
						if ( done = !( again = ( yes_no_question("Are you sure yo want to save changes for this item?") == NO ) ) ) {
							put_action_goods(last_action, EDIT, get_content_name(item), NULL, origin);
							origin = NULL;
						}
						break;
					case EDIT:
						again = false;
						break;
					case CANCEL:
						if ( done = !( again = ( yes_no_question("Are you sure you want to cancel? Input data will be lost.") == NO ) ) ) {
							if (tree_index_compare(get_content_name(item), get_content_name(origin))) {
								//int index_pos = tree_index_pos_search(goods_db, get_content_name(item));
								tree_remove(goods_db, index_pos, &item);
								clone_content(item, origin);
								index_pos = tree_insert(goods_db, get_content_name(item), item);
							}
							else {
								clone_content(item, origin);
							}
						}
						break;
					}
				} while (again);
			}
		}
	}
	item = NULL;
	if (origin) {
		free_content(&origin);
	}
	return index_pos;
	//return goods_db;
}

void edit_goods(tree_t *goods_db, list_t *last_action) {
	int page_index = 0, chosen_index;
	do {
		chosen_index = list_items(goods_db, EDIT, &page_index);
		switch (chosen_index) {
		case -1:
			break;
		default:
			edit_item(goods_db, chosen_index, last_action);
			break;
		}
	} while (chosen_index >= 0);
	//return goods_db;
}