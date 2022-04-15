#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include <ctime>
#include <random>

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

    Firework *fireworks;
    fireworks = (Firework *)malloc(10 * sizeof(Firework));

    for (int i = 0; i < 10; i++) {
        Firework f(rows - 5, i * cols / 11 + 4, std::rand() % 5 + 4,
                   std::rand() % 10 + 5);
        fireworks[i] = f;
    }

    int spawn_counter = 0;
    while (1) {
        if (getch() == 'q') break;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) mvprintw(i, j, " ");
        for (int i = 0; i < 10; i++) {
            fireworks[i].display();
            if (!fireworks[i].update()) {
                Firework f(rows - 5, fireworks[i].col, std::rand() % 3 + 4,
                           std::rand() % 10 + 5);
                fireworks[i] = f;
            }
        }
        refresh();
        spawn_counter = ++spawn_counter % 3;
        usleep(100000);
    }
    free(fireworks);
    endwin();
}
