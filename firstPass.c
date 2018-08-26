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
    rs[0] = 0;
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
        labelFlag = 0;
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
            if (rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                //continue;
            }
            labelFlag = 1;
        }
        if ((directive = ifDirective (currentLine, rs)) != NULL)
        {/*check if string or data directive*/
            /*if (rs != 0)
            {
                errorPrint ((int) rs, lineCount);

			}*/
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
                //continue;
            }
            addToDataTable (dataList, labelName, currentLine, DC, strOrNum, rs);/*add all data or str array to table*/
            if (rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                //continue;
            }
            DC = DC + dataList->sizeOfArray;
            continue;
        }
        if ((directive = ifGlobalDirective (currentLine, rs)) != NULL)
        {/*check if extern or entry directive*/
            if (rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                //continue;
            }
            labelName = (char *) malloc (strlen (directive - 1));
            for (i = 0 ; i < strlen (directive) - 1 ; i++)
            {/*copy the label name to argument*/
                labelName[i] = directive[i];

            }
            labelName[i] = '\0';
            if (strstr (directive, "1"))
            {/*1 is value for external directive*/
                addToLabelTable (labelList, labelName, DC, 2, rs);
                if (*rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    //continue;
                }
                DC = DC + 1;
                continue;
            }
            if (strstr (directive, "0"))
            {/*0 is value for entry directive*/
                addToLabelTable (labelList, labelName, DC, 1, rs);
                if (*rs != 0)
                {
                    errorPrint ((int) rs, lineCount);
                    // continue;
                }
                DC = DC + 1;
                continue;
            }

        }/*check if line contain command with label*/
        if ((verifyStringCommand (currentLine, rs) != NULL)&&(labelFlag == 1))
        {/*add only label to label list*/
            addToLabelTable (labelList, labelName, IC, 0, rs);
            if (*rs != 0)
            {
                errorPrint ((int) rs, lineCount);
                // continue;
            }
            IC = IC + 1;
            continue;
        }
        if ((verifyStringCommand (currentLine, rs) != NULL)&&(labelFlag == 0))
        {/*increase the IC value to save on correct counter*/
            IC = IC + 1;
            continue;
        }
    }
    fseek (inFile, 0, SEEK_SET);
    lineCount = 0;
    IC = 0;
    while (fgets (currentLine, BUFFER_SIZE, inFile) != '\0')
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
        labelName = ifThereIsLabel (currentLine, rs);

        verifyStringCommand (currentLine, rs);
        if (rs != 0)
        {
            errorPrint ((int) rs, lineCount);
            // continue;
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
            //continue;
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


