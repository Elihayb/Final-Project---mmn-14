#include "parsing.h"
#include "data.h"
#include <stdio.h>
#include <string.h>

int firstPass(FILE *f, commend *commendList, label *labelList){
    char labelName[MAX_LABEL];
    int rs=0;/*return status flag. 0 for success and -1 for failure*/
    char directive[MAX_DIRECT_NAME];
    IC = 0;
    DC = 0;

    while ((row != NULL)||(*row != 0)) do{
       if (labelName = ifLabel(row)!= NULL){
           LabelFlag = 1;
       }

       if(directive = ifDirective(*row)!= NULL){/*check if string or data*/
            if (LabelFlag = 1){
                *labelList = addToLabelTable(labelList,labelName,DC,0,&rs);
                if ((*labelList->labelName == NULL)&&(rs !=0)){/*check if added to labels table*/
                    fprintf(stderr,"label %s not valid",labelName);
                }

            }
            addToCommendTable(commendList,IC,*row,0,&rs);

           if (rs == -1){
               ErrorFlag=1;
           }
       }
       if (directive = ifGlobalDirective(*row)!=NULL){/*check if extern or entry*/

       }
       if (LabelFlag = 1) {
           *labelList = addToLabelTable(labelList, labelName, IC, 0, &rs);
           addToCommendTable(commendList,IC,*row,0,&rs);
       }

    }
        ErrorFlag = 1;





}