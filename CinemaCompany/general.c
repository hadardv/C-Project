#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "general.h"


char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s", msg);
	myGets(temp, MAX_STR_LEN, stdin);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr) return NULL;

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size, FILE* source)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, source);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}


void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element))
{
	for (int i = 0; i < size; i++)
		func((char*)(arr)+i * typeSize);

}

int isAllLettersOrSpaces(const char* str) {
	while (*str) {
		if (!isalpha((unsigned char)*str) && !isspace((unsigned char)*str)) { // Check if the character is neither a letter nor a space
			return 0; // Found a character that is not a letter or a space
		}
		str++;
	}
	return 1; // All characters are letters or spaces
}


