#include "land.h"
#include "main.h"
#include <iostream>

Land::Land(float x, float z,color_t color) {

    this->position = glm::vec3(x, 7, z);

    static const GLfloat vertex_buffer_data[] = {

        -500.0f,-15.0f,-500.0f,
        -500.0f,-15.0f, 500.0f,
        -500.0f, 15.0f, 500.0f,
         500.0f, 15.0f,-500.0f,
        -500.0f,-15.0f,-500.0f,
        -500.0f, 15.0f,-500.0f,
         500.0f,-15.0f, 500.0f,
        -500.0f,-15.0f,-500.0f,
         500.0f,-15.0f,-500.0f,
         500.0f, 15.0f,-500.0f,
         500.0f,-15.0f,-500.0f,
        -500.0f,-15.0f,-500.0f,
        -500.0f,-15.0f,-500.0f,
        -500.0f, 15.0f, 500.0f,
        -500.0f, 15.0f,-500.0f,
         500.0f,-15.0f, 500.0f,
        -500.0f,-15.0f, 500.0f,
        -500.0f,-15.0f,-500.0f,
        -500.0f, 15.0f, 500.0f,
        -500.0f,-15.0f, 500.0f,
         500.0f,-15.0f, 500.0f,
         500.0f, 15.0f, 500.0f,
         500.0f,-15.0f,-500.0f,
         500.0f, 15.0f,-500.0f,
         500.0f,-15.0f,-500.0f,
         500.0f, 15.0f, 500.0f,
         500.0f,-15.0f, 500.0f,
         500.0f, 15.0f, 500.0f,
         500.0f, 15.0f,-500.0f,
        -500.0f, 15.0f,-500.0f,
         500.0f, 15.0f, 500.0f,
        -500.0f, 15.0f,-500.0f,
        -500.0f, 15.0f, 500.0f,
         500.0f, 15.0f, 500.0f,
        -500.0f, 15.0f, 500.0f,
         500.0f,-15.0f, 500.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void Land::draw(glm::mat4 VP) {

    glm::mat4 MVP;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Land::tick(float speed) {
    // this->rotation += speed;
    // this->position.z += speed;

}

void Land::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
