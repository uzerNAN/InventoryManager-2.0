/**
* @file InputReader.h
* @author Sergej Maleev
* @date 18 Nov 2016
* @brief A system to read user input data and commands (based on extended enum COMMAND). Provides textbased user interface.
*
*
*/
#pragma once

#ifndef __InputReader_h__
#define __InputReader_h__

#include "Structures.h"
#include "Enums.h"

/// Read user input, identify the command and/or handle wrong inputs
/// \param what a value in range of enum READ, each value identifies different menu and accept corresponding user commands for each menu
/// \param first_char a pointer to first char in the user input command, is used in case developer want to read the first input character before calling the read_command function, otherwise pass NULL pointer if this feature is not needed
/// \returns identified user command in range of enum COMMAND, that also corresponds to chosen menu
DO read_command(READ what, char *first_char);

/// Print the question, read user input, identify the command and handle wrong inputs
/// \param question the question string to print out so the user can answer it by only using YES or NO commands
/// \returns YES or NO user command
DO yes_no_question(char *question);

/// Read user input to fill shelf values with corresponding data and handle wrong inputs
/// \param shelf a pointer to allocated shelf
void read_shelf(shelf_t *shelf);

/// Read user input to identify the input number and/or handle wrong values
/// \param what decides what to do different when wrong user input appear (cases PRICE, AMOUNT, PACK, EDIT and LIST; other values make no difference)
/// \param start_number if the value is greater than or equals to zero, the integer will be used as start of the input integer, otherwise pass -1 if this feature is not needed
/// \returns readed integer, in cases with EDIT and LIST it can return -1 if the user input were wrong
int read_integer(DO what, int start_number);

/// Read user input string and handle wrong input values, such as too long input string or if user hasn't typed anything before pressing ENTER
/// \param input pointer to allocated string place
/// \param what decides which message to print out in case the input is wrong, for now implemented only NAME and DESCRIPTION messages
/// \param size the size of the string excluding the end char '\0'
void read_string(char *input, DO what, int size);

#endif