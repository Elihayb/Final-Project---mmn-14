/*action file contain all actions management and functional  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "action.h"
#include "Data.h"
#include "parsing.h"
#include "utilities.h"

int performAction(char *buffer, label *labelList, data *dataList, command *commandList,int address, int *rs)
{
    int actionID = getActionID (buffer);
    int *PC;
    char *firstOperand = getFirstOperand (buffer, rs);
    char *secondOperand = getSecondOperand (buffer);
    char *firstParam = getFirstParam (buffer);
    char *secondParam = getSecondParam (buffer);
    registers registers[REGISTERS_ARRAY_SIZE];/*registers array*/
    memory *memory[MEMORY_SIZE];/*memory stack*/

    verifyOperand (actionID,firstOperand,0,labelList,rs);
    if (rs!=0){
        return -1;
    }
    verifyOperand (actionID,secondOperand,1,labelList,rs);
    if (rs!=0){
        return -1;
    }
    if (((actionID == 9)||(actionID == 10)||(actionID == 13))&& ((firstParam!=NULL)&&(secondParam!=NULL))){
        verifyOperand (actionID,firstParam,2,labelList,rs);
        if (rs!=0){
            return -1;
        }
        verifyOperand (actionID,secondParam,2,labelList,rs);
        if (rs!=0){
            return -1;
        }
    }

    switch (actionID)
    {
        case 0:
            mov (firstOperand,secondOperand,labelList,registers,dataList);
            break;
        case 1:
            cmp (firstOperand,secondOperand,labelList,registers,dataList);
            break;
        case 2:
            add (firstOperand,secondOperand,labelList,registers,dataList);
            break;
        case 3:
            sub (firstOperand,secondOperand,labelList,registers,dataList);
            break;
        case 4:
            lea (firstOperand,secondOperand,labelList,registers,dataList);
            break;
        case 5:
            not (firstOperand,labelList,registers,dataList);
            break;
        case 6:
            clr (firstOperand,labelList,registers,dataList);
            break;
        case 7:
            inc (firstOperand,labelList,registers,dataList);
            break;
        case 8:
            dec (firstOperand,labelList,registers,dataList);
            break;
        case 9:
            jmp (firstOperand,firstParam,secondParam,labelList,registers,dataList);
            break;
        case 10:
            bne (firstOperand,firstParam,secondParam,labelList,registers,dataList);
            break;
        case 11:
            red (firstOperand,labelList,registers,dataList);
            break;
        case 12:
            prn (firstOperand,labelList,registers,dataList);
            break;
        case 13:
            jsr (firstOperand,firstParam,secondParam,labelList,registers,dataList);
            break;
        case 14:
            rts ();
            break;
        case 15:
            stop();
            break;
        default:
            return -1;/*failure*/
    }
}
/*function search register operand and return register number. return -1 if fail*/
int searchRegister(char *operand){
    int i;
    char *temp=NULL;
    for (i=0;i<REGISTERS_ARRAY_SIZE;i++){
        sprintf(temp,"r%d",i);
        if (strstr(temp,operand)!=NULL){
            return i;
        }
    }
    return -1;
}

int mov (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList){

}

int cmp (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList){

}

int add (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList){

}

int sub (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList){

}

int lea (char *firstOperand,char *secondOperand,label *labelList,registers *registers,data *dataList){

}

int not (char *firstOperand,label *labelList,registers *registers,data *dataList){

}

int clr (char *firstOperand,label *labelList,registers *registers,data *dataList){

}

int inc (char *firstOperand,label *labelList,registers *registers,data *dataList){

}

int dec (char *firstOperand,label *labelList,registers *registers,data *dataList){

}

int jmp (char *firstOperand,char *FirstParam,char *secondParam,label *labelList,registers *registers,data *dataList){

}

int bne (char *firstOperand,char *FirstParam,char *secondParam,label *labelList,registers *registers,data *dataList){

}

int red (char *firstOperand,label *labelList,registers *registers,data *dataList){

}

int prn (char *firstOperand,label *labelList,registers *registers,data *dataList){

}

int jsr (char *firstOperand,char *FirstParam,char *secondParam,label *labelList,registers *registers,data *dataList){

}

int rts (){

}

void stop (){

}


