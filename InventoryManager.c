#include "GoodsManager.h"
#include "TestGoods.h"

int main(){
	DO what;
	tree_t *goods_db = NULL;
	list_t *last_action;
	list_new(&last_action);
	tree_new(&goods_db);
	insert_test_goods( goods_db , last_action );

	char SPACE[] = "  ";

	printf("\n%s  _______________________________________", SPACE);
	printf("\n%s / Welcome to the inventory manager 2.0 /", SPACE);
	printf("\n%s ---------------------------------------\n", SPACE);

	do
	{
					show_main_menu ( goods_db , last_action );
		what =		read_command ( MAIN_MENU, NULL );
					manage_goods ( what , goods_db , last_action );

	} while ( what != QUIT );

	free_action_list(&last_action);
	free_content_tree(&goods_db);

	return 0;
}