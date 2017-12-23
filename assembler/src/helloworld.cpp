_org(128*4);
J("start");

#include "libstd/libstd.cpp"

$("start")
    LI($16, '\n');
    JAL("putchar");
    LI($16, 1024);
    JAL("print");
    JAL("halt");

_org(1024);
    $data("hw", "Hello, world!\n");
