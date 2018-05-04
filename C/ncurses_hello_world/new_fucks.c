#include <ncurses.h>

int
main(void)
{
	initscr();
	raw();

	mvprintw(14, 15, "Hello, world!");

	getch();

	endwin();
}
