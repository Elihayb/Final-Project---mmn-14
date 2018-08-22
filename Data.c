/*data file contain all data management and words */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"
#include "parsing.h"
#include "utilities.h"

unsigned int IC = 0, DC = 0;
/*********************ACTION SECTION**********************/


/*set all actions and codes for each one*/
action *defineActionTable()
{

    static action actionTable[16];

    strcpy (actionTable[0].actionName, "mov");
    actionTable[0].actionCode = 0;
    strcpy (actionTable[0].legalMethodOprSrc, "013");
    strcpy (actionTable[0].legalMethodOprDst, "13");
    strcpy (actionTable[1].actionName, "cmp");
    actionTable[1].actionCode = 1;
    strcpy (actionTable[1].legalMethodOprSrc, "013");
    strcpy (actionTable[1].legalMethodOprDst, "013");
    strcpy (actionTable[2].actionName, "add");
    actionTable[2].actionCode = 2;
    strcpy (actionTable[2].legalMethodOprSrc, "013");
    strcpy (actionTable[2].legalMethodOprDst, "13");
    strcpy (actionTable[3].actionName, "sub");
    actionTable[3].actionCode = 3;
    strcpy (actionTable[3].legalMethodOprSrc, "013");
    strcpy (actionTable[3].legalMethodOprDst, "13");
    strcpy (actionTable[4].actionName, "not");
    actionTable[4].actionCode = 4;
    strcpy (actionTable[4].legalMethodOprSrc, "---");
    strcpy (actionTable[4].legalMethodOprDst, "13");
    strcpy (actionTable[5].actionName, "clr");
    actionTable[5].actionCode = 5;
    strcpy (actionTable[5].legalMethodOprSrc, "---");
    strcpy (actionTable[5].legalMethodOprDst, "13");
    strcpy (actionTable[6].actionName, "lea");
    actionTable[6].actionCode = 6;
    strcpy (actionTable[6].legalMethodOprSrc, "1");
    strcpy (actionTable[6].legalMethodOprDst, "13");
    strcpy (actionTable[7].actionName, "inc");
    actionTable[7].actionCode = 7;
    strcpy (actionTable[7].legalMethodOprSrc, "---");
    strcpy (actionTable[7].legalMethodOprDst, "13");
    strcpy (actionTable[8].actionName, "dec");
    actionTable[8].actionCode = 8;
    strcpy (actionTable[8].legalMethodOprSrc, "---");
    strcpy (actionTable[8].legalMethodOprDst, "13");
    strcpy (actionTable[9].actionName, "jmp");
    actionTable[9].actionCode = 9;
    strcpy (actionTable[9].legalMethodOprSrc, "---");
    strcpy (actionTable[9].legalMethodOprDst, "123");
    strcpy (actionTable[10].actionName, "bne");
    actionTable[10].actionCode = 10;
    strcpy (actionTable[10].legalMethodOprSrc, "---");
    strcpy (actionTable[10].legalMethodOprDst, "123");
    strcpy (actionTable[11].actionName, "red");
    actionTable[11].actionCode = 11;
    strcpy (actionTable[11].legalMethodOprSrc, "---");
    strcpy (actionTable[11].legalMethodOprDst, "13");
    strcpy (actionTable[12].actionName, "prn");
    actionTable[12].actionCode = 12;
    strcpy (actionTable[12].legalMethodOprSrc, "---");
    strcpy (actionTable[12].legalMethodOprDst, "013");
    strcpy (actionTable[13].actionName, "jsr");
    actionTable[13].actionCode = 13;
    strcpy (actionTable[13].legalMethodOprSrc, "---");
    strcpy (actionTable[13].legalMethodOprDst, "123");
    strcpy (actionTable[14].actionName, "rts");
    actionTable[14].actionCode = 14;
    strcpy (actionTable[14].legalMethodOprSrc, "---");
    strcpy (actionTable[14].legalMethodOprDst, "---");
    strcpy (actionTable[15].actionName, "stop");
    actionTable[15].actionCode = 15;
    strcpy (actionTable[15].legalMethodOprSrc, "---");
    strcpy (actionTable[15].legalMethodOprDst, "---");

    return actionTable;
}

/*********************LABEL SECTION**********************/

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
label *addToLabelTable(label *label, char *name, unsigned int DC, unsigned int type, int *rs)
{

    if ((name == NULL) || (*name == 0))
    {/*check if name is NULL or without value*/
        if (rs)
            *rs = -1;/*failure*/
        return label;
    }
    if (validLabel (label, name, rs) != 0)
    {
        return label;/*invalid label name*/
    }
    if (label == NULL)
    {/*list is empty and label are not exist */

        label = newLabel ();
        if (label != NULL)
        {
            label->type = type;
            label->labelName = name;
            label->addressLabel = DC;
            label->next = NULL;
            if (rs)
                *rs = 0;/*success*/

            return label;
        }
        else
        {
            free (label);/*free memory and return NULL and failure if newLabel fail*/
            if (rs)
                *rs = -1;/*failure*/
            return label;/*return received pointer with NULL address */
        }
    }
    else
    {
        label->next = addToLabelTable (label->next, name, DC, type, rs);
        if (*rs)
            *rs = 0;/*success*/
        return label;
    }
}

/*check if there are not any label with same name
 and there is not any action name or directive command that identical in names
 Parameters:
 pointer to label list.
 name of label.
 Return:
 -1 if label is not valid.
 0 if label is valid.*/
int validLabel(label *list, char *labelName, int *rs)
{
    int i;

    action *actionTable = defineActionTable ();

    if (searchLabel (list, labelName) != NULL)
    {/*check if label name equal to any exist label name*/
        *rs = -1;/*TO Do: write the correct error code*/
        return -1;/*label is not valid*/
    }
    for (i = 0 ; i < 16 ; i++)
    {/*check if label name equal to any action name */

        if (strcmp (actionTable[i].actionName, labelName) == 0)
        {
            *rs = -1;/*TO Do: write the correct error code*/
            return -1;/*label is not valid*/
        }
    }/*check if label name equal to any register name*/
    if ((strcmp (labelName, "r0") == 0) || (strcmp (labelName, "r1") == 0) || (strcmp (labelName, "r2") == 0) ||
            (strcmp (labelName, "r3") == 0) || (strcmp (labelName, "r4") == 0) || (strcmp (labelName, "r5") == 0) ||
            (strcmp (labelName, "r6") == 0) || (strcmp (labelName, "r7") == 0) || (strcmp (labelName, "PSW") == 0))
    {
        *rs = -1;/*TO Do: write the correct error code*/
        return *rs;/*label is not valid*/
    }/*check if label name equal to any directive name*/
    if (((strcmp ("string", labelName) == 0)) || ((strcmp ("data", labelName) == 0)) ||
            ((strcmp ("entry", labelName) == 0)) || ((strcmp ("extern", labelName) == 0)))
    {
        *rs = -1;/*TO Do: write the correct error code*/
        return *rs;/*label is not valid*/

    }
    *rs = 0;
    return *rs;/*label is valid*/


}


/* allocate and initialize a new label;
   space for the label is obtained via malloc();
   return a pointer to the new label, NULL if no space available*/
label *newLabel()
{
    label *lbl;
    lbl = (label *) malloc (sizeof (label));
    if (lbl)
    {
        lbl->labelName = NULL;
        lbl->type = -1;
        lbl->next = NULL;
        lbl->addressLabel = -1;
        return lbl;
    }
    free (lbl);
    return NULL;
}


/*check if there any label with same name.
 Parameters:
 pointer to label list.
 name of label.
 Return:
 pointer to label if exist.
 NULL if not exist on list.*/
label *searchLabel(label *list, char *str)
{
    label *lbl = list;
    /*save the first name for loop condition*/



    if ((list == NULL) || (str == NULL) || (*str == 0))
    {/*check if all parameters are valid*/

        return NULL;
    }
    do
    {

        /*search loop*/
        if (lbl->labelName == NULL)
        {
            return NULL;
        }
        if (strcmp (lbl->labelName, str) == 0)
        {
            return lbl;
        }
        else
        {
            lbl = lbl->next;
        }

    } while (lbl != NULL);

    return NULL;/*label with same name is not exist*/
}

/*********************DATA TABLE SECTION**********************/

/* allocate and initialize a new data;
   space for the data is obtained via malloc();
   return a pointer to the new data, NULL if no space available*/
data *newData()
{
    data *dt;
    dt = (data *) malloc (sizeof (data));
    if (dt)
    {
        dt->type = -1;
        dt->address = -1;
        dt->binaryCode = NULL;
        dt->sourceCode = NULL;
        dt->lbl = NULL;
        dt->next = NULL;
        dt->sizeOfArray = -1;
        return dt;
    }
    free (dt);
    return NULL;
}


/*add data to data list if it contain valid values
 Parameters:
 pointer to data list (MULL if there is not list).
 name.
 DC value for data address.
 type of data (0 for string, 1 for numbers).
 report success flag.
 Return:
 pointer to new label on the list.
 report success flag 0 if success, else -1.
 */
data addToDataTable(data *dataTable, char *dataLabel, char *sourceCode, int address, int strOrNun, int *rs)
{
    data *dt;
    int arraySize = 0;

    if (strOrNun == 0)
    {/*check if data from type string*/
        if (verifyStringCommand (sourceCode, rs) == NULL)
        {
            *rs = -1;
            return *dataTable;
        }
        arraySize = strlen (verifyStringCommand (sourceCode, rs));
    }
    else if (strOrNun == 1)
    {/*check if data from type numbers*/
        if (verifyDataCommand (sourceCode, rs) == NULL)
        {
            *rs = -1;
            return *dataTable;
        }
        arraySize = verifyDataCommand (sourceCode, rs)[0];
    }

    if (dataTable == NULL)
    {/*empty data list*/
        dt = newData ();
        if (dt)
        {
            dt->lbl = dataLabel;
            dt->sourceCode = sourceCode;
            dt->address = address;
            dt->type = strOrNun;
            dt->binaryCode = buildDataWord (sourceCode, rs);
            dt->sizeOfArray = arraySize;
            dt->next = NULL;
            return *dataTable;
        }
        *rs = -1;
        free (dt);
        return *dataTable;
    }
    else
    {
        *dataTable->next = addToDataTable (dataTable, dataLabel, sourceCode, address, strOrNun, rs);
        if (rs)
        {
            rs = 0;
        }
        return *dataTable;
    }
}


/*********************COMMAND SECTION**********************/
/*this function add command and all operands and parameters to commands table */
command addToCommandTable(command *list, label *labelList, unsigned int address, char *sourceCode, int *rs)
{

    if ((sourceCode == NULL) || (*sourceCode == 0))
    {/*check if line is NULL or without value*/
        if (rs)
            *rs = -1;/*failure*/
        return *list;
    }
    if (getActionID (sourceCode) == -1)
    {
        *rs = 7;/*status 2 return error about un-exist action name*/
        return *list;
    }
    if (ifCommand (sourceCode, labelList, rs) != 1)
    {
        return *list;/*rs return the error code from function*/
    }
    if (list == NULL)
    {/*list is empty*/
        list = newCommand ();
        if (list != NULL)
        {
            list->decimalAddress = address;
            list->srcCode = sourceCode;
            list->wordAmount = amountOfWord (sourceCode, labelList);
            list->machineCode = buildWord (sourceCode, labelList, rs);
            if (rs)
                *rs = 0;/*success*/
            return *list;
        }
        free (list);/*free memory and return NULL and failure if newCommand fail*/
        if (rs)
            *rs = -1;/*failure*/
        return *list;
    }
    else
    {
        *list->next = addToCommandTable (list, labelList, address, sourceCode, rs);
        if (*rs)
            *rs = 0;/*success*/
        return *list;
    }
}

/* allocate and initialize a new command;
   space for the command is obtained via malloc();
   return a pointer to the new command, NULL if no space available*/
command *newCommand()
{
    command *cmd = (command *) malloc (sizeof (command));
    if (cmd)
    {
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
 * for action with 2 operands it return 2 if all of them are registers. else, return 3.
 * for jump action it return 3 if all of params are registers. else, return 4.*/
/*not checked*/
int amountOfWord(char *sourceCode, label *labelList)
{

    int actionCode;
    int *rs = 0;
    char *operandName[3];/*array for operands and params - cannot be more than 2 operands or 1 operand and 2 params */

    actionCode = getActionID (sourceCode);

    if (ifCommand (sourceCode, labelList, rs) != 1)
    {/*check if invalid command*/
        return -1;/*failure*/
    }
    if ((actionCode == 14) || (actionCode == 15))
    {/*check if rts or stop actions*/
        return 1;/*there is only first word for action*/

    }
    else if ((actionCode == 9) || (actionCode == 10) || (actionCode == 13))
    {/*check if jump addressing method*/
        operandName[1] = getFirstParam (sourceCode);
        operandName[2] = getSecondParam (sourceCode);

        if ((verifyOperand (actionCode, operandName[1], 2, labelList, rs) == REGISTER_METHOD) &&
                (verifyOperand (actionCode, operandName[2], 2, labelList, rs) == REGISTER_METHOD))
        {
            return 3;/*for jump addressing with 2 registers params. first word, label and 2 registers in the same word*/

        }
        else
        {
            return 4;/*for jump addressing with 2 params.first word, label and 2 params in 2 additional words*/
        }
    }
    operandName[0] = getFirstOperand (sourceCode, rs);
    operandName[1] = getSecondOperand (sourceCode);
    /*duplicate condition for check certainly that are only 1 operand */
    if ((operandName[0] != NULL) && (operandName[1] == NULL) || (operandName[1] != NULL) && (operandName[0] == NULL))
    {
        return 2;/*for action with 1 operand. first word with 1 operand word*/
    }
    else if ((verifyOperand (actionCode, operandName[0], 0, labelList, rs) == REGISTER_METHOD) &&
            (verifyOperand (actionCode, operandName[1], 1, labelList, rs) == REGISTER_METHOD))
    {
        return 2;/*for action with 2 registers operands.first word and 2 registers in the same word*/
    }
    else
    {
        return 3;/*for action with 2 operands. first word and 2 operand*/
    }
}

/*function get the buffer and search which action it contain.
 * return the action ID as int.
 * return -1 if is not matching to any action */
/*not checked*/
int getActionID(char *sourceCode)
{
    action *actionTable = defineActionTable ();
    int i, actionID;
    for (i = 0 ; i < 16 ; i++)
    {
        if (strstr (sourceCode, actionTable[i].actionName) != NULL)
        {
            actionID = actionTable[i].actionCode;
            return actionID;
        }
    }
    return -1;
}

/*function return the ARE code for relevant word
 * it get the buffer and label list.
 * return array with ARE values in cells respectively of amount Of Words*/
int *setARE(char *sourceCode, label *labelList)
{
    int actionCode = getActionID (sourceCode);
    int amountOfWords = amountOfWord (sourceCode, labelList);
    int i, *rs = 0;
    static int returnArrayCods[MAX_WORDS_PER_COMMAND];/*create static array to return the values*/
    returnArrayCods[MAX_WORDS_PER_COMMAND] = 0;/*zero the static array for reuse*/
    char *operandName;
    label *lbl;

    if (ifCommand (sourceCode, labelList, rs) != 1)
    {
        return NULL;
    }
    if (amountOfWords == 1)
    {/*word that contain only action and ARE should be 00*/
        returnArrayCods[0] = 0;
        return returnArrayCods;
    }

    for (i = 0 ; i < amountOfWords ; i++)
    {
        if (i == 0)
        {
            returnArrayCods[i] = 0;/*ARE for first word is always 00*/
        }
        /*ARE for word 2 and 3 in jump action*/
        if ((actionCode == 9) || (actionCode == 10) || (actionCode == 13))
        {
            operandName = getFirstOperand (sourceCode, rs);
            lbl = searchLabel (labelList, operandName);
            if (i == 1)
            {
                if (lbl != NULL)
                {
                    if (lbl->type == 2)
                    {/*check if external label and return 01 for ARE*/
                        returnArrayCods[i] = 1;
                    }
                    else
                    {/*operand label in jump action is always 10*/
                        returnArrayCods[i] = 2;
                    }
                }
            }/*parameters section*/
            if ((i == 2) || (i == 3))
            {
                if (amountOfWords == 3)
                {/*check if params are registers*/
                    returnArrayCods[i] = 0;/*ARE for registers is always 00*/
                }
                if (i == 2)
                {
                    operandName = getFirstParam (sourceCode);
                }
                else
                {
                    operandName = getSecondParam (sourceCode);
                }
                lbl = searchLabel (labelList, operandName);
                if (lbl != NULL)
                {
                    if (lbl->type == 2)
                    {/*check if external label param and return 01 for ARE*/
                        returnArrayCods[i] = 1;
                    }
                    else
                    {/*local or entry param label in jump action is always 10*/
                        returnArrayCods[i] = 2;
                    }
                }
                else
                {/*for immediate method and register the ARE are always 0*/
                    returnArrayCods[i] = 0;
                }
            }
        }/*ARE for word 2 and 3 in regular action*/
        if (i == 1)
        {
            operandName = getFirstOperand (sourceCode, rs);
        }
        else
        {
            operandName = getSecondOperand (sourceCode);
        }
        lbl = searchLabel (labelList, operandName);
        if (lbl != NULL)
        {
            if ((lbl->type == 3) || (lbl->type == 1))
            {/*check if entry or data label operand and return 10 for ARE*/
                returnArrayCods[i] = 2;
                if (lbl->type == 2)
                {/*check if external label param and return 01 for ARE*/
                    returnArrayCods[i] = 1;
                }
                else if (lbl->type == 0)
                {/*local  label action is  00*/
                    returnArrayCods[i] = 0;
                }
            }
            else
            {/*for immediate method and register the ARE are always 0*/
                returnArrayCods[i] = 0;
            }
        }
    }
    return returnArrayCods;
}


/*This function convert decimal numbers to binary and print it to the file output.
 * if you print a char, convert it to ascii decimal code like that:
 * char a = 'a'; int n = (int)a;*/
char *convertToBinary(int n, int sizeOfBits, int *rs)
{

    int c, d, count;
    char *pointer;

    if (n < HIGHEST_NEGATIVE_VALUE)
    {
        *rs = 21;
        return NULL;
    }
    else if (n > HIGHEST_POSITIVE_VALUE)
    {
        *rs = 20;
        return NULL;
    }
    count = 0;
    pointer = (char *) malloc ((size_t) (sizeOfBits + 1));

    if (pointer == NULL)
        exit (EXIT_FAILURE);

    for (c = (sizeOfBits - 1) ; c >= 0 ; c--)
    {
        d = n >> c;
        if (d & 1)
        {
            *(pointer + count) = 1 + '0';
        }
        else
        {
            *(pointer + count) = 0 + '0';
        }
        count++;
    }
    *(pointer + count) = '\0';

    return pointer;
}

/*function build word with only data and ARE filed.
 * it get buffer line, labels list, number of child word and status flag.
 * number of child word should be large then 0. 0 saved for first word.
 * return array with binary value*/
char *buildChildWord(char *buffer, label *labelList, int numOfChildWord, int *rs)
{
    int actionID = getActionID (buffer);
    int *ARE = setARE (buffer, labelList);
    char *strAfterConvert[WORD_LENGTH - 1] = {0};/*without ARE bits*/
    char *AREAfterConvert[3];
    static char returnStr[WORD_LENGTH + 1] = {0};
    char *firstOperandName = getFirstOperand (buffer, rs);
    char *secondOperandName = getSecondOperand (buffer);
    int i = 0, typeAction = 0, immediateValue = 0;
    label *lbl;

    if ((actionID == 9) || (actionID == 10) || (actionID == 13) && (numOfChildWord > 1))
    {
        firstOperandName = getFirstParam (buffer);
        secondOperandName = getSecondParam (buffer);
        typeAction = 2;
    }
    if ((numOfChildWord == 1) || ((typeAction == 2) && (numOfChildWord == 2)))/*for first operand or first param*/
    {
        if (verifyOperand (actionID, firstOperandName, typeAction, labelList, rs) == REGISTER_METHOD)
        {
            *strAfterConvert = registerWord (buffer, labelList, numOfChildWord, rs);
        }
        if (verifyOperand (actionID, firstOperandName, typeAction, labelList, rs) == LABEL_METHOD)
        {
            lbl = searchLabel (labelList, firstOperandName);
            *strAfterConvert = convertToBinary (lbl->addressLabel, 12, rs);
            strAfterConvert[13] = '\0';
        }
        if (verifyOperand (actionID, firstOperandName, typeAction, labelList, rs) == IMMEDIATE_METHOD)
        {
            immediateValue = charToInt (*firstOperandName);
            *strAfterConvert = convertToBinary (immediateValue, 12, rs);
        }
    }
    if ((numOfChildWord > 1) || (typeAction == 2))
    {
        if (typeAction != 2)
        {
            typeAction = 1;
        }
        if (verifyOperand (actionID, secondOperandName, typeAction, labelList, rs) == REGISTER_METHOD)
        {
            *strAfterConvert = registerWord (buffer, labelList, numOfChildWord, rs);
        }
        if (verifyOperand (actionID, secondOperandName, typeAction, labelList, rs) == LABEL_METHOD)
        {
            lbl = searchLabel (labelList, secondOperandName);
            *strAfterConvert = convertToBinary (lbl->addressLabel, 12, rs);
            strAfterConvert[13] = '\0';
        }
        if (verifyOperand (actionID, secondOperandName, typeAction, labelList, rs) == IMMEDIATE_METHOD)
        {
            immediateValue = charToInt (*secondOperandName);
            *strAfterConvert = convertToBinary (immediateValue, 12, rs);
        }
    }
    *AREAfterConvert = convertToBinary (ARE[numOfChildWord], 2, rs);
    for (i = 0 ; i < WORD_LENGTH + 1 ; i++)
    {
        if (i < 2)
        {/*set ARE bits*/
            returnStr[i] = *AREAfterConvert[i];
            continue;
        }
        if (i > 1)
        {
            returnStr[i] = *strAfterConvert[i];
            continue;
        }
    }
    returnStr[15] = '\0';
    return returnStr;
}

/*function to build word that contain rgister number if there is one register or union word for 2 registers*/
char *registerWord(char *buffer, label *labelList, int numOfChildWord, int *rs)
{
    int actionID = getActionID (buffer);
    char *strAfterConvert[WORD_LENGTH - 1] = {0};/*without ARE bits*/
    char *firstOperandName = getFirstOperand (buffer, rs);
    char *secondOperandName = getSecondOperand (buffer);
    int typeAction = 0;
    int registerNum1, registerNum2 = 0;

    if ((actionID == 9) || (actionID == 10) || (actionID == 13) && (numOfChildWord > 1))
    {
        firstOperandName = getFirstParam (buffer);
        secondOperandName = getSecondParam (buffer);
        typeAction = 2;
    }
    if ((numOfChildWord == 1) || (typeAction == 2))
    {/*REGISTERS SECTION*/
        if (verifyOperand (actionID, firstOperandName, typeAction, labelList, rs) == REGISTER_METHOD)
        {/*for src register*/
            for (registerNum1 = 0 ; registerNum1 < 8 ; registerNum1++)
            {/*search the src register number*/
                sprintf (*strAfterConvert, "%d", registerNum1);
                if (strstr (*strAfterConvert, firstOperandName) != NULL)
                {
                    break;
                }
            }
            *strAfterConvert = convertToBinary (registerNum1, 6, rs);
            strAfterConvert[7] = '\0';
        }
    }/*check if union the registers words or create word for one register*/
    if ((numOfChildWord > 2) || (verifyOperand (actionID, firstOperandName, 0, labelList, rs) == REGISTER_METHOD))
    {
        if (typeAction != 2)
        {
            typeAction = 1;
        }
        if (verifyOperand (actionID, secondOperandName, typeAction, labelList, rs) == REGISTER_METHOD)
        {/*for dst register search the src register number*/
            for (registerNum2 = 0 ; registerNum2 < 8 ; registerNum2++)
            {/*search the dst register number*/
                sprintf (*strAfterConvert, "%d", registerNum2);
                if (strstr (*strAfterConvert, firstOperandName) != NULL)
                {
                    break;
                }
            }
            /*create string with 12 bits for registers with cover to scenario with one register:
             * the values is 0 by default and if it is not register it fill with 0.
             * the reason to put the append string in second condition is because that if there
             * is legal register in the src operand, must be register in dst operand*/
            *strAfterConvert = strcat (convertToBinary (registerNum2, 6, rs), *strAfterConvert);
        }
    }
    return *strAfterConvert;
}

/*function get the buffer and labels list.
 * return words array with binary value */
char *buildWord(char *buffer, label *labelList, int *rs)
{
    int amountWords = amountOfWord (buffer, labelList);
    static char wordArray[MAX_WORDS_PER_COMMAND][WORD_LENGTH + 1] = {0};
    int actionID = getActionID (buffer);
    int *ARE = setARE (buffer, labelList);
    char *strAfterConvert;
    char *operandName;
    int i, j, q;

    for (i = 0 ; i < amountWords ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {/*set ARE to word string*/
            strAfterConvert = convertToBinary (ARE[i], 2, rs);
            /*strAfterConvert[3]='\0';*/
            wordArray[i][j] = strAfterConvert[j];
        }
        if (i == 0)
        {/*first word*/
            operandName = getFirstOperand (buffer, rs);
            for (j ; j < 4 ; j++)
            {/*set addressing method for dst operand */
                q = 0;
                if ((actionID == 9) || (actionID == 10) || (actionID == 13))
                {
                    strAfterConvert = convertToBinary (JUMP_METHOD, 2, rs);/*write addressing method 2 to dst filed*/
                    wordArray[i][j] = strAfterConvert[q];
                }
                else if (verifyOperand (actionID, operandName, 1, labelList, rs) == IMMEDIATE_METHOD)
                {
                    strAfterConvert = convertToBinary (IMMEDIATE_METHOD, 2, rs);/*write addressing method to dst filed*/
                    wordArray[i][j] = strAfterConvert[q];

                }
                else if (verifyOperand (actionID, operandName, 1, labelList, rs) == LABEL_METHOD)
                {
                    strAfterConvert = convertToBinary (LABEL_METHOD, 2, rs);/*write addressing method to dst filed*/
                    wordArray[i][j] = strAfterConvert[q];

                }
                else if (verifyOperand (actionID, operandName, 1, labelList, rs) == REGISTER_METHOD)
                {
                    strAfterConvert = convertToBinary (REGISTER_METHOD, 2, rs);/*write addressing method to dst filed*/
                    wordArray[i][j] = strAfterConvert[q];
                }
            }
            operandName = getSecondOperand (buffer);
            for (j ; j < 6 ; j++)
            {/*set addressing method for src operand */
                q = 0;
                if ((actionID == 9) || (actionID == 10) || (actionID == 13))
                {
                    strAfterConvert = convertToBinary (0, 2, rs);/*write 00 addressing method 2 to src filed*/
                    wordArray[i][j] = strAfterConvert[q];
                }
                else if (verifyOperand (actionID, operandName, 0, labelList, rs) == IMMEDIATE_METHOD)
                {
                    strAfterConvert = convertToBinary (IMMEDIATE_METHOD, 2, rs);/*write addressing method to dst filed*/
                    wordArray[i][j] = strAfterConvert[q];

                }
                else if (verifyOperand (actionID, operandName, 0, labelList, rs) == LABEL_METHOD)
                {
                    strAfterConvert = convertToBinary (LABEL_METHOD, 2, rs);/*write addressing method to dst filed*/
                    wordArray[i][j] = strAfterConvert[q];

                }
                else if (verifyOperand (actionID, operandName, 0, labelList, rs) == REGISTER_METHOD)
                {
                    strAfterConvert = convertToBinary (REGISTER_METHOD, 2, rs);/*write addressing method to dst filed*/
                    wordArray[i][j] = strAfterConvert[q];
                }
            }
            for (j ; j < 10 ; j++)
            {/*set action code*/
                q = 0;
                strAfterConvert = convertToBinary (actionID, 4, rs);/*write 00 addressing method 2 to src filed*/
                wordArray[i][j] = strAfterConvert[q];
            }
            if ((actionID == 9) || (actionID == 10) || (actionID == 13))
            {/*set params addressing method*/
                operandName = getFirstParam (buffer);
                for (j ; j < 12 ; j++)
                {/*set addressing method for first parameter */
                    q = 0;

                    if (verifyOperand (actionID, operandName, 2, labelList, rs) == IMMEDIATE_METHOD)
                    {
                        strAfterConvert = convertToBinary (IMMEDIATE_METHOD, 2, rs);
                        /*write addressing method to dst filed*/
                        wordArray[i][j] = strAfterConvert[q];

                    }
                    else if (verifyOperand (actionID, operandName, 2, labelList, rs) == LABEL_METHOD)
                    {
                        strAfterConvert = convertToBinary (LABEL_METHOD, 2, rs);
                        /*write addressing method to dst filed*/
                        wordArray[i][j] = strAfterConvert[q];

                    }
                    else if (verifyOperand (actionID, operandName, 2, labelList, rs) == REGISTER_METHOD)
                    {
                        strAfterConvert = convertToBinary (REGISTER_METHOD, 2, rs);
                        /*write addressing method to dst filed*/
                        wordArray[i][j] = strAfterConvert[q];
                    }
                }
                operandName = getSecondParam (buffer);
                for (j ; j < 14 ; j++)
                {/*set addressing method for second parameter */
                    q = 0;

                    if (verifyOperand (actionID, operandName, 2, labelList, rs) == IMMEDIATE_METHOD)
                    {
                        strAfterConvert = convertToBinary (IMMEDIATE_METHOD, 2, rs);
                        /*write addressing method to dst filed*/
                        wordArray[i][j] = strAfterConvert[q];

                    }
                    else if (verifyOperand (actionID, operandName, 2, labelList, rs) == LABEL_METHOD)
                    {
                        strAfterConvert = convertToBinary (LABEL_METHOD, 2, rs);
                        /*write addressing method to dst filed*/
                        wordArray[i][j] = strAfterConvert[q];

                    }
                    else if (verifyOperand (actionID, operandName, 2, labelList, rs) == REGISTER_METHOD)
                    {
                        strAfterConvert = convertToBinary (REGISTER_METHOD, 2, rs);
                        /*write addressing method to dst filed*/
                        wordArray[i][j] = strAfterConvert[q];
                    }
                }
            }
            wordArray[i][WORD_LENGTH] = '\0';/*end of string*/
        }
        if (i > 0)
        {
            strAfterConvert = buildChildWord (buffer, labelList, i, rs);
            for (j = 0 ; j < WORD_LENGTH ; j++)
            {
                wordArray[i][j] = strAfterConvert[j];
            }
        }
    }
    return *wordArray;
}

/*function get source code line and status flag and return array with all numbers as binary with width of 14 bits*/
char *buildDataWord(char *buffer, int *rs)
{
    int strOrNun = -1;
    int *data = 0;
    char *str = NULL;
    char charToConvert;
    int i, j, numOfCells = 0;
    char *strAfterConvert;
    static char returnArray[BUFFER_SIZE][WORD_LENGTH + 1] = {0};

    /*check if data from type string*/
    if (verifyStringCommand (buffer, rs) != NULL)
    {
        str = verifyStringCommand (buffer, rs);
        numOfCells = strlen (str);
        strOrNun = 0;
    }/*check if data from type numbers*/
    else if (verifyDataCommand (buffer, rs) != NULL)
    {
        data = verifyDataCommand (buffer, rs);
        numOfCells = data[0];
        strOrNun = 1;
    }
    else
    {
        return NULL;
    }

    if ((strOrNun == 0) && (str != NULL))/*string array*/
    {
        for (i = 0 ; i < numOfCells ; i++)
        {
            charToConvert = str[i];
            int n = (int) charToConvert;
            strAfterConvert = convertToBinary (n, 14, rs);
            for (j = 0 ; j < WORD_LENGTH ; j++)
            {
                returnArray[i][j] = strAfterConvert[j];
            }
            returnArray[i][WORD_LENGTH] = '\0';
        }
    }
    if (strOrNun == 1)/*data array*/
    {
        for (i = 1 ; i == numOfCells ; i++)/*start from 1. cell 0 contain the numbers of cells*/
        {
            strAfterConvert = convertToBinary (data[i], 14, rs);
            for (j = 0 ; j < WORD_LENGTH ; j++)
            {
                returnArray[i - 1][j] = strAfterConvert[j];
            }
            returnArray[i][WORD_LENGTH] = '\0';
        }
    }
    return *returnArray;
}

/*this function save on homogeneous in error contact.
 * get row number and error id
 * and print the error with line number*/
int errorPrint(int errId, unsigned int row)
{
    switch (errId)
    {
        /*labels errors*/
        case 1:
            fprintf (stderr, "Line: %d , invalid label - declared few times or not declared at all", row);
            break;
        case 2:
            fprintf (stderr, "Line: %d , invalid label name - saved word", row);
            break;
        case 3:
            fprintf (stderr, "Line: %d , warning - label does not start in first column", row);
            break;
        case 4:
            fprintf (stderr, "Line: %d , local label cannot be declared as external", row);
            break;
        case 5:
            fprintf (stderr, "Line: %d , label is already designated as external", row);
            break;
        case 6:
            fprintf (stderr, "Line: %d , invalid label name - name large", row);
            break;
            /*command errors*/
        case 7:
            fprintf (stderr, "Line: %d , undefined instruction", row);
            break;
        case 8:
            fprintf (stderr, "Line: %d , number of arguments is not valid", row);
            break;
        case 9:
            fprintf (stderr, "Line: %d , need to set only 2 parameters ", row);
            break;
        case 10:
            fprintf (stderr, "Line: %d , invalid operand", row);
            break;
        case 11:
            fprintf (stderr, "Line: %d , invalid source operand (label)", row);
            break;
        case 12:
            fprintf (stderr, "Line: %d , invalid source operand (register)", row);
            break;
        case 13:
            fprintf (stderr, "Line: %d , invalid source operand (immediate)", row);
            break;
        case 14:
            fprintf (stderr, "Line: %d , invalid target operand (label)", row);
            break;
        case 15:
            fprintf (stderr, "Line: %d , invalid target operand (register)", row);
            break;
        case 16:
            fprintf (stderr, "Line: %d , invalid target operand (immediate)", row);
            break;
        case 17:
            fprintf (stderr, "Line: %d , invalid argument (immediate too large)", row);
            break;
            /*directive errors*/
        case 18:
            fprintf (stderr, "Line: %d , data array contain illegal values", row);
            break;
        case 19:
            fprintf (stderr, "Line: %d , incorrect string array", row);
            break;
        case 20:
            fprintf (stderr, "Line: %d , data overflow (positive value too large to fit in 14 bits)", row);
            break;
        case 21:
            fprintf (stderr, "Line: %d , data overflow (negative value too large to fit in 14 bits)", row);
            break;
        case 22:
            fprintf (stderr, "Line: %d , missing argument in directive", row);
            break;
        case 23:
            fprintf (stderr, "Line: %d , undefined directive", row);
            break;
        default:
            return -1;/*failure*/
    }
}


