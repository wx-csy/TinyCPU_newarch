#ifndef _LIBSTR_CPP
#define _LIBSTR_CPP

// void int2str(unsigned, char*)
// use: $16 - $27, $31
$("int2str")
        MOV($18, $17);
        LI($19, 10);
    $("int2str.nextdigit")
        DIVU($16, $19);
        MFHI($16); // remainder
        //
        // SW($16, _device(1, 16));
        //
        ADDIU($16, $16, '0');
        SB($16, $18, 0);
        ADDIU($18, $18, 1);
        MFLO($16); // quotient
        BEQ($16, $0, "int2str.nullchar");
        J("int2str.nextdigit");
    $("int2str.nullchar")
        SB($0, $18, 0);
        ADDIU($18, $18, -1);
    $("int2str.reverse")
        SUBU($16, $18, $17);
        BLEZ($16, "int2str.end");
        LB($16, $17, 0);
        LB($19, $18, 0);
        SB($16, $18, 0);
        SB($19, $17, 0);
        ADDIU($17, $17, 1);
        ADDIU($18, $18, -1);
        J("int2str.reverse");
    $("int2str.end")
        JR($31);

// unsigned str2int(const char*)
// use: $16 ~ $19, $31
$("str2int")
        LI($17, 0);
    $("str2int.nextchar")
        LB($19, $16, 0);
        BEQ($19, $0, "str2int.end");
        ADDIU($19, $19, -'0');
        SLL($18, $17, 2);
        ADDU($17, $17, $18);
        ADDU($17, $17, $17);
        ADDU($17, $17, $19);
        ADDIU($16, $16, 1);
        J("str2int.nextchar");
    $("str2int.end")
        MOV($16, $17);
        JR($31);

// int strcmp(const char*, const char*)
// use: $16 ~ $19, $31
$("strcmp")
        LB($18, $16, 0);
        LB($19, $17, 0);
        BEQ($18, $19, "strcmp.chareq");   // str[i] == str[j]
        SUBU($16, $18, $19);
        JR($31);
    $("strcmp.chareq")
        BEQ($19, $0, "strcmp.eqend");
        ADDIU($16, $16, 1);
        ADDIU($17, $17, 1);
        J("strcmp");
    $("strcmp.eqend")
        LI($16, 0);
        JR($31);

// int strlen(const char*)
// use: $16 ~ $19, $31
$("strlen")
        LI($17, 0);
    $("strlen.nextchar")
        LB($18, $16, 0);
        BEQ($18, $0, "strlen.end");
        ADDIU($16, $16, 1);
        ADDIU($17, $17, 1);
        J("strlen.nextchar");
    $("strlen.end")
        MOV($16, $17);
        JR($31);
#endif
