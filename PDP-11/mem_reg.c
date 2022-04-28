#include "foo.h"

word reg[8];

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

void trace_all(void)
{
    for(int i = 0; i < 7; i++)
        trace("R%d %06o  ", i, reg[i]);
    trace ("pc %06o", reg[7]);
    trace("\n");
}
