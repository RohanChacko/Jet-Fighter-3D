#include "main.h"

#ifndef LAND_H
#define LAND_H


class Land {
public:
    Land() {}
    Land(float x, float z, color_t color);
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float speed);

private:
    VAO *object;
    VAO *temp;
};

#endif // LAND_H
