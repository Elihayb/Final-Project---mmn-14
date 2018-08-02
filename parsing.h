#ifndef PARSING_H
#define PARSING_H

int matchingBrackets(char *buffer);
int char_index(char *buffer, char chr);
void getString(char *buffer, char *string, int startIndex);
int ifComment(char *buffer);
char *ifLabel(char *buffer,int *rs);
char *ifDirective(char *buffer,int *rs);
char *ifGlobalDirective(char *buffer,int *rs);

#endif /* PARSING_H */