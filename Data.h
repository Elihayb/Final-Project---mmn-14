#ifndef DATA_H
#define DATA_H

#include <stdlib.h>
#include <stdio.h>
/*defined all size of structures and other*/
#define MAX_LABEL 32
#define MAX_ACTION_NAME 5
#define BUFFER_SIZE 81
#define WORD_LENGTH 14
#define MAX_WORDS_PER_COMMAND 4
#define NUM_OF_ADDRESSING_METHOD 4
#define HIGHEST_POSITIVE_VALUE 8191
#define HIGHEST_NEGATIVE_VALUE -8192
#define REGISTERS_ARRAY_SIZE 8
#define MEMORY_SIZE 256
#define IMMEDIATE_METHOD 0
#define LABEL_METHOD 1
#define JUMP_METHOD 2
#define REGISTER_METHOD 3



/************STRUCTS DEFINITION************/





/*action contain name, code and legal method for operands according to page 15-16 and 27*/
typedef struct action
{
    char actionName[MAX_ACTION_NAME];
    int actionCode;
    char legalMethodOprSrc[NUM_OF_ADDRESSING_METHOD];/*Legal method for operand source*/
    char legalMethodOprDst[NUM_OF_ADDRESSING_METHOD];/*Legal method for operand destination*/
} action;

/*register contain code and data array*/
typedef struct registers
{
    int registerCode;
    char *dataArray[15];

}registers;

/*memory unit contain data array with 14 cells*/
typedef struct memory{
    char **dataArray[15];
}memory;

/*label contain name, address from current location of DC, type and pointers for linked list*/
typedef struct label
{
    char *labelName;
    int addressLabel;
    /*0 for local defined label, 1 for entry, 2 for external*/
    int type;
    struct label *next;
} label;

typedef struct data
{
    int type;
    char *lbl;
    char *sourceCode;
    char *binaryCode;
    int address;
    int sizeOfArray;
    struct data *next;

} data;


/*command contain address, row string, amount of related words,
 * binary machine code for all related words,
 * flag that check if this word is child of another word and link list pointer*/
typedef struct command
{
    unsigned int decimalAddress;
    char *srcCode;
    int wordAmount;
    char *machineCode;
    struct command *next;
} command;

/************DECLARATION SECTION************/
extern unsigned int IC, DC;

/*set all actions and codes for each one*/
action *defineActionTable();

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
label *addToLabelTable(label *label, char *name, unsigned int DC, unsigned int type, int *rs);

/* allocate and initialize a new label;
   space for the label is obtained via malloc();
   return a pointer to the new label, NULL if no space available*/
label *newLabel();

/*check if there any label with same name.
 Parameters:
 pointer to label list.
 name of label.
 Return:
 pointer to label if exist.
 NULL if not exist on list.*/
label *searchLabel(label *list, char *str);

/*check if there are not any label with same name
 and there is not any action name or directive command that identical in names
 Parameters:
 pointer to label list.
 name of label.
 Return:
 -1 if label is not valid.
 0 if label is valid.*/
int validLabel(label *list, char *labelName, int *rs);

/* allocate and initialize a new data;
   space for the data is obtained via malloc();
   return a pointer to the new data, NULL if no space available*/
data *newData();

/*add data to data list if it contain valid values
 Parameters:
 pointer to data list (MULL if there is not list).
 name.
 DC value for data address.
 type of data (0 for string, 1 for numbers).
 report success flag.
 Return:
 pointer to new label on the list.
 report success flag 0 if success, else -1.
 */
data addToDataTable(data *dataTable, char *dataLabel, char *sourceCode, int address, int strOrNun, int *rs);

/*this function add command and all operands and parameters to commands table */
command addToCommandTable(command *list, label *labelList, unsigned int address, char *sourceCode, int *rs);

/* allocate and initialize a new command;
   space for the command is obtained via malloc();
   return a pointer to the new command, NULL if no space available*/
command *newCommand();

/*function get the buffer and search which action it contain.
 * return the action ID as int.
 * return -1 if is not matching to any action */
int getActionID(char *sourceCode);

/*the function return the number of words to write to command table
 * for action without operands it return 1.
 * for action with 1 operand it return 2.
 * for action with 2 operands it return 2 if all of them are registers. else, return 3.
 * for jump action it return 3 if all of params are registers. else, return 4.*/
int amountOfWord(char *sourceCode, label *labelList);

/*This function convert decimal numbers to binary and print it to the file output.
 * if you print a char, convert it to ascii decimal code like that:
 * char a = 'a'; int n = (int)a;*/
char *convertToBinary(int n, int size, int *rs);

/*function return the ARE code for relevant word
 * it get the buffer and label list.
 * return array with ARE values in cells respectively of amount Of Words*/
int *setARE(char *sourceCode, label *labelList);

/*function build word with only data and ARE filed.
 * it get buffer line, labels list, number of child word and status flag.
 * number of child word should be large then 0. 0 saved for first word.
 * return array with binary value*/
char *buildChildWord(char *buffer, label *labelList, int numOfChildWord, int *rs);

/*function to build word that contain register number if there is one register or union word for 2 registers*/
char *registerWord(char *buffer, label *labelList, int numOfChildWord, int *rs);

/*function get the buffer and labels list.
 * return words array with binary value */
char *buildWord(char *buffer, label *labelList, int *rs);

/*function get source code line and status flag and return array with all numbers as binary with width of 14 bits*/
char *buildDataWord(char *buffer, int *rs);

/*this function save on homogeneous in error contact.
 * get row number and error id
 * and print the error with line number*/
int errorPrint(int errId, unsigned int row);

#endif /* DATA_H */