#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_z;
    float rotation_y;
    float radius;
    void draw(glm::mat4 VP, glm::vec3& cam_position, glm::vec3& target_position);
    void set_position(float x, float y, float z);
    void tick(int move, glm::vec3& cam_position, glm::vec3& target_position);
    double speed;
    int ticker;
    float fuel;
    int health;
    glm::mat4 orc;
    int score;

private:
    VAO *object;
    VAO *structure;
};

#endif // AIRPLANE_H
