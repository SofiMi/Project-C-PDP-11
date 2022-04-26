#include "foo.h"
#include <stdio.h>

word reg[8];
#define pc reg[7]

void do_halt(){
    trace("THE END\n");
    exit(0);
}
void do_mov(){}
void do_add(){}
void do_incb(){}
void do_movb(){}
void do_nothing(){}

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (* do_func)();
} Command;

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
    {0177700, 0105200, "incb", do_incb}, //b052dd
    {0170000, 0110000, "movb", do_movb},
    {0177777, 0000000, "halt", do_halt},
    {0000000, 0000000, "unknow", do_nothing},
    {0000000, 0000000, "exit", do_nothing}
};

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
                trace("%s \n",cmd[i].name);
                cmd[i].do_func();
                break;
            }
        }
    }
}

