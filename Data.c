

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"


/*********************ACTION SECTION**********************/


/*set all actions and codes for each one*/
action defineActionTable() {

    action actionTable[16];

    strcpy(actionTable[0].actionName, "mov");
    actionTable[0].actionCode = 0;
    strcpy(actionTable[1].actionName, "cmp");
    actionTable[1].actionCode = 1;
    strcpy(actionTable[2].actionName, "add");
    actionTable[2].actionCode = 2;
    strcpy(actionTable[3].actionName, "sub");
    actionTable[3].actionCode = 3;
    strcpy(actionTable[4].actionName, "not");
    actionTable[4].actionCode = 4;
    strcpy(actionTable[5].actionName, "clr");
    actionTable[5].actionCode = 5;
    strcpy(actionTable[6].actionName, "lea");
    actionTable[6].actionCode = 6;
    strcpy(actionTable[7].actionName, "inc");
    actionTable[7].actionCode = 7;
    strcpy(actionTable[8].actionName, "dec");
    actionTable[8].actionCode = 8;
    strcpy(actionTable[9].actionName, "jmp");
    actionTable[9].actionCode = 9;
    strcpy(actionTable[10].actionName, "bne");
    actionTable[10].actionCode = 10;
    strcpy(actionTable[11].actionName, "red");
    actionTable[11].actionCode = 11;
    strcpy(actionTable[12].actionName, "prn");
    actionTable[12].actionCode = 12;
    strcpy(actionTable[13].actionName, "jsr");
    actionTable[13].actionCode = 13;
    strcpy(actionTable[14].actionName, "rts");
    actionTable[14].actionCode = 14;
    strcpy(actionTable[15].actionName, "stop");
    actionTable[15].actionCode = 15;

    return *actionTable;
}

/*********************LABEL SECTION**********************/


/*add label to labels list if it contain valid values
 Parameters:
 pointer to label list (MULL if there is not list).
 name.
 DC value for label address.
 type of label (0 for local defined label, 1 for entry, 2 for external).
 report success flag.
 Return:
 pointer to new label on the list.
 report success flag 0 if success, else -1.
 */
label addToLabelTable(label *label, char *name, unsigned int DC, unsigned int type, int *rs) {
    /*check if name is null or without value*/
    if ((name == NULL) || (*name == 0)) {
        if (rs) *rs = -1;/*failure*/
        return *label;
    }
    if ((label == NULL) || (validLabel(label, name))) {/*list is empty and label are not exist */
        *label = newLabel();
        if (label != NULL) {
            label->type = type;
            strcpy(label->labelName, name);
            label->addressLabel = DC;
            if (rs) *rs = 0;/*success*/
            return *label;
        }
        free(label);/*free memory and return null and failure if newLabel fail*/
        if (rs) *rs = -1;/*failure*/
        return *label;
    } else {
        *label->next = addToLabelTable(label->next, *name, DC, type, *rs);
        if (*rs) *rs = 0;/*success*/
        return *label;
    }

}

/* allocate and initialize a new label;
   space for the label is obtained via malloc();
   return a pointer to the new label, NULL if no space available*/
label newLabel() {
    label *label = (label *) malloc(sizeof(label));
    if (label) {
        label->name = label->type = NULL;
        label->next = NULL;
    }
    return *label;
}

/*check if there any label with same name.
 Parameters:
 pointer to label list.
 name of label.
 Return:
 pointer to label if exist.
 NULL if not exist on list.*/
label searchLabel(label *list, char *str) {
    char temp;/*save the first name for loop condition*/
    strcpy(temp, label.labelName);

    if ((list == null) || (str == null) || (*str == 0)) {/*check if all parameters are valid*/
        return null;
    }
    do {/*search loop*/
        if (strcmp(label.labelName, str)) {
            return label;
        } else {
            label = label.next;
        }

    } while (strcmp(label.labelName, temp) != 0);

    return null;/*label with same name is not exist*/

}

/*check if there are not any label with same name
 and there is not any action name or directive commend that identical in names
 Parameters:
 pointer to label list.
 name of label.
 Return:
 -1 if label is not valid.
 0 if label is valid.*/
int validLabel(label *list, char *labelName) {
    int i;
    /**action = defineActionTable();*/
    if (searchLabel(*list, *labelName) == NULL) {
        for (i = 0; i < 16; i++) {/*check if label name equal to any action name */
            if (strcmp(actionTable[i].actionName, labelName) = 0) {
                return -1;/*label is not valid*/
            }
        }
        if ((strcmp("string", labelName) = 0) || (strcmp("data", labelName) = 0)) {
            return -1;/*label is not valid*/
        } else if ((strcmp("entry", labelName) = 0) || (strcmp("extern", labelName) = 0)) {
            return -1;/*label is not valid*/
        }
    } else {
        return 0;/*label is valid*/
    }
}

/**/
int printLabelList(label *list) {
    /*צריך למצוא את הפוינטר הראשון ולהתחיל להדפיס ממנו*/
}

/*********************COMMEND SECTION**********************/


/**/
commend addToCommendTable(commend *list, unsigned int address, char sourceCode, int childFlag, int *rs) {
    if ((sourceCode == NULL) || (sourceCode == 0)) {
        if (rs) *rs = -1;/*failure*/
        return *list;
    }
    if (list == NULL) {/*list is empty*/
        if (*list = newCommend()) {
            list->decimalAddress = address;
            strcpy(list->srcCode, sourceCode);
            wordAmount = amountOfWord(sourceCode);

            if (childFlag == 0) {
                strcpy(list->machineCode, convertToBinary(sourceCode));
            } else {
                strcpy(list->machineCode, "NoCode");
                list->relatedToPrvCommendFlag = 0;
            }
            if (rs) *rs = 0;/*success*/
            return *list;
        }
        free(list);/*free memory and return null and failure if newCommend fail*/
        if (rs) *rs = -1;/*failure*/
        return *list;
    } else {
        list->next = addToCommendTable(list->next, address, sourceCode, wordAmount, childFlag, rs);
        if (*rs) *rs = 0;/*success*/
        return *list;
    }

}

/* allocate and initialize a new commend;
   space for the commend is obtained via malloc();
   return a pointer to the new commend, NULL if no space available*/
commend newCommend() {
    commend *commend = (commend *) malloc(sizeof(commend));
    if (commend) {
        commend->relatedToPrvCommendFlag = commend->machineCode = NULL;
        commend->wordAmount = commend->srcCode = commend->decimalAddress = NULL;
        commend->next = commend->prev = NULL;
    }
    return *commend;
}

int amountOfWord(char sourceCode) {
    /*לנתח את הפקודה ולהחליט כמה משפטים יש בפקודה*/
}

char convertToBinary(char *srcCode) {
    /*הפונקציה הזו ממירה את השורה לבינארי בהתאם לכמות המילים הכתובות בה. השימוש בה הוא עבור machineCode במבנה פקודה*/
}

/**/
int printCommendList(commend *list) {
    if (list->relatedToPrvCommendFlag == 1) {/*all binary code exist in parent commend*/
        list = list->next;
    } else {
        printf("%d%10s", list->decimalAddress, list->machineCode);
    }
}

/*this function save on homogeneous in error contact.
 * get row number and error id*/
int errorPrint(unsigned int errId,unsigned int row){
    switch(errId){
        case 1:
            fprintf(stderr,"Line: %d , missing argument",row);
        case 2:
            fprintf(stderr,"Line: %d , invalid argument (cannot be instruction)",row);
        case 3:
            fprintf(stderr,"Line: %d , invalid characters",row);
        case 4:
            fprintf(stderr,"Line: %d , invalid argument (immediate too large)",row);
        case 5:
            fprintf(stderr,"Line: %d , invalid target operand (immediate)",row);
        case 6:
            fprintf(stderr,"Line: %d , invalid operand (immediate)",row);
        case 7:
            fprintf(stderr,"Line: %d , undefined instruction",row);
        case 8:
            fprintf(stderr,"Line: %d , label previously declared",row);
        case 9:
            fprintf(stderr,"Line: %d , warning - label does not start in first column",row);
        case 10:
            fprintf(stderr,"Line: %d , invalid source operand (register)",row);
        case 11:
            fprintf(stderr,"Line: %d , invalid source operand (immediate)",row);
        case 12:
            fprintf(stderr,"Line: %d , invalid label",row);
        case 13:
            fprintf(stderr,"Line: %d , local label cannot be declared as external",row);
        case 14:
            fprintf(stderr,"Line: %d , label is already designated as external",row);
        case 15:
            fprintf(stderr,"Line: %d , undefined directive",row);
        case 16:
            fprintf(stderr,"Line: %d , missing argument in directive",row);
        case 17:
            fprintf(stderr,"Line: %d , data overflow (negative value too large to fit in 14 bits)",row);
        case 18:
            fprintf(stderr,"Line: %d , data overflow (positive value too large to fit in 14 bits)",row);
        default:
            return -1;/*failure*/
    }
    return 0;/*success*/
}


