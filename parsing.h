#include "Data.h"

#ifndef PARSING_H
#define PARSING_H

int ifComment(char *buffer);

char *ifLabel(char *buffer, int *RS);

char *ifDirective(char *buffer, int *RS);

char *ifGlobalDirective(char *buffer, int *RS);

int *verifyDataCommand(char *buffer, int *RS);

char *verifyStringCommand(char *buffer, int *RS);

int verifyOperand(int actionID, char *operandName, int dstOrSrcFlag, label *labelTable, int *RS);

int ifCommand(char *buffer,int *rs);

char *getFirstOperand(char *buffer,int *rs);

char *getSecondOperand(char *buffer,int *rs);

char *getFirstParam(char *buffer,int *rs);

char *getSecondParam(char *buffer,int *rs);

#endif /* PARSING_H */