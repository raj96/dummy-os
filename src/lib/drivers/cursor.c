#include "kutils/io.h"
#include "drivers/cursor.h"

void cursor_move(uint16_t index) {
    io_write(CURSOR_CMD_PORT, CURSOR_CMD_LOW_BITS);
    io_write(CURSOR_DATA_PORT, index & 0xff);
    io_write(CURSOR_CMD_PORT, CURSOR_CMD_HIGH_BITS);
    io_write(CURSOR_DATA_PORT, (index >> 8) & 0xff);
}