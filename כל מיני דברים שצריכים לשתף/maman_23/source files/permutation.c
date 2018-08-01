#include <stdio.h>
#include <string.h>

void resetString(char st[]);

/* this is a function that checks if the string st2 is a permutation of the string st1 */
/* given that both of the strings are considered to be words (not necessarily spoken words */
/* but a combination of characters with no spaces or tabs in between */
/* the function returns an integer depending on the result of the check. 1 for positive and 0 for negative. */
int isPermut(char st1[], char st2[])
{
    int res = 0, i, j, cnt = 0;                 /* the res variable returns the result of the check */
    for (i = 0; i < strlen(st1); i++)           /* brute force check if all the letters of the first string appear in the other string */
    {
        for (j = 0; j < strlen(st2); ++j)
        {
            if (st1[i] == st2[j])
            {
                cnt++;                          /* counting the number of matches */
                break;                          /* dealing with duplicates. once there is a match returning to the outer loop and proceeding the check */
            }
        }
    }
    if (cnt == strlen(st1))                      /* if the number of matches equals the length of the first string and given they are the same length the result is positive. */
        res = 1;                                /* setting the result value to positive */
    return res;                                 /* returning the result */
}

/* this is a function that prints the permutation of the original string passed. */
/* the function is using a buffer. it compares the test string with the original string and storesin the buffer */
/* only the letters from the test string that are matched in the original string. the function then prints the string stored */
/* in the buffer which is the permutation of the original string */
void printPermutation(char testStr[], char originStr[])
{
    int i, j, cnt = 0;                                      /* indexes for the loops and counter that counts the number of matches */
    char buf[500] = {0};
    for (i = 0; i < strlen(testStr); i++)                   /* nested loops that compares the 2 strings. */
    {
        for (j = 0; j < strlen(originStr); j++)
        {
            if (testStr[i] == originStr[j])
            {
                buf[cnt] = testStr[i];                      /* storing the matched character in the buffer and incrementing the counter */
                cnt++;
            }
            if (cnt == strlen(originStr))                   /* if the number of matches equals the length of the original string there is no point */
                break;                                      /* of continue iterating the loop */
        }
        if (cnt == strlen(originStr))
            break;
    }
    puts(buf);                                              /* printing the permutation  */
}

/* function to rest a given string */
void resetString(char st[])
{
    {
        int i;
        for (i = 0; i < strlen(st); i++)
            st[i] = '\0';
    }
}