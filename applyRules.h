#ifndef APPLY_RULES_H
#define APPLY_RULES_H 1

#include "globals.h"

void applyRule(char gridCurr[][COLS], char gridNext[][COLS],const int rule[2][9]);
int neighbors(unsigned x, unsigned y, char grid[][COLS]);
#endif
