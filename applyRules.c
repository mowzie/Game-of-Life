#include <stdlib.h>
#include <stdio.h>
#include "applyRules.h"
#include "globals.h"

void setEqualTo(const char gridCurr[][COLS], char gridNext[][COLS], const int rows) {
    int i = 0, j = 0;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < COLS; j++) {
            gridNext[i][j] = gridCurr[i][j];
        }
    }
}

void applyRules(const char gridCurr[][COLS], char gridNext[][COLS], const int rows) {
    int i = 0, j = 0;
    int neighbors = 0;

    setEqualTo(gridCurr, gridNext, ROWS);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < COLS; j++) {
            // Check if an organism is born into an empty cell if it has exactly 3 neighbors
            if (gridCurr[i][j] == ' ') {
                neighbors = 0;	// initialize to no known neighbors
                if (gridCurr[i - 1][j - 1] == '*' && (i - 1) >= 0 && (j - 1) >= 0)	// top left
                    neighbors++;
                if (gridCurr[i - 1][j] == '*' && (i - 1) >= 0)	                        // left side
                    neighbors++;
                if (gridCurr[i - 1][j + 1] == '*' && (i - 1) >= 0 && (j + 1) < COLS)	// bottom left
                    neighbors++;
                if (gridCurr[i][j - 1] == '*' && (j - 1) >= 0)	                        // top side
                    neighbors++;
                if (gridCurr[i][j + 1] == '*'&& (j + 1) < COLS)	                        // bottom side
                    neighbors++;
                if (gridCurr[i + 1][j - 1] == '*' && (i + 1) < rows && (j - 1) >= 0)	// top right
                    neighbors++;
                if (gridCurr[i + 1][j] == '*' && (i + 1) < rows)	                // right side
                    neighbors++;
                if (gridCurr[i + 1][j + 1] == '*' && (i + 1) < rows && (j + 1) < COLS)	// bottom right
                    neighbors++;

                if (neighbors == 3)
                    gridNext[i][j] = '*';	// An organism is born at this location
            }

            // Check if an organism dies if it has < 2 or > 3 neighbors
            if (gridCurr[i][j] == '*') {
                neighbors = 0;  // initialize to no known neighbors
                if (gridCurr[i - 1][j - 1] == '*' && (i - 1) >= 0 && (j - 1) >= 0)	// top left
                    neighbors++;
                if (gridCurr[i - 1][j] == '*' && (i - 1) >= 0)                          // left side
                    neighbors++;
                if (gridCurr[i - 1][j + 1] == '*' && (i - 1) >= 0 && (j + 1) < COLS)    // bottom left
                    neighbors++;
                if (gridCurr[i][j - 1] == '*' && (j - 1) >= 0)                          // top side
                    neighbors++;
                if (gridCurr[i][j + 1] == '*' && (j + 1) < COLS)	                // bottom side
                    neighbors++;
                if (gridCurr[i + 1][j - 1] == '*' && (i + 1) < rows && (j - 1) >= 0)	// top right
                    neighbors++;
                if (gridCurr[i + 1][j] == '*' && (i + 1) < rows)	                // right side
                    neighbors++;
                if (gridCurr[i + 1][j + 1] == '*' && (i + 1) < rows && (j + 1) < COLS)	// bottom right
                    neighbors++;

                if (neighbors < 2 || neighbors > 3)
                    gridNext[i][j] = ' ';	// The organism dies at this location
            }
        }
    }
}
