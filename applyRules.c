#include "applyRules.h"
//---------------------------------------------------------
// Function: applyRule
//
// Title: Rule Applier
//
// Description:
// Take in two 2D arrays and Parse through the first two
//      for filled and empty cells, pases
//
// Programmer: Taylor Kenniston
//
// Date: 12/3/2014
//
// Version: 1.0
//
// Environment:
//   Intel i5 PC
//   Software: Windows 10 Preview
//   Compiles under Microsoft Visual Studio 2013//
// 
// Input: void
//
//
// Parameters: 
// const char gridCurr[][]
// char gridNext[][]
//
// Returns: void
//
// History Log:
//   03-Dec-14 TK completed version 1.0
//---------------------------------------------------------

void applyRule(const char gridCurr[][COLS], char gridNext[][COLS]) {
    int x = 0;
    int y = 0;
    int rule[2][9] =
    {   //0  1  2  3  4  5  6  7  8     //# of Neighbors
        { 0, 0, 0, 1, 0, 0, 0, 0, 0 },  //Birth Rules
        { 0, 0, 1, 1, 0, 0, 0, 0, 0 }   //Survival Rules
    };

    for (y = 0; y != ROWS; y++) {
        for (x = 0; x != COLS; x++) {
            gridNext[y][x] = rule[(gridCurr[y][x] == TRUE)][neighbors(x, y, gridCurr)];
        }
    }
}
//---------------------------------------------------------
// Function: applyRule
//
// Title: Rule Applier
//
// Description:
// Take in coords of an array that is passed through and 
//      find the total neighbors of that cell
//
// Programmer: Taylor Kenniston
//
// Date: 12/3/2014
//
// Version: 1.0
//
// Environment:
//   Intel i5 PC
//   Software: Windows 10 Preview
//   Compiles under Microsoft Visual Studio 2013//
// 
// Input: void
//
//
// Parameters: 
// unsigned int x
// unsigned int y
// const char gridCurr[][]
// char gridNext[][]
//
// Returns: ret
//
// History Log:
//   03-Dec-14 TK completed version 1.0
//---------------------------------------------------------

int neighbors(unsigned int x, unsigned int y, const char grid[][COLS]) {
    int ret = 0;

    if (x <= COLS && y <= ROWS) {
        if (x - 1 < COLS) {
            ret += (grid[y][(x - 1)] == TRUE);
            if (y - 1 < ROWS)
                ret += (grid[(y - 1)][(x - 1)] == TRUE);
            if (y + 1 < ROWS)
                ret += (grid[(y + 1)][(x - 1)] == TRUE);
        }
        if (x + 1 < COLS) {
            ret += (grid[y][(x + 1)] == TRUE);
            if (y - 1 < ROWS)
                ret += (grid[(y - 1)][(x + 1)] == TRUE);
            if (y + 1 < ROWS)
                ret += (grid[(y + 1)][(x + 1)] == TRUE);
        }
        if (y - 1 < ROWS) {
            ret += (grid[(y - 1)][x] == TRUE);
        }
        if (y + 1 < ROWS) {
            ret += (grid[(y + 1)][x] == TRUE);
        }
    }

    return ret;
}
