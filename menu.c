#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "gameoflife.h"
#include "applyRules.h"
#include "datfile.h"
#include "menu.h"

extern const char* dirprefix = ".\\worlds\\";
const char* welcomeFile = "welcome.dat";
const char* randomFile = "random.dat";

//----------------------------------------------------------------------------
// Function: runLoadScreen(char* datfile, char gridPtrCurr[][COLS], char gridPtrNext[][COLS], char tmpPtr[][COLS])
//
// Title:    
//
// Description:
//            Dual purpose to both initialize game states
//            and display friendly welcome screen
//
//
// Programmer:    Ian Littke
//
// Date:    12/04/2014
//
// Version: 1.0
//
// Environment:
//            Hardware: Intel x86_64 PC
//            Software: Windows 8.1
//            Compiles under Microsoft Visual Studio 2012
//
// Input:    N/A
//
// Ouput:    N/A
//
// Called By:    main()
//
// Calls:        readDatFile()
//               printGrid()
//               gotoxy()
//               loadScreenSleep()
//               checkLoadScreenKeyPress()
//               applyRule()
//
// Parameters:    const char* datfile
//                char gridPtrCurr[][COLS]
//                char gridPtrNext[][COLS]
//
// Returns:    N/A
//
// History Log:
//            12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
int runLoadScreen(char* datfile, char gridPtrCurr[][COLS], char gridPtrNext[][COLS], char tmpPtr[][COLS]) {
    char ch = 0;
    int quitLoadScreen = FALSE;         //"bool" to show start screen
    int count = 0;

    strcpy(datfile, dirprefix);         //Load in the Splash Screen
    strcat(datfile, welcomeFile);
    readDatFile(datfile, gridPtrCurr, ROWS);
    printGrid(gridPtrCurr);
    displayMenu();
    gotoxy(0, 0);
    quitLoadScreen = loadScreenSleep();

    if (quitLoadScreen == KEY_ESC) {
        return EXIT_APPLICATION;        //user wanted to exit the app, so exit cleanly
    }
    quitLoadScreen = checkLoadScreenKeyPress(datfile, quitLoadScreen);

    while (!quitLoadScreen) {
        if (count == 170) {             //When welcomeFile becomes stagnent, start it over
            count = 0;
            gotoxy(COLS - 9, ROWS + 1);
            printf("Gen: %4d", count);
            readDatFile(datfile, gridPtrCurr, ROWS);
            printGrid(gridPtrCurr);
            quitLoadScreen = loadScreenSleep();
        }

        printGrid(gridPtrCurr);
        applyRule(gridPtrCurr, gridPtrNext);

        // swap array pointers
        tmpPtr = gridPtrCurr;
        gridPtrCurr = gridPtrNext;
        gridPtrNext = tmpPtr;

        gotoxy(COLS - 9, ROWS + 1);
        printf("Gen: %4d", count++);

        if (kbhit()) {
            ch = getch();
            quitLoadScreen = checkLoadScreenKeyPress(datfile, ch);
            if (quitLoadScreen == EXIT_APPLICATION) {
                return EXIT_APPLICATION;
            }
        }
    }

    return quitLoadScreen;
}

int loadScreenSleep() {
    int i = 0;

    for (i = 0; i < 5000; i++) { //Sleep for 5 seconds before running welcomeFile
        if (kbhit()) {
            return getch();
        }
        _sleep(1);
    }

    return EXIT_SUCCESS;
}

int checkLoadScreenKeyPress(char* datfile, const char ch) {
    int boolQuit = TRUE;  //Assume the user is exiting out of the load screen

    switch (tolower(ch)) {
    case KEY_ESC:
        boolQuit = EXIT_APPLICATION;
        break;

    case 'c':
        enterFileName(datfile);
        createDatFile(datfile);
        break;

    case 'l':
        displayFiles(datfile);
        break;

    case 'r':
        strcpy(datfile, dirprefix);
        strcat(datfile, randomFile);
        createRandDatFile(datfile);
        break;

    default:
        boolQuit = FALSE;   //unsupported keypress
        break;
    }

    return boolQuit;
}

void displayMenu(void) {
    int i = 0;

    gotoxy(0, ROWS);
    for (i = 0; i < COLS; i++) {
        printf("-");
    }
    gotoxy(0, ROWS + 1);
    printf("Press (ESC) to exit\t(L)oad World\t(C)reate World\t(R)andom World");
}

void displayRunningMenu(void) {
    int i = 0;

    gotoxy(0, ROWS);
    for (i = 0; i < COLS; i++) {
        printf("-");
    }
    gotoxy(0, ROWS + 1);
    printf("Press (ESC) to exit back to menu");
    for (i = 0; i < COLS; i++) {
        printf(" ");
    }
    printf("\nPress any other key to advance generations");
}

void printGrid(const char gridCurr[][COLS]) {
    int i = 0;
    int j = 0;

    gotoxy(0, 0);
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            (gridCurr[i][j]) ? printf("*") : printf(" ");
        }
        puts("");
    }
    gotoxy(COLS, ROWS);
}