#include "foo.h"
#include <stdio.h>

word reg[8];
#define pc reg[7]

void do_halt(){
    trace("THE END\n");
    exit(0);
}

void run()
{
    pc = 01000;
    while(1)
    {
        word w = w_read(pc);
        trace("%06o %06o: ", pc, w);
        pc += 2;
        if (w == 0){
            trace("halt ");
            do_halt();
        }
    }
}

