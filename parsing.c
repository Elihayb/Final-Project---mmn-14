#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LABEL_SIZE 32

int matchingBrackets(char *buffer)
{
    int lcount = 0, rcount = 0, i;
    for (i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] == '(')               /* counting left brackets */
            lcount++;
        if (buffer[i] == ')')               /* counting right brackets */
            rcount++;
    }
    if (lcount - rcount == 0)               /* checking if the number of left brackets is equal to the left */
        return 0;                           /* returning 0 if yes and 1 otherwise */
    else
        return 1;
}

void getString(char *buffer, char *string, int startIndex)
{
    int j = 0;
    while (buffer[startIndex] != ' ')
    {
        string[j] = buffer[startIndex];
        j++;
        startIndex++;
    }
}

int char_index(char *buffer, char chr) /* a function that returns the index of a character in a string */
{
    int i;
    for (i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] == chr)
            break;
    }
    return i;
}

int ifComment(char *buffer)                     /* a function that returns 1 if the line in the buffer is a comment */
{
    return (buffer[0] == ';') ? 1 : 0;
}

char *ifLabel(char *buffer)
{                            /* a function that checks if there is a label and if so the function returns the label */
    int i, res = 0, spaceIndex = 0;             /* res variable 1 if there is label and 0 otherwise */
    static char label[LABEL_SIZE] = {'\0'};
    label[0] = '\0';
    if (buffer[0] == ' ' || !(isalpha(buffer[0])))      /* testing the first column */
    {
        return NULL;
    }
    for (i = 0; i < strlen(buffer); i++)                /* looking for the ':' character and the space character  */
    {
        if (buffer[i] == ' ')
            spaceIndex = i;
        if (buffer[i] == ':')
            break;
    }                                               /* i stands for the ':' character index */
    if (spaceIndex > i || spaceIndex == 0)
        res = 1;
    if (i > 31)
        return NULL;
    if (res == 1)
    {
        int j = 0;
        while (buffer[j] != ':')
        {
            if ((isalpha(buffer[j])) ||
                (isdigit(buffer[j])))          /* making sure the label consist of characters and numbers only */
                label[j] = buffer[j];
            else
                return NULL;
            j++;
        }
        return label;
    }
    else
        return NULL;
    /* the function returns the label (without the ':' character) */
}

char *ifDirective(char *buffer) /* a function that checks if there is directive and if so it returns the type */
{
    int label_index, i, dot_index, j = 0;
    static char directive[20] = {'\0'};
    directive[0] = '\0';
    if (ifLabel(buffer) != NULL)        /* in case there is a label */
    {
        label_index = char_index(buffer, ':') + 1;
        dot_index = char_index(buffer, '.');
        for (i = label_index; i < dot_index; i++)   /* after the label there should be only spaces */
        {                                           /* until the '.' character */
            if (buffer[i] != ' ')
                return NULL;
        }
        getString(buffer, directive, (dot_index + 1)); /* storing the directive */
        if ((strcmp(directive, "data") == 0) || (strcmp(directive, "string") == 0))
            return directive;   /* testing the type of the directive and returning it */
        else
            return NULL;
    }
    else        /* if there is no label */
    {
        if (buffer[0] != '.')       /* if there is no label then the line should start with '.' character */
            return NULL;
        else
            getString(buffer, directive, 1); /* storing the directive */
        if ((strcmp(directive, "data") == 0) || (strcmp(directive, "string") == 0))
            return directive;  /* testing the type of the directive and returning it */
        else
            return NULL;
    }
}

char *ifGlobalDirective(char *buffer)
{
    char type, dot_index, i = 0, j = 0;                   /* type variable - 0 for entry and 1 for extern */
    char globalDirective[20] = {'\0'};
    static char label[LABEL_SIZE] = {'\0'};
    if (ifLabel(buffer) != NULL)
        fprintf(stderr, "warning: Label at the beginning of the instruction");
    dot_index = char_index(buffer, '.');
    getString(buffer, globalDirective, (char_index(buffer, '.')) + 1);
    if (strcmp(globalDirective, "entry") == 0)
        type = '0';
    else if (strcmp(globalDirective, "extern") == 0)
        type = '1';
    i = strlen(globalDirective) + 1;
    while (buffer[i] == ' ')
        i++;
    getString(buffer, label, i);
    label[strlen(label) - 1] = type;
    return label;
}