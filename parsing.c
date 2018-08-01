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
        return 1;                           /* returning 1 if yes and 0 otherwise */
    else
        return 0;
}

int ifComment(char *buffer)                     /* a function that returns 1 if the line in the buffer is a comment */
{
    return (buffer[0] == ';') ? 1 : 0;
}

char *ifLabel(char *buffer)                     /* a function that checks if there is a label and if so the fucntion returns the label */
{
    int i, res = 0, spaceIndex = 0;             /* res variable 1 if there is label and 0 otherwise */
    static char label[LABEL_SIZE] = {'\0'};
    label[0] = '\0';
    if (buffer[0] == ' ' || !(isalpha(buffer[0])))      /* testing the first colum */
    {
        return "";
    }
    for (i = 0; i < strlen(buffer); i++)                /* looking for the ':' character and the space character  */
    {
        if (buffer[i] == ' ')
            spaceIndex = i;
        if (buffer[i] == ':')
            break;
    }                                               /* i stands for the ':' index */
    if(spaceIndex > i || spaceIndex == 0)
        res = 1;
    if (i > 31)
        return "";
    if (res == 1)
    {
       int j = 0;
        while (buffer[j] != ':')
        {
            label[j] = buffer[j];
            j++;
        }
    }
    return label;
}

