#ifndef FIREWORK_HPP
#define FIREWORK_HPP

class Firework {
   public:
    int row;
    int col;
    int size;
    int ttl;
    int age;
    int explode_count;
    int explode_radius;
    bool exploding = true;
    Firework(const int row, const int col, const int size, const int ttl);
    ~Firework();
    void display();
    bool update();
};

#endif  // FIREWORK_HPP
