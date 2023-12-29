#ifndef __FRAMEBUFFER_H
#define __FRAMEBUFFER_H

#include "nostd/stdint.h"
#include "nostd/stddef.h"

#define FB_VIDEO_MEM 0x000b8000

#define FB_COLS 80
#define FB_ROWS 25

// Framebuffer Colors
enum fb_colors_e {
	FB_BLACK,
	FB_BLUE,
	FB_GREEN,
	FB_CYAN,
	FB_RED,
	FB_MAGENTA,
	FB_BROWN,
	FB_LIGHT_GRAY,
	FB_DARK_GRAY,
	FB_LIGHT_BLUE,
	FB_LIGHT_GREEN,
	FB_LIGHT_CYAN,
	FB_LIGHT_RED,
	FB_LIGHT_MAGENTA,
	FB_LIGHT_BROWN,
	FB_WHITE
};

typedef union __attribute__((packed)) {
	uint16_t data;
	struct {
		char character:8;
		enum fb_colors_e fg_color:4;
		enum fb_colors_e bg_color:4;
	};
} fb_character_t;

typedef struct __attribute__((packed)) {
	uint8_t XPOS, YPOS;
	enum fb_colors_e BgColor, FgColor;
} fb_t;

void fb_init();
void fb_destroy();

extern volatile fb_t *framebuffer;

extern enum fb_colors_e
	BgColor,
	FgColor;

extern uint8_t 
	XPOS,
	YPOS;

void fb_write(char *msg);
void clrscr();
void printf(const char *format, ...);

#endif
