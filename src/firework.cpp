#include "firework.hpp"

#include <ncurses.h>

Firework::Firework(const int row, const int col, const int size,
                   const int ttl) {
    this->row = row;
    this->col = col;
    this->size = size;
    this->ttl = ttl;
    this->age = 0;
    this->explode_count = 0;
    this->explode_radius = 6;
    this->exploding = false;
}

Firework::~Firework() {}

void Firework::display() {
    if (!exploding) {
        mvprintw(row - size, col, "^");
        for (int i = row - size + 1; i < row; i++) mvprintw(i, col, "|");
        return;
    }
    if (explode_count > explode_radius) return;
    mvprintw(row - size - explode_count, col, "*");
    mvprintw(row - size - explode_count, col + explode_count, "*");
    mvprintw(row - size, col + explode_count, "*");
    mvprintw(row - size + explode_count, col + explode_count, "*");
    mvprintw(row - size + explode_count, col, "*");
    mvprintw(row - size + explode_count, col - explode_count, "*");
    mvprintw(row - size, col - explode_count, "*");
    mvprintw(row - size - explode_count, col - explode_count, "*");
    explode_count++;
}

void Firework::update() {
    if (!exploding) {
        age++;
        row--;
    }
    if (row - size <= 0 || age >= ttl) {
        exploding = true;
    }
}
