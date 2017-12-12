#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>
#include <assert.h>

typedef struct {uint8_t index;} _REGISTER;

#define _IMMEDIATE uint16_t
#define _ADDRESS uint32_t

#include "reg.h"
#include "error.h"
#endif
