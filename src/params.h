/**
 * @file params.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

#ifndef SRC_PARAMS_H_
#define SRC_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <ctime>
#include <iostream>

/*******************************************************************************
 * Macros
 ******************************************************************************/
/*
 * @file. Constructors for classes should use reasonable default values as
 * defined here. An exception might be if the value is 0.
 * This will also include all of common value within classes
 */

// Voting_System
#define RAND_A_NUM_LESS_THAN 13

// graphics
#define X_DIM 1024
#define Y_DIM 768
#define TEXT_BOX_WIDTH 50
#define GUI_MENU_WIDTH 180
#define GUI_MENU_GAP 10

// GUI dimension
#define MENU_X_POS 10
#define MENU_Y_POS 10
#define STATUS_X_POS 230
#define STATUS_Y_POS 10
#define SCREEN_SIZE_X 1300
#define SCREEN_SIZE_Y 400
#define TEXTBOX_SIZE_X 768
#define TEXTBOX_SIZE_Y 30
#define DEFAULT_BUTTON_SIZE 120

// GUI TEXTBOX MESSAGE
#define DEFAULT_OPEN_FILE_STATUS "Please open a voting file (.csv)!"
#define ERROR_OPEN_FILE_STATUS "Please select <.csv> file!"
#define DEFAULT_SAVE_FILE_STATUS "Please select a directory!"
#define DEFAULT_AUDIT_FILE_STATUS "System sleeping..."
#define INPUT_ERROR_AUDIT_FILE_STATUS "INPUT ERROR!!!"
#define SUCCESS_AUDIT_FILE_STATUS "AUDIT SUCCESS! See Result at Terminal Screen"

// File Format
#define TXT ".txt"
#define CSV ".csv"

// Default filename
#define INPUT_FILE_NAME ""
#define AUDIT_FILE_NAME "audit_result.txt"
#define SHARING_FILE_NAME "sharing_result.txt"

// Other
#define A_SMALL_RAND_NUM 13
#define MAXIMUM_FILE_NAME_SIZE 1024
#define MAX_CAND_NAME_WIDTH 20
#endif  // SRC_PARAMS_H_
