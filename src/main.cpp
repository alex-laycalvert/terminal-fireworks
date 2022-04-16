#include <getopt.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include <ctime>
#include <random>
#include <vector>

#include "firework.hpp"

#define DEFAULT_MAX_FIREWORKS 15
#define DEFAULT_SPAWN_RATE 5
#define DEFAULT_MIN_SIZE 4
#define DEFAULT_MAX_SIZE 8
#define DEFAULT_MIN_TTL 10
#define DEFAULT_MAX_TTL 15
#define DEFAULT_START 0

#define OPTIONS "hm:s:z:Z:t:T:S:"

using std::rand;
using std::vector;

static const struct option longopts[] = {
    {.name = "help", .has_arg = no_argument, .val = 'h'},
    {.name = "max-fireworks", .has_arg = required_argument, .val = 'm'},
    {.name = "spawn-rate", .has_arg = required_argument, .val = 's'},
    {.name = "min-size", .has_arg = required_argument, .val = 'z'},
    {.name = "max-size", .has_arg = required_argument, .val = 'Z'},
    {.name = "min-ttl", .has_arg = required_argument, .val = 't'},
    {.name = "max-ttl", .has_arg = required_argument, .val = 'T'},
    {.name = "start", .has_arg = required_argument, .val = 'S'},
};

void usage(char *name) {
    printf("usage: ./fireworks [options]\n");
    printf("\n");
    printf("options:\n");
    printf("\n");
    printf("    -h, --help               display this message\n");
    printf(
        "    -m N, --max-fireworks N  set max number of fireworks on screen at "
        "any time to N\n");
    printf(
        "    -s N, --spawn-rate N     increase the spawning rate of fireworks "
        "to "
        "N (1-10)\n");
    printf(
        "    -z N, --min-size N       set the minimum size of each firework to "
        "N\n");
    printf(
        "    -Z N, --max-size N       set the maximum size of each firework to "
        "N\n");
    printf(
        "    -t N, --min-ttl N        set the minimum living time of each "
        "firework to N\n");
    printf(
        "    -T N, --max-ttl N        set the maximum living time of each "
        "firework to N\n");
    printf(
        "    -S N, --start N          set the starting row offset from the "
        "bottom of the terminal to N\n");
}

int main(int argc, char **argv) {
    int max_fireworks, spawn_rate, min_size, max_size, min_ttl, max_ttl, start;
    initscr();
    noecho();
    raw();
    keypad(stdscr, true);
    curs_set(0);
    nodelay(stdscr, true);
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    endwin();

    max_fireworks = DEFAULT_MAX_FIREWORKS;
    spawn_rate = 11 - DEFAULT_SPAWN_RATE;
    min_size = DEFAULT_MIN_SIZE;
    max_size = DEFAULT_MAX_SIZE;
    min_ttl = DEFAULT_MIN_TTL;
    max_ttl = DEFAULT_MAX_TTL;
    start = rows - DEFAULT_START;

    int opt;
    while ((opt = getopt_long(argc, argv, OPTIONS, longopts, NULL)) != -1) {
        switch (opt) {
            case 'h':
                usage(argv[0]);
                break;
            case 'm':
                max_fireworks = atoi(optarg);
                break;
            case 's':
                spawn_rate = 11 - atoi(optarg);
                break;
            case 'z':
                min_size = atoi(optarg);
                break;
            case 'Z':
                max_size = atoi(optarg);
                break;
            case 't':
                min_ttl = atoi(optarg);
                break;
            case 'T':
                max_ttl = atoi(optarg);
                break;
            case 'S':
                start = rows - atoi(optarg);
                break;
            default:
                usage(argv[0]);
                break;
        }
    }

    // TODO argument bounds checking

    vector<Firework> fireworks;
    int spawn_counter = 0;
    while (1) {
        if (getch() == 'q') break;
        if (fireworks.size() < max_fireworks && spawn_counter == 0) {
            Firework f(start, (rand() % (cols - 2)) + 1,
                       (rand() % (max_size - min_size)) + min_size,
                       (rand() % (max_ttl - min_ttl) + min_ttl));
            fireworks.push_back(f);
        }
        for (int i = 0; i < fireworks.size(); i++) {
            if (!fireworks[i].update()) fireworks.erase(fireworks.begin() + i);
            fireworks[i].display();
        }
        refresh();
        usleep(100000);
        spawn_counter = ++spawn_counter % spawn_rate;
    }
    endwin();
}
