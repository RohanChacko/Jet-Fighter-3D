#include "ammunition.h"
#include "main.h"
#include <iostream>

Ammunition::Ammunition(glm::vec3 position_plane, color_t color) {

    for(int i = 0;i<MAX_BOMB_STOCK; ++i)
      active_bomb[i] = 0;
    for(int i = 0;i<MAX_BOMB_STOCK; ++i)
      timer_bomb[i] = 0;

    for(int i = 0;i<MAX_MISSILE_STOCK; ++i)
      active_missile[i] = 0;
    for(int i = 0;i<MAX_MISSILE_STOCK; ++i)
      timer_missile[i] = 0;

    bomb_stock = MAX_BOMB_STOCK;
    missile_stock = MAX_MISSILE_STOCK;

    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
    };

    static const GLfloat missile_vertex_buffer_data[] = {
      -0.5f,-0.5f,-2.0f,
      -0.5f,-0.5f, 2.0f,
      -0.5f, 0.5f, 2.0f,
      0.5f, 0.5f,-2.0f,
      -0.5f,-0.5f,-2.0f,
      -0.5f, 0.5f,-2.0f,
      0.5f,-0.5f, 2.0f,
      -0.5f,-0.5f,-2.0f,
      0.5f,-0.5f,-2.0f,
      0.5f, 0.5f,-2.0f,
      0.5f,-0.5f,-2.0f,
      -0.5f,-0.5f,-2.0f,
      -0.5f,-0.5f,-2.0f,
      -0.5f, 0.5f, 2.0f,
      -0.5f, 0.5f,-2.0f,
      0.5f,-0.5f, 2.0f,
      -0.5f,-0.5f, 2.0f,
      -0.5f,-0.5f,-2.0f,
      -0.5f, 0.5f, 2.0f,
      -0.5f,-0.5f, 2.0f,
      0.5f,-0.5f, 2.0f,
      0.5f, 0.5f, 2.0f,
      0.5f,-0.5f,-2.0f,
      0.5f, 0.5f,-2.0f,
      0.5f,-0.5f,-2.0f,
      0.5f, 0.5f, 2.0f,
      0.5f,-0.5f, 2.0f,
      0.5f, 0.5f, 2.0f,
      0.5f, 0.5f,-2.0f,
      -0.5f, 0.5f,-2.0f,
      0.5f, 0.5f, 2.0f,
      -0.5f, 0.5f,-2.0f,
      -0.5f, 0.5f, 2.0f,
      0.5f, 0.5f, 2.0f,
      -0.5f, 0.5f, 2.0f,
      0.5f,-0.5f, 2.0f,
    };

    this->object_bomb = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
    this->object_missile = create3DObject(GL_TRIANGLES, 36, missile_vertex_buffer_data, color, GL_FILL);
}

void Ammunition::draw_missile(glm::mat4 VP) {
    glm::mat4 MVP;

    for(int i = 0;i<MAX_MISSILE_STOCK - missile_stock; ++i)
    {
      Matrices.model = glm::mat4(1.0f);
      glm::mat4 translate = glm::translate (this->position_missile[i]);
      Matrices.model *= (translate); // * rotate);
      MVP = VP * Matrices.model;
      glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(this->object_missile);
    }
}

void Ammunition::draw_bomb(glm::mat4 VP) {
    glm::mat4 MVP;

    for(int i = 0;i< MAX_BOMB_STOCK; ++i)
    {
      Matrices.model = glm::mat4(1.0f);
      glm::mat4 translate = glm::translate (this->position_bomb[i]);    // glTranslatef
      // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
      // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
      // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
      Matrices.model *= (translate); // * rotate);
      glm::mat4 MVP = VP * Matrices.model;
      glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(this->object_bomb);
    }
}

void Ammunition::tick(int move, glm::vec3 airplane_position) {

  if(move == 5)
  {
      bomb_stock--;
      active_bomb[MAX_BOMB_STOCK - bomb_stock - 1] = 1;
      this->position_bomb[MAX_BOMB_STOCK - bomb_stock - 1] = airplane_position;
      this->position_bomb[MAX_BOMB_STOCK - bomb_stock - 1].z -= 0.085;
      this->position_bomb[MAX_BOMB_STOCK - bomb_stock - 1].y -= 0.005;
  }

  for(int i = 0;i<MAX_BOMB_STOCK - bomb_stock; ++i)
  {
    if(active_bomb[i])
    {
      timer_bomb[i]++;
      this->position_bomb[i].z -= 0.085;
      this->position_bomb[i].y -= 0.005*timer_bomb[i];
    }

    if(this->position_bomb[i].y <= -6.0)
    {
      active_bomb[i] = 0;
      timer_bomb[i] = 0;
    }
  }

  if(move == 6)
  {
      missile_stock--;
      active_missile[MAX_MISSILE_STOCK - missile_stock - 1] = 1;
      this->position_missile[MAX_MISSILE_STOCK - missile_stock - 1] = airplane_position;
      // this->position_missile.y -= 0.085;
      // this->position_missile.z -= 0.005;
  }

  for(int i = 0;i<MAX_MISSILE_STOCK; ++i)
  {
    if(active_missile[i])
    {
      timer_missile[i]++;
      this->position_missile[i].y -= 0.085;
      this->position_missile[i].z -= 0.005*timer_missile[i];
    }

    if(this->position_missile[i].z <= -500)
    {
      active_missile[i] = 0;
      timer_missile[i] = 0;
    }
  }

  //collision detection

  // ammunition_kill();

  // std::cout<<this->position.x<<" "<<this->position.y<<"\n";
}

void Ammunition::set_position(float x, float y) {
    // this->position = glm::vec3(x, y, 0);
}
