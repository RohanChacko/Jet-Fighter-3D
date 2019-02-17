#include "enemy.h"
#include "main.h"
#include <iostream>

Enemy::Enemy(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->toggle_missile = 0;
    this->pass_x = INT_MIN;

    this->pass_z = INT_MIN;

    static const GLfloat vertex_buffer_data[] = {
        -3.0f,-1.0f,-3.0f, // triangle 1 : begin
        -3.0f,-1.0f, 3.0f,
        -3.0f, 1.0f, 3.0f, // triangle 1 : end
        3.0f, 1.0f,-3.0f, // triangle 2 : begin
        -3.0f,-1.0f,-3.0f,
        -3.0f, 1.0f,-3.0f, // triangle 2 : end
        3.0f,-1.0f, 3.0f,
        -3.0f,-1.0f,-3.0f,
        3.0f,-1.0f,-3.0f,
        3.0f, 1.0f,-3.0f,
        3.0f,-1.0f,-3.0f,
        -3.0f,-1.0f,-3.0f,
        -3.0f,-1.0f,-3.0f,
        -3.0f, 1.0f, 3.0f,
        -3.0f, 1.0f,-3.0f,
        3.0f,-1.0f, 3.0f,
        -3.0f,-1.0f, 3.0f,
        -3.0f,-1.0f,-3.0f,
        -3.0f, 1.0f, 3.0f,
        -3.0f,-1.0f, 3.0f,
        3.0f,-1.0f, 3.0f,
        3.0f, 1.0f, 3.0f,
        3.0f,-1.0f,-3.0f,
        3.0f, 1.0f,-3.0f,
        3.0f,-1.0f,-3.0f,
        3.0f, 1.0f, 3.0f,
        3.0f,-1.0f, 3.0f,
        3.0f, 1.0f, 3.0f,
        3.0f, 1.0f,-3.0f,
        -3.0f, 1.0f,-3.0f,
        3.0f, 1.0f, 3.0f,
        -3.0f, 1.0f,-3.0f,
        -3.0f, 1.0f, 3.0f,
        3.0f, 1.0f, 3.0f,
        -3.0f, 1.0f, 3.0f,
        3.0f,-1.0f, 3.0f
    };

    static const GLfloat missile_vertex_buffer_data[] = {
      -0.5f,-0.5f,-4.0f, // triangle 1 : begin
      -0.5f,-0.5f, 4.0f,
      -0.5f, 0.5f, 4.0f, // triangle 1 : end
      0.5f, 0.5f,-4.0f, // triangle 4 : begin
      -0.5f,-0.5f,-4.0f,
      -0.5f, 0.5f,-4.0f, // triangle 4 : end
      0.5f,-0.5f, 4.0f,
      -0.5f,-0.5f,-4.0f,
      0.5f,-0.5f,-4.0f,
      0.5f, 0.5f,-4.0f,
      0.5f,-0.5f,-4.0f,
      -0.5f,-0.5f,-4.0f,
      -0.5f,-0.5f,-4.0f,
      -0.5f, 0.5f, 4.0f,
      -0.5f, 0.5f,-4.0f,
      0.5f,-0.5f, 4.0f,
      -0.5f,-0.5f, 4.0f,
      -0.5f,-0.5f,-4.0f,
      -0.5f, 0.5f, 4.0f,
      -0.5f,-0.5f, 4.0f,
      0.5f,-0.5f, 4.0f,
      0.5f, 0.5f, 4.0f,
      0.5f,-0.5f,-4.0f,
      0.5f, 0.5f,-4.0f,
      0.5f,-0.5f,-4.0f,
      0.5f, 0.5f, 4.0f,
      0.5f,-0.5f, 4.0f,
      0.5f, 0.5f, 4.0f,
      0.5f, 0.5f,-4.0f,
      -0.5f, 0.5f,-4.0f,
      0.5f, 0.5f, 4.0f,
      -0.5f, 0.5f,-4.0f,
      -0.5f, 0.5f, 4.0f,
      0.5f, 0.5f, 4.0f,
      -0.5f, 0.5f, 4.0f,
      0.5f,-0.5f, 4.0f
    };

    this->object_enemy = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
    this->object_missile = create3DObject(GL_TRIANGLES, 36, missile_vertex_buffer_data, color, GL_FILL);
}

void Enemy::draw_missile(glm::mat4 VP)
{
  Matrices.model = glm::mat4(1.0f);
  glm::mat4 translate = glm::translate (this->position_missile);    // glTranslatef
  float rotation_mis;
  if(abs(this->recorded_position_plane.z) - abs(this->position.z) == 0)
    rotation_mis = 90*M_PI/180.0f;
  else
    rotation_mis = atanf((abs(this->recorded_position_plane.y) - abs(this->position.y))/(abs(this->recorded_position_plane.z) - abs(this->position.z) ));

  glm::mat4 rotate    = glm::rotate((float)(rotation_mis ), glm::vec3(1, 0, 0));
  // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
  // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
  Matrices.model *= (translate * rotate);
  glm::mat4 MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(this->object_missile);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_enemy);

    if(this->toggle_missile)
    {
      draw_missile(VP);
    }
}

void Enemy::tick(glm::vec3 position_plane, glm::vec3 position_floor[10]) {

  if( !this->toggle_missile &&
      abs(this->position.x) - abs(position_plane.x) < 10.0 &&
      abs(this->position.y) - abs(position_plane.y) < 20.0 &&
      abs(this->position.z) - abs(position_plane.z) < 10.0
    )
  {
    this->toggle_missile = 1;
    this->position_missile = this->position;
    this->recorded_position_plane = position_plane;
  }
  else
  {

    if(this->position_missile.x < recorded_position_plane.x && (pass_x==INT_MIN || !pass_x))
    {
      pass_x = 0;
      this->position_missile.x+=0.5;
    }
    else if(this->position_missile.x > recorded_position_plane.x && (pass_x==INT_MIN || pass_x))
    {
      pass_x = 1;
      this->position_missile.x-=0.5;
    }


    this->position_missile.y+=0.5;


    if(this->position_missile.z < recorded_position_plane.z && (pass_z == INT_MIN || !pass_z))
    {
      this->position_missile.z+=0.5;
      pass_z = 0;
    }
    else if(this->position_missile.z > recorded_position_plane.z && (pass_z==INT_MIN || pass_z))
    {
      this->position_missile.z-=0.5;
      pass_z = 1;
    }

  }

  float temp = this->position.z;
  float enemy_y;
  if(temp <= -400)
  {
    enemy_y = position_floor[0].y;
  }
  else if(temp <= -300)
  {
    enemy_y = position_floor[1].y;
  }
  else if(temp <= -200)
  {
    enemy_y = position_floor[2].y;
  }
  else if(temp <= -100)
  {
    enemy_y = position_floor[3].y;
  }
  else if(temp <= 0)
  {
    enemy_y = position_floor[4].y;
  }
  else if(temp <= 100)
  {
    enemy_y = position_floor[5].y;
  }
  else if(temp <= 200)
  {
    enemy_y = position_floor[6].y;
  }
  else if(temp <= 300)
  {
    enemy_y = position_floor[7].y;
  }
  else if(temp <= 400)
  {
    enemy_y = position_floor[8].y;
  }
  else if(temp <= 500)
  {
    enemy_y = position_floor[9].y;
  }

    // this->rotation += speed;
  // this->position.z += speed;
  this->position.y = enemy_y + 2;

}

void Enemy::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
