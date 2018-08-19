#include "parsing.h"
#include "data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int outputCreation(FILE *inFile, struct commend *commendList, label *labelList)
{


}

/*print data table to output file fileName.ob*/
int printDataTable(data *dataTable, char *fn)
{
    char *fileName = malloc (strlen (fn + 4));/*Allocate a string name with enough space for the extensions.*/
    FILE *outExt = NULL;
    int i,j,numOfWords = 0;
    char *binaryCodeArray;
    char str[WORD_LENGTH+1];

    if (dataTable == NULL)
    {
        return 0;/*data table is empty*/
    }
    strcat (fileName, ".ob");

    do
    {/*loop for data structures*/
        numOfWords = dataTable->sizeOfArray;
        binaryCodeArray = dataTable->binaryCode;
        for(i=0;i<numOfWords;i++)/*loop for word into array*/
        {
            for(j=0;j<WORD_LENGTH;j++){
                str[j] = binaryCodeArray[j];
            }
            str[WORD_LENGTH] = '\0';
            if ((outExt = fopen (fileName, "a")) != NULL)
            {

                fprintf (outExt, "%4d - %14s", dataTable->address,str);
            }
            dataTable = dataTable->next;
        }

    } while (dataTable != NULL);

    if (outExt != NULL)
    {
        fclose (outExt);
    }

    return 0;
}

/*print label table to output files fileName.ext and fileName.ent*/
int printLabelList(label *lbl, char *fn)
{

    char *fileName = malloc (strlen (fn + 5));/*Allocate a string name with enough space for the extensions.*/
    FILE *outExt = NULL;
    FILE *outEnt = NULL;

    if (lbl == NULL)
    {
        return 0;/*label list is empty and the function should be do nothing*/
    }
    do
    {/*print loop*/
        if (lbl->type == 1)
        {/*print to entry labels file*/
            strcat (fileName, ".ent");
            if ((outEnt = fopen (fileName, "a")) != NULL)
            {
                fprintf (outEnt, "%32s - %4d", lbl->labelName, lbl->addressLabel);
            }
        }
        else if (lbl->type == 2)
        {/*print to extern labels file*/
            strcat (fileName, ".ext");
            if ((outExt = fopen (fileName, "a")) != NULL)
            {
                fprintf (outExt, "%32s - %4d", lbl->labelName, lbl->addressLabel);
            }
        }
        lbl = lbl->next;
    } while (lbl != NULL);

    if (outEnt != NULL)
    {
        fclose (outEnt);
    }
    if (outExt != NULL)
    {
        fclose (outExt);
    }
    return 0;
}

/*print commands table to output file fileName.ob*/
int printCommandList(command *list, char *fn)
{
    char *fileName = malloc (strlen (fn + 4));/*Allocate a string name with enough space for the extensions.*/
    FILE *outExt = NULL;
    int i,j,numOfWords = 0;
    char *binaryCodeArray;
    char str[WORD_LENGTH+1];

    if (list == NULL)
    {
        return 0;/*data table is empty*/
    }
    strcat (fileName, ".ob");

    do
    {/*loop for data structures*/
        numOfWords = list->wordAmount;
        binaryCodeArray = list->machineCode;
        for(i=0;i<numOfWords;i++)/*loop for word into array*/
        {
            for(j=0;j<WORD_LENGTH;j++){
                str[j] = binaryCodeArray[j];
            }
            str[WORD_LENGTH] = '\0';
            if ((outExt = fopen (fileName, "a")) != NULL)
            {

                fprintf (outExt, "%4d - %14s", list->decimalAddress,str);
            }
            list = list->next;
        }

    } while (list != NULL);

    if (outExt != NULL)
    {
        fclose (outExt);
    }
    return 0;
}