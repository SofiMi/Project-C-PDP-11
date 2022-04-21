#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Adress;        // 16 bit

#define MEMSIZE (64*1024)

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);
void load_file(const char * filename);
void test_mem();
void test_load();
trace(const char *format, ...);
void run();
