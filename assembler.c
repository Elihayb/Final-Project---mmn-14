#include "parsing.h"
#include "data.h"
#include "first_pass.h"
#include "output_creation.h"
#include <stdio.h>
#include <string.h>

/*int main(){
    printf ("Hello world");
    return 0;
}*/

int main(int argc, char **argv) {



    FILE *inFile;
     label *labelList = NULL;
     command *commandList = NULL;
     data *dataList= NULL;
     static int *rs=0;


    if (argc == 1) {
        fprintf(stderr, "\n%s: you need to specify at least one input file\n", *argv);
        return -1;
    }
    if (strstr (*argv,".as")!=NULL){/*check if files contain ".as" extension*/
        fprintf(stderr, "\n your \"%s\" file contain incorrect extension format\n", *argv);
        return -1;
    }
    while (--argc) {
        if ((inFile = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "\nUnable to open file \"%s\" in read mode\n", *argv);
            continue;
        }
        if (firstPass(inFile,commandList,dataList,labelList,rs) == -1) {
            fprintf(stderr, "\nThere is errors in your \"%s\" file, please check them and try again\n", *argv);
            continue;
        }
        outputCreation(*argv,dataList,commandList,labelList,rs) ;

    }return 0;/*success*/
}
