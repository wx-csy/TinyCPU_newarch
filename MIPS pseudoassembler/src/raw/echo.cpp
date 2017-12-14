_org(0);
    NOP();
    LI($3, 'H');
    SW($3, _device(1, 16));
$("START")
    LW($1, _device(1, 0));
    BLEZ($1, "START");
$("SEND");
    LW($2, _device(1, 16));
    SW($2, _device(1, 16));
    J("START");
