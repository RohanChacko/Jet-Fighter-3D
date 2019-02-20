#include "parachute.h"
#include "main.h"
#include <iostream>

Parachute:: Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);


    this->val = 2;

    this->box.height = 0.15;
    this->box.width = 0.15;

    this->is_hit = 0;

    static GLfloat parachute[] = {

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

    this->object = create3DObject(GL_TRIANGLES, 36,parachute, COLOR_SPRING, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
  if(!this->is_hit || this->position.y > -15)
  {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
  }
}

int Parachute::collision(glm::vec3 position_missile)
{
  if( !this->is_hit &&
      fabs( fabs(this->position.x) - fabs(position_missile.x) ) < 5.0 &&
      fabs( fabs(this->position.y) - fabs(position_missile.y) ) < 5.0 &&
      fabs( fabs(this->position.z) - fabs(position_missile.z) ) < 5.0
    )
    {

      this->is_hit = 1;
      return 20;
    }
  return 0;
}
int Parachute::tick() {

  // this->position.y -= 0.1;

  this->box.x = this->position.x;
  this->box.y = this->position.y;

  return INT_MIN;
}

void Parachute::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
