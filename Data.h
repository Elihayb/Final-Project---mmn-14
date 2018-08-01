#ifndef DATA_H
   #define DATA_H

/*defined all size of structures and other*/
    #define MAX_LABEL 32
    #define MAX_ACTION_NAME 5
    #define MEMORY_SIZE 256
    #define BUFFER_SIZE 81
    #define WORD_LENGTH 14
    #define MAX_WORDS_PER_COMMEND 4


/************STRUCTS DEFINITION************/


/*define word struct according to page 15*/
typedef struct word {
    unsigned ERA:2;
    unsigned operandDst:2;
    unsigned operandSrc:2;
    unsigned opcode:4;
    unsigned param2:2;
    unsigned param1:2;
}word;

/*action contain name and code according to page 15-16*/
typedef struct action{
    char actionName[MAX_ACTION_NAME];
    unsigned int actionCode;
} action;

/*label contain name, address from current location of DC, type and pointers for linked list*/
typedef struct label{
    char labelName[MAX_LABEL];
    unsigned int addressLabel;
    /*0 for local defined label, 1 for entry, 2 for external*/
    unsigned int type;
    label *next;
    label *prev;
} label;

/*commend contain address, row string, amount of related words,
 * binary machine code for all related words,
 * flag that check if this word is child of another word and link list pointer*/
typedef struct commend{
    unsigned int decimalAddress;
    char srcCode[BUFFER_SIZE];
    unsigned int wordAmount;
    char machineCode[MAX_WORDS_PER_COMMEND*WORD_LENGTH];
    /*check if this commend related to previous commend.
     * All binary data save to first commend. 0 if true*/
    unsigned int relatedToPrvCommendFlag;
    struct commend *next;
    struct commend *prv;
} commend;

unsigned int IC,DC,dataErrorFlag = 0;

/*Registers*/
word r0,r1,r2,r3,r4,r5,r6,r7,PSW;

/*memory array definition*/
word memory[MEMORY_SIZE];


/************DECLARATION SECTION************/


action defineActionTable();

label addToLabelTable(label *label, char *name,unsigned int DC,unsigned int type,int *rs);

label newLabel();

label searchLabel(label *list,char *str);

int validLabel(label *list, char labelName);

int printLabelList(label *list);

commend addToCommendTable(commend *list,unsigned int address, char sourceCode,unsigned int wordAmount,int childFlag,int *rs);

commend newCommend();

int amountOfWord(char sourceCode);

char convertToBinary(char *srcCode);

int printCommendList(commend *list);
   
#endif /* DATA_H */