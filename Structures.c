#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "Strings.h"
#include "LinkedList.h"
#include "AVLtree.h"

typedef enum COMMAND DO;

typedef struct shelf
{
	char place;
	int number;
	int zero_at_start;
	int amount;
} shelf_t;

typedef struct content
{
	char name[20];
	char description[100];
	int price;
	list_t *shelfs;
} content_t;


const int NAME_LENGTH = 20;
const int DESC_LENGTH = 100;



const size_t ALLOC_SHELF = sizeof(shelf_t);
const size_t ALLOC_CONTENT = sizeof(content_t);
const size_t ALLOC_CHAR = sizeof(char);

int abs_int(int out) {
	if (out<0) {
		out = -out;
	}
	return out;
}

int double_to_int(double in) {
	return (int)(in + 0.1);
}

int get_int_size(int n) {
	int size = 0;

	switch (n) {
	case 0:
		size = 1;
		break;
	default:
		size = double_to_int(floor(log10((double)abs_int(n)))) + 1;
		break;
	}

	return size;
}

void new_shelf(shelf_t **shelf) {
	*shelf = (shelf_t *)
		malloc(ALLOC_SHELF);
	(*shelf)->place = '\0';
	(*shelf)->zero_at_start = 0;
	(*shelf)->number = 0;
	(*shelf)->amount = 0;
}

void new_content(content_t **content) {
	(*content) = (content_t *)malloc(ALLOC_CONTENT);
	(*content)->shelfs = NULL;
}

void new_string(char **string, int size) {
	size_t alloc_chars = ALLOC_CHAR*(size + 1);
	*string = (char *)malloc(alloc_chars);
}

void prepare_for_free_string(char *string, int size) {
	int i = 0;
	while (i < size) {
		string[i] = 'A';
		i++;
	}
	string[i] = '\0';
}


void copy_shelf(shelf_t *copy, shelf_t *shelf) {
	copy->place = shelf->place;
	copy->number = shelf->number;
	copy->zero_at_start = shelf->zero_at_start;
	copy->amount = shelf->amount;
}

int shelf_equal(shelf_t *shelf, shelf_t * equal) {
	return (shelf->place == equal->place
		&& shelf->zero_at_start == equal->zero_at_start
		&& shelf->number == equal->number) ? 0 : (equal->place < shelf->place
			|| (equal->place == shelf->place
				&& equal->number < shelf->number)
			|| (equal->place == shelf->place
				&& equal->number == shelf->number
				&& equal->zero_at_start < shelf->zero_at_start)) ? 1 : -1;
}

void shelf_to_string(char *s, shelf_t *shelf, int shelf_size) {
	int integer = shelf->number;
	int i = shelf_size;
	s[i] = '\0';
	i--;
	s[0] = shelf->place;
	for (; i >= 1; i--) {
		if (integer>0) {
			s[i] = (char)(integer % 10 + 48);
			integer = integer / 10;
		}
		else {
			s[i] = (char)48;
		}
	}
}

void free_shelf(shelf_t **shelf) {
	free(*shelf);
	*shelf = NULL;
}

void free_shelf_list(list_t *shelfs) {
	int i = 0, size = list_length(shelfs);
	shelf_t *shelf = NULL;
	while (i < size) {
		list_remove(shelfs, 0, &shelf);
		free_shelf(&shelf);
		i++;
	}
	//free(shelfs);
}

int print_shelfs(list_t *shelfs) {
	int i = 0, shelf_size, l = list_length(shelfs);
	shelf_t *shelf = NULL;
	char *string = NULL;
	char SPACE[] = "  ";
	printf("\n%s %-8s%-10s%s\n", SPACE, "INDEX", "SHELF", "AMOUNT");
	for (; i<l; i++) {
		shelf = (shelf_t *)list_get(shelfs, i);
		shelf_size = 1 + shelf->zero_at_start + get_int_size(shelf->number);
		new_string(&string, shelf_size);
		shelf_to_string(string, shelf, shelf_size);
		printf("%s  %-8d%-10s%d\n", SPACE, (i + 1), string, shelf->amount);
		free(string);
		string = NULL;
		shelf = NULL;
	}
	printf("\n");

	//printf(NEWLINE);
	return i;
}

int show_goods(content_t *content, int shelf_index) {
	shelf_t *shelf = NULL;
	char *shelf_string = NULL;
	int i = 0, shelf_size;
	char SPACE[] = "  ";

	printf("\n%s %-15s%s\n", SPACE, "NAME", content->name);
	printf("%s %-15s%s\n", SPACE, "DESCRIPTION", content->description);
	printf("%s %-15s%0.2f KR\n", SPACE, "PRICE", ((float)content->price) / 100.00f);
	switch (shelf_index) {
	case -1:
		i = print_shelfs(content->shelfs);
		break;
	case -2:
		break;
	default:
		shelf = (shelf_t *)list_get(content->shelfs, shelf_index);
		shelf_size = 1 + shelf->zero_at_start + get_int_size(shelf->number);
		new_string(&shelf_string, shelf_size);
		shelf_to_string(shelf_string, shelf, shelf_size);
		printf("%s %-15s%s\n", SPACE, "SHELF", shelf_string);
		free(shelf_string);
		shelf_string = NULL;
		printf("%s %-15s%d\n\n", SPACE, "AMOUNT", shelf->amount);
		shelf = NULL;
		i++;
		break;
	}
	return i;
}

const char *print_not_equal_string(char *string, char *not_equal) {
	const char *print;
	switch (tree_index_compare(string, not_equal)) {
	case 0:
		print = "[EQUAL]";
		break;
	default:
		print = not_equal;
		break;
	}
	return print;
}

void int_to_string(char *string, int integer) {
	int i = get_int_size(integer);
	string[i] = '\0';
	i--;
	for (; i >= 0; i--) {
		string[i] = integer % 10 + 48;
		integer = integer / 10;
	}

}

void copy_string(char *copy, char *string, int copy_size) {
	int i = 0;
	for (; i<copy_size && string[i] != '\0'; i++) {
		copy[i] = string[i];
	}
	copy[i] = '\0';
}

void clone_content(content_t *clone, content_t *content) {
	shelf_t *shelf_c = NULL, *shelf_i = NULL;
	int i = 0, l = content->shelfs ? list_length(content->shelfs) : 0;
	copy_string(clone->name, content->name, NAME_LENGTH);
	copy_string(clone->description, content->description, DESC_LENGTH);
	clone->price = content->price;
	while (i < l) {
		shelf_c = list_get(clone->shelfs, i);
		shelf_i = list_get(content->shelfs, i);
		shelf_c->place = shelf_i->place;
		shelf_c->number = shelf_i->number;
		shelf_c->zero_at_start = shelf_i->zero_at_start;
		shelf_c->amount = shelf_i->amount;
		shelf_c = NULL;
		shelf_i = NULL;
		i++;
	}
}

void print_side_by_side(content_t *first, content_t *second, const char *first_h, const char *second_h) {
	shelf_t *first_s, *second_s;
	int size_1, size_2;
	char *not_equal = NULL, *also_not_equal = NULL;
	int i = 0, j = 0, li = list_length(first->shelfs), lj = list_length(second->shelfs);
	char SPACE[] = "  ";

	printf("\n%s %-15s%-15s%s\n", SPACE, " ", first_h, second_h);

	printf("%s %-15s%-15s%s\n", SPACE, "NAME", first->name, print_not_equal_string(first->name, second->name));

	if (first->price != second->price) {
		printf("%s %-15s%-15.2f%0.2f", SPACE, "PRICE", ((float)first->price) / 100.0f, ((float)second->price) / 100.0f);
	}
	else {
		printf("%s %-15s%-15.2f%s", SPACE, "PRICE", ((float)first->price) / 100.0f, "[EQUAL]");
	}

	printf("\n%s ---------------------------------------\n", SPACE);

	printf("%s DESC. %-9s%s\n", SPACE, first_h, first->description);
	printf("%s DESC. %-9s%s", SPACE, second_h, print_not_equal_string(first->description, second->description));

	printf("\n%s ---------------------------------------\n", SPACE);

	printf("%s %-15s%-15s%s\n", SPACE, " ", first_h, second_h);

	for (; i >= 0 || j >= 0; i = ((i >= 0 && i + 1 < li) ? i + 1 : -1), j = ((j >= 0 && j + 1 < lj) ? j + 1 : -1)) {
		first_s = (i<0) ? NULL : (shelf_t *)list_get(first->shelfs, i);
		second_s = (j<0) ? NULL : (shelf_t *)list_get(second->shelfs, j);
		if (i > 0 || j > 0) {
			printf("\n%s ----------\n", SPACE);
		}
		if (first_s != NULL) {

			size_1 = 1 + first_s->zero_at_start + get_int_size(first_s->number);
			new_string(&not_equal, size_1);
			shelf_to_string(not_equal, first_s, size_1);
			if (second_s != NULL) {
				if (shelf_equal(first_s, second_s) != 0) {
					size_2 = 1 + second_s->zero_at_start + get_int_size(second_s->number);
					new_string(&also_not_equal, size_2);
					shelf_to_string(also_not_equal, second_s, size_2);
				}
				else {
					also_not_equal = "[EQUAL]";
				}
			}
			else {
				also_not_equal = " ";
			}

		}
		else {

			not_equal = " ";
			if (second_s != NULL) {
				size_2 = 1 + second_s->zero_at_start + get_int_size(second_s->number);
				new_string(&also_not_equal, size_2);
				shelf_to_string(also_not_equal, second_s, size_2);
			}
			else {
				also_not_equal = " ";
			}
		}

		printf("%s %-15s%-15s%s\n", SPACE, "SHELF", not_equal, also_not_equal);
		if (first_s != NULL) {
			free(not_equal);
			if (second_s != NULL && shelf_equal(first_s, second_s) != 0) {
				free(also_not_equal);
			}
		}
		else if (second_s != NULL) {
			free(also_not_equal);
		}
		not_equal = NULL;
		also_not_equal = NULL;
		if (first_s != NULL) {
			new_string(&not_equal, get_int_size(first_s->amount));
			int_to_string(not_equal, first_s->amount);
			if (second_s != NULL) {
				if (first_s->amount != second_s->amount) {
					new_string(&also_not_equal, get_int_size(second_s->amount));
					int_to_string(also_not_equal, second_s->amount);
				}
				else {
					also_not_equal = "[EQUAL]";
				}
			}
			else {
				also_not_equal = " ";
			}
		}
		else {
			not_equal = " ";
			if (second_s != NULL) {
				new_string(&also_not_equal, get_int_size(second_s->amount));
				int_to_string(also_not_equal, second_s->amount);
			}
			else {
				also_not_equal = " ";
			}
		}
		printf("%s %-15s%-15s%s", SPACE, "AMOUNT", not_equal, also_not_equal);
		if (first_s != NULL) {
			free(not_equal);
			if (second_s != NULL && first_s->amount != second_s->amount) {
				free(also_not_equal);
			}
			second_s = NULL;
			first_s = NULL;
		}
		else if (second_s != NULL) {
			free(also_not_equal);
			second_s = NULL;
		}
		not_equal = NULL;
		also_not_equal = NULL;
	}

	printf("\n\n");
}


void copy_shelf_list(list_t *copy, list_t *list) {
	shelf_t *shelf = NULL;
	int i = 0, l = list_length(list);

	while (i < l) {
		new_shelf(&shelf);
		copy_shelf(shelf, (shelf_t *)list_get(list, i));
		list_insert(copy, i, shelf);
		shelf = NULL;
		i++;
	}
}

void copy_content(content_t *copy, content_t *content) {
	copy_string(copy->name, content->name, NAME_LENGTH);
	copy_string(copy->description, content->description, DESC_LENGTH);
	copy_shelf_list(copy->shelfs, content->shelfs);
	copy->price = content->price;
}

void show_content_shelf(content_t *content, shelf_t *shelf) {
	int shelf_size;
	char *shelf_string = NULL;
	char SPACE[] = "  ";
	show_goods(content, -2);

	shelf_size = 1 + shelf->zero_at_start + get_int_size(shelf->number);
	new_string(&shelf_string, shelf_size);
	shelf_to_string(shelf_string, shelf, shelf_size);

	printf("%s %-15s%s\n", SPACE, "SHELF", shelf_string);
	free(shelf_string);
	shelf_string = NULL;
	printf("%s %-15s%d\n\n", SPACE, "AMOUNT", shelf->amount);
}

void free_content_shelfs(content_t *content) {
	if (content) {
		if (content->shelfs) {
			free_shelf_list(content->shelfs);
			free(content->shelfs);
			content->shelfs = NULL;
		}
		//free(content);
	}
}

void free_string(char **string, int size) {
	if (*string) {
		prepare_for_free_string(*string, size);
		free(*string);
		*string = NULL;
	}
}

void free_content(content_t **content) {
	if (*content) {
		free_content_shelfs(*content);
		free(*content);
		*content = NULL;
	}
}

void free_content_tree(tree_t **contents) {
	if (*contents) {
		content_t *content = NULL;
		while (tree_size(*contents)) {
			tree_remove(*contents, 0, &content);
			free_content(&content);
			content = NULL;
		}
		free(*contents);
		*contents = NULL;
	}
}

list_t *get_content_shelfs(content_t *content) {
	return content->shelfs;
}

void set_content_shelfs(content_t *content, list_t *shelfs) {
	if(content->shelfs){
		free_shelf_list(content->shelfs);
	}
	content->shelfs = shelfs;
}

void set_shelf(shelf_t *shelf, char place, int number, int zero_at_start, int amount) {
	shelf->place = place;
	shelf->number = number;
	shelf->zero_at_start = zero_at_start;
	shelf->amount = amount;
}

void set_shelf_place(shelf_t *shelf, char place) {
	shelf->place = place;
}

void set_shelf_number(shelf_t *shelf, int number) {
	shelf->number = number;
}

void set_shelf_zero_at_start(shelf_t *shelf, int zero_at_start) {
	shelf->zero_at_start = zero_at_start;
}

int get_shelf_zero_at_start(shelf_t *shelf) {
	return shelf->zero_at_start;
}

int get_shelf_amount(shelf_t *shelf) {
	return shelf->amount;
}

char get_shelf_place(shelf_t *shelf) {
	return shelf->place;
}

int get_shelf_number(shelf_t *shelf) {
	return shelf->number;
}

void set_shelf_amount(shelf_t *shelf, int amount) {
	shelf->amount = amount;
}

char *get_content_name(content_t *content) {
	return content->name;
}

char *get_content_description(content_t *content) {
	return content->description;
}

int get_content_price(content_t *content) {
	return content->price;
}

void set_content_price(content_t *content, int price) {
	content->price = price;
}

int get_shelf_index(list_t *shelfs, shelf_t *shelf) {
	char *shelf_str = NULL, *compare_str = NULL;
	shelf_t *shelf_compare;
	int li = list_length(shelfs), i = (li != 0) ? 0 : -1, ci = 1, s1 = 1 + get_shelf_zero_at_start(shelf) + get_int_size(get_shelf_number(shelf)), s2;
	new_string(&shelf_str, s1);
	shelf_to_string(shelf_str, shelf, s1);
	while (i >= 0 && ci != 0) {
		shelf_compare = (shelf_t *)list_get(shelfs, i);
		s2 = 1 + get_shelf_zero_at_start(shelf_compare) + get_int_size(get_shelf_number(shelf_compare));
		new_string(&compare_str, s2);
		shelf_to_string(compare_str, shelf_compare, s2);
		ci = tree_index_compare(compare_str, shelf_str);
		free(compare_str);
		compare_str = NULL;
		i = (i + 1<li && ci != 0) ? i + 1 : (ci == 0) ? i : -1;
	}
	shelf_compare = NULL;
	free(shelf_str);
	shelf_str = NULL;
	return i;
}