#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *structure;
};

#endif // AIRPLANE_H
