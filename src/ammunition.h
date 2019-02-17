#include "main.h"

#ifndef AMMUNITION_H
#define AMMUNITION_H

#define MAX_BOMB_STOCK 100
#define MAX_MISSILE_STOCK 75


class Ammunition {
public:
    Ammunition() {}
    Ammunition(glm::vec3 position_plane, color_t color);
    glm::vec3 position_bomb[MAX_BOMB_STOCK];
    glm::vec3 position_missile[MAX_MISSILE_STOCK];



    int active_bomb[MAX_BOMB_STOCK];
    int active_missile[MAX_MISSILE_STOCK];
    int timer_bomb[MAX_BOMB_STOCK];
    int timer_missile[MAX_MISSILE_STOCK];
    int bomb_stock;
    int missile_stock;

    void draw_bomb(glm::mat4 VP);
    void draw_missile(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int move, glm::vec3 position);

private:
    VAO *object_bomb;
    VAO *object_missile;
};

#endif // AMMUNITION_H
