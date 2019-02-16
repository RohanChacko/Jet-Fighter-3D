#include "floor.h"
#include "main.h"
#include <iostream>

Floors::Floors(float x, float y,color_t color) {

    this->position[0] = glm::vec3(x, y, 0);
    toggle_bit[0] = 1;
    for(int i = 1;i<10;++i)
    {
      this->position[i] = this->position[i-1];
      this->position[i].y -= 0.75;
      toggle_bit[i] = 1;
    }

    static const GLfloat vertex_buffer_data[10][18] = {
      {
        -500.0f, 0.0f, -401.0f, // triangle 1 : begin
        -500.0f, 0.0f, -500.0f,
         500.0f, 0.0f, -500.0f, // triangle 1 : end

        -500.0f, 0.0f, -401.0f, // triangle 2 : begin
         500.0f, 0.0f, -401.0f,
        500.0f, 0.0f, -500.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, -301.0f, // triangle 1 : begin
        -500.0f, 0.0f, -400.0f,
         500.0f, 0.0f, -400.0f, // triangle 1 : end

        -500.0f, 0.0f, -301.0f, // triangle 2 : begin
         500.0f, 0.0f, -301.0f,
        500.0f, 0.0f, -400.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, -201.0f, // triangle 1 : begin
        -500.0f, 0.0f, -300.0f,
         500.0f, 0.0f, -300.0f, // triangle 1 : end

        -500.0f, 0.0f,-201.0f, // triangle 2 : begin
         500.0f, 0.0f,-201.0f,
        500.0f, 0.0f, -300.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, -101.0f, // triangle 1 : begin
        -500.0f, 0.0f, -200.0f,
         500.0f, 0.0f, -200.0f, // triangle 1 : end

        -500.0f, 0.0f, -101.0f, // triangle 2 : begin
         500.0f, 0.0f, -101.0f,
        500.0f, 0.0f, -200.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, 1.0f, // triangle 1 : begin
        -500.0f, 0.0f, -100.0f,
         500.0f, 0.0f, -100.0f, // triangle 1 : end

        -500.0f, 0.0f, 1.0f, // triangle 2 : begin
         500.0f, 0.0f, 1.0f,
        500.0f, 0.0f, -100.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, 101.0f, // triangle 1 : begin
        -500.0f, 0.0f, 0.0f,
         500.0f, 0.0f, 0.0f, // triangle 1 : end

        -500.0f, 0.0f, 101.0f, // triangle 2 : begin
         500.0f, 0.0f, 101.0f,
        500.0f, 0.0f, 0.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, 201.0f, // triangle 1 : begin
        -500.0f, 0.0f, 100.0f,
         500.0f, 0.0f, 100.0f, // triangle 1 : end

        -500.0f, 0.0f, 201.0f, // triangle 2 : begin
         500.0f, 0.0f, 201.0f,
        500.0f, 0.0f, 100.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, 301.0f, // triangle 1 : begin
        -500.0f, 0.0f, 200.0f,
         500.0f, 0.0f, 200.0f, // triangle 1 : end

        -500.0f, 0.0f, 301.0f, // triangle 2 : begin
         500.0f, 0.0f, 301.0f,
        500.0f, 0.0f, 200.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, 401.0f, // triangle 1 : begin
        -500.0f, 0.0f, 300.0f,
         500.0f, 0.0f, 300.0f, // triangle 1 : end

        -500.0f, 0.0f, 401.0f, // triangle 2 : begin
         500.0f, 0.0f, 401.0f,
        500.0f, 0.0f, 300.0f, // triangle 2 : end
    },

    {
        -500.0f, 0.0f, 500.0f, // triangle 1 : begin
        -500.0f, 0.0f, 400.0f,
         500.0f, 0.0f, 400.0f, // triangle 1 : end

        -500.0f, 0.0f, 500.0f, // triangle 2 : begin
         500.0f, 0.0f, 500.0f,
        500.0f, 0.0f, 400.0f, // triangle 2 : end
    }
  };

    static const GLfloat floor_whole[] = {
    -501.0f, 0.0f, -500.0f, // triangle 1 : begin
    -501.0f, 0.0f, 500.0f,
     501.0f, 0.0f, 500.0f, // triangle 1 : end

    -501.0f, 0.0f, -500.0f, // triangle 2 : begin
     501.0f, 0.0f, -500.0f,
    501.0f, 0.0f, 500.0f, // triangle 2 : end
  };
    this->object_whole = create3DObject(GL_TRIANGLES, 2*3, floor_whole, color, GL_FILL);

    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[0], color, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[1], color, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[2], color, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[3], color, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[4], color, GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[5], color, GL_FILL);
    this->object[6] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[6], color, GL_FILL);
    this->object[7] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[7], color, GL_FILL);
    this->object[8] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[8], color, GL_FILL);
    this->object[9] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data[9], color, GL_FILL);
}

void Floors::draw(glm::mat4 VP) {

    glm::mat4 MVP;

    for(int i = 0;i<10;++i)
    {
      Matrices.model = glm::mat4(1.0f);
      glm::mat4 translate = glm::translate (this->position[i]);    // glTranslatef
      Matrices.model *= (translate);
      MVP = VP * Matrices.model;
      glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(this->object[i]);
    }

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(0, -17.6, 0));    // glTranslatef
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_whole);
}

void Floors::tick(float speed) {
    // this->rotation += speed;
    // this->position.z += speed;

    for(int i = 0;i<10;++i)
    {
      this->position[i].y += toggle_bit[i]*0.1;

      if(this->position[i].y > 2.0)
      {
        toggle_bit[i]*=-1;
      }
      else if(this->position[i].y <= -9.0)
      {
        toggle_bit[i]*=-1;
      }
    }

    // for(int i = 0;i<10;++i)
    //   std::cout<<"height: ["<<i<<"]: "<<this->position[i].y<<"\n";
}

void Floors::set_position(float x, float y) {
    this->position[0] = glm::vec3(x, y, 0);
}
