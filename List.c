#include <ctype.h>
//#include "Strings.h"
#include "InputReader.h"




int list_items(tree_t *goods_db, DO what, int *page_index) {
	//tree_t *iterator = goods_db;

	int i = 0, total = 0, p = *page_index, l = 10, out = -1; // 0 20
	bool done = false;
	bool again = false;
	
	char SPACE[] = "  ";
	char NEWLINE[] = "\n";
	char *BROWSE = "";
	char *REASON = "";
	//const char *CHOISES;
	char first_char;
	switch (what) {
	case REMOVE:
		REASON = " to remove";
		break;
	case EDIT:
		REASON = " to edit";
		break;
	case PACK:
		REASON = " to pack";
		break;
	default:
		break;
	}

	while (!done) {
		printf(NEWLINE);
		if (!again) {
			i = tree_print_indexes(goods_db, p*l, l);
			switch (p) {
			case 0: if (i<tree_size(goods_db)) { BROWSE = ", Next for browse"; } break;
			default: if (i<tree_size(goods_db)) { BROWSE = ", Previous or Next for browse"; }
					 else { BROWSE = ", Previous for browse"; } break;
			}
		}
		else {
			printf("%sIncorrect input. Choose from alternatives in the menu.\n", SPACE);
			printf("%s--------------------------------------------------------------------------\n", SPACE);
			again = false;
		}

		printf(NEWLINE);
		if ((i - p*l) <= 1) {
			printf("%sChoose index%s %d%s or Cancel : ", SPACE, REASON, i, BROWSE);
		}
		else {
			printf("%sChoose index%s %d-%d%s or Cancel : ", SPACE, REASON, p*l+1, i, BROWSE);
		}
		first_char = getchar();
		if (isdigit(first_char)) {
			int nr = read_integer(LIST, (first_char - 48));
			if (nr <= p*l || nr > i) {
				again = true;
			}
			else {
				out = nr - 1;
				done = true;
			}
		}
		else {
			switch (read_command(LIST_MENU, &first_char)) {
			case AGAIN:
				again = true;
				break;
			case NEXT:
				if (i < tree_size(goods_db)) {
					p++;
				}
				else {
					again = true;
				}
				break;
			case PREVIOUS:
				if (p > 0) {
					p--;
				}
				else {
					again = true;
				}
				break;
			case CANCEL:
				done = true;
				break;
			}

		}
	}
	*page_index = p;
	return out;
}


int list_shelfs(list_t *shelfs) {
	char SPACE[] = "  ";
	int j = 1, i = print_shelfs(shelfs);
	switch (i) {
	case 1:
		j = 1;
		break;
	default:

		do {
			if (j <= 0) {
				i = print_shelfs(shelfs);
				printf("%sIncorrect input.\n", SPACE);
			}

			printf("%sChoose shelf from the list [1-%d] to continue : ", SPACE, i);
			j = read_integer(LIST, -1);
		} while (j <= 0);

		break;
	}
	return j - 1;
}

void list_goods(tree_t *goods_db) {
	char SPACE[] = "  ";
	int chosen_index, page_index = 0;
	content_t *content;
	do {
		chosen_index = list_items(goods_db, LIST, &page_index);
		
		switch (chosen_index) {
		case -1:
			content = NULL;
			break;
		default:
			content = (content_t *)tree_search(goods_db, tree_index_search(goods_db, chosen_index));
			show_goods(content, (list_length(get_content_shelfs(content)) > 1) ? -1 : 0);
			printf("%sPress Enter to continue . . . ", SPACE);
			while (getchar() != '\n') {}
			break;
		}
	} while (chosen_index > -1);
}