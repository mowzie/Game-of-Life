//---------------------------------------------------------
// File:        applyRules.h
//
// Functions:
//              applyRule()
//              neighbors()
//---------------------------------------------------------

#ifndef APPLY_RULES_H
#define APPLY_RULES_H

#include "gameoflife.h"

//---------------------------------------------------------
// Function:    applyRule
//
// Title:       Rule Applier
//
// Description:
//              Take in two 2D arrays and Parse through the first two
//              for filled and empty cells, pases
//
// Programmer:  Taylor Kenniston
//
// Date:        12/3/2014
//
// Version:     1.0
//
// Environment:
//              Intel i5 PC
//              Software: Windows 10 Preview
//              Compiles under Microsoft Visual Studio 2013
//
// Input:       N/A
//
// Output:      N/A
//
// Called By:   main()
//
// Calls:       N/A
//
// Parameters:  const char gridCurr[][COLS]
//              char gridNext[][COLS]
//
// Returns:     N/A
//
// History Log:
//              03-Dec-14 TK completed version 1.0
//---------------------------------------------------------
void applyRule(const char gridCurr[][COLS], char gridNext[][COLS]);

//---------------------------------------------------------
// Function:    neighbors
//
// Title:       Function to find total neighbors
//
// Description:
//              Take in coords of an array that is passed through and
//              find the total neighbors of that cell
//
// Programmer:  Taylor Kenniston
//
// Date:        12/3/2014
//
// Version:     1.0
//
// Environment:
//              Intel i5 PC
//              Software: Windows 10 Preview
//              Compiles under Microsoft Visual Studio 2013
//
// Input:       N/A
//
// Output:      N/A
//
// Called By:   applyRule()
//
// Calls:       N/A
//
// Parameters:  char* datfile
//
// Returns:     N/A
//
// History Log:
//              03-Dec-14 TK completed version 1.0
//---------------------------------------------------------
int neighbors(unsigned int x, unsigned int y, const char grid[][COLS]);

#endif
