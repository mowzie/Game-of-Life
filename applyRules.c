#include "globals.h"
#include "applyRules.h"



void applyRule(char gridCurr[][COLS], char gridNext[][COLS], int rule[2][9]) {
	for (int y = 0; y != ROWS; y++) {
		for (int x = 0; x != COLS; x++) {
			gridNext[y][x] = rule[(gridCurr[y][x] == TRUE)][neighbors(x, y, gridCurr)];
		}
	}
}

int neighbors(unsigned x, unsigned y, char grid[][COLS]) {
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
