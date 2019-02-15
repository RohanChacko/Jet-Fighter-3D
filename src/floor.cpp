#include "floor.h"
#include "main.h"
#include <iostream>

Floors::Floors(float x, float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->toggle_bit = -1;
    static const GLfloat vertex_buffer_data[] = {
        -500.0f, 0.0f, 500.0f, // triangle 1 : begin
        -500.0f, 0.0f, -500.0f,
         500.0f, 0.0f, -500.0f, // triangle 1 : end

        -500.0f, 0.0f, 500.0f, // triangle 2 : begin
         500.0f, 0.0f, 500.0f,
        500.0f, 0.0f, -500.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Floors::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Floors::tick(float speed) {
    // this->rotation += speed;
    // this->position.z += speed;
    this->position.y += toggle_bit*0.08;

    if(this->position.y <= -2.5)
    {
      toggle_bit*=-1;
    }
    else if(this->position.y >= 1.5)
    {
      toggle_bit*=-1;
    }
}

void Floors::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
