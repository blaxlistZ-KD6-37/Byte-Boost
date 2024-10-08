#include "bbst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BIT_MAX 63		  // Maximum shift scale for bit shifting.
#define MAX_FILE_CHAR 233 // Windows only supports 233 character size.

unsigned long long setBufferSize(size_t size)
{
	if (size > BIT_MAX)
	{
		perror("Size scale is too large, causes an overflow\n");
		return 0;
	}

	unsigned long long buffer_size = (1ULL << size) - 1;

	return buffer_size;
}

char *generateLetters(int letter_length)
{
	size_t buf_size = setBufferSize(letter_length);

	if (buf_size == 0)
	{
		perror("Buffer size too large, would cause overflow\n");
		return '\0';
	}

	char *letters = (char *)calloc(buf_size, sizeof(char));
	if (!letters)
	{
		perror("Memory allocation failed\n");
		return '\0';
	}

	size_t i = 0;
	for (i = 0; i < buf_size; i++)
	{
		char alphabet = 'a' + (i % 26);
		letters[i] = (i > 0 && i % (1 << 7) == 0) ? '\n' : alphabet;
	}

	return letters;
}

void generateLetterFile(char *file_name, int letter_length)
{
	char *letters = generateLetters(letter_length);

	FILE *file_pointer = fopen(file_name, "wb");
	if (!file_pointer)
	{
		perror(file_name);
		free(letters);
		exit(EXIT_FAILURE);
	}
	fwrite(letters, sizeof(letters[0]), setBufferSize(letter_length), file_pointer);

	fclose(file_pointer);
}

char restrictionInterp(int x)
{
	// Newton's Finite Difference Method
	char interp = 34 + 8 * (x) + ((3) * (x) * (x - 1) * (x - 3)) / 2 - (x) * (x - 1) * (x - 2) * (x - 3) + ((2) * (x) * (x - 1) * (x - 2) * (x - 3) * (x - 4)) / 5 - ((41) * (x) * (x - 1) * (x - 2) * (x - 3) * (x - 4) * (x - 5)) / 360 + ((13) * (x) * (x - 1) * (x - 2) * (x - 3) * (x - 4) * (x - 5) * (x - 6)) / 420;
	if (x == 8)
	{
		interp = 124;
	}
	return interp;
}

char **generateFileItems(int size)
{
	char **file_items = (char **)calloc(size, sizeof(char *));

	char type = '!';
	int i, j, k, x;
	i = j = k = x = 0;
	for (i = 0; i < size && type < '{'; i++)
	{

		// Windows file structure overrwrites file whether uppercase or lowercase.
		while (type >= 'a' && type < 'z')
		{
			k++;
			type = '!' + k;
		}

		char restriction = restrictionInterp(x);

		if (i > 0 && type != restriction && i % MAX_FILE_CHAR == 0)
		{
			j = 0;
			k++;
			type = '!' + k;
		}

		if (type == restriction)
		{
			x++;
			restriction = restrictionInterp(x);
			type = restriction + x;
		}

		file_items[i] = (char *)calloc(i + 6, sizeof(char));
		memset(file_items[i], type, j + 1);
		strcat(file_items[i], ".txt");
		j++;
	}

	return file_items;
}

void clearFileItems(char **file_items, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		free(file_items[i]);
	}
}

void CreateBoost(int letter_length, int file_size)
{
	char *letters = generateLetters(letter_length);
	char **file_items = generateFileItems(file_size);

	int i = 0;
	for (i = 0; i < file_size; i++)
	{
		generateLetterFile(file_items[i], letter_length);
	}
	clearFileItems(file_items, file_size);

	free(letters);
	free(file_items);
}
