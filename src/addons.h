#include "main.h"

#ifndef ADDONS_H
#define ADDONS_H


class Addon {
public:
    Addon() {}
    Addon(float x, float y, float z, int type);
    glm::vec3 position_fuel;
    float rotation;
    float rotation_fuel;
    color_t color_fuel;
    int val_fuel;
    int picked;

    struct bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    int tick_fuel(glm::vec3 position_plane);

private:
    VAO *object;
};

#endif // ADDONS_H
