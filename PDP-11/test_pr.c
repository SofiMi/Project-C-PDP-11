#include "foo.h"

void test_mem()
{
    // Test 1:
    // Write byte, read byte
    Adress adr_test_1 = 2;
    byte b_test_1 = 0x0a;
    b_write(adr_test_1, b_test_1);
    byte bres_test_1 = b_read(adr_test_1);
    //printf ("byte_write/byte_read \t %02hhx == %02hhx\n", b_test_1, bres_test_1);
    assert (b_test_1 == bres_test_1);

    // Test 2:
    // Write word, read word
    Adress adr_test_2 = 4;
    word w_test_2 = 0x0bac;
    w_write(adr_test_2, w_test_2);
    word wres_test_2 = w_read(adr_test_2);
    //printf("word_write/word_read \t %04hx == %04hx\n", wres_test_2, w_test_2);
    assert(w_test_2 == wres_test_2);

    // Test 3:
    // Write word, read 2 byte
    Adress adr_test_3 = 6;
    word w_test_3 = 0x0b0c;
    w_write(adr_test_3, w_test_3);
    byte b0res_test_3 = b_read(adr_test_3);
    byte b1res_test_3 = b_read(adr_test_3 + 1);
    word wres_test_3 = (b1res_test_3 << 8)|b0res_test_3;
    //printf("word_write/byte_read \t %04hx == %04hx\n", w_test_3, wres_test_3);
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
    //printf("byte_write/word_read \t %04hx == %02hhx%02hhx\n", wres_test_4, b1_test_4, b0_test_4);
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

void test_load()
{
    unsigned int list_byte[] = {0xc0, 0x65, 0x7a, 0x00, 0x3f, 0x10, 0xf8, 0x01, 0x00, 0x00, 0x76, 0x0f};
    for (int i = 0; i < 10; i++)
    {
        printf("%02x == %02x\n", b_read(512 + i), list_byte[i]);
        assert(b_read(0x0200 + i) == list_byte[i]);
    }
}

