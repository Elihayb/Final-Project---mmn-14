#include "parsing.h"
#include "data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int outputCreation(FILE *inFile, struct commend *commendList, label *labelList){


}

int printLabelList(label *lbl,char *fileName) {

    char *fn = malloc(strlen(fileName+5));/*Allocate a string name with enough space for the extensions.*/
    FILE *outExt=NULL;
    FILE *outEnt=NULL;

    if (lbl==NULL){
        return 0;/*label list is empty and the function should be do nothing*/
    }
    do {/*print loop*/
        if (lbl->type==1) {/*print to entry labels file*/
            strcat(fileName,".ent");
            if ((outEnt = fopen(fileName,"a"))!=NULL) {
                fprintf(outEnt,"%32s - %4d", lbl->labelName, lbl->addressLabel);
            }
        }
        else if(lbl->type==2){/*print to extern labels file*/
            strcat(fileName,".ext");
            if ((outExt = fopen(fileName,"a"))!=NULL) {
                fprintf(outExt,"%32s - %4d", lbl->labelName, lbl->addressLabel);
            }
        }
        lbl = lbl->next;
    } while (lbl != NULL);

    if (outEnt!=NULL){
        fclose(outEnt);
    }
    if (outExt!=NULL){
        fclose(outExt);
    }
}

/**/
int printCommandList(command *list,FILE *f) {

}