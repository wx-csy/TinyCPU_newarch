_org(0);
    J("boot._start");

$("boot.readchar") // function
        LW($16, _device(1, 0));
        BLEZ($16, "boot.readchar");
        LW($16, _device(1, 16));
        JR($31);

$("boot.writechar")
        LW($17, _device(1, 1));
        BLEZ($17, "boot.writechar.write");
        J("boot.writechar");
    $("boot.writechar.write")
        SW($16, _device(1, 16));
        JR($31);

$("boot._start")
        LI($16, 0x36);
        JAL("boot.writechar");
        LI($16, 0x47);
        JAL("boot.writechar");
        LI($16, 0xf8);
        JAL("boot.writechar");
        LI($16, 0xea);
        JAL("boot.writechar");
        #define szImg $1
        LI(szImg, 0);
        // read size of image
        JAL("boot.readchar");
        OR(szImg, szImg, $16);
        JAL("boot.readchar");
        SLL($16, $16, 8);
        OR(szImg, szImg, $16);
        JAL("boot.readchar");
        SLL($16, $16, 16);
        OR(szImg, szImg, $16);
        JAL("boot.readchar");
        SLL($16, $16, 24);
        OR(szImg, szImg, $16);

        #define checkSum $2
        MOV(checkSum, szImg);
        LI($3, 0);

    $("boot.nextWord")
        BLEZ(szImg, "boot.sendCheckSum");
        LI($4, 0);
        JAL("boot.readchar");
        OR($4, $4, $16);
        JAL("boot.readchar");
        SLL($16, $16, 8);
        OR($4, $4, $16);
        JAL("boot.readchar");
        SLL($16, $16, 16);
        OR($4, $4, $16);
        JAL("boot.readchar");
        SLL($16, $16, 24);
        OR($4, $4, $16);
        SW($4, $3, "start");
        ADDU(checkSum, checkSum, $4);
        ADDIU($3, $3, 4);
        ADDIU(szImg, szImg, -1);
        J("boot.nextWord");

    $("boot.sendCheckSum")
        ANDI($16, checkSum, 0xFF);
        JAL("boot.writechar");
        SRL(checkSum, checkSum, 8);
        ANDI($16, checkSum, 0xFF);
        JAL("boot.writechar");
        SRL(checkSum, checkSum, 8);
        ANDI($16, checkSum, 0xFF);
        JAL("boot.writechar");
        SRL(checkSum, checkSum, 8);
        ANDI($16, checkSum, 0xFF);
        JAL("boot.writechar");

        J("start");

_org(128*4);
$("start")
