//#include "Strings.h"
#include "InputReader.h"
#include "Action.h"
#include "Add.h"
#include "Remove.h"
#include "List.h"

int shelfs_amount(list_t *shelfs) {
	int amount = 0, i = 0, l = list_length(shelfs);
	while (i < l) {
		amount += get_shelf_amount((shelf_t *)list_get(shelfs, i));
		i++;
	}
	return amount;
}

unsigned long int content_price(content_t *content) {
	return (unsigned long int)get_content_price(content)*shelfs_amount(get_content_shelfs(content));
}

unsigned long int goods_price(tree_t *goods) {
	int i = 0, price = 0, goods_size = tree_size(goods);

	while (i < goods_size) {
		price += content_price((content_t *)tree_search(goods, tree_index_search(goods, i)));
		i++;
	}

	return price;
}

void show_pallet(tree_t* pallet, bool receipt) {
	int pallet_size, i = 0;
	content_t *content = NULL;
	char SPACE[] = "  ";
	pallet_size = tree_size(pallet);


	printf("\n%sThe pallet %s\n", SPACE, pallet_size ? "contains :\n" : "is empty.");

	if (pallet_size) {
		while (i < pallet_size) {
			content = (content_t *)tree_search(pallet, tree_index_search(pallet, i));
			printf("%s ", SPACE);
			if (receipt) {
				printf("%d. %-15s ( %d st * %.2f kr )   %.2f KR\n", (i + 1), get_content_name(content), shelfs_amount(get_content_shelfs(content)), get_content_price(content) / 100.00f, content_price(content) / 100.00f);
			}
			else {
				printf("- %s (%d)\n", get_content_name(content), shelfs_amount(get_content_shelfs(content)));
			}
			i++;
		}
		if (receipt) {
			printf("\n%sTotal price for your pallet : %.2f KR\n", SPACE, goods_price(pallet) / 100.00f);
		}
		content = NULL;
	}
	printf("\n");
}

void show_pallet_receipt(tree_t *pallet) {

	char *string = NULL, *name = NULL;
	shelf_t *shelf = NULL;
	content_t *content = NULL;
	list_t *places = NULL, *names = NULL;
	int i = 0, j, l, size = tree_size(pallet);
	char SPACE[] = "  ";

	show_pallet(pallet, true);

	printf("%sPlaces to go :\n\n", SPACE);

	list_new(&places);
	list_new(&names);

	while (i < size) {
		content = (content_t *)tree_search(pallet, tree_index_search(pallet, i));
		j = 0;
		l = list_length(get_content_shelfs(content));
		while (j < l) {
			list_insert(names, add_shelf(places, (shelf_t *)list_get(get_content_shelfs(content), j)), get_content_name(content));
			j++;
		}
		i++;
	}
	content = NULL;

	i = 0;
	size = list_length(places);

	while (i < size) {
		list_remove(places, 0, &shelf);
		list_remove(names, 0, &name);
		j = 1 + get_shelf_zero_at_start(shelf) + get_int_size(get_shelf_number(shelf));
		new_string(&string, j);
		shelf_to_string(string, shelf, j);
		printf("%s %s (%d %s)\n", SPACE, string, get_shelf_amount(shelf), name);
		free(string);
		string = NULL;
		name = NULL;
		shelf = NULL;
		i++;
	}
	printf("\n");
	free(names);
	names = NULL;
	free(places);
	places = NULL;
}

void add_pallet(tree_t *goods_db, tree_t *pallet) {
	content_t *content = NULL;
	list_t *shelfs = NULL;
	shelf_t *shelf = NULL;
	int j, l, i = tree_size(pallet);

	do {
		i--;
		tree_remove(pallet, i, &content);
		if (tree_search(goods_db, get_content_name(content))) {
			j = 0;
			shelfs = get_content_shelfs((content_t *)tree_search(goods_db, get_content_name(content)));
			l = list_length(get_content_shelfs(content));
			while (j < l) {
				list_remove(get_content_shelfs(content), j, &shelf);

				add_shelf(shelfs, shelf);
				j++;
			}
			free_content(&content);
			//free(content);
			shelfs = NULL;
		}
		else {
			tree_insert(goods_db, get_content_name(content), content);
			content = NULL;
		}
		//i++;
	} while (i);

}

int get_max_shelf(list_t *shelfs, shelf_t **shelf) {
	//shelf_t *shelf = NULL;
	int i = 0, o = -1, l = list_length(shelfs);
	while (i < l) {
		if (*shelf == NULL || get_shelf_amount(*shelf) < get_shelf_amount((shelf_t *)list_get(shelfs, i))) {
			*shelf = (shelf_t *)list_get(shelfs, i);
			o = i;
		}
		i++;
	}
	return o;
}

void pack_item(tree_t *pallet, content_t *content, shelf_t *shelf) {
	content_t *item = NULL;
	list_t *shelfs = NULL;
	item = tree_search(pallet, get_content_name(content));

	if (item == NULL) {
		new_content(&item);
		list_new(&shelfs);
		set_content_shelfs(item, shelfs);
		shelfs = NULL;

		copy_string(get_content_name(item), get_content_name(content), NAME_LENGTH);
		copy_string(get_content_description(item), get_content_description(content), DESC_LENGTH);
		set_content_price(item, get_content_price(content));


		add_item(pallet, item, shelf, NULL);

		if (!get_content_shelfs(item)) {
			free(item);
		}

		
		//free(item);
	}
	else {
		add_shelf(get_content_shelfs(item), shelf);
	}
	item = NULL;
	//return pallet;
}

//char PACK_AMOUNT[] = "Type the amount of items to pack [0-%d] : ";

void pack_pallet(tree_t *goods_db, list_t *last_action) {
	tree_t *pallet = NULL;
	content_t *content = NULL;
	list_t *shelfs = NULL;
	shelf_t *shelf = NULL, *max_shelf = NULL;
	int i, index, s, page_index = 0;
	bool add = true;
	char SPACE[] = "  ";

	tree_new(&pallet);
	do {
		printf("\n%sItems in the database :\n", SPACE);
		index = list_items(goods_db, PACK, &page_index);
		switch (index) {
		case -1:
			add = false;
			break;
		default:

			content = (content_t *)tree_search(goods_db, tree_index_search(goods_db, index));

			show_goods(content, -2);
			shelfs = get_content_shelfs(content);
			s = shelfs_amount(shelfs);
			i = 0;
			do {
				if (s < i) {
					printf("\n%sIncorrect input.", SPACE);
				}
				printf("\n%sType the amount of items to pack [0-%d] : ", SPACE, s);
				i = read_integer(AMOUNT, -1);
			} while (s < i);

			while (i) {
				s = get_max_shelf(shelfs, &max_shelf);
				if (!shelf) {
					new_shelf(&shelf);
				}
				copy_shelf(shelf, max_shelf);
				if (get_shelf_amount(shelf) <= i) {
					i -= get_shelf_amount(shelf);
					pack_item(pallet, content, shelf);
					if (get_shelf_amount(shelf)) {
						shelf = NULL;
					}
					if (list_length(shelfs) == 1 && i == 0) {
						//show_goods(content, 0);
						content = NULL;
					}
					max_shelf = NULL;
					remove_item(goods_db, index, s, NULL);
				}
				else {
					set_shelf_amount(shelf, i);

					pack_item(pallet, content, shelf);
					if (get_shelf_amount(shelf)) {
						shelf = NULL;
					}
					set_shelf_amount(max_shelf, get_shelf_amount(max_shelf) - i);
					i = 0;
					max_shelf = NULL;
				}
			}
			content = NULL;
			break;
		}
		if (add || tree_size(pallet)) {
			show_pallet(pallet, false);
			if (tree_size(pallet)) {
				s = tree_size(goods_db);
				if (!s) {
					printf("\n%sThere is no more items.", SPACE);
				}
				printf("\n%sDo you want to %s and get the receipt?", SPACE, (s ? "add more items or pack" : "pack items"));
				printf("\n%sConfirm your choise by typing %s or Cancel : ", SPACE, (s ? "Add, Pack" : "Pack"));

				switch (read_command((s ? ADD_PACK_PALLET : PACK_PALLET), NULL)) {
				case ADD:
					break;
				case PACK:
					if (yes_no_question("Are you sure you want to pack item(s)?") == YES) {
						put_action_pallet(last_action, pallet);
						show_pallet_receipt(pallet);
						//free_content_tree(pallet);
						//free(pallet);
						pallet = NULL;
						printf("%sPress Enter to continue . . . ", SPACE);
						while (getchar() != '\n') {}
					}
					add = false;
					break;
				case CANCEL:
					if (yes_no_question("Are you sure you want to cancel and return item(s)?") == YES) {
						add = false;
					}
					break;
				}
			}
		}

	} while (add);

	if (pallet) {
		if (tree_size(pallet)) {

			add_pallet(goods_db, pallet);

		}
		free(pallet);
		pallet = NULL;
	}
	if (shelf) {
		free(shelf);
		shelf = NULL;
	}
	//return goods_db;
}
