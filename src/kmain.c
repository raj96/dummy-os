#include "drivers/video/framebuffer.h"

int kmain() {
	// initialize_framebuffer();
    // framebuffer->BgColor = FB_CYAN;
	clrscr();
	fb_write("Booting DummyOS for a dummy :)\n");
	// destroy_framebuffer();
    while (1) {}
}
