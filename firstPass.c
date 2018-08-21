#include "parsing.h"
#include "data.h"
#include <stdio.h>
#include <string.h>
#include "utilities.h"

/*need to perform code that update the counters IC and DC*/
int firstPass(char *fileName, command *commandList, data *dataList, label *labelList, int *rs)
{
    char *labelName = NULL;
    char *directive = NULL;
    char *currentLine;
    char *ch;/*for testing*/
    FILE *inFile;
    FILE *fout;/*for testing*/
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

    while (fgets (currentLine, BUFFER_SIZE, inFile) != NULL)
    {
        lineCount++;
        ch = currentLine;
        if ((isEmpty (ch) == 1) || (ifComment (currentLine) == 1))
        {/*check if line is empty or comment*/
            continue;
        }
        if (matchingBrackets (currentLine) == 1)
        {/*check Brackets if matching*/
            errorPrint (7, lineCount);/*undefined instruction*/
            continue;
        }
        labelName = ifLabel (currentLine, rs);
                if (labelName != NULL)
                {/*check if there is label*/
                    if (rs != 0)
                    {
                        errorPrint ((int) rs, lineCount);
                        continue;
                    }
                    labelFlag = 1;
                }
        if ((directive = ifDirective (currentLine, rs)) != NULL)
        {/*check if string or data directive*/
            if (rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }
            if (strstr (directive, "string") == 0)
            {/*check if string directive*/
                strOrNum = 0;
            }
            else
            {/*check if data directive*/
                strOrNum = 1;
            }
            addToLabelTable (labelList, labelName, DC, 0, rs);/*add label name to labels list*/
            if (*rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }
            addToDataTable (dataList, labelName, currentLine, DC, strOrNum, rs);/*add all data or str array to table*/
            if (rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }
            DC = DC + dataList->sizeOfArray;
        }
        if ((directive = ifGlobalDirective (currentLine, rs)) != NULL)
        {/*check if extern or entry directive*/
            if (rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }
            labelName = (char *) malloc (strlen (directive - 1));
            for (i = 1 ; i < strlen (directive) ; i++)
            {/*copy the label name to argument*/
                labelName[i - 1] = directive[i];
            }
            if (strstr (directive, "1"))
            {/*1 is value for external directive*/
                addToLabelTable (labelList, labelName, DC, 2, rs);
                if (*rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    continue;
                }
            }
            if (strstr (directive, "0"))
            {/*0 is value for entry directive*/
                addToLabelTable (labelList, labelName, DC, 1, rs);
                if (*rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    continue;
                }

            }
            DC = DC + 1;
            continue;
        }
    }
    fseek (inFile, 0, SEEK_SET);
    while (fgets (currentLine, BUFFER_SIZE, inFile) != NULL)
    {
        lineCount++;

        if ((strcmp (currentLine, "") == 0) || (ifComment (currentLine) == 1))
        {/*check if line is empty or comment*/
            continue;
        }
        if (matchingBrackets (currentLine) == 0)
        {/*check Brackets if matching*/
            errorPrint (7, lineCount);/*undefined instruction*/
            continue;
        }
        if ((ifDirective (currentLine, rs) != NULL) || (ifGlobalDirective (currentLine, rs) != NULL))
        {
            continue;
        }
        labelName = ifLabel (currentLine, rs);

        verifyStringCommand (currentLine, rs);
        if (rs != 0)
        {
            errorPrint ((int) rs, lineCount);
            continue;
        }
        /*this section should be care about command line, with\without label*/
        if (labelFlag == 1)
        {
            addToLabelTable (labelList, labelName, IC, 0, rs);
            if (*rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }
        }
        addToCommandTable (commandList, labelList, IC, currentLine, rs);
        if (*rs != 0)
        {
            errorPrint ((int) rs, lineCount);
            continue;
        }
        IC = IC + commandList->wordAmount;
    }
    fclose (inFile);
    fclose (fout);
    if (&rs != 0)
    {
        return -1;
    }
    return 0;
}


