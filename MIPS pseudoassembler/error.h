#ifndef _ERROR_H
#define _ERROR_H

#include <cstdio>
#include <cstdlib>
#define Assert(cond, fmt, arg...) if (!(cond)) {fprintf(stderr, "Error: "); fprintf(stderr, fmt, ##arg); exit(0);}
#define Warn(cond, fmt, arg...) if(!(cond)) {fprintf(stderr, "Warning: "); fprintf(stderr, fmt, ##arg);}
#define _BITS_LIMIT(a, x) assert((uint32_t)(a) < (((uint32_t)(1))<<(x)))

#endif
