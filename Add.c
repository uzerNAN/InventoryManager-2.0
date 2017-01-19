//#include "Strings.h"
#include "InputReader.h"
#include "Action.h"
#include "Edit.h"

// After using add_shelf function
// the inputted shelf has to be checked for amount.
// Shelf amount is set to zero to show that the shelf is not linked to the list,
// it happens if same shelf already exists.
int add_shelf(list_t *shelfs, shelf_t *shelf) {
	bool iterate = true;
	shelf_t *ishelf = NULL;

	int i = 0, shelf_i = get_shelf_index(shelfs, shelf);
	switch (shelf_i) {
	case -1:
		if (list_length(shelfs) > 0) {
			while (iterate) {
				switch (shelf_equal((shelf_t *)list_get(shelfs, i), shelf)) {
				case -1:
					i++;
					if (i >= list_length(shelfs)) {
						list_append(shelfs, shelf);
						iterate = false;
					}
					break;
					/*
				case 0:
					ishelf = (shelf_t *)list_get(shelfs, i);
					set_shelf_amount(ishelf, get_shelf_amount(ishelf) + get_shelf_amount(shelf));
					iterate = false;
					break;
					*/
				case 1:
					list_insert(shelfs, i, shelf);
					iterate = false;
					break;
				}
			}
		}
		else {
			list_insert(shelfs, 0, shelf);
		}
		break;
	default:
		i = shelf_i;
		ishelf = (shelf_t *)list_get(shelfs, i);
		set_shelf_amount(ishelf, get_shelf_amount(ishelf) + get_shelf_amount(shelf));
		if (ishelf != shelf) {
			set_shelf_amount(shelf, 0);
		}
		break;
	}
	ishelf = NULL;
	return i;
}

bool shelf_is_free(tree_t *tree_db, shelf_t *shelf, char *name) {
	bool iterate = true;
	bool is_free = true;
	bool read_list = true;
	content_t *content_it;
	int j = 0;

	while (iterate && is_free) {

		content_it = (content_t *)tree_search(tree_db, tree_index_search(tree_db, j));

		if (content_it != NULL) {
			if (get_content_shelfs(content_it) != NULL) {

				switch (get_shelf_index(get_content_shelfs(content_it), shelf)) {
				case -1:

					break;
				default:
					if (tree_index_compare(get_content_name(content_it), name) != 0) {
						is_free = false;
					}
					iterate = false;
					break;
				}
			}
			else {
				printf("\nThere is no shelfs to check.. Whaat? Name : %s\n", get_content_name(content_it));
			}
			content_it = NULL;
		}
		if (is_free) {
			j++;
			if (j >= tree_size(tree_db)) {
				iterate = false;
			}
		}
	}
	return is_free;
}

void read_and_verify_shelf(shelf_t *shelf, tree_t *goods_db, char *print, content_t *content) {
	bool verifyed;
	char SPACE[] = "  ";
	do {
		printf("%sType in%sshelf to allocate\n", SPACE, print); //%s%s%s%s\n%s%s : 
		printf("%s [A-Z][0-9]+ : ", SPACE);
		read_shelf(shelf);
		if (tree_size(goods_db) > 0) {
			verifyed = shelf_is_free(goods_db, shelf, get_content_name(content));
		}
		else {
			verifyed = true;
		}
		switch (verifyed) {
		case false:
			printf("%sThe shelf you are trying to allocate is not empty. Try other shelf.\n", SPACE);
			printf("%s--------------------------------------------------------------------------\n", SPACE);
			break;
		case true:
			break;
		default:
			break;
		}

	} while (!verifyed);
}

// After use of add_item function the content input has to be checked,
// if the shelf list is set to NULL, then it is not linked to the list.
// Also shelf input has to be checked according to the description for add_shelf function.
void add_item(tree_t *goods_db, content_t *input, shelf_t *shelf, list_t *last_action) {
	content_t *reserve_c = NULL;
	shelf_t *action_shelf = NULL;

	if (last_action != NULL) {
		new_shelf(&action_shelf);
		copy_shelf(action_shelf, shelf);
		put_action_goods(last_action, ADD, get_content_name(input), action_shelf, NULL);
		action_shelf = NULL;
	}

	reserve_c = tree_search(goods_db, get_content_name(input));

	if (reserve_c == NULL) {

		add_shelf(get_content_shelfs(input), shelf);

		tree_insert(goods_db, get_content_name(input), input);
	}
	else {
		//reserve_c = (content_t *)tree_search(goods_db, get_content_name(input));

		add_shelf(get_content_shelfs(reserve_c), shelf);
		if (input != reserve_c) {

			free_content_shelfs(input);

		}
		reserve_c = NULL;
	}
	//return goods_db;
}

void verify_and_add_item(tree_t *goods_db, content_t *item, shelf_t *shelf, list_t *last_action) {
	DO confirm;
	content_t *reserve = NULL;
	list_t *shelfs = NULL;
	shelf_t *edit_s = NULL;
	char SPACE[] = "  ";
	do {
		show_content_shelf(item, shelf);

		printf("%sConfirm your choise by typing Add, Edit or Cancel : ", SPACE);

		confirm = read_command(INSERTION, NULL);

		switch (confirm) {

		case ADD:
			if (yes_no_question("Are you sure you want to add this item?") == YES) {
				add_item(goods_db, item, shelf, last_action);
			}
			break;

		case EDIT:
			if (list_length(get_content_shelfs(item)) > 0) {
				new_content(&reserve);
				copy_string(get_content_name(reserve), get_content_name(item), NAME_LENGTH);
				list_new(&shelfs);
				set_content_shelfs(reserve, shelfs);
				new_shelf(&edit_s);
				copy_shelf(edit_s, (shelf_t *)list_get(shelfs, 0));
				list_insert(shelfs, 0, edit_s);
				edit_s = NULL;
				if (edit_shelf_and_amount(goods_db, reserve, 0) == 0) {

					copy_shelf(shelf, (shelf_t *)list_get(shelfs, 0));
					
				}
				shelfs = NULL;
				free_content_shelfs(reserve);
				free(reserve);
				reserve = NULL;
			}
			else {
				shelfs = get_content_shelfs(item);
				list_insert(shelfs, 0, shelf);


				int index_pos = tree_insert(goods_db, get_content_name(item), item);

				index_pos = edit_item(goods_db, index_pos, NULL);

				//index_pos = tree_index_pos_search(goods_db, get_content_name(item));

				tree_remove(goods_db, index_pos, &item);


				list_remove(shelfs, 0, &shelf);
				shelfs = NULL;

			}
			break;

		case CANCEL:
			if (yes_no_question("Are you sure you want to cancel? Input data will be lost.") == NO) {
				confirm = AGAIN;
			}
			break;

		}

	} while (confirm != ADD && confirm != CANCEL);
	//return goods_db;
}

//char MATCHED[] = "Found a product in the base with this name, loading data . . .";

void add_goods(tree_t *goods_db, list_t *last_action) {
	shelf_t *shelf = NULL;
	content_t *known_item = NULL, *item = NULL;
	list_t *shelfs = NULL;
	int integer, size_of_tree = tree_size(goods_db);
	char SPACE[] = "  ";
	new_content(&item);
	//shelfs = get_content_shelfs(item);
	list_new(&shelfs);
	set_content_shelfs(item, shelfs);
	shelfs = NULL;
	
	printf("\n%sType in the name of the item\n%s [UP TO 20 CHARACTERS] : ", SPACE, SPACE);
	read_string(get_content_name(item), NAME, NAME_LENGTH);
	known_item = (content_t *)tree_search(goods_db, get_content_name(item));
	
	if (known_item != NULL) {
		printf("\n%sFound a product in the base with this name, loading data . . .\n", SPACE);
		copy_content(item, known_item);
		known_item = NULL;
		show_goods(item, -1);
	}
	else {

		printf("%sType in the description of the item\n%s [UP TO 100 CHARACTERS] : ", SPACE, SPACE);
		
		read_string(get_content_description(item), DESCRIPTION, DESC_LENGTH);

		printf("%sType in the calculated price\n%s [0-9]+ (ORE) : ", SPACE, SPACE);
		integer = read_integer(PRICE, -1);
		set_content_price(item, integer);
	}
	new_shelf(&shelf);
	read_and_verify_shelf(shelf, goods_db, " the ", item);

	printf("%sType in the amount of new items\n%s [0-9]+ : ", SPACE, SPACE);
	integer = read_integer(AMOUNT, -1);
	set_shelf_amount(shelf, integer);
	verify_and_add_item(goods_db, item, shelf, last_action);
	if (!get_content_shelfs(item) || size_of_tree == tree_size(goods_db)) {
		free(item);
	}
	if (!get_shelf_amount(shelf)) {
		free(shelf);
	}
	item = NULL;
	shelf = NULL;
	//return goods_db;
}