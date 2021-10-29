#include <haruhi/console.h>
#include <haruhi/string.h>
#include <haruhi/types.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20
#define VGA_CELLS (VGA_WIDTH*VGA_HEIGHT)
#define VGA_BUFFER 0xB8000

static u8 cursor_x;
static u8 cursor_y;

enum
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_PURPLE,
	VGA_COLOR_BROWN,
	VGA_COLOR_GRAY,
	VGA_COLOR_DARK_GRAY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_PURPLE,
	VGA_COLOR_YELLOW,
	VGA_COLOR_WHITE
};

static void putchar(char c)
{
	*(u16 *)(VGA_BUFFER + 2 * (cursor_x + VGA_WIDTH * cursor_y)) = c
						| VGA_COLOR_WHITE << 8
						| VGA_COLOR_BLACK << 12;
}

void console_init(void)
{
	cursor_x = 0;
	cursor_y = 0;
	console_clear();
}

void console_clear(void)
{
	for (size_t i = 0; i < VGA_CELLS; ++i)
		*(u16 *)(VGA_BUFFER+2*i) = VGA_COLOR_BLACK << 12;
}

void asprintk(const char *str)
{
	for (size_t i = 0; i < strlen(str); i++) {
		switch (str[i]) {
		case '\n':
			cursor_x = 0;
			cursor_y++;
			break;
		default:
			putchar(str[i]);
			cursor_x = (cursor_x + 1) % VGA_WIDTH;
			break;
		}
	}
}

