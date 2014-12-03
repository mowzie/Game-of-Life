#include <conio.h>      //getch && kbhit
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>    //for setting window sizes and moving to console locations
#include "datfile.h"
#include "applyRules.h"
#include "dirent.h"     //for listing directory contents
#include "globals.h"
#define EXIT_APPLICATION -1

void enterFileName(char* datfile);
int hasDatExt(const char* filename);
void displayFiles(char* datfile);
void displayMenu(void);
void displayRunningMenu(void);
void printGrid(const char gridCurr[][COLS]);
int checkLoadScreenKeyPress(char* datfile, char const ch);

const char* dirprefix = ".\\worlds\\";

int main(void) {
    char datfile[FILENAME_MAX];         //starting world filename
    char gridA[ROWS][COLS] = {{0}};     //create two arrays for the current and next state
    char gridB[ROWS][COLS] = {{0}};
    char (*gridPtrCurr)[COLS] = NULL;   //pointer to the currently displayed array
    char (*gridPtrNext)[COLS] = NULL;   //pointer to the next array to be used
    char (*tmpPtr)[COLS] = NULL;        //temporary pointer used for pointer swap
    int rule[2][9] = 
	{   //0	 1	2  3  4	 5	6  7  8		//# of Neighbors
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0 },	//Birth Rules
		{ 0, 0, 1, 1, 0, 0, 0, 0, 0 }	//Survival Rules
	};
    char ch = ' ';                      //getch holder when running
    int quit = 0;                       //"bool" to show start screen
    int count = 0;                      //generation counter
    int i = 0;                          //loop vars
    int j = 0;

    //Windows.h call: set the window size when it loads so we can see everything
    SMALL_RECT windowSize = {0 , 0 , COLS , ROWS + 3};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    strcpy(datfile, dirprefix);
    strcat(datfile, "welcome.dat");
    readDatFile(datfile, gridA, ROWS);
    gridPtrCurr = gridA;
    gridPtrNext = gridB;
    printGrid(gridPtrCurr);
    puts("");

    displayMenu();
    gotoxy(0,0);

    _sleep(3500);  // TODO: this currently blocks UI, Fix this

    //Should we put the game logic in its own function outside of MAIN?
    //that way we can call it whenever/however we want  (such as restarting, etc)
    while (!quit) {
        if (count == 170) { //When welcome.dat becomes stagnent, start it over
            count = 0;
            readDatFile(datfile, gridA, ROWS);
            printGrid(gridPtrCurr);
            _sleep(3500);  // TODO: this currently blocks UI, Fix this
        }
        printGrid(gridPtrCurr);
        applyRule(gridPtrCurr, gridPtrNext, rule);

        // swap array pointers
        tmpPtr = gridPtrCurr;
        gridPtrCurr = gridPtrNext;
        gridPtrNext = tmpPtr;

        gotoxy(COLS - 9, ROWS + 1);
        printf("Gen: %4d", count++);

        if (kbhit()) {
            ch = getch();
            quit = checkLoadScreenKeyPress(datfile, ch);
            if (quit == EXIT_APPLICATION) {
                return EXIT_SUCCESS;  //user wanted to exit the app, so exit cleanly
            }
        }
    }

    readDatFile(datfile, gridA, ROWS);
    gridPtrCurr = gridA;
    gridPtrNext = gridB;
    count = 0;
    displayRunningMenu();

    do {
        gotoxy(COLS - 9, ROWS + 1);
        printf("Gen: %4d", count++);

        applyRule(gridPtrCurr, gridPtrNext, rule);
        printGrid(gridPtrCurr);

        // swap pointers
        tmpPtr = gridPtrCurr;
        gridPtrCurr = gridPtrNext;
        gridPtrNext = tmpPtr;

        ch = getch();   // TODO: allow the user to let the simulation run until a key is pressed?
    } while(ch != KEY_ESC);

    return EXIT_SUCCESS;
}

int checkLoadScreenKeyPress(char* datfile, const char ch) {
    int boolQuit = 0;

    switch (tolower(ch)) {
    case 27:    // ESC key
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
        strcat(datfile, "random.dat");
        createRandDatFile(datfile);
        break;
    }

    return boolQuit;
}

void enterFileName(char* datfile) {
    char filename[FILENAME_MAX];

    system("cls");
    printf("Please enter a filename to save as your new dat file.");

    do {
        printf("\nYour filename must end with a '.dat' file extension.\n");
        printf(">>> ");

        fgets(filename, FILENAME_MAX, stdin);
        if (filename[strlen(filename) - 1] == '\n') //remove newline
            filename[strlen(filename) - 1] = '\0';  //terminate string
        else
            while (getchar() != '\n')
                ;
    // Verify that the file ends in .dat and isn't too long for the datfile buffer
    } while (!hasDatExt(filename) && (strlen(filename) < sizeof(datfile)-strlen(dirprefix)));

    strcpy(datfile, dirprefix);
    strcat(datfile, filename);

    puts("");
}

int hasDatExt(const char* filename) {
    size_t len = strlen(filename);
    return len > 4 && strcmp(filename + len - 4, ".dat") == 0;
}

void displayFiles(char* datfile) {
    unsigned int filenum = 0;
    char filename[128][MAX_PATH];   // Array of strings to hold filenames
    DIR* d = NULL;
    struct dirent* dir = NULL;

    system("cls");
    printf("Please choose a file\n");
    printf("--------------------\n\n");

    d = opendir(dirprefix);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".dat")) {
                strcpy(filename[filenum], dir->d_name);
                printf("    %d: %s\n", ++filenum, dir->d_name);
            }
        }
        closedir(d);
        printf("\nEnter the file number and press Enter >>> ");
        while (fscanf(stdin, "%d", &filenum) != 1) {
            while (getchar() != '\n')
                ;
            printf("Enter the file number and press Enter >>> ");
        }
        strcpy(datfile, dirprefix);
        strcat(datfile, filename[filenum - 1]);
    } else {
        fprintf(stderr, "Could not open the directory");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
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
    printf("Press (ESC) to exit");
    for (i = 0; i < COLS; i++) {
        printf(" ");
    }
    printf("\nPress any other key to advance generations");
}

void printGrid(const char gridCurr[][COLS]) {
    int i = 0;
    int j = 0;

    gotoxy(0,0);
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            (gridCurr[i][j]) ? printf("*") : printf(" ");
        }
        puts("");
    }
    gotoxy(COLS, ROWS);
}
