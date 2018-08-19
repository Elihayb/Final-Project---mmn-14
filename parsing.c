#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"
#include "Data.h"

#define LABEL_SIZE 32
#define STRING_SIZE 81

/* a function that returns 1 if the line in the buffer is a comment */
int ifComment(char *buffer)
{
    return (buffer[0] == ';') ? 1 : 0;
}

/* a function that checks if there is a label and if so the function returns the label and NULL otherwise */
char *ifLabel(char *buffer, int *RS)                                            /* RS variable stands for error code. */
{
    int i, res = 0, spaceIndex = 0;                               /* res variable 1 if there is label and 0 otherwise */
    static char label[LABEL_SIZE] = {'\0'};
    label[0] = '\0';
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
            if ((isalpha (buffer[j])) ||
                    (isdigit (buffer[j])))            /* making sure the label consist of characters and numbers only */
                label[j] = buffer[j];
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
        *RS = 6;
        return NULL;
    }
}

/* a function that checks if there is directive and if so it returns the type and NULL otherwise */
char *ifDirective(char *buffer, int *RS)
{
    int label_index, i, dot_index, j = 0;                                       /* RS variable stands for error code. */
    static char directive[20] = {'\0'};
    directive[0] = '\0';
    if (ifLabel (buffer, RS) != NULL)                                                     /* in case there is a label */
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
        if (buffer[0] != '.')                   /* if there is no label then the line should start with '.' character */
        {
            *RS = 23;
            return NULL;
        }
        else
            getString (buffer, directive, 1);                                                /* storing the directive */
        if ((strcmp (directive, "data") == 0) || (strcmp (directive, "string") == 0))
            return directive;                                   /* testing the type of the directive and returning it */
        else
        {
            *RS = 23;
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
    char *index = buffer;                                                                    /* pointer to the buffer */
    if (ifLabel (buffer, RS) == NULL)                               /* in case there is no label before the directive */
    {
start:
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
        while (index[0] == ' ')                                    /* advancing the index pointer to the label string */
            index++;
        strcpy (label, index);                                                                   /* storing the label */
        label[strlen (label)] = ':';                    /* adding the : char so the label can be checked with ifLabel */
        if (ifLabel (label, RS) == NULL)                                   /* if the label isn't legal returning NULL */
        {
            *RS = 2;
            return NULL;
        }
        else
            label[strlen (label) - 1] = type;                         /* replacing the : char with the directive type */
        return label;                                            /* returning the label along with the directive type */
    }
    else                                                             /* in case there is a label before the directive */
    {
        fprintf (stderr, "Warning: Label at the beginning of the line.\n");                      /* sending a warning */
        while (index[0] != ' ')                       /* making the index pointer to skip the label and point to the  */
            index++;                                                                    /* beginning of the directive */
        while (index[0] == ' ')
            index++;
        goto start;                             /* once the index skipped the label we proceed as we wood in the case */
    }                                      /* there was no label at the beginning and jumping back to the start label */
}

/* a function the checks the syntax of the .data command and returns array with the numeric parameters on success */
/* and NULL of failure */
int *verifyDataCommand(char *buffer, int *RS)
{                                                                               /* RS variable stands for error code. */
    char *index = buffer;                                                              /* index pointer to the buffer */
    static int arr[10];                                                              /* array to store the parameters */
    int *arrptr = arr;                                                                    /* pointer to the arr array */
    if ((ifDirective (buffer, RS) != NULL) && (strcmp ("data", ifDirective (buffer, RS)) == 0)) /* testing  directive */
    {
        index = strstr (buffer, "data");                           /* advancing the index to point to the data string */
        index = nextStr (index);                                            /* advancing the index to the next string */
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
    label *lbl;
    action *actionTable = defineActionTable ();
    lbl = searchLabel (labelTable, operandName);
    if (lbl != NULL)
    {/*operand is label*/
        if ((dstOrSrcFlag == 0) || (dstOrSrcFlag == 2))
        {/*check legal method for source operand*/
            if ((strstr (actionTable[actionID].legalMethodOprSrc, "1") != NULL) || (dstOrSrcFlag == 2))
            {/*verify if label is legal operand*/
                return *rs = 0;/*valid operand*/
            }
            else
            {
                *rs = -1;
                return *rs;
            }
        }
        else if (dstOrSrcFlag == 1)
        {/*check legal method for destination operand*/
            if ((strstr (actionTable[actionID].legalMethodOprDst, "1") != NULL))
            {/*verify if label is legal operand*/
                return *rs = 0;/*valid operand*/
            }
            else
            {
                *rs = -1;
                return *rs;
            }
        }
    }
    /*check if operand name equal to any register name*/
    if ((strcmp (operandName, "r0") == 0) || (strcmp (operandName, "r1") == 0) || (strcmp (operandName, "r2") == 0) ||
            (strcmp (operandName, "r3") == 0) || (strcmp (operandName, "r4") == 0) ||
            (strcmp (operandName, "r5") == 0) || (strcmp (operandName, "r6") == 0) || (strcmp (operandName, "r7") == 0))
    {
        if (dstOrSrcFlag == 0 || (dstOrSrcFlag == 2))
        {/*check legal method for source operand*/
            if ((strstr (actionTable[actionID].legalMethodOprSrc, "3") != NULL) || (dstOrSrcFlag == 2))
            {/*verify if register is legal operand*/
                return *rs = 0;/*valid operand*/
            }
            else
            {
                *rs = -1;
                return *rs;
            }
        }
        else if (dstOrSrcFlag == 1)
        {/*check legal method for destination operand*/
            if ((strstr (actionTable[actionID].legalMethodOprDst, "3") != NULL))
            {/*verify if register is legal operand*/
                return *rs = 0;/*valid operand*/
            }
            else
            {
                *rs = -1;
                return *rs;
            }
        }
    }
    if (isdigit ((unsigned char) *operandName) != 0)
    {/*check if immediate is legal operand*/
        if ((dstOrSrcFlag == 0) || (dstOrSrcFlag == 2))
        {/*check legal method for source operand*/
            if ((strstr (actionTable[actionID].legalMethodOprSrc, "0") != NULL) || (dstOrSrcFlag == 2))
            {/*verify if immediate is legal operand*/
                return *rs = 0;/*valid operand*/
            }
            else
            {
                *rs = -1;
                return *rs;
            }
        }
        else if (dstOrSrcFlag == 1)
        {/*check legal method for destination operand*/
            if ((strstr (actionTable[actionID].legalMethodOprDst, "0") != NULL))
            {/*verify if immediate is legal operand*/
                return *rs = 0;/*valid operand*/
            }
            else
            {
                *rs = -1;
                return *rs;
            }
        }

    }
}

int ifCommand (char *sourceCode, int *rs){
    return 0;
}

char *getFirstOperand(char *buffer,int *rs){
    static char p[4] = "abc";
    return p;
}

char *getSecondOperand(char *buffer,int *rs){
    static char p[4] = "abc";
    return p;
}

char *getFirstParam(char *buffer,int *rs){
    static char p[4] = "abc";
    return p;
}

char *getSecondParam(char *buffer,int *rs){
    static char p[4] = "abc";
    return p;
}