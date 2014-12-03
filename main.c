#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "datfile.h"
#include "applyRules.h"
#include "gameoflife.h"
#include "menu.h"

int main(void) {
    char datfile[FILENAME_MAX];         //starting world filename
    char gridA[ROWS][COLS] = {{0}};     //create two arrays for the current and next state
    char gridB[ROWS][COLS] = {{0}};
    char (*gridPtrCurr)[COLS] = gridA;  //pointer to the currently displayed array
    char (*gridPtrNext)[COLS] = gridB;  //pointer to the next array to be used
    char (*tmpPtr)[COLS] = NULL;        //temporary pointer used for pointer swap
    char ch = 0;                        //getch holder when running
    int quit = 0;
    int count = 0;                      //generation counter
    int i = 0;                          //loop vars
    int j = 0;

    //windows.h call: set the window size when it loads so we can see everything
    SMALL_RECT windowSize = {0 , 0 , COLS , ROWS + 3};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    while (TRUE) {
        if (runLoadScreen(datfile, gridPtrCurr, gridPtrNext, tmpPtr) == EXIT_APPLICATION)
            return EXIT_SUCCESS;

        readDatFile(datfile, gridA, ROWS); //reset game info
        gridPtrCurr = gridA;               //
        gridPtrNext = gridB;               //
        count = 0;                         //
        displayRunningMenu();

        do {
            gotoxy(COLS - 9, ROWS + 1);
            printf("Gen: %4d", count++);

            applyRule(gridPtrCurr, gridPtrNext);
            printGrid(gridPtrCurr);

            // swap pointers
            tmpPtr = gridPtrCurr;
            gridPtrCurr = gridPtrNext;
            gridPtrNext = tmpPtr;

            ch = getch();
        } while(ch != KEY_ESC);
    }

    return EXIT_SUCCESS;
}