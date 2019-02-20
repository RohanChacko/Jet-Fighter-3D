#include "smokering.h"
#include "main.h"
#include <iostream>

Smokering::Smokering(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);

    // position_arrow = glm::vec3(-1, -1 , -1);
    this->rotation = 0;
    this->color = color;

    this->is_passed = 0;

    //num_triangles: Specify the roundness of the ring shape
    // num_triangles = 100;
    num_circles = 36;

    // GLfloat vertex_buffer_data[1000];

    vertex_buffer_data[0] = -0.5; vertex_buffer_data[1] = -0.5; vertex_buffer_data[2] = 0.0;
    vertex_buffer_data[3] = -0.5; vertex_buffer_data[4] = 0.5; vertex_buffer_data[5] = 0.0;
    vertex_buffer_data[6] = 0.5; vertex_buffer_data[7] = -0.5; vertex_buffer_data[8] = 0.0;

    vertex_buffer_data[9] = 0.5; vertex_buffer_data[10] = -0.5; vertex_buffer_data[11] = 0.0;
    vertex_buffer_data[12] = 0.5; vertex_buffer_data[13] = 0.5; vertex_buffer_data[14] = 0.0;
    vertex_buffer_data[15] = -0.5; vertex_buffer_data[16] = 0.5; vertex_buffer_data[17] = 0.0;

    for(int j = 1;j<num_circles;++j)
    {
      for(int i = 0;i<18;i+=3)
      {
        vertex_buffer_data[18*j+i] =  vertex_buffer_data[18*j+i - 18]*cosf(10*M_PI/180.0f) + vertex_buffer_data[18*j+i+1 - 18]*sinf(10*M_PI/180.0f) + 0.55;
        vertex_buffer_data[18*j+i+ 1] = -1*vertex_buffer_data[18*j+i - 18]*sinf(10*M_PI/180.0f) + vertex_buffer_data[18*j+i+1 - 18]*cosf(10*M_PI/180.0f);
        vertex_buffer_data[18*j+i+ 2] = 0;
      };
    }

    this->object = create3DObject(GL_TRIANGLES, num_circles*6, vertex_buffer_data, color, GL_FILL);
}

void Smokering::draw(glm::mat4 VP) {

  if(!this->is_passed)
  {
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
}

int Smokering::tick(glm::vec3 position_plane) {

  if(
      position_plane.x + 3.5 >= this->position.x &&
      position_plane.x <= this->position.x + 3.5 &&
      position_plane.y + 1.5 < this->position.y &&
      position_plane.y + 7.5 >= this->position.y &&
      abs(abs(position_plane.z) - abs(this->position.z)) <= 0.5 &&
      this->is_passed==0
    )
    {
      // CREDITS - SHASHWAT
      // std::cout<<"Passed this one: "<<passed_count<<" "<<position_plane.z<<" "<<this->position.z <<"\n";
      this->is_passed = 1;
      return 50;
    }

    return 0;
}

void Smokering::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, 0);
}
