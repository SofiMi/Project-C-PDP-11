#include "foo.h"

void load_file(const char * filename)
{
    FILE * fin  = fopen(filename, "r");

    unsigned int adr_start_block, now_byte, number_byte, i;

    while (fscanf (fin, "%x %x", &adr_start_block, &number_byte) == 2)
    {
        //printf("%x\n", number_byte);
        for (i = 0; i < number_byte; i++)
            {
                fscanf (fin, "%x", &now_byte);
                b_write (adr_start_block, now_byte);
                adr_start_block++;
                //printf("%d\n", i);
                //printf("Yes\n");
            }
    }
    fclose(fin);
}
