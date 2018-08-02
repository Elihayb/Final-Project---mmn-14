#ifndef PARSING_H
#define PARSING_H

int matchingBrackets(char *buffer);
int char_index(char *buffer, char chr);
void getString(char *buffer, char *string, int startIndex);
int ifComment(char *buffer);
char *ifLabel(char *buffer);
char *ifDirective(char *buffer);
char *ifGlobalDirective(char *buffer);

#endif /* PARSING_H */