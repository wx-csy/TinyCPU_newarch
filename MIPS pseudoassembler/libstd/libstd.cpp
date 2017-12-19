#ifndef _LIBSTD_CPP
#define _LIBSTD_CPP

// void halt();
// use: none
$("halt")
        J("halt");

// int getchar();
// use: $16 - $19, $31
$("getchar")
        LW($16, _device(1, 0));
        BEQ($16, $0, "getchar");
        LW($16, _device(1, 16));
        JR($31);

// int getce();
// use: $16 - $19, $31
/*
$("getce")
        LW($16, _device(1, 0));
        BEQ($16, $0, "getce");
        LW($16, _device(1, 16));
    $("getce.wait")
        LW($17, _device(1, 1));
        BEQ($17, $0, "getce.write");
        J("getce.wait");
    $("getce.write")
        SW($16, _device(1, 16));
        JR($31);
*/
// void putchar(int)
// use: $16 - $19, $31
$("putchar")
        LW($17, _device(1, 1));
        BEQ($17, $0, "putchar.write");
        J("putchar");
    $("putchar.write")
        SW($16, _device(1, 16));
        JR($31);

// void print(const char*)
// use: $16 - $23, $31
$("print")
        MOV($20, $16);
        MOV($21, $31);
    $("print.nextchar")
        LB($22, $20, 0);
        ANDI($16, $22, 0xff);
        BEQ($16, $0, "print.end");
        JAL("putchar");
        ADDIU($20, $20, 1);
        J("print.nextchar");
    $("print.end")
        JR($21);

// void scan(char*)
// use $16 - $23, $31
$("scan")
        MOV($20, $16);
        MOV($21, $31);
    $("scan.nextchar")
        JAL("getchar");
        LI($17, '\n');
        BEQ($16, $17, "scan.end");
        SB($16, $20, 0);
        ADDIU($20, $20, 1);
        J("scan.nextchar");
    $("scan.end")
        SB($0, $20, 0);
        JR($21);

// void scane(char*)
// use $16 - $23, $31
$("scane")
        MOV($20, $16);
        MOV($21, $31);
    $("scane.nextchar")
        JAL("getchar");
        JAL("putchar");
        LI($17, '\n');
        BEQ($16, $17, "scane.end");
        SB($16, $20, 0);
        ADDIU($20, $20, 1);
        J("scane.nextchar");
    $("scane.end")
        SB($0, $20, 0);
        JR($21);

#endif
