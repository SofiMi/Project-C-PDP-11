#include <stdlib.h>
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

void test_mem()
{
    // Тест 1:
    // Пишем байт, читаем байт
    Adress adr_test_1 = 2;
    byte b_test_1 = 0x0a;
    b_write(adr_test_1, b_test_1);
    byte bres_test_1 = b_read(adr_test_1);
    printf ("byte_write/byte_read \t %02hhx == %02hhx\n", b_test_1, bres_test_1);
    assert (b_test_1 == bres_test_1);

    // Тест 2:
    // Пишем слово - читаем слово
    Adress adr_test_2 = 4;
    word w_test_2 = 0x0bac;
    w_write(adr_test_2, w_test_2);
    word wres_test_2 = w_read(adr_test_2);
    printf("word_write/word_read \t %04hx == %04hx\n", wres_test_2, w_test_2);
    assert(w_test_2 == wres_test_2);

    // Тест 3:
    // Пишем слово - читаем 2 байта
    Adress adr_test_3 = 6;
    word w_test_3 = 0x0b0c;
    w_write(adr_test_3, w_test_3);
    byte b0res_test_3 = b_read(adr_test_3);
    byte b1res_test_3 = b_read(adr_test_3 + 1);
    word wres_test_3 = (b1res_test_3 << 8)|b0res_test_3;
    printf("word_write/byte_read \t %04hx == %04hx\n", w_test_3, wres_test_3);
    assert(w_test_3 == wres_test_3);

    // Тест 4:
    // Пишем 2 байта - читаем одно слово
    Adress adr_test_4 = 8;
    byte b1_test_4 = 0x0b;
    byte b0_test_4 = 0x0a;
    word w_test_4 = 0x0b0a;
    b_write(adr_test_4, b0_test_4);
    b_write(adr_test_4 + 1, b1_test_4);
    word wres_test_4 = w_read(adr_test_4);
    printf("byte_write/word_read \t %04hx == %02hhx%02hhx\n", wres_test_4, b1_test_4, b0_test_4);
    assert(w_test_4 == wres_test_4);
}

int main(){
    test_mem();
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
   // Записываем в первый байт
   b_write(adr + 1, w >> 8);
   // Записываем во второй байт
   b_write(adr, w & 0xFF);
}

word w_read(Adress adr)
{
    // Читаем первый байт
    word w = ((word)mem[adr + 1]) << 8;
    // Читаем второй байт
    w = w | mem[adr];
    return w;
}
