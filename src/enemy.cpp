#include "enemy.h"
#include "main.h"
#include <iostream>

Enemy::Enemy(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->toggle_missile = 0;
    this->pass_x = INT_MIN;
    this->sphere_radius = 75;
    this->pass_z = INT_MIN;
    this->speed = 1.0;
    this->is_hit = 0;
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
  float rotation_mis_x;
  float rotation_mis_y;
  if(this->recorded_position_plane.z  == 0)
    rotation_mis_x = 90*M_PI/180.0f;
  else
    rotation_mis_x = -1*atanf( this->recorded_position_plane.y/sqrt(pow(this->recorded_position_plane.z,2) + pow(this->recorded_position_plane.z,2)) );

    if(this->recorded_position_plane.y  == 0)
      rotation_mis_y = 90*M_PI/180.0f;
    else
      rotation_mis_y = atanf( this->recorded_position_plane.z/this->recorded_position_plane.x );

  glm::mat4 rotate_x    = glm::rotate((float)(rotation_mis_x ), glm::vec3(1, 0, 0));
  glm::mat4 rotate_y    = glm::rotate((float)(rotation_mis_y ), glm::vec3(0, 1, 0));
  // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
  // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
  Matrices.model *= (translate * rotate_y * rotate_x);
  glm::mat4 MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(this->object_missile);
}

void Enemy::draw(glm::mat4 VP) {

  if(!this->is_hit)
  {
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
}

int Enemy::collision(glm::vec3 position_bomb)
{
  if( !this->is_hit &&
      fabs( fabs(this->position.x) - fabs(position_bomb.x) ) < 6.0 &&
      fabs( fabs(this->position.y) - fabs(position_bomb.y) ) < 6.0 &&
      fabs( fabs(this->position.z) - fabs(position_bomb.z) ) < 6.0
    )
    {
      this->is_hit = 1;
      // std::cout<<"DEDDDDDDD\n";
      return 10;
    }

    return 0;
}

void Enemy::tick(glm::vec3 position_plane, glm::vec3 position_floor[10], int &airplane_score) {

  float L2_dist = pow((this->position.x - position_plane.x), 2) + pow((this->position.y - position_plane.y), 2) + pow((this->position.z - position_plane.z), 2);
  if( !this->toggle_missile && L2_dist < pow(sphere_radius,2) )
  {
    this->toggle_missile = 1;
    this->position_missile = this->position;
    this->recorded_position_plane = position_plane - this->position;
    this->recorded_position_plane /= sqrt(pow(this->recorded_position_plane.x,2) + pow(this->recorded_position_plane.y,2) + pow(this->recorded_position_plane.z,2));
  }
  else
  {

    // if(this->position_missile.x < recorded_position_plane.x && (pass_x==INT_MIN || !pass_x))
    // {
    //   pass_x = 0;
    //   this->position_missile.x+=0.5;
    // }
    // else if(this->position_missile.x > recorded_position_plane.x && (pass_x==INT_MIN || pass_x))
    // {
    //   pass_x = 1;
    //   this->position_missile.x-=0.5;
    // }
    //
    //
    // this->position_missile.y+=0.5;
    //
    //
    // if(this->position_missile.z < recorded_position_plane.z && (pass_z == INT_MIN || !pass_z))
    // {
    //   this->position_missile.z+=0.5;
    //   pass_z = 0;
    // }
    // else if(this->position_missile.z > recorded_position_plane.z && (pass_z==INT_MIN || pass_z))
    // {
    //   this->position_missile.z-=0.5;
    //   pass_z = 1;
    // }

    this->position_missile.x += this->recorded_position_plane.x*this->speed;
    this->position_missile.y += this->recorded_position_plane.y*this->speed;
    this->position_missile.z += this->recorded_position_plane.z*this->speed;


  }

  // MISSILE COLLISION

  if(
      fabs( fabs(this->position_missile.x) - fabs(position_plane.x) ) < 3.0 &&
      fabs( fabs(this->position_missile.y) - fabs(position_plane.y) ) < 3.0 &&
      fabs( fabs(this->position_missile.z) - fabs(position_plane.z) ) < 3.0
    )
    {
      // this->is_hit = 1;
      // std::cout<<" HITTTTTTTTTTTT\n";
      airplane_score -=2;
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
