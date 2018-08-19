#ifndef OUTPUT_CREATION_H
   #define OUTPUT_CREATION_H

#include "Data.h"
#include <stdio.h>

int outputCreation(char *fileName, data *dataList, command *commendList, label *labelList,int *rs);

int printLabelList(label *lbl,char *fileName);

int printCommandList(command *list,char *fileName);

int printDataTable(data *dataTable, char *fileName);

   
#endif /* OUTPUT_CREATION_H */