#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void draw_missile(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(glm::vec3 position_plane);
    double speed;
    int ticker;
    int toggle_missile;
    glm::vec3 position_missile;
    glm::vec3 recorded_position_plane;
private:
    VAO *object_enemy;
    VAO *object_missile;
    VAO *structure;
};

#endif // ENEMY_H