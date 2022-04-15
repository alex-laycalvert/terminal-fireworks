#include <ncurses.h>
#include <unistd.h>

#include "firework.hpp"

int main(int argc, char **argv) {
    (void)argc, (void)argv;
    initscr();
    noecho();
    raw();
    keypad(stdscr, true);
    curs_set(0);
    nodelay(stdscr, true);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    Firework firework1(rows - 2, cols / 4, 5, 15);
    Firework firework2(rows - 5, 3 * cols / 4, 5, 10);
    while (1) {
        if (getch() == 'q') break;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) mvprintw(i, j, " ");
        firework1.display();
        firework1.update();
        firework2.display();
        firework2.update();
        usleep(100000);
    }
    endwin();
}
