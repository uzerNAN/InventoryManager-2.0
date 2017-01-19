#include <stdio.h>
#include <ctype.h>
#include "Structures.h"
#include "Enums.h"
//#include "Strings.h"

////#include "Strings.h"

typedef struct {
	int length_of_word;
	READ type;
} TUPLE;

typedef struct {
	char *name;
	int length_of_array;
	TUPLE *menu;
} TUPLE_ARRAY;

char choose_again_message(READ what, char char_to_confirm) {
	char SPACE[] = "  ";
	char LINE[] = "\n%s--------------------------------------------------------------------------\n";
	char INCORRECT[] = "%sIncorrect input.";
	char CONFIRM[] = "%sConfirm your choise by typing %s or Cancel : ";
	char QUESTION[] = "%sDo you want to %s %s?\n";
	char THIS_ITEM[] = "this item";

	switch (what) {
	case INSERTION:
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(CONFIRM, SPACE, "Add, Edit"); // %s%s%s  %s%s : 
		break;
	case CHANGES:
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(CONFIRM, SPACE, "Save, Edit");
		break;
	case DELETE:
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(CONFIRM, SPACE, "Remove");
		break;
	case UNDO_ADD: // %s%s%s  %s\n  %s%s : 
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(QUESTION, SPACE, "remove", THIS_ITEM);
		printf(CONFIRM, SPACE, "Remove");
		break;
	case UNDO_EDIT:
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(QUESTION, SPACE, "edit", THIS_ITEM);
		printf(CONFIRM, SPACE, "Edit");
		break;
	case UNDO_REMOVE:
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(QUESTION, SPACE, "add", THIS_ITEM);
		printf(CONFIRM, SPACE, "Add");
		break;
	case UNDO_PACK:
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(QUESTION, SPACE, "return", "this items and add them back to the inventory");
		printf(CONFIRM, SPACE, "Add");
		break;
	case MAIN_MENU:
		printf(INCORRECT, SPACE, " Choose from alternatives in the menu.");
		printf(LINE, SPACE);
		printf("%sWhat do you want to do this time?\n\n%s- I want to ", SPACE, SPACE);
		break;
	case EDIT_SHELF:
		printf(INCORRECT, SPACE, "\n");
		printf("%sFor edit type Shelf, Amount or Cancel : ", SPACE);
		break;
	case PACK_PALLET:
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(QUESTION, SPACE, "pack", "items and get the receipt");
		printf(CONFIRM, SPACE, "Pack");
		break;
	case ADD_PACK_PALLET:
		printf(INCORRECT, SPACE);
		printf(LINE, SPACE);
		printf(QUESTION, SPACE, "add", "more items or pack and get the receipt");
		printf(CONFIRM, SPACE, "Add, Pack");
		break;
	case CONFIDENCE:
		
		//break;
	case EDIT_MENU:
		//printf(PRINT_4, SPACE, INCORRECT, RULE_MENU, LINE);
		//show_edit_menu();
		//break;
	case LIST_MENU:
		char_to_confirm = '\n';
		break;
	default:
		break;
	}
	return char_to_confirm;
}



DO read_command(READ what, char *first_char) {
	DO choise = AGAIN;
	bool found;
	int i = 0, length_of_word = 0, j, k;
	char char_to_confirm = '_';

	TUPLE add_length[5] = { { 9, MAIN_MENU },{ 3, INSERTION },{ 3, UNDO_REMOVE },{ 3, ADD_PACK_PALLET },{ 3, UNDO_PACK } };
	TUPLE remove_length[3] = { { 12, MAIN_MENU },{ 6, DELETE },{ 6, UNDO_ADD } };
	TUPLE edit_length[5] = { { 19, MAIN_MENU },{ 4, INSERTION },{ 4, CHANGES },{ 4, UNDO_EDIT },{ 4, SAVE_EDIT } };
	TUPLE undo_length[1] = { { 16, MAIN_MENU } };
	TUPLE list_goods_length[1] = { { 14, MAIN_MENU } };
	TUPLE quit_length[1] = { { 4, MAIN_MENU } };
	TUPLE cancel_length[12] = { { 6, EDIT_MENU },{ 6, LIST_MENU },{ 6, DELETE },{ 6, INSERTION },{ 6, CHANGES },{ 6, EDIT_SHELF },
	{ 6, UNDO_ADD },{ 6, UNDO_EDIT },{ 6, UNDO_REMOVE },{ 6, UNDO_PACK },{ 6, PACK_PALLET },{ 6, ADD_PACK_PALLET } };
	TUPLE name_length[1] = { { 4, EDIT_MENU } };
	TUPLE description_length[1] = { { 12, EDIT_MENU } };
	TUPLE price_length[1] = { { 5, EDIT_MENU } };
	TUPLE shelf_length[2] = { { 5, EDIT_MENU },{ 5, EDIT_SHELF } };
	TUPLE amount_length[2] = { { 6, EDIT_MENU },{ 6, EDIT_SHELF } };
	TUPLE next_length[1] = { { 4, LIST_MENU } };
	TUPLE previous_length[1] = { { 8, LIST_MENU } };
	TUPLE save_length[2] = { { 4, CHANGES },{ 4, SAVE_EDIT } };
	TUPLE pack_length[3] = { { 11, MAIN_MENU },{ 4, PACK_PALLET },{ 4, ADD_PACK_PALLET } };
	TUPLE yes_length[1] = { { 3, CONFIDENCE } };
	TUPLE no_length[1] = { { 2, CONFIDENCE } };

	int command_length = 18;
	TUPLE_ARRAY command[18] = {
		{ "ADD GOODS", 5, add_length },
		{ "REMOVE GOODS", 3, remove_length },
		{ "EDIT SPECIFIC GOODS", 5, edit_length },
		{ "LIST ALL GOODS", 1, list_goods_length },
		{ "UNDO LAST CHANGE", 1, undo_length },
		{ "QUIT", 1, quit_length },
		{ "CANCEL", 12, cancel_length },
		{ "NAME", 1, name_length },
		{ "DESCRIPTION", 1, description_length },
		{ "PRICE", 1, price_length },
		{ "SHELF", 2, shelf_length },
		{ "AMOUNT", 2, amount_length },
		{ "NEXT", 1, next_length },
		{ "PREVIOUS", 1, previous_length },
		{ "SAVE", 2, save_length },
		{ "PACK PALLET", 3, pack_length },
		{ "YES", 1, yes_length },
		{ "NO", 1, no_length }
	};

	while (char_to_confirm != '\n') {
		if (first_char != NULL) {
			char_to_confirm = toupper(*first_char);
			first_char = NULL;
		}
		else {
			char_to_confirm = toupper(getchar());
		}
		switch (i) {
		case 0:
			found = false;
			j = -1;
			while (!found && j+1 < command_length) {
				j++;
				k = -1;
				while (!found && k+1 < command[j].length_of_array) {
					k++;
					found = ((command[j].menu[k]).type == what);
				}
				if (found) {
					if (char_to_confirm == command[j].name[0]) {
						choise = (DO)j;
						length_of_word = (command[j].menu[k]).length_of_word;
					}
					else {
						found = false;
					}
				}
			}
			break;
		default:
			if (char_to_confirm != '\n' && choise != AGAIN) {
				if (i >= length_of_word || (command[j].name[i]) != char_to_confirm) {
					choise = AGAIN;
				}
			}
			break;
		}
		if (char_to_confirm == '\n' && choise == AGAIN) {
			char_to_confirm = '_';
			i = 0;
			char_to_confirm = choose_again_message(what, char_to_confirm);
		}
		else if (i < length_of_word) {
			i++;
		}
	}
	return choise;
}

DO yes_no_question(char *question) {
	char SPACE[] = "  ";
	char PRINT_2_NL[] = "%s%s\n";
	char CONFIRM_YES_NO[] = "%sConfirm your choise by typing Yes or No : ";
	DO choise = AGAIN;
	printf(PRINT_2_NL, SPACE, question);
	printf(CONFIRM_YES_NO, SPACE);
	while (choise == AGAIN) {
		if ((choise = read_command(CONFIDENCE, NULL)) == AGAIN) {
			printf("%sIncorrect input.\n", SPACE);
			printf(PRINT_2_NL, SPACE, question);
			printf(CONFIRM_YES_NO, SPACE);
		}
	}
	return choise;
}

void read_shelf(shelf_t *shelf) {
	bool again = false;
	int i = 0;
	char char_to_confirm = '_';
	while (char_to_confirm != '\n') {
		char_to_confirm = getchar();
		switch (i) {
		case 0:
			if (isalpha(char_to_confirm)) {
				set_shelf_place(shelf, toupper(char_to_confirm));
				set_shelf_zero_at_start(shelf, 0);
				set_shelf_number(shelf, -1);
			}
			else {
				again = true;
			}
			break;
		default:
			if (again == false) {
				if (isdigit(char_to_confirm)) {
					if (get_shelf_number(shelf)<0 && (char_to_confirm - 48) == 0) {
						set_shelf_zero_at_start(shelf, get_shelf_zero_at_start(shelf) + 1);
					}
					else {
						if (get_shelf_number(shelf)<0) {
							set_shelf_number(shelf, 0);
						}
						set_shelf_number(shelf, get_shelf_number(shelf) * 10 + (char_to_confirm - 48));
					}
				}
				else if (char_to_confirm != '\n') {
					again = true;
				}
			}

			break;
		}
		if (char_to_confirm == '\n' && (again || (get_shelf_number(shelf) < 0 && get_shelf_zero_at_start(shelf) == 0))) {
			i = 0;
			char_to_confirm = '_';
			again = false;
			char SPACE[] = "  ";
			printf("%sIncorrect input.\n%sThe shelf identifies with a letter [A-Z], followed by a number [0-9]+.\n", SPACE, SPACE);
			printf("%s--------------------------------------------------------------------------\n", SPACE);
			printf("%sType in the shelf to allocate\n%s [A-Z][0-9]+ : ", SPACE, SPACE); // %s%s%s%s  %s%s%s\n   %s : 
		}
		else if (char_to_confirm == '\n' && get_shelf_number(shelf) < 0 && get_shelf_zero_at_start(shelf) > 0) {
			set_shelf_number(shelf, 0);
			set_shelf_zero_at_start(shelf, get_shelf_zero_at_start(shelf) - 1);
		}
		else {
			i++;
		}
	}
}

int read_integer(DO what, int number) { // err_type = 0 : PRICE // err_type = 1 : AMOUNT
	

	bool read = true, first = true;
	char char_to_confirm = '_';
	if (number >= 0) {
		first = false;
	}
	else {
		number = 0;
	}

	while (char_to_confirm != '\n') {
		char_to_confirm = getchar();
		if (!isdigit(char_to_confirm) && ((read && char_to_confirm != '\n') || (first && char_to_confirm == '\n'))) {
			read = false;
		}
		if (read && char_to_confirm != '\n') {
			number = number * 10 + (char_to_confirm - 48);
			if (first) {
				first = false;
			}
		}
		else if (!read) {
			char SPACE[] = "  ";
			while (char_to_confirm != '\n') { char_to_confirm = getchar(); }
			
			number = 0;
			first = true;
			read = true;
			char_to_confirm = '_';
			switch (what) {
			case PRICE: // PRICE
			case AMOUNT:
			case PACK:
				printf("%sIncorrect input. Only digits are allowed.\n", SPACE);
				printf("%s--------------------------------------------------------------------------\n", SPACE);
				printf("\n");
				switch (what) {
				case PRICE:
					printf("%sType in the calculated price\n%s [0-9]+ (ORE) : ", SPACE, SPACE);
					break;
				case AMOUNT: // AMOUNT
					printf("%sType in the amount of new items\n%s [0-9]+ : ", SPACE, SPACE);
					break;
				case PACK:
					printf("%sType in the amount of items to pack\n%s [0-9]+ : ", SPACE, SPACE);
					break;
				}
				break;
			case EDIT:
			case LIST:
				number = -1;
				char_to_confirm = '\n';
				break;
			default:
				break;
			}
		}
	}
	return number;
}

void read_string(char *input, DO what, int size) { // err_type = 0 : NAME // err_type = 1 : DESCRIPTION
												   
	bool read = false;
	int i = 0; 
	char char_to_confirm = '_';
	while (char_to_confirm != '\n' || read) {
		char_to_confirm = getchar();
		if ((i == 0 || i > size) && char_to_confirm == '\n') {
			char SPACE[] = "  ";
			char LINE[] = "\n%s--------------------------------------------------------------------------\n";
			char INCORRECT_MESSAGE[] = "%sIncorrect input. The input is empty or too large.";
			char TYPE_THE[] = "%s Type in the %s of the item\n%s[UP TO %d CHARACTERS] : ";
			switch (what) {
			case NAME:
				printf(INCORRECT_MESSAGE, SPACE);
				printf(LINE, SPACE);
				printf(TYPE_THE, SPACE, "name", SPACE, 20);
				break;
			case DESCRIPTION:
				printf(INCORRECT_MESSAGE, SPACE);
				printf(LINE, SPACE);
				printf(TYPE_THE, SPACE, "description", SPACE, 100);
				break;
			default:
				break;
			}
			if (i > size) {
				i = 0;
			}
			read = true;
		}
		else if (char_to_confirm != '\n') {
			if (i <= size) {
				input[i] = char_to_confirm; i++;
				read = false;
			}
			else if (read != true) {
				read = true;
			}
		}
	}
	input[i] = '\0';
}
