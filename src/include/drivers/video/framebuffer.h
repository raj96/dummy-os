#ifndef __FRAMEBUFFER_H
#define __FRAMEBUFFER_H

#include "stdint.h"
#include "stddef.h"

#define FB_VIDEO_MEM 0x000b8000

#define FB_COLS 80
#define FB_ROWS 25

// Framebuffer Colors
enum FramebufferColors {
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
		enum FramebufferColors fg_color:4;
		enum FramebufferColors bg_color:4;
	};
} FramebufferCharacter_t;

typedef struct __attribute__((packed)) {
	uint8_t XPOS, YPOS;
	enum FramebufferColors BgColor, FgColor;
} Framebuffer_t;

void initialize_framebuffer();
void destroy_framebuffer();

extern volatile Framebuffer_t *framebuffer;

extern enum FramebufferColors
	BgColor,
	FgColor;

extern uint8_t 
	XPOS,
	YPOS;

void fb_write(char *msg);
void clrscr();

#endif
