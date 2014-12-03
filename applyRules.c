#include "applyRules.h"

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
