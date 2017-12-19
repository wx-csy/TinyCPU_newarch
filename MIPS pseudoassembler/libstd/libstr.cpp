#ifndef _LIBSTR_CPP
#define _LIBSTR_CPP

// void int2str(unsigned, char*)
// use: $16 - $19, $31
$("int2str")
        MOV($18, $17);
        LI($19, 10);
    $("int2str.nextdigit")
        DIVU($16, $19);
        MFHI($16); // remainder
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
        SUBU($16, $17, $18);
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
        LI($18, 10);
    $("str2int.nextchar")
        LB($19, $16, 0);
        BEQ($19, $0, "str2int.end");
        ADDIU($19, $19, -'0');
        MULTU($17, $18);
        MFLO($17);
        ADDU($17, $17, $19);
        J("str2int.nextchar");
    $("str2int.end")
        MOV($16, $17);
        JR($31);

// int strcmp(const char*, const char*)
// use: $16 ~ $19, $31
$("strcmp")
        LB($19, $16, 0);
        LB($20, $17, 0);
        BEQ($19, $20, "strcmp.eqend");   // str[i] == str[j]
        SLT($16, $20, $19);              // str[i] > str[j]
        BEQ($16, $0, "strcmp.lessthan"); // str[i] < str[j]
        JR($31);
    $("strcmp.lessthan")
        LI($16, -1);
        JR($31);
    $("strcmp.chareq")
        BEQ($19, $0, "strcmp.eqend");
        ADDIU($16, $16, 1);
        ADDIU($17, $17, 1);
        J("strcmp");
    $("strcmp.eqend")
        LI($16, 0);
        JR($31);

#endif // _LIBSTR_CPP
