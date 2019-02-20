#include "main.h"

#ifndef SMOKERING_H
#define SMOKERING_H


class Smokering {
public:
    Smokering() {}
    Smokering(float x, float y, float z, color_t color);
    glm::vec3 position;

    float radius;
    float rotation;
    float toggle_bit;

    void draw(glm::mat4 VP);

    void set_position(float x, float y, float z);

    int tick(glm::vec3 position_plane);


    double speed;
    int ticker;
    int num_circles;
    int num_triangles;
    int is_passed;
    color_t color;
    GLfloat vertex_buffer_data[1000];
private:
    VAO *object;
    VAO *structure;
};

#endif // SMOKERING_H
