$("getchar")
        LW($16, _device(1, 0));
        BLEZ($16, "getc");
        LW($16, _device(1, 16));
        JR($31);

$("putchar")
        LW($17, _device(1, 1));
        BLEZ($17, "putc.write");
        J("putc");
    $("putc.write")
        SW($16, _device(1, 16));
        JR($31);
