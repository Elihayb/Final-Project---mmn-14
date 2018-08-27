#include "parsing.h"
#include "Data.h"
#include <stdio.h>
#include <string.h>
#include "utilities.h"

/*need to perform code that update the counters IC and DC*/
int firstPass(char *fileName, command *commandList, data *dataList, label *labelList, int *rs)
{
    char *labelName = NULL;
    char *directive = NULL;
    /*following variables must to be without initialization -
     * file reading fail if doing initialization for NULL*/
    char *currentLine;
    char *ch = NULL;/*for testing*/
    FILE *inFile = NULL;
    FILE *fout = NULL;/*for testing*/
    unsigned int lineCount = 0;
    int i, labelFlag = 0, strOrNum = 0;
    IC = 0;
    DC = 0;


    inFile = fopen (fileName, "r");

    fout = fopen ("tstOutput.txt", "w");/*the function is not working without this. we don't kne why :( */

    if (inFile == NULL)
    {
        fprintf (stderr, "\nUnable to open file \"%s\" in read mode\n", fileName);
    }
    while ((fgets (currentLine, BUFFER_SIZE, inFile)) != NULL)
    {
        labelName = 0;
        labelFlag = 0;
        directive = 0;
        rs[0] = 0;
        lineCount++;
        if ((isEmpty (currentLine) == 1) || (ifComment (currentLine) == 1))
        {/*check if line is empty or comment*/
            continue;
        }
        if (matchingBrackets (currentLine) == 1)
        {/*check Brackets if matching*/
            errorPrint (7, lineCount);/*undefined instruction*/
            continue;
        }
        labelName = ifThereIsLabel (currentLine, rs);
        if (labelName != NULL)
            {/*check if there is label*/
                if (*rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    continue;
                }
                labelFlag = 1;
        }
        if ((directive = ifDirective (currentLine, rs)) != NULL)
        {/*check if string or data directive*/
            if (*rs != 0)
            {
                errorPrint ((int) rs, lineCount);

            }
            if (strstr (directive, "string") == 0)
            {/*check if string directive*/
                strOrNum = 0;
            }
            else
            {/*check if data directive*/
                strOrNum = 1;
            }
            labelList= addToLabelTable (labelList, labelName, DC, 0, rs);/*add label name to labels list*/
            if (*rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }/*TODO: data are not added to table - WHY???? */
            dataList = addToDataTable (dataList, labelName, currentLine, DC, strOrNum, rs);/*add all data or str array to table*/
            if (*rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }
            DC = DC + dataList->sizeOfArray;
            continue;
        }
        if ((directive = ifGlobalDirective (currentLine, rs)) != NULL)
        {/*check if extern or entry directive*/
            if (*rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }
            labelName = (char *) malloc (strlen (directive - 1));
            for (i = 0 ; i < strlen (directive) - 1 ; i++)
            {/*copy the label name to argument*/
                labelName[i] = directive[i];

            }
            labelName[i] = '\0';
            if (strstr (directive, "1"))
            {/*1 is value for external directive*/
               labelList = addToLabelTable (labelList, labelName, DC, 2, rs);
                if (*rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    continue;
                }
                DC = DC + 1;
                continue;
            }
            if (strstr (directive, "0"))
            {/*0 is value for entry directive*/
                labelList = addToLabelTable (labelList, labelName, DC, 1, rs);
                if (*rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    continue;
                }
                DC = DC + 1;
                continue;
            }

        }/*check if line contain command with label*/
        ifCommand (currentLine,labelList, rs);
        if (((*rs == 10)&&(labelFlag == 1))||((*rs == 0)&&(labelFlag == 1)))
        {/*add only label to label list*/
            labelList = addToLabelTable (labelList, labelName, IC, 0, rs);
            IC = IC + amountOfWord (currentLine,labelList);
            *rs =0;
            continue;
        }else if (*rs != 0)
        {
            errorPrint ((int) rs, lineCount);
            continue;
        }
        if (labelFlag == 0)/*there isn't label and we need only to increase IC counter*/
        {/*increase the IC value to save on correct counter*/
            IC = IC + amountOfWord (currentLine,labelList);
        }
    }

    if (*rs!=0){
        return -1;/*first pass fail*/
    }

    fseek (inFile, 0, SEEK_SET);
    lineCount = 0;
    IC = 0;
    while (fgets (currentLine, BUFFER_SIZE, inFile) != '\0')
    {
        lineCount++;
        rs[0] = 0;
        if ((isEmpty (currentLine) == 1) || (ifComment (currentLine) == 1))
        {/*check if line is empty or comment*/
            continue;
        }
        if (matchingBrackets (currentLine) == 1)
        {/*check Brackets if matching*/
            errorPrint (7, lineCount);/*undefined instruction*/
            continue;
        }
        if ((ifDirective (currentLine, rs) != NULL) || (ifGlobalDirective (currentLine, rs) != NULL))
        {
            continue;
        }
        labelName = ifThereIsLabel (currentLine, rs);

        ifCommand (currentLine,labelList, rs);
        if (*rs != 0)
        {
            errorPrint ((int) rs, lineCount);
             continue;
        }
        /*TODO: there is exception in this code section - need to check that*/
        *commandList = addToCommandTable (commandList, labelList, IC, currentLine, rs);
        if (*rs != 0)
        {
            errorPrint ((int) rs, lineCount);
            continue;
        }
        IC = IC + commandList->wordAmount;
    }
    fclose (inFile);
    fclose (fout);
    if (*rs != 0)
    {
        return -1;
    }
    return 0;
}


