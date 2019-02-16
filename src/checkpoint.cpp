#include "checkpoint.h"
#include "main.h"
#include <iostream>

Checkpoint::Checkpoint(float x, float y, float z, color_t color) {
    this->position_checkpoint = glm::vec3(x, y, z);
    this->position_initial = glm::vec3(x, y, z);
    // position_arrow = glm::vec3(-1, -1 , -1);
    this->rotation = 0;

    rotation_arrow_x = 0;
    rotation_arrow_y = 0;
    rotation_arrow_z = 0;

    int random = rand();
    if(random%2 == 0)
      this->toggle_bit = -1;
    else
      this->toggle_bit = 1;

    this->is_passed = 0;

    //num_triangles: Specify the roundness of the ring shape
    // num_triangles = 100;
    num_circles = 36;

    static GLfloat vertex_buffer_data[1000];

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

    this->object_checkpoint = create3DObject(GL_TRIANGLES, num_circles*6, vertex_buffer_data, color, GL_FILL);

    static GLfloat arrow_vertex_buffer_data[50];

    arrow_vertex_buffer_data[0] = -0.15; arrow_vertex_buffer_data[1] = -0.25; arrow_vertex_buffer_data[2] = 0.0;
    arrow_vertex_buffer_data[3] = -0.15; arrow_vertex_buffer_data[4] = 0.25; arrow_vertex_buffer_data[5] = 0.0;
    arrow_vertex_buffer_data[6] = 0.15; arrow_vertex_buffer_data[7] = -0.25; arrow_vertex_buffer_data[8] = 0.0;

    arrow_vertex_buffer_data[9] = 0.15; arrow_vertex_buffer_data[10] = -0.25; arrow_vertex_buffer_data[11] = 0.0;
    arrow_vertex_buffer_data[12] = 0.15; arrow_vertex_buffer_data[13] = 0.25; arrow_vertex_buffer_data[14] = 0.0;
    arrow_vertex_buffer_data[15] = -0.15; arrow_vertex_buffer_data[16] = 0.25; arrow_vertex_buffer_data[17] = 0.0;


    arrow_vertex_buffer_data[18] = -0.30; arrow_vertex_buffer_data[19] = 0.25; arrow_vertex_buffer_data[20] = 0.0;
    arrow_vertex_buffer_data[21] = 0.30; arrow_vertex_buffer_data[22] = 0.25; arrow_vertex_buffer_data[23] = 0.0;
    arrow_vertex_buffer_data[24] = 0.0; arrow_vertex_buffer_data[25] = 0.5; arrow_vertex_buffer_data[26] = 0.0;

    this->object_arrow = create3DObject(GL_TRIANGLES, 3*3, arrow_vertex_buffer_data, color, GL_FILL);

}

void Checkpoint::draw(glm::mat4 VP, int passed_count) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position_checkpoint);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_checkpoint);
}

void Checkpoint::draw_arrow(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position_arrow);    // glTranslatef
    glm::mat4 rotate_x    = glm::rotate((float) (rotation_arrow_x), glm::vec3(1, 0, 0));
    glm::mat4 rotate_z    = glm::rotate((float) (rotation_arrow_z), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate_x * rotate_z);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_arrow);

}


void Checkpoint::tick_arrow(glm::vec3 position_plane, glm::vec3 position_next_checkpoint)
{
  this->position_arrow = position_plane;

  this->position_arrow.y -= 2.0;
  this->position_arrow.z += 3.0;

  float del_z_1 = abs(position_next_checkpoint.z);
  float del_z_2 = abs(position_plane.z);

  float del_y_1 = abs(position_next_checkpoint.y);
  float del_y_2 = abs(position_plane.y);

  float del_x_1 = abs(position_next_checkpoint.x);
  float del_x_2 = abs(position_plane.x);

  float diver_x, diver_z,dz,dy,dx, sign = 1.0f, sign_x = 1.0f;

  if(position_plane.y > position_next_checkpoint.y)
    dy = del_y_2 - del_y_1;
  else
    dy = del_y_1 - del_y_2;

  if(position_plane.x > position_next_checkpoint.x && position_next_checkpoint.x >= 0)
  {
    dx = del_x_2 - del_x_1;
    sign_x = 1.0f;
  }
  else if(position_plane.x < position_next_checkpoint.x && position_next_checkpoint.x < 0)
  {
    dx = del_x_2 - del_x_1;
    sign_x = -1.0f;
  }
  else if(position_plane.x > 0 && position_next_checkpoint.x < 0)
  {
    dx = del_x_1 + del_x_2;
    sign_x = 1.0f;
  }
  else if(position_plane.x < 0 && position_next_checkpoint.x > 0)
  {
    dx = del_x_1 + del_x_2;
    sign_x = -1.0f;
  }
  else if(position_plane.x < position_next_checkpoint.x && position_plane.x >= 0)
  {
    dx = del_x_1 - del_x_2;
    sign_x = -1.0f;
  }
  else
  {
    dx = del_x_1 - del_x_2;
    sign_x = 1.0f;
  }


  if(position_plane.z < position_next_checkpoint.z)
  {  dz = del_z_2 - del_z_1;
    sign = 1.0f;
  }
  else if(position_plane.z > 0)
  {
     dz = del_z_1 + del_z_2;
     sign = -1.0f;
  }
  else
    {
      dz = del_z_1 - del_z_2;
      sign = -1.0f;
    }

  diver_x = (dy)/(dz);
  diver_x *= sign;

  if(position_next_checkpoint.z - position_plane.z == 0 || abs(position_next_checkpoint.y) - abs(position_plane.y) == 0)
    rotation_arrow_x = 90*M_PI/180.0f;
  else
    rotation_arrow_x = atanf(diver_x);

  diver_z = dy/dx;
  diver_z *= sign_x;

  if(position_next_checkpoint.x - position_plane.x == 0 || abs(position_next_checkpoint.y) - abs(position_plane.y) == 0)
    rotation_arrow_z = 90*M_PI/180.0f;
  else
    rotation_arrow_z = atanf(diver_z);
  // if(position_plane.z < position_next_checkpoint.z)
  //   rotation_arrow_x*=-1.0f;

  // std::cout<<"tick fn: "<<rotation_arrow_x*180.0f/M_PI<<" "<< position_next_checkpoint.y<<" "<< position_next_checkpoint.z<<"\n";

}


int Checkpoint::tick(glm::vec3 position_plane, int passed_count) {

  if(
      position_plane.x + 3.5 >= this->position_checkpoint.x &&
      position_plane.x <= this->position_checkpoint.x + 3.5 &&
      position_plane.y + 1.5 < this->position_checkpoint.y &&
      position_plane.y + 7.5 >= this->position_checkpoint.y &&
      abs(abs(position_plane.z) - abs(this->position_checkpoint.z)) <= 0.5 &&
      this->is_passed==0
    )
    {
      ++passed_count;
      // std::cout<<"Passed this one: "<<passed_count<<" "<<position_plane.z<<" "<<this->position_checkpoint.z <<"\n";
      this->is_passed = 1;
    }

    //Oscillate checkpoint
    this->position_checkpoint.x += toggle_bit*0.05;

    if(this->position_checkpoint.x - this->position_initial.x > 1.5)
    {
      toggle_bit*=-1;
    }
    else if(this->position_checkpoint.x - this->position_initial.x < -1.5)
    {
      toggle_bit*=-1;
    }
    return passed_count;
}

void Checkpoint::set_position(float x, float y, float z) {
    this->position_checkpoint = glm::vec3(x, y, 0);
}
