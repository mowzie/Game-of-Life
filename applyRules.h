//---------------------------------------------------------
// File: applyRules.h
//
// Functions:
//    applyRule()
//    neighbors()
//---------------------------------------------------------
#ifndef APPLY_RULES_H
#define APPLY_RULES_H

#include "gameoflife.h"

void applyRule(const char gridCurr[][COLS], char gridNext[][COLS]);


int neighbors(unsigned int x, unsigned int y, const char grid[][COLS]);

#endif
