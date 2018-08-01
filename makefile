# specify filenames in the following lists

EXEC_FILE = assembler
C_FILES = assembler.c cmdData.c firstPass.c labelsData.c outData.c outputCreation.c parsing.c secondPass.c wordData.c  
H_FILES = cmd_data.h first_pass.h labels_data.h out_data.h output_creation.h parsing.h second_pass.h word_data.h   

# ==> to flush stdout after each line, insert in main() the statement: FLUSH_STDOUT; 
# ==> to flush stderr after each line, insert in main() the statement: FLUSH_STDERR;

#--------------------------------------------
# no changes need to be made beyond this line

# definitions for flushing after earch line
D_OFLUSH = -DFLUSH_STDOUT='setvbuf(stdout,NULL,_IOLBF,BUFSIZ);'
D_EFLUSH = -DFLUSH_STDERR='setvbuf(stderr,NULL,_IOLBF,BUFSIZ);'
D_FLUSH = $(D_OFLUSH) $(D_EFLUSH)

O_FILES = $(C_FILES:.c=.o)

all: $(EXEC_FILE)

$(EXEC_FILE): $(O_FILES) 
	gcc -Wall -ansi -pedantic $(O_FILES) -o $(EXEC_FILE) -lm

%.o: %.c $(H_FILES)
	gcc -Wall -ansi -pedantic -c $(D_FLUSH) -o $@ $<
	
clean:
	rm -f *.o $(EXEC_FILE)
	
	