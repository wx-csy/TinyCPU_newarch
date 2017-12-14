_org(0);
    NOP();

    LI($1, 0);
$("SENDCHAR")
    LW($2, $1, "hw");
    BLEZ($2, "_end");
    SW($2, _device(1, 16));
    ADDIU($1, $1, 4);
    J("SENDCHAR");

$("_end")
    J("_end");

_org(100);
$data("hw", "Hello, world!");
