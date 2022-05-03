#include "foo.h"
Arg ss, dd, nn, r, xx;
char byte_n;
char flag_N, flag_Z, flag_C;

extern word reg[8];
#define pc reg[7]

void get_flag_N(word w_res)
{
    printf("\nStart get_flag_N\n");
    printf ("\nres = %d", w_res);
    if ((w_res & 1 << 15) == 1 << 15)
        {
            flag_N = 1;
            printf ("Yes");
        }
    else
       flag_N = 0;
}
void get_flag_Z(word w_res)
{
    if (w_res == 0)
        flag_Z = 1;
    else
       flag_Z = 0;
}
void get_flag_C(word w_res)
{
    printf("Start get_flag_C\n");
    if ((w_res >> 15) >= 2)
        flag_C = 1;
    else
       flag_C = 0;
}

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
    else if ((dd.mode == 1) || (dd.mode == 4))
    {
        w_write(dd.adr, ss.val);
    }
    else if (dd.mode == 2)
    {
        reg[dd.adr] = ss.val;
    }
    get_flag_Z(ss.val);
}

void do_add(){
    word sum;
    if (dd.mode == 0)
    {
        sum = ss.val + reg[dd.adr];
        reg[dd.adr] = sum;
    }
    else if (dd.mode == 2)
    {
        sum = ss.val + reg[dd.adr];
        reg[dd.adr] = sum;
    }
    else if (dd.mode == 1)
    {
        sum = ss.val + w_read(dd.adr);
        w_write(dd.adr, sum);
    }
    /*get_flag_N(sum);
    get_flag_Z(sum);
    get_flag_C(sum);

    printf("\nN = %d Z = %d C = %d \n", flag_N, flag_Z, flag_C);*/
}

void do_incb(){}

void do_movb(){
  if (dd.mode == 0)
    {
        word w;
        if (ss.val >> 7)
            w = (0377 << 8) | ss.val;
        else
            w = ss.val;
        reg[dd.adr] = w;
    }
    else if (dd.mode == 1)
    {
        word w;
        if (ss.val >> 7)
            w = (0377 << 8) | ss.val;
        else
            w = ss.val;
        w_write(dd.adr, w);
    }
    else if (dd.mode == 2)
    {
        word w;
        if (ss.val >> 7)
            w = (0377 << 8) | ss.val;
        else
            w = ss.val;
        reg[dd.adr] = w;
    }
    get_flag_Z(ss.val);
}
void do_nothing(){}

void do_sob(){
    //printf ("\n I am%o\n", r.val);
    r.val -= 1;
    reg[r.adr] -= 1;
    if (r.val != 0)
    {
        pc = pc - nn.val*2;
    }
}

void do_clr(){
    reg[dd.adr] = 0;
}

void do_br(){
    trace ("%o", (pc + 2 * xx.adr) & 0177777);
    pc = (pc + 2* xx.adr) & 0177777;
}

void do_beq(){
    if (flag_Z == 1)
        do_br();
    else
        trace ("%o", (pc + 2 * xx.adr) & 0177777);
}
