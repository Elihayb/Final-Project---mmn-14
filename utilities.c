#include <string.h>
#include <ctype.h>

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
    while (strIndex[0] != ' ' && strIndex[0] != '\0')
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
    char *tmp = index;
    while (tmp[0] != end && tmp[0] != '\0')
    {
        string[0] = tmp[0];
        string++;
        tmp++;
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

/*function check if buffer contain only spaces or tabs. return 0 if buffer contain another chars and 1 if empty*/
int isEmpty(const char *s)
{
    while (s[0] != '\0')
    {
        if (!isspace ((unsigned char) *s))
            return 0;
        s++;
    }
    return 1;
}

/*the function convert the binary array to decimal digit*/
int convertToChar(char *buffer, int length)
{
    int multiplier = 0;
    int i;
    int num;
    char *zero = "0";
    int sum = 0;
    for (i = length - 1 ; i >= 0 ; i--)
    {
        if (strstr ((char *) buffer[i], zero))
        {
            sum += (0 * (1 << multiplier++));
        }
        else
            sum += (1 * (1 << multiplier++));
    }
    return sum;
}