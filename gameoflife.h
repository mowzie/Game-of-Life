//----------------------------------------------------------------------------
// File:        gameoflife.h
//----------------------------------------------------------------------------

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#define ROWS              24
#define COLS              79
#define KEY_ESC           27
#define ARROW_UP          72
#define ARROW_DOWN        80
#define ARROW_LEFT        75
#define ARROW_RIGHT       77
#define KEY_PRESS_ESCAPE 224
#define WELCOME_END      170
#define GEN_COUNT_LENGTH   9
#define MENU_HEIGHT        4
#define MAX_FILES     ROWS - MENU_HEIGHT
#define TRUE               1
#define FALSE              0
#define EXIT_APPLICATION  -1    //internal define for if user wants to exit

#pragma warning(disable: 4996)

const char* DIRPREFIX;          // Make globally accessible to other .c files

#endif
