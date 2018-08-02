#include "parsing.h"
#include "data.h"
#include <stdio.h>
#include <string.h>

int firstPass(FILE *f, commend *commendList, label *labelList) {
    char labelName[MAX_LABEL];
    char directive[MAX_DIRECT_NAME];
    char currentLine[BUFFER_SIZE];
    int lineCount, i, rs, labelFlag = 0;/*return status flag. 0 for success and error ID for failure*/
    IC = DC = 0;

    defineActionTable();/*set all actions with IDs*/

    while (fgets(currentLine, BUFFER_SIZE, f) != NULL) {
        lineCount++;

        if ((strcmp(currentLine, "") == 0) || (ifComment(currentLine) == 1)) {/*check if line is empty or comment*/
            continue;
        }
        if (matchingBrackets(currentLine) == 0) {/*check Brackets if matching*/
            errorPrint(3, lineCount);
            continue;
        }
        if (strcpy(labelName, ifLabel(currentLine, &rs)) != NULL) {/*check if there is label*/
            if (rs != 0) {
                errorPrint(&rs, lineCount);
                continue;
            }
            labelFlag = 1;
        }
        if (ifDirective(currentLine, &rs) != NULL) {/*check if string or data directive*/
            if (rs != 0) {
                errorPrint(&rs, lineCount);
                continue;
            }
            addToLabelTable(labelList, labelName, DC, 0, &rs);/*add label name to labels list*/
            if (rs != 0) {
                errorPrint(&rs, lineCount);
                continue;
            }
            addToCommendTable(commendList, IC, *currentLine, 0, &rs);/*add array to commend table*/
            if (rs != 0) {
                errorPrint(&rs, lineCount);
                continue;
            }
        }
        if ((*directive = *ifGlobalDirective(currentLine, &rs)) != NULL) {/*check if extern or entry directive*/
            if (rs != 0) {
                errorPrint(&rs, lineCount);
                continue;
            }
            for (i = 1; i < strlen(directive); i++) {/*copy the label name to argument*/
                labelName[i - 1] = directive[i];
            }
            if (strstr(directive, "1")) {/*1 is value for external directive*/
                addToLabelTable(labelList,labelName,DC,2,&rs);
                if (rs != 0) {
                    errorPrint(&rs, lineCount);
                    continue;
                }
            }/*row 9 in project doc*/


        }

    }


}


}