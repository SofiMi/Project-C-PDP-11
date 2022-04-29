#include "foo.h"
Arg ss, dd, nn, r;

extern word reg[8];
#define pc reg[7]

void do_halt(){
    trace("THE END\n");
    trace_all();
    exit(0);
}

void do_mov(){
    if (dd.mode == 0)
    {
        reg[dd.adr] = ss.val;
    }
    else if (dd.mode == 1)
    {
        w_write(dd.adr, ss.val);
    }
    else if (dd.mode == 2)
    {
        reg[dd.adr] = ss.val;
    }
}

void do_add(){
    if (dd.mode == 0)
    {
        word sum = ss.val + reg[dd.adr];
        reg[dd.adr] = sum;
    }
    else if (dd.mode == 2)
    {
        word sum = ss.val + reg[dd.adr];
        reg[dd.adr] = sum;
    }
    else if (dd.mode == 1)
    {
        word sum = ss.val + w_read(dd.adr);
        w_write(dd.adr, sum);
    }
}

void do_incb(){}
void do_movb(){}
void do_nothing(){}

void do_sob(){
    //printf ("\n I am%o\n", r.val);
    if (r.val != 0)
    {
        pc = pc - nn.val*2;
        r.val -= 1;
        reg[r.adr] -= 1;
    }
}

void do_clr(){
    printf ("\n I am%o\n", dd.adr);
    reg[dd.adr] = 0;
}
