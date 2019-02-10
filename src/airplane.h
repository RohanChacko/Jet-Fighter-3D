#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_z;
    float rotation_y;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(int move);
    double speed;
    int ticker;
    int rotate_sign[3];
private:
    VAO *object;
    VAO *structure;
};

#endif // AIRPLANE_H
