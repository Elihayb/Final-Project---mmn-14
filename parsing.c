#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "utilities.h"
#include "Data.h"

#define LABEL_SIZE 32
#define STRING_SIZE 81

/* a function that returns 1 if the line in the buffer is a comment */
int ifComment(char *buffer)
{
    if (buffer != NULL)
        return (buffer[0] == ';') ? 1 : 0;
}

/* a function that checks if there is a label and if so the function returns the label and NULL otherwise */
char *ifThereIsLabel(char *buffer, int *RS)                                            /* RS variable stands for error code. */
{
    if (strchr (buffer, ':') != NULL)
    {
        int i, res = 0, spaceIndex = 0;                               /* res variable 1 if there is label and 0 otherwise */
        static char label[LABEL_SIZE] = {'\0'};
        label[0] = '\0';
        memset (label, 0, LABEL_SIZE);
        if (buffer[0] == ' ' || !(isalpha (buffer[0])))                                       /* testing the first column */
        {
            *RS = 3;
            return NULL;
        }
        for (i = 0 ; i < strlen (buffer) ; i++)                 /* looking for the ':' character and the space character  */
        {
            if (buffer[i] == ' ')
                spaceIndex = i;
            if (buffer[i] == ':')
                break;
        }                                                                         /* i stands for the ':' character index */
        if (spaceIndex > i || spaceIndex == 0)
            res = 1;
        if (i > 31)
        {
            *RS = 6;
            return NULL;
        }
        if (res == 1)
        {
            int j = 0;
            while (buffer[j] != ':')
            {
                if ((isalpha (buffer[j])) || (isdigit (buffer[j])))
                {          /* making sure the label consist of characters and numbers only */
                    label[j] = buffer[j];
                }
                else if (buffer[j] == '\n')
                {
                    break;
                }
                else
                {
                    *RS = 2;
                    return NULL;
                }
                j++;
            }
            return label;                                   /* the function returns the label (without the ':' character) */
        }
        else
        {
            return NULL;
        }
    }
    else
        return NULL;
}

/* this function checks if a label is legal. the function returns 0 if not legal and 1 otherwise. */
int ifLabel(char *string)
{
    char *index = string;
    while (index[0] != '\0')
    {
        if (index[0] == '\0')
            break;
        if (!(isalpha (index[0])) && !(isdigit (index[0])))                         /* making sure the label consist of characters and numbers only */
            return 0;
        index++;
    }
    return 1;
}

/* a function that checks if there is directive and if so it returns the type and NULL otherwise */
char *ifDirective(char *buffer, int *RS)
{
    int label_index, i, dot_index;                                              /* RS variable stands for error code. */
    static char directive[20] = {'\0'};
    char *index = buffer;
    directive[0] = '\0';
    if (ifThereIsLabel (buffer, RS) != NULL)                                                     /* in case there is a label */
    {
        label_index = char_index (buffer, ':') + 1;
        dot_index = char_index (buffer, '.');
        for (i = label_index ; i < dot_index ; i++)                    /* after the label there should be only spaces */
        {                                                                                  /* until the '.' character */
            if (buffer[i] != ' ')
            {
                *RS = 23;
                return NULL;
            }
        }
        getString (buffer, directive, (dot_index + 1));                                      /* storing the directive */
        if ((strcmp (directive, "data") == 0) || (strcmp (directive, "string") == 0))
            return directive;                                   /* testing the type of the directive and returning it */
        else
        {
            *RS = 23;
            return NULL;
        }
    }
    else                                                                                      /* if there is no label */
    {
        index = skipSpcaes (index);
        if (index[0] != '.')                   /* if there is no label then the line should start with '.' character */
        {
            *RS = 23;
            return NULL;
        }
        else
            getString (index, directive, 1);                                                /* storing the directive */
        if ((strcmp (directive, "data") == 0) || (strcmp (directive, "string") == 0))
            return directive;                                   /* testing the type of the directive and returning it */
        else
        {
            return NULL;
        }
    }
}

/* a function that checks the syntax of global directives. */
/* on success the function returns a string with the label name */
/* and the type of the directive: 0 for .entry and 1 for .extern */
char *ifGlobalDirective(char *buffer, int *RS)
{
    int i = 0;                                                                  /* RS variable stands for error code. */
    char global_directive[20] = {'\0'}, type = '*';                                  /* string to store the directive */
    static char label[LABEL_SIZE] = {'\0'};                                              /* string to store the label */
    char *index = buffer, *lblptr = label;                                                                    /* pointer to the buffer */
    memset (label, 0, LABEL_SIZE);/*remove all values from static array*/
    if (ifThereIsLabel (buffer, RS) == NULL)                               /* in case there is no label before the directive */
    {
start:
        index = skipSpcaes (index);
        if (index[0] != '.')
        {
            return NULL;
        }
        index++;                                   /* making the index pointer to point to the start of the directive */
        while (index[0] != ' ')                                                /* storing the global directive string */
        {
            global_directive[i] = index[0];
            i++;
            index++;
        }
        if (strcmp ("entry", global_directive) == 0)                             /* testing the type of the directive */
            type = '0';
        else if (strcmp ("extern", global_directive) == 0)
            type = '1';
        if (!((type == '0') || (type == '1')))                      /* if it is not a global directive returning NULL */
        {
            *RS = 23;
            return NULL;
        }
        index = skipSpcaes (index);
        while (index[0] != '\0' && strcmp (index, "\\n") != 0)
        {
            if (isalpha (index[0]) || isdigit (index[0]))
            {
                lblptr[0] = index[0];
                lblptr++, index++;
            }
            else
                index++;
        }                                                                                         /* storing the label */
        if ((ifLabel (label) != 1))                                        /* if the label isn't legal returning NULL */
        {
            *RS = 2;
            return NULL;
        }
        else
            label[strlen (label)] = type;                         /* replacing the : char with the directive type */
        return label;                                            /* returning the label along with the directive type */
    }
    else                                                             /* in case there is a label before the directive */
    {
        /*fprintf (stderr, "Warning: Label at the beginning of the line.\n");*/                      /* sending a warning */
        index = nextStr (index);
        goto start;                             /* once the index skipped the label we proceed as we wood in the case */
    }                                      /* there was no label at the beginning and jumping back to the start label */
}

/* a function the checks the syntax of the .data command and returns array with the numeric parameters on success */
/* and NULL of failure, the first element of the array is the number of its elements */
int *verifyDataCommand(char *buffer, int *RS)
{                                                                               /* RS variable stands for error code. */
    char *index = buffer, *temp;                                                       /* index pointer to the buffer */
    static int *arr;                                                                 /* array to store the parameters */
    int *arrptr;
    int numOfElements = 0;
    if ((ifDirective (buffer, RS) != NULL) && (strcmp ("data", ifDirective (buffer, RS)) == 0)) /* testing  directive */
    {
        index = strstr (buffer, "data");                           /* advancing the index to point to the data string */
        index = nextStr (index);                                            /* advancing the index to the next string */
        temp = index;
        while (temp[0] != '\0')
        {
            skipSpcaes (temp);
            if (isdigit (temp[0]))
                numOfElements++;
            temp++;
        }
        arr = malloc ((numOfElements + 1) * sizeof (int));
        arrptr = arr;
        arr[0] = numOfElements;
        arrptr++;
        while (index[0] != '\0')
        {
            skipSpcaes (index);                                             /* making the index skip the white spaces */
            if (isdigit (index[0]))                                                        /* testing the first value */
            {
                arrptr[0] = charToInt (index[0]);     /* converting the char number to integer and storing the number */
                arrptr++;                                                                         /* in the arr array */
                index++;
                index = skipSpcaes (index);
                if (index[0] == '\0')
                    return arr;
                else if (index[0] != ',')                            /* making sure there is , char after each number */
                {
                    *RS = 18;
                    return NULL;
                }
            }
            else if (index[0] == ',')                         /* going to the next number and storing it in the array */
            {
                index++;
                index = skipSpcaes (index);
                if (!(isdigit (index[0])))
                {
                    *RS = 18;
                    return NULL;
                }
            }
        }
    }
    else
        return NULL;
    return arr;
}

/* a function the checks the syntax of the .string command and returns the string parameter on success */
/* or NULL on failure */
char *verifyStringCommand(char *buffer, int *RS)
{
    static char string[STRING_SIZE] = {'\0'};                                   /* RS variable stands for error code. */
    char tmp[STRING_SIZE] = {'\0'};
    char *index = buffer, *strptr = string, *tmpptr = tmp;             /* ptr to  buffer, ptr to  string, ptr to  tmp */
    if ((ifDirective (buffer, RS) != NULL) && (strcmp ("string", ifDirective (buffer, RS)) == 0)) /*testing  directive*/
    {
        index = strstr (buffer, "string");                                 /* making the index point to the directive */
        index = nextStr (index);                           /* making the index point to the next string in the buffer */
        strcpy (tmp, index);                                                   /* storing the string parameter in tmp */
        if (tmp[0] == '\"' && tmp[strlen (tmp) == '\"'])                                 /* testing the string syntax */
        {
            while (tmpptr[0] != '\0')
            {
                if (tmpptr[0] != '\"')                      /* storing parameter in the string in the string variable */
                {
                    strptr[0] = tmpptr[0];
                    strptr++;
                }
                tmpptr++;
            }
            return string;                                                          /* returning the string parameter */
        }
        else                                                                       /* retuning NULL on syntax failure */
        {
            *RS = 19;
            return NULL;
        }
    }
    else                                                                        /* retuning NULL on directive failure */
    {
        *RS = 23;
        return NULL;
    }
}


int verifyOperand(int actionID, char *operandName, int dstOrSrcFlag, label *labelTable, int *rs)
{
    *rs = 0;
    label *lbl;
    int i, operand;
    action *actionTable = defineActionTable ();
    lbl = searchLabel (labelTable, operandName);
    if (operandName == NULL)
    {
        return -1;
    }

    if (lbl != NULL)
    {/*operand is label*/
        if ((dstOrSrcFlag == 0) || (dstOrSrcFlag == 2))
        {/*check legal method for source operand*/
            if ((actionID == 9) || (actionID == 10) || (actionID == 13))
            {
                if (strstr (actionTable[actionID].legalMethodOprDst, "1") != NULL)
                {/*verify if label is legal operand*/
                    *rs = 0;
                    return LABEL_METHOD;/*valid operand*/
                }
            }
            if ((strstr (actionTable[actionID].legalMethodOprSrc, "1") != NULL) || (dstOrSrcFlag == 2))
            {/*verify if label is legal operand*/
                *rs = 0;
                return LABEL_METHOD;/*valid operand*/
            }
            else
            {
                *rs = 11;
                return -1;
            }
        }
        else if (dstOrSrcFlag == 1)
        {/*check legal method for destination operand*/
            if ((strstr (actionTable[actionID].legalMethodOprDst, "1") != NULL))
            {/*verify if label is legal operand*/
                *rs = 0;
                return LABEL_METHOD;/*valid operand*/
            }
            else
            {
                *rs = 14;
                return -1;
            }
        }
    }
    /*check if operand name equal to any register name*/
    if ((strcmp (operandName, "r0") == 0) || (strcmp (operandName, "r1") == 0) || (strcmp (operandName, "r2") == 0) ||
            (strcmp (operandName, "r3") == 0) || (strcmp (operandName, "r4") == 0) || (strcmp (operandName, "r5") == 0) ||
            (strcmp (operandName, "r6") == 0) || (strcmp (operandName, "r7") == 0))
    {
        if (dstOrSrcFlag == 0 || (dstOrSrcFlag == 2))
        {/*check legal method for source operand*/
            if ((strstr (actionTable[actionID].legalMethodOprSrc, "3") != NULL) || (dstOrSrcFlag == 2))
            {/*verify if register is legal operand*/
                *rs = 0;
                return REGISTER_METHOD;/*valid operand*/
            }
            else
            {
                *rs = 12;
                return -1;
            }
        }
        else if (dstOrSrcFlag == 1)
        {/*check legal method for destination operand*/
            if ((strstr (actionTable[actionID].legalMethodOprDst, "3") != NULL))
            {/*verify if register is legal operand*/
                *rs = 0;
                return REGISTER_METHOD;/*valid operand*/
            }
            else
            {
                *rs = 15;
                return -1;
            }
        }
    }
    if (atoi (operandName) != 0)
    {/*check if immediate is legal operand*/
        if ((dstOrSrcFlag == 0) || (dstOrSrcFlag == 2))
        {/*check legal method for source operand*/
            if ((strstr (actionTable[actionID].legalMethodOprSrc, "0") != NULL) || (dstOrSrcFlag == 2))
            {/*verify if immediate is legal operand*/
                *rs = 0;
                return IMMEDIATE_METHOD;/*valid operand*/
            }
            else
            {
                *rs = 13;
                return -1;
            }
        }
        else if (dstOrSrcFlag == 1)
        {/*check legal method for destination operand*/
            if ((strstr (actionTable[actionID].legalMethodOprDst, "0") != NULL))
            {/*verify if immediate is legal operand*/
                *rs = 0;
                return IMMEDIATE_METHOD;/*valid operand*/
            }
            else
            {
                *rs = 16;
                return -1;
            }
        }

    }
    *rs = 10;
    return -1;
}

/* a function that returns the first operand of an action and NULL if there is not a proper action */
char *getFirstOperand(char *buffer, int *rs)
{
    static char operand[MAX_LABEL];
    char *index = NULL;
    char *opIndex = operand;                                                       /* pointer to the operand variable */
    memset (operand,0,MAX_LABEL);
    action *acn = defineActionTable ();                                /* variable that contains all the action names */
    int i = 0;
    for (i = 0 ; i < 16 ; i++)                                                           /* searching for the command */
    {
        if (strstr (buffer, acn[i].actionName) != NULL)
        {
            index = strstr (buffer, acn[i].actionName);
            break;
        }
    }
    if (index == NULL)
    {
        *rs = 7;
        return NULL;
    }
    index = nextStr (index);
    if ((strcmp (acn[i].actionName, "jmp") == 0) || (strcmp (acn[i].actionName, "bne") == 0) || (strcmp (acn[i].actionName, "jsr") == 0))
    {                                                               /* storing the command  and returning the command */
        while (index[0] != EOF && index[0] != ' ')                                              /* for type 2 actions */
        {
            if (index[0] == '(')
                break;
            else
            {
                if (index[0] != '#')
                {
                    opIndex[0] = index[0];
                    opIndex++;
                    index++;
                }
                else
                    index++;
            }
        }
        return operand;
    }
    while (index[0] != '\0' && index[0] != ' ')                      /* storing the command  and returning the command */
    {
        if (index[0] == ',')
            break;
        else
        {
            if (index[0] != '#')
            {
                opIndex[0] = index[0];
                opIndex++;
                index++;
            }
            else
                index++;
        }
    }
    return operand;
}

/* a function that returns the first operand of an action and NULL if there is no second operand */
char *getSecondOperand(char *buffer)
{
    static char operand[MAX_LABEL];
    char *index = NULL;
    char *opIndex = operand;                                                       /* pointer to the operand variable */
    operand[0] = '\0';
    index = strstr (buffer, ",");                                                      /* pointing to the , character */
    memset (operand,0,MAX_LABEL);
    if (index == NULL)                                                                  /* if there is no , character */
        return NULL;
    index++;
    while (index[0] != '\0')                                                     /* storing and returning the operand */
    {
        if (index[0] != ' ' && index[0] != '#')
        {
            opIndex[0] = index[0];
            opIndex++;
            index++;
        }
        else
            index++;
    }
    return operand;
}

/* a function that returns the first param of an action and NULL if there is no  param */
char *getFirstParam(char *buffer)
{
    static char param[MAX_LABEL];
    char *index = NULL;
    char *opIndex = param;                                                         /* pointer to the operand variable */
    memset (param,0,MAX_LABEL);
    index = strstr (buffer, "(");                                                      /* pointing to the , character */
    if (index == NULL)                                                                  /* if there is no , character */
        return NULL;
    index++;
    index = skipSpcaes (index);
    while (index[0] != EOF)                      /* storing the command  and returning the command */
    {
        if (index[0] == ',')
            break;
        else
        {
            if (index[0] != '#' && index[0] != ' ' && index[0] != ')')
            {
                opIndex[0] = index[0];
                opIndex++;
                index++;
            }
            else
                index++;
        }
    }
    return param;
}

/* a function that returns the second param of an action and NULL if there is no first param */
char *getSecondParam(char *buffer)
{
    static char param[MAX_LABEL];
    char *temp;
    int i=0;
    memset (param,0,MAX_LABEL);
    if (getFirstParam (buffer) == NULL)                                                 /* if there is no first param */
        return NULL;
    temp = getSecondOperand (buffer);
    if (temp != NULL)
    {
        temp[strlen (temp) - 1] = '\0';
        /*elihay: this while remove all irrelevant letters (like ')' or blank letters)*/
        while((isalpha (temp[0]))||(isdigit (temp[0]))){
            param[i]=temp[0];
            temp++;
            i++;
        }
        param[i]='\0';
    }/*end of elihay section*/
    return param;
}

int ifCommand(char *buffer, label *labelList, int *rs)
{
    *rs=0;
    char command[BUFFER_SIZE] = {'\0'};
    char *index = buffer, *firstParam = NULL, *secondParam = NULL;
    int actionId;
    if (ifThereIsLabel (buffer, rs) != NULL)
        index = nextStr (index);
    index = skipSpcaes (index);
    getString2 (index, command, ' ');
    actionId = getActionID (command);
    if ((strcmp (command, "jmp") == 0) || (strcmp (command, "jsr") == 0) || (strcmp (command, "bne") == 0))
    {
        index = nextStr2 (index);
        index = skipSpcaes (index);
        firstParam = getFirstParam (index);
        secondParam = getSecondParam (index);
        if (firstParam != NULL && secondParam != NULL)
        {
            while (index[0] != ')')
            {
                if (index[0] == ' ')
                    return 0;                                                             /* spaces between arguments */
                index++;
            }
            if (secondParam[0] == '\0')
                return 0;
            verifyOperand (actionId, firstParam, 2, labelList, rs);
            if (*rs != 0)
                return 0;                                                                     /* error on first param */
            verifyOperand (actionId, secondParam, 2, labelList, rs);
            if (*rs != 0)
                return 0;
        }
        verifyOperand (actionId, getFirstOperand (buffer, rs), 1, labelList, rs);
        if (*rs != 0)
            return 0;                                                                                /* operand error */

    }
    else if ((strcmp (command, "mov") == 0) || (strcmp (command, "cmp") == 0) || (strcmp (command, "add") == 0) || (strcmp (command, "sub") == 0) ||
            (strcmp (command, "lea") == 0))
    {
        firstParam = getFirstOperand (index, rs);
        secondParam = getSecondOperand (index);
        if (secondParam == NULL)                                                   /* in case there is only 1 operand */
            return 0;
        verifyOperand (actionId, firstParam, 0, labelList, rs);
        if (*rs != 0)
            return 0;
        verifyOperand (actionId, firstParam, 1, labelList, rs);
        if (*rs != 0)
            return 0;
    }
    else if ((strcmp (command, "not") == 0) || (strcmp (command, "clr") == 0) || (strcmp (command, "inc") == 0) || (strcmp (command, "dec") == 0) ||
            (strcmp (command, "red") == 0) || (strcmp (command, "prn") == 0))
    {
        if (getSecondOperand (index) != NULL)
            return 0;                                                         /* in case there is more then 1 operand */
        verifyOperand (actionId, getFirstOperand (buffer, rs), 1, labelList, rs);
        if (*rs != 0)
            return 0;
    }
    else if ((strcmp (command, "rts") == 0) || (strcmp (command, "stop") == 0))
    {
        index = nextStr2 (index);
        while (index[0] != '\0')
        {
            if (index[0] != ' ')
                return 0;                                             /* in case there is something after the command */
            index++;
        }
    }
    else
        return 0;                                                                                     /* failure :-*( */
    return 1;                                                                                           /* success!!! */
}
