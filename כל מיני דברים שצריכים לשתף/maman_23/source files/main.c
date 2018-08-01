#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int isPermut(char st1[], char st2[]);
int read_words(FILE *f, char st[]);
void printPermutation(char testStr[], char originStr[]);
void resetString(char st[]);
int isFileOpen(FILE *p);
int isEmptyFile(FILE *p);
int numOfArg(int a);
int numOfPermut(int a);


int main(int argc, char *argv[])
{
    FILE *fp;
    numOfArg(argc);                     /* checking the number of arguments. */
    fp = fopen(argv[1], "r");
    isFileOpen(fp);                     /* error checking */
    isEmptyFile(fp);
    rewind(fp);                         /* setting the file stream back to beginning. */
    numOfPermut(read_words(fp, argv[2])); /* also checking if there were permutations found. */
    fclose(fp);
	return 0;
}

/* this is the function that is reading from the text file one word at a time. */
/* the function the checks if a word is a permutation of the original string. */
/* if it is then the word is printed else the function continues to the next word. */
/* the function returns the number of permutations found. */
int read_words(FILE *f, char st[])
{
    int numOfPermut = 0;
    char buf[500] = {0};                        /* buffer assuming one word is max of 500 characters. the word is not necessarily a spoken word  */
    while (fscanf(f, "%s", buf) != EOF)         /* it can be mix of random characters */
    {
        if (isPermut(st, buf))                  /* checking if the current word is a permutation. */
        {
            numOfPermut++;
            printPermutation(buf, st);          /* if it is it is being printed */
        }
        else
            resetString(buf);                   /* resetting the buffer so it would be ready to store the next word */
    }
    return numOfPermut;
}
