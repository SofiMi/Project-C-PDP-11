#include "foo.h"

byte mem[MEMSIZE];

void b_write(Adress adr, byte b)
{
    mem[adr] = b;
}

byte b_read(Adress adr)
{
    return mem[adr];
}

void w_write(Adress adr, word w)
{
   assert(0 == adr % 2);
   // Write to the 1 byte
   b_write(adr + 1, w >> 8);
   // Write to the 2 byte
   b_write(adr, w & 0xFF);
}

word w_read(Adress adr)
{
    assert(0 == adr % 2);
    // Read to the 1 byte
    word w = ((word)mem[adr + 1]) << 8;
    // Read to the 2 byte
    w = w | mem[adr];
    return w;
}
