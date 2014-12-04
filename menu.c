//----------------------------------------------------------------------------
// File:        menu.c
//
// Functions:
//              runLoadScreen()
//              loadScreenSleep()
//              checkLoadScreenKeyPress()
//              displayMenu()
//              displayRunningMenu()
//              printGrid()
//----------------------------------------------------------------------------

#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "gameoflife.h"
#include "applyRules.h"
#include "datfile.h"
#include "menu.h"

//project wide global variable
extern const char* DIRPREFIX = "worlds\\";
//internal global variables
const char* welcomeFile = "welcome.dat";
const char* randomFile = "random.dat";

//----------------------------------------------------------------------------
// Function:    runLoadScreen()
//
// Title:       Function to run opening simulation as a splash screen
//
// Description:
//              Dual purpose to both initialize game states
//              and display friendly welcome screen
//
//
// Programmer:  Ian Littke
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 8.1
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       "Life" Generation counter to stdout
//
// Called By:   main()
//
// Calls:       readDatFile()
//              printGrid()
//              gotoxy()
//              loadScreenSleep()
//              checkLoadScreenKeyPress()
//              applyRule()
//
// Parameters:  const char* datfile
//              char gridPtrCurr[][COLS]
//              char gridPtrNext[][COLS]
//
// Returns:     int quitLoadScreen
//
// History Log:
//              12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
int runLoadScreen(char* datfile, char gridPtrCurr[][COLS],
                  char gridPtrNext[][COLS], char tmpPtr[][COLS]) {
    char ch = 0;
    int quitLoadScreen = FALSE;     //"bool" to show start screen
    int count = 0;

    strcpy(datfile, DIRPREFIX);     //Load in the Splash Screen
    strcat(datfile, welcomeFile);
    if (readDatFile(datfile, gridPtrCurr) == EXIT_FAILURE) {
        printf("\nCreating new 'welcome.dat' from a randomly generated file\n\n");
        printf("Press any key to continue.");
        getch();
        system("mkdir worlds");
        createRandDatFile(datfile);
        readDatFile(datfile, gridPtrCurr);
    }
    displayMenu();
    printGrid(gridPtrCurr);
    gotoxy(COLS, ROWS);     //hide the curser by the game border
    quitLoadScreen = loadScreenSleep();

    //user wanted to exit the app, so exit cleanly
    if (quitLoadScreen == KEY_ESC) {
        return EXIT_APPLICATION;
    }
    quitLoadScreen = checkLoadScreenKeyPress(datfile, quitLoadScreen);

    while (!quitLoadScreen) {
        if (count == 170) { //When welcomeFile becomes stagnent, start it over
            count = 0;
            gotoxy(COLS - 9, ROWS + 1);
            printf("Gen: %4d", count);
            readDatFile(datfile, gridPtrCurr);
            printGrid(gridPtrCurr);
            quitLoadScreen = loadScreenSleep();
        }

        applyRule(gridPtrCurr, gridPtrNext);
        printGrid(gridPtrCurr);

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

//----------------------------------------------------------------------------
// Function:    loadScreenSleep()
//
// Title:       Function to keep splash screen still
//
// Description:
//              Keeps the splash screen from "evolving" while still
//              accepting a keypress
//
//
// Programmer:  Ian Littke
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 8.1
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       key press to enter into the game
//
// Ouput:       N/A
//
// Called By:   runLoadScreen()
//
// Calls:       N/A
//
// Parameters:  N/A
//
// Returns:     int either exit_success (1) or value of keypress
//
// History Log:
//              12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
int loadScreenSleep() {
    int i = 0;

    //Sleep for 5 seconds before running welcomeFile
    for (i = 0; i < 5000; i++) {
        if (kbhit()) {
            return getch();  //side effect of starting the simulation early
        }
        _sleep(1);
    }

    return EXIT_SUCCESS;
}

//----------------------------------------------------------------------------
// Function:    checkLoadScreenKeyPress()
//
// Title:       Function to evualuate keypress
//
// Description:
//              Evauluates keypress while splashscreen is running
//              Exits loadscreen and starts game if valid keypress
//
//
// Programmer:  Ian Littke
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 8.1
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       N/A
//
// Called By:   runLoadScreen()
//
// Calls:       enterFileName()
//              creatDatFile()
//              createRandDatFile()
//              displayFiles()
//
// Parameters:  char* datfile
//              const char ch
//
// Returns:     int boolQuit
//              either exit_success (1) or value of keypress
//
// History Log:
//              12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
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
        strcpy(datfile, DIRPREFIX);
        strcat(datfile, randomFile);
        createRandDatFile(datfile);
        break;

    default:
        boolQuit = FALSE;   //unsupported keypress
        break;
    }

    return boolQuit;
}

//----------------------------------------------------------------------------
// Function:    displayMenu()
//
// Title:       Displays simple menu below game field
//
// Description:
//              Sets a border below the game field, and shows the simple menu
//
// Programmer:  Ian Littke
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 8.1
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       row of "-"s below valid game field
//              Simple menu for valid keypresses
//
// Called By:   runLoadScreen()
//
// Calls:       gotoxy()
//
// Parameters:  void
//
// Returns:     void
//
// History Log:
//              12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
void displayMenu(void) {
    int i = 0;

    system("cls");

    gotoxy(0, ROWS);
    for (i = 0; i < COLS; i++) {
        printf("-");
    }
    gotoxy(0, ROWS + 1);
    printf("Press (ESC) to exit   (L)oad World   (C)reate World   "
            "(R)andom World");
}

//----------------------------------------------------------------------------
// Function:    displayRunningMenu(void)
//
// Title:       Displays simple menu below game field
//
// Description:
//              Sets a border below the game field, and shows the simple menu
//
// Programmer:  Ian Littke
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 8.1
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       row of "-"s below valid game field
//              Simple menu for valid keypresses
//
// Called By:   main()
//
// Calls:       gotoxy()
//
// Parameters:  void
//
// Returns:     void
//
// History Log:
//              12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
// Function:    printGrid()
//
// Title:       Prints current status of life
//
// Description:
//              Iterates through each piece of life and displays if its alive
//
// Programmer:  Ian Littke
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 8.1
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       a "*" for each piece of living life in the grid in stdout
//
// Called By:   main()
//              runLoadScreen()
//
// Calls:       gotoxy()
//
// Parameters:  gridCur[][COLS]
//
// Returns:     void
//
// History Log:
//              12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
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
