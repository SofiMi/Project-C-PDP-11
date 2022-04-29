#include "foo.h"
#include <stdio.h>

extern Arg ss, dd;
extern word reg[8];
#define pc reg[7]

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (* do_func)();
    char params;
} Command;

extern Command cmd[];

void run()
{
    pc = 01000;
    while (1)
    {
        word w = w_read(pc);
        trace("%06o %06o: ", pc, w);
        pc += 2;
        for(int i = 0; cmd[i].name != "exit"; i++)
        {
            if ((w & cmd[i].mask) == cmd[i].opcode)
            {
                trace("%s ",cmd[i].name);
                if ((cmd[i].params >> 1) & 1)
                    ss = mode_reg(w >> 6); //!!!
                if (cmd[i].params & 1)
                    dd = mode_reg(w);
                cmd[i].do_func();
                trace("[%o] = %o", pc - 2, ss.val);
                trace("\n");
                break;
            }
        }
    }
}

