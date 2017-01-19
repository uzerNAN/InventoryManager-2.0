//#include "Strings.h"
#include "Enums.h"
#include "Action.h"
#include "Add.h"
#include "Edit.h"
#include "List.h"
#include "Remove.h"
#include "Pallet.h"

void show_main_menu(tree_t *goods_db, list_t *last_action) {

	char SPACE[] = "  ";

	printf("\n%sAdd goods\n", SPACE);
	if (tree_size(goods_db) > 0) {
		printf("%sPack pallet\n", SPACE);
		printf("%sRemove goods\n", SPACE);
		printf("%sEdit specific goods\n", SPACE);
		printf("%sList all goods\n", SPACE);
	}
	if (list_length(last_action) > 1) {
		printf("%sUndo last change\n", SPACE);
	}
	printf("%sQuit\n\n", SPACE);
	printf("%sWhat do you want to do this time?\n\n%s- I want to ", SPACE, SPACE);
}


void manage_goods(DO what, tree_t *goods_db, list_t *last_action) {
	bool incorrect = false;
	switch (what) {
	case ADD:
		add_goods(goods_db, last_action);
		break;
	case PACK:
		if (tree_size(goods_db) == 0) {
			incorrect = true;
		}
		else {
			pack_pallet(goods_db, last_action);
		}
		break;
	case REMOVE:
		if (tree_size(goods_db) == 0) {
			incorrect = true;
		}
		else {
			remove_goods(goods_db, last_action);
		}
		break;
	case EDIT:
		if (tree_size(goods_db) == 0) {
			incorrect = true;
		}
		else {
			edit_goods(goods_db, last_action);
		}
		break;
	case UNDO:
		if (list_length(last_action) < 2) {
			incorrect = true;
		}
		else {
			undo_last_action(goods_db, last_action);
		}
		break;
	case LIST:
		if (tree_size(goods_db) == 0) {
			incorrect = true;
		}
		else {
			list_goods(goods_db);
		}
		break;
	case QUIT:
		break;
	case AGAIN:
		incorrect = true;
		break;
	}
	if (incorrect) {
		char SPACE[] = "  ";
		printf("%sIncorrect input. Choose from alternatives in the menu.\n", SPACE);
		printf("%s--------------------------------------------------------------------------\n", SPACE);
	}
	//return goods_db;
}

