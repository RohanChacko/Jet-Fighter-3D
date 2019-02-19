#include "addons.h"
#include "main.h"
#include <iostream>

Addon::Addon(float x, float y, float z, int type) {
    this->position_fuel = glm::vec3(x, y, z);
    if(rand()%2 == 0)
      this->rotation_fuel = -5;
    else
      this->rotation_fuel = 5;

    if(type == 1)
      this->color_fuel = COLOR_YELLOW;

    this->val_fuel = 2;

    this->box.height = 0.15;
    this->box.width = 0.15;
    this->picked = 0;

    static GLfloat fuel[] = {

      -1.0f,-2.0f,-1.0f, // triangle 1 : begin
      -1.0f,-2.0f, 1.0f,
      -1.0f, 2.0f, 1.0f, // triangle 1 : end
      1.0f, 2.0f,-1.0f, // triangle 2 : begin
      -1.0f,-2.0f,-1.0f,
      -1.0f, 2.0f,-1.0f, // triangle 2 : end
      1.0f,-2.0f, 1.0f,
      -1.0f,-2.0f,-1.0f,
      1.0f,-2.0f,-1.0f,
      1.0f, 2.0f,-1.0f,
      1.0f,-2.0f,-1.0f,
      -1.0f,-2.0f,-1.0f,
      -1.0f,-2.0f,-1.0f,
      -1.0f, 2.0f, 1.0f,
      -1.0f, 2.0f,-1.0f,
      1.0f,-2.0f, 1.0f,
      -1.0f,-2.0f, 1.0f,
      -1.0f,-2.0f,-1.0f,
      -1.0f, 2.0f, 1.0f,
      -1.0f,-2.0f, 1.0f,
      1.0f,-2.0f, 1.0f,
      1.0f, 2.0f, 1.0f,
      1.0f,-2.0f,-1.0f,
      1.0f, 2.0f,-1.0f,
      1.0f,-2.0f,-1.0f,
      1.0f, 2.0f, 1.0f,
      1.0f,-2.0f, 1.0f,
      1.0f, 2.0f, 1.0f,
      1.0f, 2.0f,-1.0f,
      -1.0f, 2.0f,-1.0f,
      1.0f, 2.0f, 1.0f,
      -1.0f, 2.0f,-1.0f,
      -1.0f, 2.0f, 1.0f,
      1.0f, 2.0f, 1.0f,
      -1.0f, 2.0f, 1.0f,
      1.0f,-2.0f, 1.0f,
    };

    if(type == 1)
      this->object = create3DObject(GL_TRIANGLES, 36, fuel, COLOR_YELLOW, GL_FILL);
}

void Addon::draw(glm::mat4 VP) {
  if(!this->picked)
  {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position_fuel);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation_fuel * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
  }
}

int Addon::tick_fuel(glm::vec3 position_plane) {

  if(this->rotation_fuel > 0)
    this->rotation_fuel+=5.0;
  else
    this->rotation_fuel-=5.0;

  if( !this->picked &&
      fabs( fabs(this->position_fuel.x) - fabs(position_plane.x) ) < 3.0 &&
      fabs( fabs(this->position_fuel.y) - fabs(position_plane.y) ) < 3.0 &&
      fabs( fabs(this->position_fuel.z) - fabs(position_plane.z) ) < 3.0
    )
    {
      this->picked = 1;
      return this->val_fuel;
    }

  this->box.x = this->position_fuel.x;
  this->box.y = this->position_fuel.y;

  return INT_MIN;
}

void Addon::set_position(float x, float y) {
    this->position_fuel = glm::vec3(x, y, 0);
}
