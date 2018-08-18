#ifndef DATA_H
#define DATA_H

/*defined all size of structures and other*/
#define MAX_LABEL 32
#define MAX_ACTION_NAME 5
#define BUFFER_SIZE 81
#define WORD_LENGTH 14
#define MAX_WORDS_PER_COMMAND 4
#define MAX_DIRECT_NAME 7
#define NUM_OF_ADDRESSING_METHOD 4
#define HIGHEST_POSITIVE_VALUE 8191
#define HIGHEST_NEGATIVE_VALUE -8192
#define IMMEDIATE_METHOD 0
#define LABEL_METHOD 1
#define JUMP_METHOD 2
#define REGISTER_METHOD 3



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



/*action contain name, code and legal method for operands according to page 15-16 and 27*/
typedef struct action{
    char actionName[MAX_ACTION_NAME];
    unsigned int actionCode;
    char legalMethodOprSrc[NUM_OF_ADDRESSING_METHOD];/*Legal method for operand source*/
    char legalMethodOprDst[NUM_OF_ADDRESSING_METHOD];/*Legal method for operand destination*/
} action;

/*label contain name, address from current location of DC, type and pointers for linked list*/
typedef struct label{
    char *labelName;
    int addressLabel;
    /*0 for local defined label, 1 for entry, 2 for external*/
    int type;
    struct label *next;
} label;


/*command contain address, row string, amount of related words,
 * binary machine code for all related words,
 * flag that check if this word is child of another word and link list pointer*/
typedef struct command{
    unsigned int decimalAddress;
    char srcCode[BUFFER_SIZE];
     int wordAmount;
    char machineCode[MAX_WORDS_PER_COMMAND*WORD_LENGTH];
    /*check if this command related to previous command.
     * All binary data save to first command. 0 if true*/
    unsigned int childFlag;
    struct command *next;
} command;

unsigned int IC,DC = 0;


/************DECLARATION SECTION************/


action *defineActionTable();

label addToLabelTable(label *label, char *name,unsigned int DC,unsigned int type,int *rs);

label *newLabel();

label *searchLabel(label *list,char *str);

int validLabel(label *list, char *labelName, int *rs) ;

command addToCommandTable(command *list, label *labelList, unsigned int address, char *sourceCode, int childFlag, int *rs);

command *newCommand();

int getActionID(char *sourceCode);

int amountOfWord(char *sourceCode, label *labelList);

char *convertToBinary(int n,int size, int *rs);

int *setARE(char *sourceCode,label *labelList);


int errorPrint(unsigned int errId,unsigned int row);

#endif /* DATA_H */