/**
* @file Enums.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief Menu identifiers and expected input commands in two enum arrays
*
*
*/
#pragma once

#ifndef __Enums_h__
#define __Enums_h__

typedef enum COMMAND {
	ADD,
	REMOVE,
	EDIT,
	LIST,
	UNDO,
	QUIT,
	CANCEL,
	NAME,
	DESCRIPTION,
	PRICE,
	SHELF,
	AMOUNT,
	NEXT,
	PREVIOUS,
	SAVE,
	PACK,
	YES,
	NO,
	AGAIN
} DO;
typedef enum {
	INSERTION,
	CHANGES,
	DELETE,
	MAIN_MENU,
	EDIT_MENU,
	EDIT_SHELF,
	LIST_MENU,
	UNDO_ADD,
	UNDO_EDIT,
	UNDO_REMOVE,
	UNDO_PACK,
	SAVE_EDIT,
	PACK_PALLET,
	ADD_PACK_PALLET,
	CONFIDENCE
} READ;

#endif