
#include <cctype>
#ifndef LIBCHAR_CPP
#define LIBCHAR_CPP

// int isdigit(int);
// use: $16 , $31
$("isdigit")
        ADDIU($16, $16, - '0');
        SLTIU($16, $16, 10);
        JR($31);

// int isdigit(int);
// use: $16 , $31
$("isalpha")
        ORI($16, $16, 32);
        ADDIU($16, $16, - 'a');
        SLTIU($16, $16, 26);
        JR($31);

// int isdigit(int);
// use: $16 , $31
$("islower")
        ADDIU($16, $16, - 'a');
        SLTIU($16, $16, 26);
        JR($31);

// int isdigit(int);
// use: $16 , $31
$("isupper")
        ADDIU($16, $16, - 'A');
        SLTIU($16, $16, 26);
        JR($31);

// int toupper(int);
// use $16 - $19, $31
$("toupper")
        ORI($17, $16, 32);
        ADDIU($17, $17, - 'a');
        SLTIU($17, $17, 26);
        SLL($17, $17, 5);
        OR($16, $16, $17);
        JR($31);

// int tolower(int);
// use $16 - $19, $31
$("tolower")
        ORI($17, $16, 32);
        ADDIU($17, $17, - 'a');
        SLTIU($17, $17, 26);
        SLL($17, $17, 5);
        NOT($17, $17);
        AND($16, $16, $17);
        JR($31);

#endif
