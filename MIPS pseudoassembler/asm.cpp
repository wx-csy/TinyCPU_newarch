_org(128*4);
J("_start");

#include "libstd/libstd.cpp"
#include "libstd/libstr.cpp"

$("_start")
        LI($16, '\n');
        JAL("putchar");
        LOFFSET($16, "welcome");
        JAL("print");

$("cmd")
        LOFFSET($16, "intro");
        JAL("print");
        LOFFSET($16, "buf");
        JAL("scane");

        LOFFSET($16, "buf");    // compare "fib"
        LOFFSET($17, "progname.fib");
        JAL("strcmp");
        BEQ($16, $0, "cmd.call.fib");

        LOFFSET($16, "buf");    // compare "euclid"
        LOFFSET($17, "progname.euclid");
        JAL("strcmp");
        BEQ($16, $0, "cmd.call.euclid");

        LOFFSET($16, "prog_inexist");
        JAL("print");
        J("cmd");

    $("cmd.call.fib")
        JAL("prog.fib");
        J("cmd");

    $("cmd.call.euclid")
        JAL("prog.euclid");
        J("cmd");

    _data("welcome", "This is a Tiny CPU demo program. Hello, world!\n");
    _data("intro", "> ");
    _data("prog_inexist", "This program does not exist. Please try again.\n");
    _udata("buf", 20);
    _data("progname.fib", "fib");
    _data("progname.euclid", "euclid");

$("prog.fib")
        MOV($15, $31);

        JR($15);

$("prog.euclid")
        MOV($15, $31);
        LOFFSET($16, "prog.euclid.welcome");
        JAL("print");

        // read two numbers to $1 and $2
        LOFFSET($16, "buf");
        JAL("scane");
        LOFFSET($16, "buf");
        JAL("str2int");
        MOV($1, $16);
        LOFFSET($16, "buf");
        JAL("scane");
        LOFFSET($16, "buf");
        JAL("str2int");
        MOV($2, $16);

    $("prog.euclid.mainloop")
        BEQ($2, $0, "prog.euclid.end");
        DIVU($1, $2);
        MOV($1, $2);
        MFHI($2);
        J("prog.euclid.mainloop");

    $("prog.euclid.end")
        // print ans in $1
        LOFFSET($16, "prog.euclid.result");
        JAL("print");
        MOV($16, $1);
        LOFFSET($17, "buf");
        JAL("int2str");
        LOFFSET($16, "buf");
        JAL("print");
        LI($16, '\n');
        JAL("putchar");
        JR($15);

    _data("prog.euclid.welcome", "Please enter two numbers, press <return> after each number.");
    _data("prog.euclid.result", "The greatest common divisor of these two numbers are: ");

