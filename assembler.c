#include "parsing.h"
#include "data.h"
#include "first_pass.h"
#include "second_pass.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

    FILE *inFile;
    struct label *labelList = NULL;
    struct commend *commendList = NULL;

    if (argc == 1) {
        fprintf(stderr, "\n%s: you need to specify at least one input file\n", *argv);
        return -1;
    }
    while (--argc) {
        if ((inFile = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "\nUnable to open file \"%s\" in read mode\n", *argv);
            continue;
        }
        if (firstPass(*inFile, commendList, labelList) == -1) {
            fprintf(stderr, "\nThere is error in your \"%s\" file, please check them and try again\n", *argv);
            continue;
        }
        if (secondPass(*inFile, commendList, labelList) == -1) {
            fprintf(stderr, "\nThere is error in your \"%s\" file, please check them and try again\n", *argv);
            continue;

        }
        if (outputCreation(*inFile, commendList, labelList) == -1) {
            fprintf(stderr,
                    "\nProgram fail to create output files for your \"%s\" file, please check the error and try again\n", *argv);
            continue;
        }


    }return 0;/*success*/


}