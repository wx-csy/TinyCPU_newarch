_org(128*4);
J("_start");

#include "lib/libstd.cpp"
#include "lib/libstr.cpp"
#include "lib/libchar.cpp"

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

        LOFFSET($16, "buf");    // compare "string"
        LOFFSET($17, "progname.string");
        JAL("strcmp");
        BEQ($16, $0, "cmd.call.string");

        LOFFSET($16, "prog_inexist");
        JAL("print");
        J("cmd");

    $("cmd.call.fib")
        JAL("prog.fib");
        J("cmd");

    $("cmd.call.euclid")
        JAL("prog.euclid");
        J("cmd");

    $("cmd.call.string")
        JAL("prog.string");
        J("cmd");

    _data("welcome", "This is a Tiny CPU demo program. Hello, world!\n");
    _data("intro", "> ");
    _data("prog_inexist", "This program does not exist. Please try again.\n");
    _udata("buf", 40);
    _data("progname.fib", "fib");
    _data("progname.euclid", "euclid");
    _data("progname.string", "string");

$("prog.fib")
        MOV($15, $31);
        LOFFSET($16, "prog.fib.welcome");
        JAL("print");

        // read a number to $1
        LOFFSET($16, "buf");
        JAL("scane");
        LOFFSET($16, "buf");
        JAL("str2int");
        MOV($3, $16);

        LI($1, 0);
        BEQ($3, $0, "prog.fib.end");
        ADDIU($3, $3, -1);
        LI($1, 1);
        BEQ($3, $0, "prog.fib.end");
        ADDIU($3, $3, -1);
        LI($2, 1);
    $("prog.fib.nextloop")
        BEQ($3, $0, "prog.fib.end");
        ADDU($4, $1, $2);
        MOV($2, $1);
        MOV($1, $4);
        MOV($16, $1);
        LOFFSET($17, "buf");
        JAL("int2str");
        LOFFSET($16, "buf");
        JAL("print");
        LI($16, '\n');
        JAL("putchar");
        ADDIU($3, $3, -1);
        J("prog.fib.nextloop");

    $("prog.fib.end")
        // print ans in $1
        LOFFSET($16, "prog.fib.result");
        JAL("print");
        MOV($16, $1);
        LOFFSET($17, "buf");
        JAL("int2str");
        LOFFSET($16, "buf");
        JAL("print");
        LI($16, '\n');
        JAL("putchar");
        JR($15);

        _data("prog.fib.welcome", "Please input a number and press <RETURN>.\n");
        _data("prog.fib.result", "The i-th term of the Fibonacci sequence is: ");


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

        // debug

        // JAL("putchar");
/*
        LOFFSET($17, "buf");
        JAL("int2str");
        LOFFSET($16, "buf");
        JAL("print");
*/
        // end debug

        LOFFSET($16, "buf");
        JAL("scane");
        LOFFSET($16, "buf");
        JAL("str2int");
        MOV($2, $16);

    $("prog.euclid.mainloop")
        BEQ($2, $0, "prog.euclid.end");
        // MOV($16, $0)
        DIVU($1, $2);
        MOV($1, $2);
        MFHI($2);
      //  LI($16, '!');
      //  JAL("putchar");
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

    _data("prog.euclid.welcome", "Please enter two numbers, press <RETURN> after each number.\n");
    _data("prog.euclid.result", "The greatest common divisor (GCD) of the two numbers is ");


$("prog.string")
        MOV($15, $31);
        LOFFSET($16, "prog.string.welcome");
        JAL("print");

        LOFFSET($16, "buf");
        JAL("scane");

    #define len $1
    #define ptr $2
    #define digitcnt $3
    #define alphacnt $4
    #define length $5

        // length
        LOFFSET($16, "prog.string.length");
        JAL("print");
        LOFFSET($16, "buf");
        JAL("strlen");
        MOV(len, $16);
        LOFFSET($17, "prog.string.buf");
        JAL("int2str");
        LOFFSET($16, "prog.string.buf");
        JAL("print");
        LI($16, '\n');
        JAL("putchar");

        MOV(length, len);
        LOFFSET(ptr, "buf");
        LI(digitcnt, 0);
        LI(alphacnt, 0);

    $("prog.string.nextchar")
        BEQ(len, $0, "prog.string.adend");
        LB($6, ptr, 0);
        MOV($16, $6);
        JAL("isdigit");
        ADDU(digitcnt, digitcnt, $16);
        MOV($16, $6);
        JAL("isalpha");
        ADDU(alphacnt, alphacnt, $16);
        ADDIU(ptr, ptr, 1);
        ADDIU(len, len, -1);
        J("prog.string.nextchar");

    $("prog.string.adend")
        LOFFSET($16, "prog.string.ad1");
        JAL("print");
        MOV($16, alphacnt);
        LOFFSET($17, "buf");
        JAL("int2str");
        LOFFSET($16, "buf");
        JAL("print");
        LOFFSET($16, "prog.string.ad2");
        JAL("print");
        MOV($16, digitcnt);
        LOFFSET($17, "buf");
        JAL("int2str");
        LOFFSET($16, "buf");
        JAL("print");
        LOFFSET($16, "prog.string.ad3");
        JAL("print");
        JR($15);

        _data("prog.string.welcome", "Please input a string.\n");
        _data("prog.string.length", "The length of the string is ");
        _data("prog.string.ad1", "There are ");
        _data("prog.string.ad2", " alphabetic letters and ");
        _data("prog.string.ad3", " digits.\n");
        _udata("prog.string.buf", 40);
    #undef length
    #undef ptr
    #undef digitcnt
    #undef alphacnt
