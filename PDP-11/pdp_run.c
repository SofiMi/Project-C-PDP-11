#include "foo.h"
#include <stdio.h>

word reg[8];
#define pc reg[7]

void trace_all(void)
{
    for(int i = 0; i < 7; i++)
        trace("R%d %o  ", i, reg[i]);
}
void do_halt(){
    trace("THE END\n");
    trace_all();
    exit(0);
}
typedef struct{
    word val;  // значение аргумента
    word adr;
    int mode;
} Arg;

Arg ss, dd;

void b_write_reg(Adress adr, byte b)
{
    reg[adr] = b;
}

byte b_read_reg(Adress adr)
{
    return reg[adr];
}

void w_write_reg(Adress adr, word w)
{
   //assert(0 == adr % 2);
   // Write to the 1 byte
   b_write_reg(adr + 1, w >> 8);
   // Write to the 2 byte
   b_write_reg(adr, w & 0xFF);
}

word w_read_reg(Adress adr)
{
    // Read to the 1 byte
    word w = ((word)reg[adr + 1]) << 8;
    // Read to the 2 byte
    w = w | reg[adr];
    return w;
}

Arg mode_reg(word w)
{
    Arg res;
    int r = w & 7;
    int mode = (w >> 3) & 7;
    switch(mode) {
        case 0: // R3
            res.adr = r;
            res.val = reg[r];
            trace("R%o ", r);
            res.mode = 0;
            break;

        case 1: // (R3)
            res.adr = reg[r];
            res.val = w_read(res.adr); //!!! b_read
            trace("(R%o) ", r);
            res.mode = 1;
            break;

        case 2: // (R3)+ #3
            res.adr = reg[r];
            res.val = w_read(res.adr); //!!! b_read
            reg[r] += 2;
            res.mode = 2;
            if (r == 7)
                trace("#%o ", res.val);
            else
                trace("(R%o)+", r);
            break;

        default:
            fprintf(stderr, "Mode %o NOT IMPLEMENTED YET!!!\n", mode);
            exit(1);
    }
    return res;
}

void do_mov(){
    if (dd.mode == 0)
    {
        w_write_reg(dd.adr, ss.val);
        //printf("I am in mode 0\n");
        //printf ("dd.adr  = %o, dd.val = %o, ss.val = %o, ss.adr = %o, \n",dd.adr, dd.val, ss.val, ss.adr );
    }
    //trace_all();
}
void do_add(){
    if (dd.mode == 0)
    {
        w_write_reg(dd.adr, ss.val + w_read_reg(dd.adr));
        //printf("I am in mode 0\n");
        //printf ("%o",dd.adr );
        //printf ("%o",ss.val );
    }
    //trace_all();
}
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
                trace("%s ",cmd[i].name);
                ss = mode_reg(w >> 6); //!!!
                dd = mode_reg(w);
                cmd[i].do_func();
                trace("\n");
                break;
            }
        }
    }
}

