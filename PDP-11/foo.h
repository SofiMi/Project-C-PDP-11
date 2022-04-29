#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Adress;        // 16 bit

typedef struct{
    word val;  // значение аргумента
    word adr;
    int mode;
}Arg;

#define MEMSIZE (64*1024)

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);
void load_file(const char * filename);
void test_mem();
void test_load();
void trace(const char *format, ...);
void run();

void trace_all(void);
void b_write_reg(Adress adr, byte b);
byte b_read_reg(Adress adr);
void w_write_reg(Adress adr, word w);
word w_read_reg(Adress adr);
Arg mode_reg(word w);

Arg get_N(word w);
Arg get_R(word w);

