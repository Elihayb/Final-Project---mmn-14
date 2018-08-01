#include <stdio.h>
#include <stdlib.h>
/* checking the argc value. it should be equals to 3. */
int numOfArg(int a)
{
    if (a != 3)
    {
        fprintf(stderr,"\nThere should be exactly 2 arguments in the command line.");
        exit(0);
    }
    else
        return 1;
}
/* checking if the pointer pointing to the file is not equal to null. if it is then the file opening wasn't successful.  */
int isFileOpen(FILE *p)
{
    if(p == NULL)
    {
        fprintf(stderr,"\nError opening file.");
        exit(0);
    }
    else
        return 1;
}
/* counting the number of characters in the file. if the counter equals to 0 then the file is empty. */
int isEmptyFile(FILE *p)
{
    int cnt = 0;
    while(fgetc(p) != EOF)
        cnt++;
    if (cnt == 0)
    {
        fprintf(stderr,"\nThe file is empty.");
        exit(0);
    }
    else
        return 0;
}
/* counting the number of permutations found in the file. */
int numOfPermut(int a)
{
    if(a == 0)
    {
        printf("\nThere are no permutations in the file.");
        exit(0);
    }
    else return 1;
}