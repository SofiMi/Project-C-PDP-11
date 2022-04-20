#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Adress;        // 16 bit

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);
void load_file();

void test_mem()
{
    // Test 1:
    // Write byte, read byte
    Adress adr_test_1 = 2;
    byte b_test_1 = 0x0a;
    b_write(adr_test_1, b_test_1);
    byte bres_test_1 = b_read(adr_test_1);
    printf ("byte_write/byte_read \t %02hhx == %02hhx\n", b_test_1, bres_test_1);
    assert (b_test_1 == bres_test_1);

    // Test 2:
    // Write word, read word
    Adress adr_test_2 = 4;
    word w_test_2 = 0x0bac;
    w_write(adr_test_2, w_test_2);
    word wres_test_2 = w_read(adr_test_2);
    printf("word_write/word_read \t %04hx == %04hx\n", wres_test_2, w_test_2);
    assert(w_test_2 == wres_test_2);

    // Test 3:
    // Write word, read 2 byte
    Adress adr_test_3 = 6;
    word w_test_3 = 0x0b0c;
    w_write(adr_test_3, w_test_3);
    byte b0res_test_3 = b_read(adr_test_3);
    byte b1res_test_3 = b_read(adr_test_3 + 1);
    word wres_test_3 = (b1res_test_3 << 8)|b0res_test_3;
    printf("word_write/byte_read \t %04hx == %04hx\n", w_test_3, wres_test_3);
    assert(w_test_3 == wres_test_3);

    // Test 4:
    // Write 2 byte - write word
    Adress adr_test_4 = 8;
    byte b1_test_4 = 0x0b;
    byte b0_test_4 = 0x0a;
    word w_test_4 = 0x0b0a;
    b_write(adr_test_4, b0_test_4);
    b_write(adr_test_4 + 1, b1_test_4);
    word wres_test_4 = w_read(adr_test_4);
    printf("byte_write/word_read \t %04hx == %02hhx%02hhx\n", wres_test_4, b1_test_4, b0_test_4);
    assert(w_test_4 == wres_test_4);

    // Test 5:
    // We check if the program is inoperable when writing an odd address
    Adress adr_test_5 = 7;
    byte b_test_5 = 0x0a;
    word w_test_5 = 0x0b0a;
    // We comment so as not to be scared every time:
    // if we write an odd address, the program will immediately tell us about it
    //w_write(adr_test_5, w_test_5);
    //w_read(adr_test_5);

}

int main(){
    test_mem();
    load_file();
    return 0;
}

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

void load_file()
{
    FILE * fin  = fopen("data.txt", "r");

    Adress adr_start_block;
    int number_byte;
    byte now_byte;
    while (fscanf ("%x %x", &adr_start_block, &number_byte) == 2)
    {
        for (int i = 0; i < number_byte; i++)
            {
                scanf ("%x", &now_byte);
                b_write (adr_start_block, now_byte);
                adr_start_block++;
            }
    }
    fclose(fin);
}
