#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"
#include "parsing.h"
#include "utilities.h"

int mov (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList);

int cmp (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList,registers *PSW);

int add (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList);

int sub (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList);

int lea (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList);

int not (char *firstOperand,label *labelList,registers *registers,data *dataList);

int clr (char *firstOperand,label *labelList,registers *registers,data *dataList);

int inc (char *firstOperand,label *labelList,registers *registers,data *dataList);

int dec (char *firstOperand,label *labelList,registers *registers,data *dataList);

int jmp (char *firstOperand,char *FirstParam,char *secondParam,label *labelList,registers *registers,data *dataList);

int bne (char *firstOperand,char *FirstParam,char *secondParam,label *labelList,registers *registers,data *dataList);

int red (char *firstOperand,label *labelList,registers *registers,data *dataList);

int prn (char *firstOperand,label *labelList,registers *registers,data *dataList);

int jsr (char *firstOperand,char *FirstParam,char *secondParam,label *labelList,registers *registers,data *dataList);

int rts ();

void stop ();

#endif /* ACTION_H */