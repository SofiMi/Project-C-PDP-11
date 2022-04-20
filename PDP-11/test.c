#include "define.c"

void test_mem()
{
    byte b0 = 0x0a;
    // Пишем байт, читаем байт
    b_write(2, b0);
    byte bres = b_read(2);
    printf ("%02hhx == %02hhx\n", b0, bres);

    // Пишем 2 байта - читаем одно слово
    Adress a = 4;
    byte b1 = 0xcb;
    b0 = 0x0a;
    word w = 0x0b0a;
    b_write(a, b0);
    b_write(a + 1, b1);
    word wres = w_read(a);
    printf("word_write/byte_read \t %04hx == %02hhx%02hhx\n", wres, b1, b0);
}
