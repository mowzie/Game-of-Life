#include <conio.h>      //getch && kbhit
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>    //for setting window sizes and moving to console locations
#include "datfile.h"
#include "applyRules.h"
#include "dirent.h"     //for listing directory contents
#include "globals.h"

void enterFileName(char* datfile);
int displayFiles(char* datfile);
void displayMenu(void);
void displayRunningMenu(void);
void printGrid(const char gridCurr[][COLS]);

int main(void) {
    char datfile[FILENAME_MAX];         //starting world filename
    char gridA[ROWS][COLS] = {{0}};     //create two arrays for the current and next state
    char gridB[ROWS][COLS] = {{0}};
    char (*gridPtrCurr)[COLS] = NULL;   //pointer to the currently displayed array
    char (*gridPtrNext)[COLS] = NULL;   //pointer to the next array to be used
    char (*tmpPtr)[COLS] = NULL;        //temporary pointer used for pointer swap
    char ch = ' ';                      //getch holder when running
    int quit = 0;                       //"bool" to show start screen
    int count = 0;                      //generation counter
    int i = 0, j = 0;                   //loop vars

    //Windows.h call: set the window size when it loads so we can see everything
    SMALL_RECT windowSize = {0 , 0 , COLS , ROWS + 3};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    strcpy(datfile, ".\\worlds\\welcome.dat");  // TODO: ensure that worlds dir exists
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
        applyRules(gridPtrCurr, gridPtrNext, ROWS);

        // swap array pointers
        tmpPtr = gridPtrCurr;
        gridPtrCurr = gridPtrNext;
        gridPtrNext = tmpPtr;

        gotoxy(COLS - 9, ROWS + 1);
        printf("Gen: %4d", count++);

        if (kbhit()) {
            ch = getch();
            switch (tolower(ch)) {
            case 'q':
                return EXIT_SUCCESS;
                break;

            case 'c':
                system("cls");
                enterFileName(datfile);
                createDatFile(datfile);
                quit = 1;
                break;

            case 'l':
                system("cls");
                displayFiles(datfile);  // TODO: check return value
                quit = 1;
                break;

            case 'r':
                createRandDatFile("worlds/random.dat");
                strcpy(datfile, ".\\worlds\\random.dat");
                quit = 1;
                break;

            default:
                break;
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

        applyRules(gridPtrCurr, gridPtrNext, ROWS);
        printGrid(gridPtrCurr);

        // swap pointers
        tmpPtr = gridPtrCurr;
        gridPtrCurr = gridPtrNext;
        gridPtrNext = tmpPtr;

        ch = getch();   // TODO: allow the user to let the simulation run until a key is pressed?
    } while(ch != KEY_ESC);

    return EXIT_SUCCESS;
}

void enterFileName(char* datfile) {
    char filename[FILENAME_MAX];

    printf("Please enter a filename to save as your new dat file.\n");
    printf("Your filename must end with a '.dat' file extension.\n");
    printf(">>> ");

    fgets(filename, FILENAME_MAX, stdin);   // TODO: ensure that filename ends in .dat
    if (filename[strlen(filename) - 1] == '\n') //remove newline
        filename[strlen(filename) - 1] = '\0';  //terminate string
    else
        while (getchar() != '\n')
            ;
    strcpy(datfile, ".\\worlds\\");
    strcat(datfile, filename);  // TODO: check that we don't overflow datfile length

    puts("");
}

int displayFiles(char* datfile) {
    int filenum = 0;
    char filename[128][MAX_PATH];   // Array of strings to hold filenames
    DIR* d = NULL;
    struct dirent* dir = NULL;

    printf("Please choose a file\n");
    printf("---------------------\n\n");

    d = opendir("./worlds/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".dat")) {
                strcpy(filename[filenum], dir->d_name);
                printf("    %d: %s\n", ++filenum, dir->d_name);
            }
        }
        closedir(d);
        printf("\nEnter the file number and press Enter >>> ");
        fscanf(stdin, "%d", &filenum);  // TODO: Add error checking
        strcpy(datfile, ".\\worlds\\");
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
    printf("(Q)uit\t(L)oad World\t(C)reate World\t(R)andomize a world");
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
    int i, j = 0;

    gotoxy(0,0);
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            (gridCurr[i][j]) ? printf("*") : printf(" ");
        }
        puts("");
    }
    gotoxy(COLS, ROWS);
}
