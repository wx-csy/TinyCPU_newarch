_org(128*4);
J("start");

#include "libstd/libstd.cpp"

$("start")
    LI($16, '\n');
    JAL("putchar");
    LOFFSET($16, "hw");
    JAL("print");
    JAL("halt");

_data("hw", "Hello, world!\n");