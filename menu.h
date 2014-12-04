#ifndef MENU_H
#define MENU_H

//----------------------------------------------------------------------------
// File:      menu.h
//
// Functions:
//            runLoadScreen()
//            loadScreenSleep()
//            checkLoadScreenKeyPress()
//            displayMenu()
//            displayRunningMenu()
//            printGrid()
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Function:   displayMenu(void)
//
// Title:      Displays simple menu below game field
//
// Description:
//             Sets a border below the game field, and shows the simple menu
//
// Programmer: Ian Littke
//
// Date:       12/04/2014
//
// Version:    1.0
//
// Environment:
//             Hardware: Intel x86_64 PC
//             Software: Windows 8.1
//             Compiles under Microsoft Visual Studio 2012
//
// Input:      N/A
//
// Ouput:      row of "-"s below valid game field
//             Simple menu for valid keypresses
//
// Called By:  runLoadScreen()
//
// Calls:      gotoxy()
//
// Parameters: void
//
// Returns:    void
//
// History Log:
//             12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
void displayMenu(void);

//----------------------------------------------------------------------------
// Function:   displayRunningMenu(void)
//
// Title:      Displays simple menu below game field
//
// Description:
//             Sets a border below the game field, and shows the simple menu
//
// Programmer: Ian Littke
//
// Date:       12/04/2014
//
// Version:    1.0
//
// Environment:
//             Hardware: Intel x86_64 PC
//             Software: Windows 8.1
//             Compiles under Microsoft Visual Studio 2012
//
// Input:      N/A
//
// Ouput:      row of "-"s below valid game field
//             Simple menu for valid keypresses
//
// Called By:  main()
//
// Calls:      gotoxy()
//
// Parameters: void
//
// Returns:    void
//
// History Log:
//             12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
void displayRunningMenu(void);

//----------------------------------------------------------------------------
// Function:   printGrid(const char gridCurr[][COLS])
//
// Title:      Prints current status of life
//
// Description:
//             Iterates through each piece of life and displays if its alive
//
// Programmer: Ian Littke
//
// Date:       12/04/2014
//
// Version:    1.0
//
// Environment:
//             Hardware: Intel x86_64 PC
//             Software: Windows 8.1
//             Compiles under Microsoft Visual Studio 2012
//
// Input:      N/A
//
// Ouput:      a "*" for each piece of living life in the grid in stdout
//
// Called By:  main()
//             runLoadScreen()
//
// Calls:      gotoxy()
//
// Parameters: gridCur[][COLS]
//
// Returns:    void
//
// History Log:
//             12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
void printGrid(const char gridCurr[][COLS]);

//----------------------------------------------------------------------------
// Function:   checkLoadScreenKeyPress(char* datfile, const char ch)
//
// Title:      Function to evualuate keypress
//
// Description:
//             Evauluates keypress while splashscreen is running
//             Exits loadscreen and starts game if valid keypress
//
//
// Programmer: Ian Littke
//
// Date:       12/04/2014
//
// Version:    1.0
//
// Environment:
//             Hardware: Intel x86_64 PC
//             Software: Windows 8.1
//             Compiles under Microsoft Visual Studio 2012
//
// Input:      N/A
//
// Ouput:      N/A
//
// Called By:  runLoadScreen()
//
// Calls:      enterFileName()
//             creatDatFile()
//             createRandDatFile()
//             displayFiles()
//
// Parameters: char* datfile
//             const char ch
//
// Returns:    int boolQuit
//                 either exit_success (1) or value of keypress
//
// History Log:
//             12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
int checkLoadScreenKeyPress(char* datfile, char const ch);

//----------------------------------------------------------------------------
// Function:   loadScreenSleep()
//
// Title:      Function to keep splash screen still
//
// Description:
//             Keeps the splash screen from "evolving" while still 
//             accepting a keypress
//
//
// Programmer: Ian Littke
//
// Date:       12/04/2014
//
// Version:    1.0
//
// Environment:
//             Hardware: Intel x86_64 PC
//             Software: Windows 8.1
//             Compiles under Microsoft Visual Studio 2012
//
// Input:      key press to enter into the game
//
// Ouput:      N/A
//
// Called By:  runLoadScreen()
//
// Calls:      N/A
//
// Parameters: N/A
//
// Returns:    int
//                 either exit_success (1) or value of keypress
//
// History Log:
//             12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
int loadScreenSleep();

//----------------------------------------------------------------------------
// Function:   runLoadScreen(char* datfile, char gridPtrCurr[][COLS],
//                           char gridPtrNext[][COLS], char tmpPtr[][COLS])
//
// Title:      Function to run opening simulation as a splash screen
//
// Description:
//             Dual purpose to both initialize game states
//             and display friendly welcome screen
//
//
// Programmer: Ian Littke
//
// Date:       12/04/2014
//
// Version:    1.0
//
// Environment:
//             Hardware: Intel x86_64 PC
//             Software: Windows 8.1
//             Compiles under Microsoft Visual Studio 2012
//
// Input:      N/A
//
// Ouput:      "Life" Generation counter to stdout
//
// Called By:  main()
//
// Calls:      readDatFile()
//             printGrid()
//             gotoxy()
//             loadScreenSleep()
//             checkLoadScreenKeyPress()
//             applyRule()
//
// Parameters: const char* datfile
//             char gridPtrCurr[][COLS]
//             char gridPtrNext[][COLS]
//
// Returns:    int quitLoadScreen
//
// History Log:
//             12/04/2014 IL completed version 1.0
//----------------------------------------------------------------------------
int runLoadScreen(char *datfile, char gridPtrCurr[][COLS], char gridPtrNext[][COLS], char tmpPtr[][COLS]);

#endif
