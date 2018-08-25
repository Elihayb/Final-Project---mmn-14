#include "parsing.h"
#include "data.h"
#include "utilities.h"
#include "first_pass.h"
#include "output_creation.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    static int rs[1] = {0};
    label *labelList = NULL;
    command *commandList = NULL;
    data *dataList = NULL;
	
    if (argc == 1)
    {
        fprintf (stderr, "\n%s: you need to specify at least one input file\n", *argv);
        return -1;
    }
    while (--argc)
    {
        argv++;
        if (strstr (*argv, ".as") == NULL)
        {/*check if files contain ".as" extension*/
            fprintf (stderr, "\n your \"%s\" file contain incorrect extension format\n", *argv);
            return -1;
        }

        if (firstPass (*argv, commandList, dataList, labelList, rs) == -1)
        {
            fprintf (stderr, "\nThere is errors in your \"%s\" file, please check them and try again\n", *argv);
            continue;
        }
        outputCreation (*argv, dataList, commandList, labelList, rs);

    }
    return 0;/*success*/
}
