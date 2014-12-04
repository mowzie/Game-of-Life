//---------------------------------------------------------
// File:        datfile.h
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

#ifndef DATFILE_H
#define DATFILE_H

#include "gameoflife.h"

// Struct to store the current location as x, y coordinates
struct Location {
    int x;
    int y;
};

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
int readDatFile(const char* filename, char gridCurr[][COLS]);

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
void createDatFile(const char* filename);

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
void createRandDatFile(const char* filename);

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
void gotoxy(const int x, const int y);

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
void enterFileName(char* datfile);

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
int hasDatExt(const char* filename);

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
int displayFiles(char* datfile);

#endif
