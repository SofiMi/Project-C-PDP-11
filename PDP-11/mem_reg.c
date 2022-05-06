#include "foo.h"

word reg[8];
extern char byte_n;

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
            if (byte_n)
                res.val = b_read(res.adr);
            else
                res.val = w_read(res.adr); //!!! b_read
            trace("(R%o) ", r);
            res.mode = 1;
            break;

        case 2: // (R3)+ #3
            res.adr = reg[r];
            if (byte_n)
            {
                res.val = b_read(res.adr); //!!! b_read
                reg[r] += 1;
            }
            else
            {
                res.val = w_read(res.adr);
                reg[r] += 2;
            }
            res.mode = 2;
            if (r == 7)
                trace("#%o ", res.val);
            else
                trace("(R%o)+", r);
            break;

        case 3:
            res.adr = reg[r];
            res.adr = w_read(res.adr);
            res.val = w_read(res.adr);
            reg[r] += 2;
            res.mode = 3;
            if (r == 7)
                trace("@#%o ", res.adr);
            else
                trace("@(R%o)+ ", r);
            break;

        case 4:
            if (byte_n)
            {
                reg[r] -= 1;
            }
            else
            {
                reg[r] -= 2;
            }
            res.adr = reg[r];
            res.val = w_read(res.adr);
            res.mode = 4;
            trace("-(Rn)");
            break;

        default:
            fprintf(stderr, "Mode %o NOT IMPLEMENTED YET!!!\n", mode);
            exit(1);
    }
    return res;
}

Arg get_N(word w)
{
    Arg res;
    res.val =  w & 63;
    return res;
}

Arg get_R(word w)
{
    Arg res;
    res.adr = (w >> 6) & 7;
    res.val =  reg[(w >> 6) & 7];
    //printf ("\n word = %o res = %o", w, res.val);
    return res;
}

Arg get_XX(word w)
{
    Arg res;
    res.adr = w & 255;
    if ((res.adr >> 7 & 1) == 1)
    {
        res.adr = (256 - res.adr) * (-1);
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
