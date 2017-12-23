#ifndef _LIBSTD_CPP
#define _LIBSTD_CPP

#define NEWLINE_CRLF

// void halt();
// use: none
$("halt")
        J("halt");

// int getchar();
// use: $16, $31
$("getchar")
        LW($16, _device(1, 0));
        BEQ($16, $0, "getchar");
        LW($16, _device(1, 16));
#ifdef NEWLINE_CRLF
        LI($17, '\r');
        BEQ($16, $17, "getchar");
#endif
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
// use: $16 - $17, $31
$("putchar")
#ifdef NEWLINE_CRLF
        LI($17, '\n');
        BEQ($16, $17, "putchar.cr");
        J("putchar.begin");
    $("putchar.cr")
        LW($17, _device(1, 1));
        BEQ($17, $0, "putchar.writecr");
        J("putchar.cr");
    $("putchar.writecr")
        LI($18, '\r');
        SW($18, _device(1, 16));
#endif
    $("putchar.begin")
        LW($17, _device(1, 1));
        BEQ($17, $0, "putchar.write");
        J("putchar.begin");
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
