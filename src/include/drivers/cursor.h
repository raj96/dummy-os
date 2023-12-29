#ifndef __CURSOR_H
#define __CURSOR_H

#include "nostd/stdint.h"

#define CURSOR_CMD_PORT 0x3d4
#define CURSOR_DATA_PORT 0x3d5

#define CURSOR_CMD_HIGH_BITS 0xe
#define CURSOR_CMD_LOW_BITS 0xf

void cursor_move(uint16_t index);

#endif