#ifndef _DEVICE_H
#define _DEVICE_H
#include "common.h"
#define _device(devno, port) $0, device(devno, port)
_ADDRESS device(uint32_t devno, uint32_t port){
    _BITS_LIMIT(devno, 5);
    _BITS_LIMIT(port, 10);
    union {
        struct {
            uint32_t port:10;
            uint32_t devno:5;
            uint32_t padding:17;
        };
        _ADDRESS u32_addr;
    } addr;
    addr.devno = devno;
    addr.port = port;
    addr.padding = -1;
    return addr.u32_addr;
}
#endif
