#ifndef BBST_H
#define BBST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

unsigned long long setBufferSize(size_t size);

char *generateLetters(int letter_length);
char **generateFileItems(int size);
void generateLetterFile(char *file_name, int letter_length);

void CreateBoost(int letter_length, int file_size);

#ifdef __cplusplus
}
#endif

#endif // BBST_H
