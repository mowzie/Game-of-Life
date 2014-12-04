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

int runLoadScreen(char* datfile, char gridPtrCurr[][COLS], char gridPtrNext[][COLS], char tmpPtr[][COLS]) {
    char ch = 0;
    int quitLoadScreen = FALSE;         //"bool" to show start screen
    int count = 0;

    displayMenu();

    strcpy(datfile, dirprefix);         //Load in the Splash Screen
    strcat(datfile, welcomeFile);
    readDatFile(datfile, gridPtrCurr, ROWS);
    printGrid(gridPtrCurr);
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

    system("cls");

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
    puts("\nPress Spacebar to toggle autorun");
    puts("Press any other key to manually advance generations");
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