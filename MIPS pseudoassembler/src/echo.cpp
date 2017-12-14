_org(128*4);
J("start");

#include "libstd/libstd.cpp"

$("start")
    JAL("getchar");
    JAL("putchar");
    J("start");
