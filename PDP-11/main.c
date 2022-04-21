#include "foo.h"

int main(int argc, char* argv[]){
    test_mem();
    load_file(argv[1]);
    test_load();
    run();
    return 0;
}

