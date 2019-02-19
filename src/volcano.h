#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float z);
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(glm::vec3 position_plane, GLFWwindow *window);

private:
    VAO *object;
    VAO *lava;
};

#endif // VOLCANO_H
