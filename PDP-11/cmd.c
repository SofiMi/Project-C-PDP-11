#include "foo.h"
extern void do_halt();
extern void do_mov();
extern void do_add();
extern void do_incb();
extern void do_movb();
extern void do_nothing();
extern void do_sob();
extern void do_clr();
extern void do_br();
extern void do_beq();
extern void do_bpl();
extern void do_tstb();

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (* do_func)();
    char params;
} Command;

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov, 3},
    {0170000, 0060000, "add", do_add, 3},
    {0177700, 0105200, "incb", do_incb, 3}, //b052dd
    {0170000, 0110000, "movb", do_movb, 3},
    {0177777, 0000000, "halt", do_halt, 0},
    {0177000, 0077000, "sob", do_sob, 12},
    {0177700, 0005000, "clr", do_clr, 1},
    {0177400, 0000400, "br", do_br, 16}, // 0177400 так как хотим узнать лишь про 1
    {0177700, 0001400, "beq", do_beq, 16},
    {0177400, 0100000, "bpl", do_bpl, 16},
    {0177700, 0105700, "tstb", do_tstb, 1},
    {0000000, 0000000, "unknow", do_nothing, 0},
    {0000000, 0000000, "exit", do_nothing, 0}
};
