#include "bbst.h"
#include <stdio.h>

#define SHIFT_SCALE 63
#define FILE_SIZE 13514

int main(void) {
	CreateBoost(SHIFT_SCALE, FILE_SIZE);
    return 0;
}
