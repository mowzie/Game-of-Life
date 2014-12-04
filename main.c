//----------------------------------------------------------------------------
// File:        main.c
//
// Functions:
//              main()
//----------------------------------------------------------------------------

#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "datfile.h"
#include "applyRules.h"
#include "gameoflife.h"
#include "menu.h"

//----------------------------------------------------------------------------
// Function:   main(void)
//
// Title:      Play the Game of Life
//
// Description:
//             Sets up variables and functions to play the Game of Life
//
// Programmer: Ian Littke & Matt Alexander
//
// Date:       12/04/2014
//
// Version:    1.0
//
// Environment:
//             Hardware: Intel x86_64 PC
//             Software: Windows 8.1
//             Compiles under Microsoft Visual Studio 2012
//
// Input:      N/A
//
// Ouput:      N/A
//
// Called By:  N/A
//
// Calls:      runLoadScreen()
//             readDatFile()
//             gotoxy()
//             displayRunningMenu()
//             applyRule()
//             printGrid()
//
// Parameters: N/A
//
// Returns:    int EXIT_SUCCESS
//
// History Log:
//             12/04/2014 IL/MA completed version 1.0
//----------------------------------------------------------------------------
int main(void) {
    char datfile[FILENAME_MAX];         //starting world filename
    char gridA[ROWS][COLS] = {{0}};     //create two arrays for two states
    char gridB[ROWS][COLS] = {{0}};
    char (*gridPtrCurr)[COLS] = gridA;  //pointer to current array
    char (*gridPtrNext)[COLS] = gridB;  //pointer to next array to be used
    char (*tmpPtr)[COLS] = NULL;        //temp pointer used for pointer swap
    char ch = 0;                        //getch holder when running
    unsigned int count = 0;             //generation counter
    int autorun = FALSE;                //start with user input required

    //windows.h call: set the window size when it loads
    SMALL_RECT windowSize = {0 , 0 , COLS , ROWS + 4};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    //Run the game forever
    //or until the user presses "ESC" while on the main menu
    while (TRUE) {
        if (runLoadScreen(datfile, gridPtrCurr, gridPtrNext,
                          tmpPtr) == EXIT_APPLICATION)
            return EXIT_SUCCESS;  //This is the only way out of the game

        readDatFile(datfile, gridA);        //reset game info
        gridPtrCurr = gridA;                //
        gridPtrNext = gridB;                //
        count = 0;                          //
        displayRunningMenu();               //
        autorun = FALSE;                    //

        //Run simulation
        do {
            gotoxy(COLS - 9, ROWS + 1);
            printf("Gen: %4d", count++);

            applyRule(gridPtrCurr, gridPtrNext);
            printGrid(gridPtrCurr);

            //Swap pointers to make the next array state the current state
            tmpPtr = gridPtrCurr;
            gridPtrCurr = gridPtrNext;
            gridPtrNext = tmpPtr;

            //Toggle autorun
            if (!autorun) {
                ch = getch();
                if (ch == ' ') {
                    autorun = !autorun;
                }
            }
            if (kbhit()) {
                ch = getch();
                if (ch == ' ') {
                    autorun = !autorun;
                }
            }
        } while(ch != KEY_ESC); //Exit the simulation back to the menu
    }

    return EXIT_SUCCESS;
}
