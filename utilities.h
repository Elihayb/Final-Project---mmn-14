#ifndef MAMAN_14_UTILITIES_H
#define MAMAN_14_UTILITIES_H

int matchingBrackets(char *buffer);

char *nextStr(char *strIndex);

char *nextStr2(char *strIndex);

char *skipSpcaes(char *strIndex);

int charToInt(char ch);

void getString(char *buffer, char *string, int startIndex);

void getString2(char *index, char *string, char end);

int char_index(char *buffer, char chr);

#endif