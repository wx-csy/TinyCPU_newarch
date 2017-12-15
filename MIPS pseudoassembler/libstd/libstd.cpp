$("halt")
        J("halt");

$("getchar")
        LW($16, _device(1, 0));
        BLEZ($16, "getchar");
        LW($16, _device(1, 16));
        JR($31);

$("putchar")
        LW($17, _device(1, 1));
        BLEZ($17, "putchar.write");
        J("putchar");
    $("putchar.write")
        SW($16, _device(1, 16));
        JR($31);

$("print")
        MOV($20, $16);
        MOV($21, $31);
    $("print.nextchar")
        LW($22, $20, 0);
        ANDI($16, $22, 0xff);
        BLEZ($16, "print.end");
        JAL("putchar");
        SRL($22, $22, 8);
        ANDI($16, $22, 0xff);
        BLEZ($16, "print.end");
        JAL("putchar");
        SRL($22, $22, 8);
        ANDI($16, $22, 0xff);
        BLEZ($16, "print.end");
        JAL("putchar");
        SRL($16, $22, 8);
        BLEZ($16, "print.end");
        JAL("putchar");
        ADDIU($20, $20, 4);
        J("print.nextchar");
    $("print.end")
        JR($21);
