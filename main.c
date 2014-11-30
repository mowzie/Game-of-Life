#include <conio.h>		//getch && kbhit
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>	//for setting window sizes and moving to console locations
#include "datfile.h"
#include "applyRules.h"
#include "dirent.h"		//for listing directory contents
#include "globals.h"

int displayFiles(void);
void displayMenu(void);
int displayRunningMenu(void);
int printGrid(const char gridCurr[][COLS], const char gridNext[][COLS]);

int main(void) {
	char filename[FILENAME_MAX];		//TODO:  this should go to a seperate function
	char gridA[ROWS][COLS];				//
	char gridB[ROWS][COLS];
	char (*gridPtrCurr)[COLS] = NULL;	//
	char (*gridPtrNext)[COLS] = NULL;	//
	char (*tmpPtr)[COLS] = NULL;		//
	char ch = ' ';						//getch holder when running
	char datfile[FILENAME_MAX];			//starting world
	int quit = 0;						//"bool" to show start screen
	int count = 0;						//generation counter
	int i = 0;
	int j = 0;

    ////Windows.h call:  set the window size when it loads so we can see everything
    SMALL_RECT windowSize = {0 , 0 , COLS , ROWS+3};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    //
	for (i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			gridA[i][j] = ' ';
			gridB[i][j] = ' ';
		}
	}
	strcpy(datfile, ".\\worlds\\welcome.txt");
    
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
	while(!quit)
    {
        if (count == 170)  //When welcome.txt becomes stagnent, start it over
        {
            count = 0;
            readDatFile(datfile, gridA, ROWS);
            printGrid(gridPtrCurr, gridPtrNext);
        }
        printGrid(gridPtrCurr, gridPtrNext);
		
		applyRules(gridPtrCurr, gridPtrNext, ROWS);
		
		// swap pointers
		tmpPtr = gridPtrCurr;
		gridPtrCurr = gridPtrNext;
		gridPtrNext = tmpPtr;
        gotoxy(COLS-9,ROWS+1);
        printf("Gen: %4d", count++);
        if (kbhit())
        {
            ch = getch();
            switch (ch)
            {
            case 'Q':
            case 'q':
                return EXIT_SUCCESS;
                break;
            case 'C':
            case 'c': //TODO: Prompt for a name to save as
                system("cls");
                strcpy(datfile, ".\\worlds\\new.txt");
                createDatFile(datfile);
                quit = 1;
                break;
            case 'L':
            case 'l':  //TODO:  Put this in a function Call
                    system("cls");
                    printf("Please choose a file\n");
                    displayFiles();

                   fgets(filename, FILENAME_MAX, stdin);
                   /* remove the newline from the filename and terminate string */
                   if(filename[strlen(filename) - 1] == '\n')
                     filename[strlen(filename) -1] = '\0';
                   else
                      while(getchar() != '\n')
                        ;
                   strcpy(datfile, ".\\worlds\\");
                   strcat(datfile, filename);
             //      strncat(datfile,filename);
            //    datfile = ".\\world\\" + filename;
                //strcat(datfile, filename);
                quit = 1;
                break;
            case 'R':
            case 'r':
            	createRandDatFile("worlds/datfile.txt");
                strcpy(datfile, ".\\worlds\\datfile.txt");
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
        gotoxy(COLS-9,ROWS+1);
        printf("Gen: %4d", count++);
        //setEqualTo(gridPtrCurr, gridPtrNext, ROWS);
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

int displayFiles(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir("./worlds/");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if ((strstr(dir->d_name,".txt")) || (strstr(dir->d_name,".dat")))
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    else
    {
        printf("Could not open the directory");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void displayMenu(void)
{
    int i = 0;
    gotoxy(0, ROWS);
    for(i = 0; i < COLS;i++)
        printf("-");
    gotoxy(0, ROWS+1);
    printf("(Q)uit\t(L)oad World\t(C)reate World\t(R)andomize a world");
}

int displayRunningMenu(void)
{
    int count = 0;
    gotoxy(0, ROWS+1);
    count = printf("(ESC) to quit");
    for (count; count < COLS; count++)
    {
        printf(" ");
    }
    printf("\nAny other key to advance generations");
    //printf("(ESC) to quit\t(L)oad World\t(C)reate World\t(R)estart World\nAny other key to advance generations");
    return 1;
}

int printGrid(const char gridCurr[][COLS],const char gridNext[][COLS])
{
	int i = 0, j = 0;
    char ch = ' ';
	
    for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++)
        {
                gotoxy(j,i); //(x) columns, (y)row
                printf("%c", gridCurr[i][j]);
        }
	}
    gotoxy(COLS,ROWS);
    return EXIT_SUCCESS;
}
