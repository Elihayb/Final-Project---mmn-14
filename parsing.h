#include "Data.h"

#ifndef PARSING_H
#define PARSING_H

int ifComment(char *buffer);

char *ifLabel(char *buffer);

char *ifDirective(char *buffer);

char *ifGlobalDirective(char *buffer);

int *verifyDataCommand(char *buffer);

char *verifyStringCommand(char *buffer);

int verifyOperand(int actionID, char *operandName, int dstOrSrcFlag, label *labelTable, int *rs);

int ifCommand(char *buffer, int *rs);

char *getFirstOperand(char *buffer, int *rs);

char *getSecondOperand(char *buffer, int *rs);

char *getFirstParam(char *buffer, int *rs);

char *getSecondParam(char *buffer, int *rs);

#endif /* PARSING_H */