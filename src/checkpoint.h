#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z, color_t color);
    glm::vec3 position_checkpoint;
    glm::vec3 position_arrow;
    glm::vec3 position_initial;
    float radius;
    float rotation;
    float toggle_bit;
    float rotation_arrow_x;
    float rotation_arrow_y;
    float rotation_arrow_z;

    void draw(glm::mat4 VP, int passed_count);
    void draw_arrow(glm::mat4 VP);

    void set_position(float x, float y, float z);

    int tick(glm::vec3 position_plane, int passed_count);
    void tick_arrow(glm::vec3 position_plane, glm::vec3 position_next_checkpoint);

    double speed;
    int ticker;
    int num_circles;
    int num_triangles;
    int is_passed;
    color_t color;
    GLfloat vertex_buffer_data[1000];
private:
    VAO *object_checkpoint;
    VAO *object_arrow;
    VAO *structure;
};

#endif // CHECKPOINT_H
