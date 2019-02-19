#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    
    color_t color;
    int val;

    int is_hit;

    struct bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    int tick(glm::vec3 position_plane);

private:
    VAO *object;
};

#endif // PARACHUTE_H
