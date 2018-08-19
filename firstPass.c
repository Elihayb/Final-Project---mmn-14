#include "parsing.h"
#include "data.h"
#include <stdio.h>
#include <string.h>
#include "utilities.h"

/*need to perform code that update the counters IC and DC*/
int firstPass(FILE *f, command *commandList, data *dataList, label *labelList, int *rs)
{
    char *labelName;
    char *directive;
    char *currentLine = {0};
    unsigned int lineCount = 0;
    int i, labelFlag = 0, strOrNum = 0;
    IC = 0;
    DC = 0;


    while (fgets (currentLine, BUFFER_SIZE, f) != NULL)
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
            if (rs != 0)
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
                if (rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    continue;
                }
            }
            if (strstr (directive, "0"))
            {/*0 is value for entry directive*/
                addToLabelTable (labelList, labelName, DC, 1, rs);
                if (rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    continue;
                }

            }
            DC = DC + 1;
            continue;
        }
    }
    fseek (f, 0, SEEK_SET);
    while (fgets (currentLine, BUFFER_SIZE, f) != NULL)
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
        if ((ifDirective (currentLine, rs) != NULL) || (ifGlobalDirective (currentLine, rs) != NULL)){
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
            if (rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                continue;
            }
        }
        addToCommandTable (commandList, labelList, IC, currentLine, rs);
        if (rs != 0)
        {
            errorPrint ((int) rs, lineCount);
            continue;
        }
        IC = IC + commandList->wordAmount;
    }
    if (&rs != 0)
    {
        return -1;
    }
    return 0;
}


