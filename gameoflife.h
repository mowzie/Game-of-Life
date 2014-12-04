#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

//----------------------------------------------------------------------------
// File:      gameoflife.h
//----------------------------------------------------------------------------

#define ROWS              24
#define COLS              79
#define	KEY_ESC           27
#define	ARROW_UP          72
#define	ARROW_DOWN        80
#define	ARROW_LEFT        75
#define	ARROW_RIGHT       77
#define TRUE               1
#define FALSE              0
#define EXIT_APPLICATION  -1  //internal define for if user wants to exit

#pragma warning(disable: 4996)

const char* dirprefix;   // Make globally accessible to other .c files

#endif
