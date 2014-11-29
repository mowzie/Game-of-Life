#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "datfile.h"
#include "applyRules.h"

#define ROWS 24
#define COLS 79
#define	KEY_ESC 27

int main(void) {
	char gridA[ROWS][COLS];
	char gridB[ROWS][COLS];
	char (*gridPtrCurr)[COLS] = NULL;
	char (*gridPtrNext)[COLS] = NULL;
	char (*tmpPtr)[COLS] = NULL;
	char ch;
	char* datfile = "datfile-gosper-glider-gun.txt";
	
	//createDatFile("datfile-custom.txt");
	//createRandDatFile("datfile.txt");
	
	readDatFile(datfile, gridA, ROWS);
	gridPtrCurr = gridA;
	gridPtrNext = gridB;

	do {
		system("cls");
		printGrid(gridPtrCurr, ROWS);
		setEqualTo(gridPtrCurr, gridPtrNext, ROWS);
		applyRules(gridPtrCurr, gridPtrNext, ROWS);
		
		// swap pointers
		tmpPtr = gridPtrCurr;
		gridPtrCurr = gridPtrNext;
		gridPtrNext = tmpPtr;

		ch = getch();
	} while(ch != KEY_ESC);

	return EXIT_SUCCESS;
}