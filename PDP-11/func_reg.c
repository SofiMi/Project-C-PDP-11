#include "foo.h"
Arg ss, dd;

void do_halt(){
    trace("THE END\n");
    trace_all();
    exit(0);
}

void do_mov(){
    if (dd.mode == 0)
    {
        w_write_reg(dd.adr, ss.val);
    }
}

void do_add(){
    if (dd.mode == 0)
    {
        w_write_reg(dd.adr, ss.val + w_read_reg(dd.adr));
    }
}

void do_incb(){}
void do_movb(){}
void do_nothing(){}
