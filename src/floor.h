#include "main.h"

#ifndef FLOOR_H
#define FLOOR_H


class Floors {
public:
    Floors() {}
    Floors(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float speed);
    int toggle_bit;
private:
    VAO *object;
};

#endif // FLOOR_H
