#include "volcano.h"
#include "main.h"
#include <iostream>


Volcano::Volcano(float x, float z) {

    this->position = glm::vec3(x, 25, z);

    GLfloat vertex_buffer_data[] = {

        -30.0f,-4.0f,-30.0f,
        -30.0f,-4.0f, 30.0f,
        -30.0f, 4.0f, 30.0f,
         30.0f, 4.0f,-30.0f,
        -30.0f,-4.0f,-30.0f,
        -30.0f, 4.0f,-30.0f,
         30.0f,-4.0f, 30.0f,
        -30.0f,-4.0f,-30.0f,
         30.0f,-4.0f,-30.0f,
         30.0f, 4.0f,-30.0f,
         30.0f,-4.0f,-30.0f,
        -30.0f,-4.0f,-30.0f,
        -30.0f,-4.0f,-30.0f,
        -30.0f, 4.0f, 30.0f,
        -30.0f, 4.0f,-30.0f,
         30.0f,-4.0f, 30.0f,
        -30.0f,-4.0f, 30.0f,
        -30.0f,-4.0f,-30.0f,
        -30.0f, 4.0f, 30.0f,
        -30.0f,-4.0f, 30.0f,
         30.0f,-4.0f, 30.0f,
         30.0f, 4.0f, 30.0f,
         30.0f,-4.0f,-30.0f,
         30.0f, 4.0f,-30.0f,
         30.0f,-4.0f,-30.0f,
         30.0f, 4.0f, 30.0f,
         30.0f,-4.0f, 30.0f,
         30.0f, 4.0f, 30.0f,
         30.0f, 4.0f,-30.0f,
        -30.0f, 4.0f,-30.0f,
         30.0f, 4.0f, 30.0f,
        -30.0f, 4.0f,-30.0f,
        -30.0f, 4.0f, 30.0f,
         30.0f, 4.0f, 30.0f,
        -30.0f, 4.0f, 30.0f,
         30.0f,-4.0f, 30.0f,

       -20.0f, 4.0f,-20.0f,
       -20.0f, 4.0f, 20.0f,
       -20.0f, 12.0f, 20.0f,
        20.0f, 12.0f,-20.0f,
       -20.0f, 4.0f,-20.0f,
       -20.0f, 12.0f,-20.0f,
        20.0f, 4.0f, 20.0f,
       -20.0f, 4.0f,-20.0f,
        20.0f, 4.0f,-20.0f,
        20.0f, 12.0f,-20.0f,
        20.0f, 4.0f,-20.0f,
       -20.0f, 4.0f,-20.0f,
       -20.0f, 4.0f,-20.0f,
       -20.0f, 12.0f, 20.0f,
       -20.0f, 12.0f,-20.0f,
        20.0f, 4.0f, 20.0f,
       -20.0f, 4.0f, 20.0f,
       -20.0f, 4.0f,-20.0f,
       -20.0f, 12.0f, 20.0f,
       -20.0f, 4.0f, 20.0f,
        20.0f, 4.0f, 20.0f,
        20.0f, 12.0f, 20.0f,
        20.0f, 4.0f,-20.0f,
        20.0f, 12.0f,-20.0f,
        20.0f, 4.0f,-20.0f,
        20.0f, 12.0f, 20.0f,
        20.0f, 4.0f, 20.0f,
        20.0f, 12.0f, 20.0f,
        20.0f, 12.0f,-20.0f,
       -20.0f, 12.0f,-20.0f,
        20.0f, 12.0f, 20.0f,
       -20.0f, 12.0f,-20.0f,
       -20.0f, 12.0f, 20.0f,
        20.0f, 12.0f, 20.0f,
       -20.0f, 12.0f, 20.0f,
        20.0f, 4.0f, 20.0f,

        -15.0f, 12.0f,-15.0f,
        -15.0f, 12.0f, 15.0f,
        -15.0f, 20.0f, 15.0f,
         15.0f, 20.0f,-15.0f,
        -15.0f, 12.0f,-15.0f,
        -15.0f, 20.0f,-15.0f,
         15.0f, 12.0f, 15.0f,
        -15.0f, 12.0f,-15.0f,
         15.0f, 12.0f,-15.0f,
         15.0f, 20.0f,-15.0f,
         15.0f, 12.0f,-15.0f,
        -15.0f, 12.0f,-15.0f,
        -15.0f, 12.0f,-15.0f,
        -15.0f, 20.0f, 15.0f,
        -15.0f, 20.0f,-15.0f,
         15.0f, 12.0f, 15.0f,
        -15.0f, 12.0f, 15.0f,
        -15.0f, 12.0f,-15.0f,
        -15.0f, 20.0f, 15.0f,
        -15.0f, 12.0f, 15.0f,
         15.0f, 12.0f, 15.0f,
         15.0f, 20.0f, 15.0f,
         15.0f, 12.0f,-15.0f,
         15.0f, 20.0f,-15.0f,
         15.0f, 12.0f,-15.0f,
         15.0f, 20.0f, 15.0f,
         15.0f, 12.0f, 15.0f,
         15.0f, 20.0f, 15.0f,
         15.0f, 20.0f,-15.0f,
        -15.0f, 20.0f,-15.0f,
         15.0f, 20.0f, 15.0f,
        -15.0f, 20.0f,-15.0f,
        -15.0f, 20.0f, 15.0f,
         15.0f, 20.0f, 15.0f,
        -15.0f, 20.0f, 15.0f,
         15.0f, 12.0f, 15.0f,
    };

    GLfloat lava[500];
    for(int i = 0;i<50;i++)
    {
      lava[9*i] = 0.0f;
      lava[9*i+1] = 20.5f;
      lava[9*i+2] = 0.0f;
      lava[9*i+3] = 10.0f*cosf(2*3.14159265*i/50);
      lava[9*i+4] = 20.5f;
      lava[9*i+5] = 10.0f*sinf(2*3.14159265*i/50);
      lava[9*i+6] = 10.0f*cosf((2*3.14159265*(i+1))/50);
      lava[9*i+7] = 20.5f;
      lava[9*i+8] = 10.0f*sinf((2*3.14159265*(i+1))/50);
    };

    this->object = create3DObject(GL_TRIANGLES, 108 , vertex_buffer_data, COLOR_BROWN, GL_FILL);
    this->lava = create3DObject(GL_TRIANGLES, 3*50 , lava, COLOR_ORANGE, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {

    glm::mat4 MVP;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->lava);
}

void Volcano::tick(glm::vec3 position_plane) {
    // this->rotation += speed;
    // this->position.z += speed;

}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
