#include "Structures.h"
#include "Add.h"

typedef struct {
	char place;
	int number;
	int zero_at_start;
	int amount;
} test_shelf;

typedef struct {
	int length_of_array;
	test_shelf *s_array;
} shelf_array;

typedef struct {
	char *name;
	char *description;
	int price;
	shelf_array shelfs;
} test_content;

test_shelf laptop_shelfs[2] = {
	{ 'F', 45, 1, 30 },
	{ 'D', 874, 0, 4000 } };

test_shelf gurka_shelfs[2] = {
	{ 'G', 834, 0, 1000 },
	{ 'R', 475, 0, 400 } };

test_shelf tomat_shelfs[3] = {
	{ 'A', 4, 2, 1500 },
	{ 'H', 713, 0, 3000 },
	{ 'Y', 83, 1, 2250 } };

test_shelf helikopter_shelfs[2] = {
	{ 'D', 333, 0, 3450 },
	{ 'F', 74, 1, 1550 } };

test_shelf bord_shelfs[1] = {
	{ 'G', 555, 0, 40 } };

test_shelf stol_shelfs[2] = {
	{ 'F', 334, 0, 120 },
	{ 'K', 2, 2, 880 } };

test_shelf musmatta_shelfs[2] = {
	{ 'F', 46, 1, 930 },
	{ 'D', 875, 0, 170 } };

test_shelf hushallspapper_shelfs[2] = {
	{ 'D', 4, 2, 200 },
	{ 'K', 1, 2, 450 } };

test_shelf boll_shelfs[2] = {
	{ 'A', 5, 2, 500 },
	{ 'A', 6, 2, 400 } };

test_shelf gammaldagsbrod_shelfs[3] = {
	{ 'L', 85, 1, 10},
	{ 'Z', 86, 1, 50},
	{ 'B', 87, 1, 100} };

test_shelf kaffe_shelfs[2] = {
	{ 'C', 655, 0, 400 },
	{ 'C', 656, 0, 300 } };

test_shelf bil_shelfs[2] = {
	{ 'V', 433, 0, 100 },
	{ 'B', 45, 1, 20 } };

test_shelf ingefara_shelfs[2] = {
	{ 'G', 999, 0, 200 },
	{ 'D', 9, 2, 300 } };

test_shelf tidning_shelfs[2] = {
	{ 'R', 39, 1, 300 },
	{ 'V', 88, 1, 100 } };

test_shelf fikus_shelfs[2] = {
	{ 'T', 8, 2, 400 },
	{ 'S', 1, 2, 30 } };

test_shelf flyttkartonger_shelfs[2] = {
	{ 'E', 3, 2, 200 },
	{ 'A', 999, 0, 6000 } };

test_shelf slang_shelfs[2] = {
	{ 'L', 56, 1, 500 },
	{ 'K', 45, 1, 500 } };

test_shelf sopsack_shelfs[2] = {
	{ 'H', 44, 1, 400 },
	{ 'V', 999, 0, 700 } };

test_shelf windows_shelfs[2] = {
	{ 'J', 123, 0, 567 },
	{ 'J', 124, 0, 765 } };

test_shelf fonsterputs_shelfs[2] = {
	{ 'O', 5, 2, 345 },
	{ 'O', 6, 2, 543 } };

test_shelf is_shelfs[2] = {
	{ 'P', 1, 2, 333 },
	{ 'P', 2, 2, 444 } };

test_shelf miniugn_shelfs[2] = {
	{ 'I', 3, 2, 666 },
	{ 'I', 4, 2, 999 } };

test_shelf potatis_shelfs[2] = {
	{ 'H', 444, 0, 928 },
	{ 'H', 445, 0, 732 } };

test_shelf vodka_shelfs[2] = {
	{ 'S', 3, 2, 333 },
	{ 'S', 4, 2, 444 } };

test_shelf vatten_shelfs[2] = {
	{ 'M', 1, 2, 987 },
	{ 'M', 2, 2, 789 } };

test_shelf grus_shelfs[2] = {
	{ 'L', 44, 1, 765 },
	{ 'L', 43, 1, 567 } };

test_shelf glassstrytars_shelfs[2] = {
	{ 'W', 877, 0, 3544 },
	{ 'W', 876, 0, 8873 } };

test_shelf fralle_shelfs[2] = {
	{ 'Q', 222, 0, 993 },
	{ 'Q', 223, 0, 883 } };

test_shelf smorcroissan_shelfs[2] = {
	{ 'Y', 888, 0, 999 },
	{ 'Y', 887, 0, 988 } };

test_shelf handskarm_shelfs[2] = {
	{ 'X', 777, 0, 3000 },
	{ 'X', 775, 0, 4000 } };

const int array_length = 30;

test_content test_goods[30] = {
	{ "Laptop", "Elektronik", 3999000,{ 2, laptop_shelfs } },
	{ "Gurka", "Gronsaker", 1300,{ 2, gurka_shelfs } },
	{ "Tomat", "Gronsaker", 290,{ 3, tomat_shelfs } },
	{ "Helikopter", "Leksak", 50000,{ 2, helikopter_shelfs } },
	{ "Bord", "Tra", 49990,{ 1, bord_shelfs } },
	{ "Stol", "Metall", 29990,{ 2, stol_shelfs } },
	{ "Musmatta", "Elektronik", 79990,{ 2, musmatta_shelfs } },
	{ "Hushallspapper", "Mjuk och sjon", 2990,{ 2, hushallspapper_shelfs } },
	{ "Boll", "Har minst ett hål", 990,{ 2, boll_shelfs } },
	{ "Gammaldagsbrod", "Fettgammal", 590,{ 3, gammaldagsbrod_shelfs } },
	{ "Kaffe", "Stark", 5990,{ 2, kaffe_shelfs } },
	{ "Bil", "Utan motor", 399990,{ 2, bil_shelfs } },
	{ "Ingefara", "Rutten", 500,{ 2, ingefara_shelfs } },
	{ "Tidning", "Gammal", 2000,{ 2, tidning_shelfs } },
	{ "Fikus", "Blomma", 5990,{ 2, fikus_shelfs } },
	{ "Flyttkartonger", "Stora o jobbiga att bara", 1990,{ 2, flyttkartonger_shelfs } },
	{ "Slang", "5 meter lång, 2 cm i diameter", 5990,{ 2, slang_shelfs } },
	{ "Sopsack", "5 liters", 2000,{ 2, sopsack_shelfs } },
	{ "Windows 10 Pro", "OS CD-skiva, licens for 12 manader", 50000,{ 2, windows_shelfs } },
	{ "Fonsterputs", "For alla glasytor", 3990,{ 2, fonsterputs_shelfs } },
	{ "Is", "Kall som om den var fran frysen", 2000,{ 2, is_shelfs } },
	{ "Mini-Ugn", "40 liter", 300000,{ 2, miniugn_shelfs } },
	{ "Potatis", "Fast", 90,{ 2, potatis_shelfs } },
	{ "Vodka", "Rysk", 40000,{ 2, vodka_shelfs } },
	{ "Vatten", "Kall kranvatten", 2000,{ 2, vatten_shelfs } },
	{ "Grus", "Bast for att halla i skorna", 4000,{ 2, grus_shelfs } },
	{ "Glass strytar S", "Stora", 2000,{ 2, glassstrytars_shelfs } },
	{ "Fralle", "Alltid dagens", 190,{ 2, fralle_shelfs } },
	{ "Smorcroissan", "Alltid dagens", 790,{ 2, smorcroissan_shelfs } },
	{ "Handskar M", "Medium storlek", 5000,{ 2, handskarm_shelfs } }
}; // { "", "", ,{ , _shelfs } },

void insert_test_goods(tree_t *goods_db, list_t *last_action) {
	list_t *shelfs = NULL;
	content_t *new_item = NULL;
	shelf_t *shelf = NULL;
	int i = 0, j;
	//new_shelf(&shelf);
	for (; i<array_length; i++) {

		new_content(&new_item);
		list_new(&shelfs);
		set_content_shelfs(new_item, shelfs);

		//}
		copy_string(get_content_name(new_item), test_goods[i].name, NAME_LENGTH);
		copy_string(get_content_description(new_item), test_goods[i].description, DESC_LENGTH);
		set_content_price(new_item, test_goods[i].price);

		//copy_shelf(shelf, &(shelfs[i]));
		for (j = 0; j < (test_goods[i].shelfs).length_of_array; j++) {
			new_shelf(&shelf);
			test_shelf *tshelf = &(test_goods[i].shelfs.s_array[j]);
			set_shelf(shelf, tshelf->place, tshelf->number, tshelf->zero_at_start, tshelf->amount);
			add_item(goods_db, new_item, shelf, last_action);
			shelf = NULL;
		}


		if (!get_content_shelfs(new_item)) {
			free(new_item);
		}
		new_item = NULL;
		shelfs = NULL;
	}
	//return goods_db;
}