#include "bbst.h"
#include <stdio.h>

// DO NOT EVER BUILD AND RUN WITH THIS SETTINGS
#define SHIFT_SCALE 63  // Maximum shift scale for bit shifting (Same as BIT_MAX)
#define FILE_SIZE 13514 // 233 Character Capacity * 58 Unrestricted ASCII. Much better solution is Implementation of Combinations.

int main(void)
{
    CreateBoost(SHIFT_SCALE, FILE_SIZE);
    return 0;
}
