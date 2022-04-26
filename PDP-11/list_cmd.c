typedef struct {
    word mask;
    word opcode;
    char * name;
    void (* do_func)();
} Command;

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
    {0177700, 0105200, "incb", do_incb}, //b052dd
    {0170000, 0110000, "movb", do_movb},
    {0177777, 0000000, "halt", do_halt},
    {0000000, 0000000, "nothing", do_nothing}
};
