#include "drivers/video/framebuffer.h"

uint8_t XPOS = 0;
uint8_t YPOS = 0;

enum FramebufferColors BgColor = FB_BLACK;
enum FramebufferColors FgColor = FB_LIGHT_GREEN;

void __fb_write(uint16_t fbc, int index) {
    *((uint16_t *)FB_VIDEO_MEM + index) = fbc;
}

void fb_write(char *msg) {
    uint16_t i = 0;
    while(msg[i] != '\0') {
        XPOS++;
        
        if(msg[i] == '\n') {
            YPOS++;
            XPOS = 0;
            i++;
            if(msg[i] == '\0') break;
        }


        if(XPOS >= FB_COLS) {
            XPOS = 0;
            YPOS++;
        }
        if(YPOS >= FB_ROWS) {
                // Scroll
                XPOS = 0;
                YPOS = FB_ROWS - 1;
                
                for(int y = 1; y < FB_ROWS; y++) {
                    for(int x = 0; x < FB_COLS; x++) {
                        int index = x + y * FB_COLS;
                        __fb_write(
                            *((uint16_t *)FB_VIDEO_MEM + index),
                            index - FB_COLS
                        );
                    }
                }
            }

        int index = XPOS + YPOS * FB_COLS;
        FramebufferCharacter_t fbc = {
            .character = msg[i],
            .bg_color = BgColor,
            .fg_color = FgColor,
        };
        __fb_write(fbc.data, index);
        i++;
    }
}

void clrscr() {
    for(int y = 0; y < FB_ROWS; y++) {
        for(int x = 0; x < FB_COLS; x++) {
            int i = x + y * FB_COLS;
            FramebufferCharacter_t fbc = {
                .character = ' ',
                .bg_color = BgColor,
                .fg_color = FgColor,
            };
            __fb_write(fbc.data, i);
        }
    }

    XPOS = YPOS = 0;
}