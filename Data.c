

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"
#include "parsing.h"


/*********************ACTION SECTION**********************/


/*set all actions and codes for each one*/
action *defineActionTable() {

    static action actionTable[16];

    strcpy(actionTable[0].actionName, "mov");
    actionTable[0].actionCode = 0;
    strcpy(actionTable[0].legalMethodOprSrc, "013");
    strcpy(actionTable[0].legalMethodOprDst, "13");
    strcpy(actionTable[1].actionName, "cmp");
    actionTable[1].actionCode = 1;
    strcpy(actionTable[1].legalMethodOprSrc, "013");
    strcpy(actionTable[1].legalMethodOprDst, "013");
    strcpy(actionTable[2].actionName, "add");
    actionTable[2].actionCode = 2;
    strcpy(actionTable[2].legalMethodOprSrc, "013");
    strcpy(actionTable[2].legalMethodOprDst, "13");
    strcpy(actionTable[3].actionName, "sub");
    actionTable[3].actionCode = 3;
    strcpy(actionTable[3].legalMethodOprSrc, "013");
    strcpy(actionTable[3].legalMethodOprDst, "13");
    strcpy(actionTable[4].actionName, "not");
    actionTable[4].actionCode = 4;
    strcpy(actionTable[4].legalMethodOprSrc, "---");
    strcpy(actionTable[4].legalMethodOprDst, "13");
    strcpy(actionTable[5].actionName, "clr");
    actionTable[5].actionCode = 5;
    strcpy(actionTable[5].legalMethodOprSrc, "---");
    strcpy(actionTable[5].legalMethodOprDst, "13");
    strcpy(actionTable[6].actionName, "lea");
    actionTable[6].actionCode = 6;
    strcpy(actionTable[6].legalMethodOprSrc, "1");
    strcpy(actionTable[6].legalMethodOprDst, "13");
    strcpy(actionTable[7].actionName, "inc");
    actionTable[7].actionCode = 7;
    strcpy(actionTable[7].legalMethodOprSrc, "---");
    strcpy(actionTable[7].legalMethodOprDst, "13");
    strcpy(actionTable[8].actionName, "dec");
    actionTable[8].actionCode = 8;
    strcpy(actionTable[8].legalMethodOprSrc, "---");
    strcpy(actionTable[8].legalMethodOprDst, "13");
    strcpy(actionTable[9].actionName, "jmp");
    actionTable[9].actionCode = 9;
    strcpy(actionTable[9].legalMethodOprSrc, "---");
    strcpy(actionTable[9].legalMethodOprDst, "123");
    strcpy(actionTable[10].actionName, "bne");
    actionTable[10].actionCode = 10;
    strcpy(actionTable[10].legalMethodOprSrc, "---");
    strcpy(actionTable[10].legalMethodOprDst, "123");
    strcpy(actionTable[11].actionName, "red");
    actionTable[11].actionCode = 11;
    strcpy(actionTable[11].legalMethodOprSrc, "---");
    strcpy(actionTable[11].legalMethodOprDst, "13");
    strcpy(actionTable[12].actionName, "prn");
    actionTable[12].actionCode = 12;
    strcpy(actionTable[12].legalMethodOprSrc, "---");
    strcpy(actionTable[12].legalMethodOprDst, "013");
    strcpy(actionTable[13].actionName, "jsr");
    actionTable[13].actionCode = 13;
    strcpy(actionTable[13].legalMethodOprSrc, "---");
    strcpy(actionTable[13].legalMethodOprDst, "123");
    strcpy(actionTable[14].actionName, "rts");
    actionTable[14].actionCode = 14;
    strcpy(actionTable[14].legalMethodOprSrc, "---");
    strcpy(actionTable[14].legalMethodOprDst, "---");
    strcpy(actionTable[15].actionName, "stop");
    actionTable[15].actionCode = 15;
    strcpy(actionTable[15].legalMethodOprSrc, "---");
    strcpy(actionTable[15].legalMethodOprDst, "---");

    return actionTable;
}


/*********************LABEL SECTION**********************/


/*check if there are not any label with same name
 and there is not any action name or directive command that identical in names
 Parameters:
 pointer to label list.
 name of label.
 Return:
 -1 if label is not valid.
 0 if label is valid.*/
int validLabel(label *list, char *labelName, int *rs) {
    int i;

    action *actionTable = defineActionTable();

    if (searchLabel(list, labelName) != NULL) {/*check if label name equal to any exist label name*/
        *rs = -1;/*TO Do: write the correct error code*/
        return -1;/*label is not valid*/
    }
    for (i = 0; i < 16; i++) {/*check if label name equal to any action name */

        if (strcmp(actionTable[i].actionName, labelName) == 0) {
            *rs = -1;/*TO Do: write the correct error code*/
            return -1;/*label is not valid*/
        }
    }/*check if label name equal to any register name*/
    if ((strcmp(labelName, "r0") == 0) || (strcmp(labelName, "r1") == 0) || (strcmp(labelName, "r2") == 0) ||
        (strcmp(labelName, "r3") == 0) || (strcmp(labelName, "r4") == 0) || (strcmp(labelName, "r5") == 0) ||
        (strcmp(labelName, "r6") == 0) || (strcmp(labelName, "r7") == 0) || (strcmp(labelName, "PSW") == 0)) {
        *rs = -1;/*TO Do: write the correct error code*/
        return *rs;/*label is not valid*/
    }/*check if label name equal to any directive name*/
    if (((strcmp("string", labelName) == 0)) || ((strcmp("data", labelName) == 0)) ||
        ((strcmp("entry", labelName) == 0)) || ((strcmp("extern", labelName) == 0))) {
        *rs = -1;/*TO Do: write the correct error code*/
        return *rs;/*label is not valid*/

    }
    return *rs = 0;/*label is valid*/


}


/* allocate and initialize a new label;
   space for the label is obtained via malloc();
   return a pointer to the new label, NULL if no space available*/
label *newLabel() {
    label *lbl;
    lbl = (label *) malloc(sizeof(label));
    if (lbl) {
        lbl->labelName = NULL;
        lbl->type = -1;
        lbl->next = NULL;
        lbl->addressLabel = -1;
        return lbl;
    }
    free(lbl);
    return NULL;
}


/*check if there any label with same name.
 Parameters:
 pointer to label list.
 name of label.
 Return:
 pointer to label if exist.
 NULL if not exist on list.*/
label *searchLabel(label *list, char *str) {
    label *lbl = list;
    /*save the first name for loop condition*/



    if ((list == NULL) || (str == NULL) || (*str == 0)) {/*check if all parameters are valid*/

        return NULL;
    }
    do {

/*search loop*/

        if (strcmp(lbl->labelName, str) == 0) {
            return lbl;
        } else {
            lbl = lbl->next;
        }

    } while (lbl != NULL);

    return NULL;/*label with same name is not exist*/
}







/*add label to labels list if it contain valid values
 Parameters:
 pointer to label list (MULL if there is not list).
 name.
 DC value for label address.
 type of label (0 for local defined label, 1 for entry, 2 for external).
 report success flag.
 Return:
 pointer to new label on the list.
 report success flag 0 if success, else -1.
 */
/*To Do: need to add return errors status with rs flag*/
label addToLabelTable(label *label, char *name, unsigned int DC, unsigned int type, int *rs) {

    if ((name == NULL) || (*name == 0)) {/*check if name is NULL or without value*/
        if (rs) *rs = -1;/*failure*/
        return *label;
    }
    if (validLabel(label, name, rs) != 0) {
        return *label;/*invalid label name*/
    }
    if (label == NULL) {/*list is empty and label are not exist */

        label = newLabel();
        if (label != NULL) {
            label->type = type;
            label->labelName = name;
            label->addressLabel = DC;
            label->next = NULL;
            if (rs) *rs = 0;/*success*/

            return *label;
        } else {
            free(label);/*free memory and return NULL and failure if newLabel fail*/
            if (rs) *rs = -1;/*failure*/
            return *label;/*return received pointer with NULL address */
        }
    } else {
        *label->next = addToLabelTable(label->next, name, DC, type, rs);
        if (*rs) *rs = 0;/*success*/
        return *label;
    }
}

/*********************COMMAND SECTION**********************/

/*command addToCommandTable(command *list, label *labelList, unsigned int address, char *sourceCode, int childFlag, int *rs) {
    int i;
    action *actionTable = defineActionTable();

    if ((sourceCode == NULL) || (*sourceCode == 0)) {
        if (rs)
            *rs = -1;*//*failure*//*
        return *list;
    }
    if (getActionID(sourceCode) == -1) {
        *rs = 7;*//*status 2 return error about un-exist action name*//*
        return *list;
    }
    if (ifCommand(sourceCode, rs) != 1) {
        return *list;*//*rs return the error code from function*//*
    }
    if (list == NULL) {*//*list is empty*//*
        list = newCommand();
        if (list != NULL) {
            list->decimalAddress = address;
            strcpy(list->srcCode, sourceCode);
            list->wordAmount= amountOfWord(sourceCode,labelList);
*//*To Do: need to fill the machineCode filed with relevant data*//*
          *//*  if (childFlag == 0) {
                strcpy(list->machineCode, convertToBinary(sourceCode,WORD_LENGTH-2,rs));
            } else {
                strcpy(list->machineCode, "NoCode");
                list->childFlag = 0;
            }
            if (rs)
                *rs = 0;*//**//*success*//**//*
            return *list;*//*
        }
        free(list);*//*free memory and return NULL and failure if newCommand fail*//*
        if (rs)
            *rs = -1;*//*failure*//*
        return *list;
    } else {
        list->next = addToCommandTable(list->next, address, sourceCode, wordAmount, childFlag, rs);
        if (*rs)
            *rs = 0;*//*success*//*
        return *list;
    }

}*/

/* allocate and initialize a new command;
   space for the command is obtained via malloc();
   return a pointer to the new command, NULL if no space available*/
command *newCommand() {
    command *cmd = (command *) malloc(sizeof(command));
    if (cmd) {
        cmd->childFlag = 0;
        cmd->machineCode[0] = '\0';
        cmd->wordAmount = 0;
        cmd->srcCode[0] = '\0';
        cmd->decimalAddress = 0;
        cmd->next = NULL;
    }
    return cmd;
}

/*the function return the number of words to write to command table
 * for action without operands it return 1.
 * for action with 1 operand it return 2.
 * for action with 2 operands it return 3 if all of them are registers. else, return 4.
 * for jump action it return 3 if all of params are registers. else, return 4.*/
/*not checked*/
int amountOfWord(char *sourceCode, label *labelList) {

    int actionCode;
    int *rs = 0;
    char *operandName[3];/*array for operands and params - cannot be more than 2 operands or 1 operand and 2 params */

    actionCode = getActionID(sourceCode);

    if (ifCommand(sourceCode, rs) != 1) {/*check if invalid command*/
        return -1;/*failure*/
    }
    if ((actionCode == 14) || (actionCode == 15)) {/*check if rts or stop actions*/
        return 1;/*there is only first word for action*/

    } else if ((actionCode == 9) || (actionCode == 10) || (actionCode == 13)) {/*check if jump addressing method*/
        operandName[1] = getFirstParam(sourceCode, rs);
        operandName[2] = getSecondParam(sourceCode, rs);

        if ((verifyOperand(actionCode, operandName[1], 2, labelList, rs) == REGISTER_METHOD) &&
            (verifyOperand(actionCode, operandName[2], 2, labelList, rs) == REGISTER_METHOD)) {
            return 3;/*for jump addressing with 2 registers params. first word, label and 2 registers in the same word*/

        } else {
            return 4;/*for jump addressing with 2 params.first word, label and 2 params in 2 additional words*/
        }
    }
    operandName[0] = getFirstOperand(sourceCode, rs);
    operandName[1] = getSecondOperand(sourceCode, rs);
    /*duplicate condition for check certainly that are only 1 operand */
    if ((operandName[0] != NULL) && (operandName[1] == NULL) || (operandName[1] != NULL) && (operandName[0] == NULL)) {
        return 2;/*for action with 1 operand. first word with 1 operand word*/
    } else if ((verifyOperand(actionCode, operandName[0], 0, labelList, rs) == REGISTER_METHOD) &&
               (verifyOperand(actionCode, operandName[1], 1, labelList, rs) == REGISTER_METHOD)) {
        return 2;/*for action with 2 registers operands.first word and 2 registers in the same word*/
    } else {
        return 3;/*for action with 2 operands. first word and 2 operand*/
    }
}

/*not checked*/
int getActionID(char *sourceCode) {
    action *actionTable = defineActionTable();
    int i, actionID;
    for (i = 0; i < 16; i++) {
        if (strstr(sourceCode, actionTable[i].actionName) != NULL) {
            actionID = actionTable[i].actionCode;
            return actionID;
        }
    }
    return -1;
}

/*This function convert decimal numbers to binary and print it to the file output.
 * if you print a char, convert it to ascii decimal code like that:
 * char a = 'a'; int n = (int)a;*/
char *convertToBinary(int n, int sizeOfBits, int *rs) {

    int c, d, count;
    char *pointer;

    if (n < HIGHEST_NEGATIVE_VALUE) {
        *rs = 21;
        return NULL;
    } else if (n > HIGHEST_POSITIVE_VALUE) {
        *rs = 20;
        return NULL;
    }
    count = 0;
    pointer = (char *) malloc((size_t) (sizeOfBits + 1));

    if (pointer == NULL)
        exit(EXIT_FAILURE);

    for (c = (sizeOfBits - 1); c >= 0; c--) {
        d = n >> c;
        if (d & 1) {
            *(pointer + count) = 1 + '0';
        } else {
            *(pointer + count) = 0 + '0';
        }
        count++;
    }
    *(pointer + count) = '\0';

    return pointer;
}

/**/
int printCommandList(command *list) {
    if (list->childFlag == 1) {/*all binary code exist in parent command*/
        list = list->next;
    } else {
        printf("%d%10s", list->decimalAddress, list->machineCode);
    }
}

/*this function save on homogeneous in error contact.
 * get row number and error id*/
int errorPrint(unsigned int errId, unsigned int row) {
    switch (errId) {
        /*labels errors*/
        case 1:
            fprintf(stderr, "Line: %d , invalid label - declared few times or not declared at all", row);
        case 2:
            fprintf(stderr, "Line: %d , invalid label name - saved word", row);
        case 3:
            fprintf(stderr, "Line: %d , warning - label does not start in first column", row);
        case 4:
            fprintf(stderr, "Line: %d , local label cannot be declared as external", row);
        case 5:
            fprintf(stderr, "Line: %d , label is already designated as external", row);
        case 6:
            fprintf(stderr, "Line: %d , invalid label name - name large", row);
            /*command errors*/
        case 7:
            fprintf(stderr, "Line: %d , undefined instruction", row);
        case 8:
            fprintf(stderr, "Line: %d , number of argoments is not valid", row);
        case 9:
            fprintf(stderr, "Line: %d , need to set only 2 parameters ", row);
        case 10:
            fprintf(stderr, "Line: %d , need more parameters", row);
        case 11:
            fprintf(stderr, "Line: %d , invalid source operand (label)", row);
        case 12:
            fprintf(stderr, "Line: %d , invalid source operand (register)", row);
        case 13:
            fprintf(stderr, "Line: %d , invalid source operand (immediate)", row);
        case 14:
            fprintf(stderr, "Line: %d , invalid target operand (label)", row);
        case 15:
            fprintf(stderr, "Line: %d , invalid target operand (register)", row);
        case 16:
            fprintf(stderr, "Line: %d , invalid target operand (immediate)", row);
        case 17:
            fprintf(stderr, "Line: %d , invalid argument (immediate too large)", row);
            /*directive errors*/
        case 18:
            fprintf(stderr, "Line: %d , data array contain illegal values", row);
        case 19:
            fprintf(stderr, "Line: %d , incorrect string array", row);
        case 20:
            fprintf(stderr, "Line: %d , data overflow (positive value too large to fit in 14 bits)", row);
        case 21:
            fprintf(stderr, "Line: %d , data overflow (negative value too large to fit in 14 bits)", row);
        case 22:
            fprintf(stderr, "Line: %d , missing argument in directive", row);
        case 23:
            fprintf(stderr, "Line: %d , undefined directive", row);
        default:
            return -1;/*failure*/
    }
}


