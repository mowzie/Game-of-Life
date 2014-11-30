#include <conio.h>		//getch && kbhit
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>	//for setting window sizes and moving to console locations
#include "datfile.h"
#include "applyRules.h"
#include "dirent.h"		//for listing directory contents
#include "globals.h"

void loadFile(char* datfile);
int displayFiles(void);
void displayMenu(void);
int displayRunningMenu(void);
int printGrid(const char gridCurr[][COLS], const char gridNext[][COLS]);

int main(void) {
	char datfile[FILENAME_MAX];			//starting world filename
	char gridA[ROWS][COLS];				//create two arrays for the current and next state
	char gridB[ROWS][COLS];
	char (*gridPtrCurr)[COLS] = NULL;	//pointer to the currently displayed array
	char (*gridPtrNext)[COLS] = NULL;	//pointer to the next array to be used
	char (*tmpPtr)[COLS] = NULL;		//temporary pointer used for pointer swap
	char ch = ' ';						//getch holder when running
	int quit = 0;						//"bool" to show start screen
	int count = 0;						//generation counter
	int i = 0;
	int j = 0;

	////Windows.h call:  set the window size when it loads so we can see everything
	SMALL_RECT windowSize = {0 , 0 , COLS , ROWS + 3};
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

	for (i = 0; i < ROWS; i++) {
		for(j = 0; j < COLS; j++) {
			gridA[i][j] = ' ';
			gridB[i][j] = ' ';
		}
	}
	strcpy(datfile, ".\\worlds\\welcome.dat");
    
	readDatFile(datfile, gridA, ROWS);
	gridPtrCurr = gridA;
	gridPtrNext = gridB;
	printGrid(gridPtrCurr, gridPtrNext);
	puts("");
    
	displayMenu();
	gotoxy(0,0);
    
	_sleep(3500);  //this currently blocks UI, Fix this

	//Should we put the game logic in its own function outside of MAIN?
	//that way we can call it whenever/however we want  (such as restarting, etc)
	while (!quit) {
		if (count == 170) { //When welcome.dat becomes stagnent, start it over
            count = 0;
            readDatFile(datfile, gridA, ROWS);
            printGrid(gridPtrCurr, gridPtrNext);
        }
        printGrid(gridPtrCurr, gridPtrNext);
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

            case 'c': //TODO: Prompt for a name to save as
                system("cls");
                strcpy(datfile, ".\\worlds\\new.dat");
                createDatFile(datfile);
                quit = 1;
                break;

            case 'l':
				loadFile(datfile);
				quit = 1;
				break;

            case 'r':
            	createRandDatFile("worlds/datfile.dat");
                strcpy(datfile, ".\\worlds\\datfile.dat");
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
		printGrid(gridPtrCurr, gridPtrNext);

		// swap pointers
		tmpPtr = gridPtrCurr;
		gridPtrCurr = gridPtrNext;
		gridPtrNext = tmpPtr;

		ch = getch();
	} while(ch != KEY_ESC);

	return EXIT_SUCCESS;
}

void loadFile(char* datfile) {
	char filename[FILENAME_MAX];

	system("cls");
	printf("Please choose a file\n");
	displayFiles();

	fgets(filename, FILENAME_MAX, stdin);
	/* remove the newline from the filename and terminate string */
	if (filename[strlen(filename) - 1] == '\n')
		filename[strlen(filename) - 1] = '\0';
	else
		while (getchar() != '\n')
			;
	strcpy(datfile, ".\\worlds\\");
	strcat(datfile, filename);
}

int displayFiles(void) {
    DIR* d;
    struct dirent* dir;

    d = opendir("./worlds/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".dat"))
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        printf("Could not open the directory");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void displayMenu(void) {
    int i = 0;

    gotoxy(0, ROWS);
    for(i = 0; i < COLS; i++)
        printf("-");
    gotoxy(0, ROWS + 1);
    printf("(Q)uit\t(L)oad World\t(C)reate World\t(R)andomize a world");
}

int displayRunningMenu(void) {
    int count = 0;

    gotoxy(0, ROWS + 1);
    printf("(ESC) to quit");
    for (count = 0; count < COLS; count++) {
        printf(" ");
    }
    printf("\nAny other key to advance generations");

    return 1;
}

int printGrid(const char gridCurr[][COLS], const char gridNext[][COLS]) {
	int i = 0, j = 0;
	char ch = ' ';

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			gotoxy(j, i);	//(x) columns, (y)row
			printf("%c", gridCurr[i][j]);
		}
	}
	gotoxy(COLS, ROWS);

	return EXIT_SUCCESS;
}
