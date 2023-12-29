#include <stdarg.h>

#include "drivers/video/framebuffer.h"
#include "drivers/cursor.h"


uint8_t XPOS = 0;
uint8_t YPOS = 0;

enum fb_colors_e BgColor = FB_BLACK;
enum fb_colors_e FgColor = FB_WHITE;

void __fb_write(uint16_t fbc, int index) {
    *((uint16_t *)FB_VIDEO_MEM + index) = fbc;
    cursor_move(index+1);
}

void fb_write_char(char c) {
    if (c == '\n') {
        YPOS++;
        XPOS = 0;
        return;
    }
    if (c == '\t') {
        XPOS += 4;
        return;
    }

    int index = XPOS + YPOS * FB_COLS;
    fb_character_t fbc = {
        .character = c,
        .bg_color = BgColor,
        .fg_color = FgColor,
    };
    __fb_write(fbc.data, index);

    XPOS++;
    if (XPOS >= FB_COLS) {
        XPOS = 0;
        YPOS++;
    }

    if (YPOS >= FB_ROWS) {
        XPOS = 0;
        YPOS = FB_ROWS - 1;

        for (int y = 1; y < FB_ROWS; y++) {
            for (int x = 0; x < FB_COLS; x++) {
                uint16_t index = x + y * FB_COLS;
                __fb_write(
                    *((uint16_t *)FB_VIDEO_MEM + index),
                    index - FB_COLS);
            }
        }
    }
}

const char NUMBER_MAP[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

// Can print upto hexadecimal (base 16 numbers)
void __fb_write_number(uint64_t number, uint8_t base) {
    if (number == 0) return;

    __fb_write_number(number / base, base);
    fb_write_char(NUMBER_MAP[number % base]);
}

void fb_write(char *msg) {
    while (*msg != '\0') {
        fb_write_char(*msg);
        msg++;
    }
}

void clrscr() {
    for (int y = 0; y < FB_ROWS; y++) {
        for (int x = 0; x < FB_COLS; x++) {
            int i = x + y * FB_COLS;
            fb_character_t fbc = {
                .character = ' ',
                .bg_color = BgColor,
                .fg_color = FgColor,
            };
            __fb_write(fbc.data, i);
        }
    }

    XPOS = YPOS = 0;
}

void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    uint64_t v;

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case '%':
                    fb_write_char('%');
                    break;
                case 'c':
                    fb_write_char((char)va_arg(args, int));
                    break;
                case 's':
                    fb_write(va_arg(args, char *));
                    break;
                case 'd':
                    v = va_arg(args, uint64_t);
                    if (v == 0) {
                        fb_write_char('0');
                    } else {
                        __fb_write_number(v, 10);
                    }
                    break;
                case 'x':
                case 'X':
                    v = va_arg(args, uint64_t);
                    if (v == 0) {
                        fb_write_char('0');
                    } else {
                        __fb_write_number(v, 16);
                    }
                    break;
                case 'b':
                case 'B':
                    v = va_arg(args, uint64_t);
                    if (v == 0) {
                        fb_write_char('0');
                    } else {
                        __fb_write_number(v, 2);
                    }
                    break;
                default:
                    printf("(%%%c)?", *format);
            }
        } else {
            fb_write_char(*format);
        }
        format++;
    }

    va_end(args);
}