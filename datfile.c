//---------------------------------------------------------
// File:        datfile.c
//
// Functions:
//              readDatFile()
//              createDatFile()
//              createRandDatFile()
//              gotoxy()
//              enterFileName()
//              hasDatExt()
//              displayFiles()
//---------------------------------------------------------

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "dirent.h"     //for listing directory contents
#include "datfile.h"


//---------------------------------------------------------
// Function:    gotoxy()
//
// Title:       Takes an X and Y coordinate and goes to that console location
//
// Description:
//              Wraps a Windows-specific function, SetConsoleCursorPosition,
//              and moves the curser to that console location.
//
//
// Programmer:  Matt Alexander
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 7
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       N/A
//
// Called By:   createDatFile()
//
// Calls:       SetConsoleCursorPosition()
//
// Parameters:  int x, int y
//
// Returns:     N/A
//
// History Log:
//              12/04/2014 MA completed version 1.0
//---------------------------------------------------------
void gotoxy(const int x, const int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//---------------------------------------------------------
// Function:    createDatFile()
//
// Title:       Function to create a custom Dat File.
//
// Description:
//              Creates a representation of a dat file in the console
//              and allows the user to move around using either the
//              arrow keys or the wasd keys.  Toggling a particular
//              position on or off can be done with the spacebar.
//              The results are saved to the passed in filename.
//
//
// Programmer:  Matt Alexander
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 7
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       Console input for moving and selecting locations
//
// Ouput:       A text file with coordinates of the marked locations
//
// Called By:   main()
//
// Calls:       gotoxy()
//
// Parameters:  const char* filename
//
// Returns:     N/A
//
// History Log:
//              12/04/2014 MA completed version 1.0
//---------------------------------------------------------
void createDatFile(const char* filename) {
    FILE* outFileH = NULL;
    char grid[ROWS][COLS] = {{0}};
    int i = 0;
    int j = 0;
    int keyPress = 0;
    struct Location loc = {0, 0};

    system("cls");
    puts("Welcome to the Game-of-Life dat file creation tool!\n");
    puts("Use the arrow keys to move around the grid or use the wasd keys.");
    puts("Press the spacebar to toggle a spot on or off.");
    puts("When you're finished, press the Esc key to exit.");
    printf("Your selections will be saved to the file, \"%s\"\n", filename);
    puts("\nPress any key to continue");
    getch();
    system("cls");

    // Draw menu
    gotoxy(0, ROWS);
    for (i = 0; i < COLS; i++) {
        printf("-");
    }
    gotoxy(0, ROWS + 1);
    printf("Press (ESC) to exit");
    gotoxy(0, ROWS + 2);
    puts("Use the arrow keys (or wasd) to move");
    puts("Press Spacebar to toggle a location");

    // Start in top left corner
    gotoxy(loc.x, loc.y);

    // User can move around the grid with either the arrow keys or WASD.
    // The spacebar is used to toggle organisms on or off.
    while((keyPress = getch()) != KEY_ESC) {
        if (keyPress == 224) {      // Arrow keys require two reads from getch()
            keyPress = getch();
            switch(keyPress) {
            case ARROW_UP:          // UP
                if (--loc.y < 0) loc.y = 0;
                break;
            case ARROW_DOWN:        // DOWN
                if (++loc.y >= ROWS) loc.y = ROWS - 1;
                break;
            case ARROW_LEFT:        // LEFT
                if (--loc.x < 0) loc.x = 0;
                break;
            case ARROW_RIGHT:       // RIGHT
                if (++loc.x >= COLS) loc.x = COLS - 1;
                break;
            }
        } else {
            switch(keyPress) {
            case 'w':       // UP
                if (--loc.y < 0) loc.y = 0;
                break;
            case 's':       // DOWN
                if (++loc.y >= ROWS) loc.y = ROWS - 1;
                break;
            case 'a':       // LEFT
                if (--loc.x < 0) loc.x = 0;
                break;
            case 'd':       // RIGHT
                if (++loc.x >= COLS) loc.x = COLS - 1;
                break;
            case ' ':       // Toggle spot
                if (grid[loc.y][loc.x]) {  // loc.x, loc.y are reversed from ROWS, COLUMNS
                    grid[loc.y][loc.x] = 0;
                    printf(" ");
                } else {
                    grid[loc.y][loc.x] = 1;
                    printf("*");
                }
            }
        }
        gotoxy(loc.x, loc.y);
    }

    outFileH = fopen(filename, "w");
    if (!outFileH) {
    printf("\n*** Error! Could not open input file: \"%s\" ***\n\n"
           "Press any key to continue.", filename);
        getch();
        exit(EXIT_FAILURE);
    }

    // Write out dat file
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grid[i][j]) {
                fprintf(outFileH, "%d,%d\n", i, j);
            }
        }
    }

    fclose(outFileH);
    system("cls");
}

//---------------------------------------------------------
// Function:    createRandDatFile()
//
// Title:       Function to create a random Dat File.
//
// Description:
//              Generates randomly placed marked spots and saves
//              this to a dat file with the passed in filename.
//
//
// Programmer:  Matt Alexander
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 7
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       A text file with coordinates of the marked locations
//
// Called By:   main()
//
// Calls:       N/A
//
// Parameters:  const char* filename
//
// Returns:     N/A
//
// History Log:
//              12/04/2014 MA completed version 1.0
//---------------------------------------------------------
void createRandDatFile(const char* filename) {
    FILE* outFileH = NULL;
    char grid[ROWS][COLS] = {{0}};
    int i = 0;
    int j = 0;

    // Seed random number generator with the current time
    srand((unsigned int)time(NULL));

    // Randomly choose whether or not a location will be marked
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (rand() % 8 == 1) {    // Randomly choose one out of every 8
                grid[i][j] = 1;
            }
        }
    }

    outFileH = fopen(filename, "w");
    if (!outFileH) {
        printf("\n*** Error! Could not open input file: \"%s\" ***\n\n"
               "Press any key to continue.", filename);
        getch();
        exit(EXIT_FAILURE);
    }

    // Write out dat file
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grid[i][j]) {
                fprintf(outFileH, "%d,%d\n", i, j);
            }
        }
    }

    fclose(outFileH);
}

//---------------------------------------------------------
// Function:    readDatFile()
//
// Title:       Function to read a given dat file and populate a 2D array
//
// Description:
//              Populates a 2D array given a dat file, the array, and the
//              number of rows in the array.
//
//
// Programmer:  Matt Alexander
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 7
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       N/A
//
// Called By:   main()
//
// Calls:       N/A
//
// Parameters:  const char* filename
//              char grid[][COLS]
//
// Returns:     Int:  Exit status
//
// History Log:
//              12/04/2014 MA completed version 1.0
//---------------------------------------------------------
int readDatFile(const char* filename, char grid[][COLS]) {
    FILE* inFileH = NULL;
    int i = 0;
    int j = 0;
    char read = 0;

    // init grid with 0
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }

    inFileH = fopen(filename, "r");
    if (!inFileH) {
        system("cls");
        fprintf(stderr,"\n*** Error! Could not open input file: \"%s\" ***\n\n"
               "Press any key to continue.", filename);
        getch();
        return EXIT_FAILURE;
    }

    // process input file
    fscanf(inFileH, "%c", &i);
    fseek(inFileH, 0,SEEK_SET);
    if (!isdigit(i)) {
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                read = fgetc(inFileH);
                if (read == '\n')
                    break;
                else if (!isspace(read) && read != EOF)
                    grid[i][j] = 1;
                else
                    grid[i][j] = 0;
            }
        }
        
    } else {
        while (fscanf(inFileH, "%d,%d", &i, &j) != EOF) {
            grid[i][j] = 1;
        }
    }
    fclose(inFileH);
    return EXIT_SUCCESS;
}

//---------------------------------------------------------
// Function:    enterFileName()
//
// Title:       Function to get a filename from the user
//
// Description:
//              Prompts the user for a .dat filename to save the
//              new scenario.
//
//
// Programmer:  Matt Alexander
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 7
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       N/A
//
// Called By:   main()
//
// Calls:       hasDatExt()
//
// Parameters:  char* datfile
//
// Returns:     N/A
//
// History Log:
//              12/04/2014 MA completed version 1.0
//---------------------------------------------------------
void enterFileName(char* datfile) {
    char filename[FILENAME_MAX];
    wchar_t buff[PATH_MAX];

    _wgetcwd(buff, PATH_MAX);   //get string of current working dir
        
    system("cls");
    puts("Please enter a filename to save as your new dat file.");

    do {
        puts("Your filename must end with a '.dat' file extension.");
        printf(">>> ");

        fgets(filename, FILENAME_MAX, stdin);
        if (filename[strlen(filename) - 1] == '\n') { //remove newline
            filename[strlen(filename) - 1] = '\0';  //terminate string
        } else {
            while (getchar() != '\n')
                ;
        }
    // Verify that the file ends in .dat and isn't longer than MAX_PATH
    } while ((!hasDatExt(filename)) || (strlen(filename) >= MAX_PATH
                                       - wcslen(buff) - strlen(DIRPREFIX) - 1));
    strcpy(datfile, DIRPREFIX);
    strcat(datfile, filename);
    
    puts("");
}


//---------------------------------------------------------
// Function:    hasDatExt()
//
// Title:       Function to verify that a filename ends in .dat
//
// Description:
//              Verify that a passed in filename has a .dat file extension.
//
//
// Programmer:  Matt Alexander
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 7
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       N/A
//
// Called By:   enterFileName()
//
// Calls:       N/A
//
// Parameters:  const char* filename
//
// Returns:     N/A
//
// History Log:
//              12/04/2014 MA completed version 1.0
int hasDatExt(const char* filename) {
    size_t len = strlen(filename);
    return len > 4 && strcmp(filename + len - 4, ".dat") == 0;
}

//---------------------------------------------------------
// Function:    displayFiles()
//
// Title:       Function to display files and select a file
//
// Description:
//              Displays the current files in a directory
//              and prompts the user to select a file to use.
//
//
// Programmer:  Ian Littke & Matt Alexander
//
// Date:        12/04/2014
//
// Version:     1.0
//
// Environment:
//              Hardware: Intel x86_64 PC
//              Software: Windows 7
//              Compiles under Microsoft Visual Studio 2012
//
// Input:       N/A
//
// Ouput:       N/A
//
// Called By:   checkLoadScreenKeyPress()
//
// Calls:       N/A
//
// Parameters:  char* datfile
//
// Returns:     N/A
//
// History Log:
//              12/04/2014 IL/MA completed version 1.0
//---------------------------------------------------------
int displayFiles(char* datfile) {
    unsigned int fileNum = 0;
    unsigned int fileCount = 0;
    char filename[128][MAX_PATH];   // Array of strings to hold filenames
    DIR* dh = NULL;         // DIR handle
    struct dirent* dir = NULL;
    int okay = FALSE;

    system("cls");
    printf("Please choose a file\n");
    printf("--------------------\n\n");

    dh = opendir(DIRPREFIX);
    if (dh) {
        while ((dir = readdir(dh)) != NULL) {
            if (strstr(dir->d_name, ".dat")) {
                strcpy(filename[fileNum], dir->d_name);
                printf("    %d: %s%s\n", ++fileNum, DIRPREFIX, dir->d_name);
                fileCount++;
            }
        }
        closedir(dh);
     
        if (fileCount == 0) {
            printf("No files found in directory \"%s\"\n\n"
                    "Press any key to continue.", DIRPREFIX);
            getch();
            return EXIT_FAILURE;
        }

        puts("");
        do {
            printf("Enter the file number and press Enter >>> ");
            while (fscanf(stdin, "%d", &fileNum) != 1) {
                while (getchar() != '\n')
                    ;
                printf("Enter the file number and press Enter >>> ");
            }
            while (getchar() != '\n')
                ;
            if ((fileNum <= fileCount) && (fileNum != 0))
                okay = TRUE;
        } while (!okay);
        
        strcpy(datfile, DIRPREFIX);
        strcat(datfile, filename[fileNum - 1]);
    } else {
        fprintf(stderr, "*** Error! Could not open the directory '%s' ***\n\n"
                            "Press any key to continue.", DIRPREFIX);
        getch();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
