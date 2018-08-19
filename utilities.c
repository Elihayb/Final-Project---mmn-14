#include <string.h>


int matchingBrackets(char *buffer)
{
    int lcount = 0, rcount = 0, i;
    for (i = 0 ; i < strlen (buffer) ; i++)
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

char *nextStr(char *strIndex)
{
    while (strIndex[0] != ' ')
        strIndex++;
    while (strIndex[0] == ' ')
        strIndex++;
    return strIndex;
}

char *nextStr2(char *strIndex)
{
    while (strIndex[0] != ' ')
        strIndex++;
    return strIndex;
}

char *skipSpcaes(char *strIndex)
{
    while (strIndex[0] == ' ')
        strIndex++;
    return strIndex;
}

int charToInt(char ch)
{
    return ch - '0';
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

void getString2(char *index, char *string, char end)
{
    while(index[0] != end)
    {
        string[0] = index[0];
        string++;
        index++;
    }
}

int char_index(char *buffer, char chr) /* a function that returns the index of a character in a string */
{                                       /* if there is no such character then the function returns -1 */
    int i, index = -1;
    for (i = 0 ; i < strlen (buffer) ; i++)
    {
        if (buffer[i] == chr)
        {
            index = i;
            break;
        }
    }
    return index;
}