#ifndef MENU_H
#define MENU_H

void displayMenu(void);


void displayRunningMenu(void);


void printGrid(const char gridCurr[][COLS]);


int checkLoadScreenKeyPress(char* datfile, char const ch);


int loadScreenSleep();


int runLoadScreen(char *datfile, char gridPtrCurr[][COLS], char gridPtrNext[][COLS], char tmpPtr[][COLS]);

#endif