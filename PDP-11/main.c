#include "foo.h"

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);
void load_file(const char * filename);
void test_mem();
void test_load();


int main(int argc, char* argv[]){
    test_mem();
    load_file(argv[1]);
    test_load();
    return 0;
}
