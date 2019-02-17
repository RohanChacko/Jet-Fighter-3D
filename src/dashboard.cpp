#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(color_t color) {
    this->position_altimeter = glm::vec3(-2, -3, -50);
    this->rotation_altimeter = 0;

    this->position_speedometer = glm::vec3(0, -3, -50);
    this->rotation_speedometer = 29;

    this->position_fuelbar = glm::vec3(2, -3, -50);
    this->height_fuelbar = 10.0f;

    speed = 1;
    int num_circles = 36;

    static GLfloat altimeter[1000];

    altimeter[0] = -0.05; altimeter[1] = -0.05; altimeter[2] = 0.0;
    altimeter[3] = -0.05; altimeter[4] = 0.05; altimeter[5] = 0.0;
    altimeter[6] = 0.05; altimeter[7] = -0.05; altimeter[8] = 0.0;

    altimeter[9] = 0.05; altimeter[10] = -0.05; altimeter[11] = 0.0;
    altimeter[12] = 0.05; altimeter[13] = 0.05; altimeter[14] = 0.0;
    altimeter[15] = -0.05; altimeter[16] = 0.05; altimeter[17] = 0.0;

    for(int j = 1;j<num_circles;++j)
    {
      for(int i = 0;i<18;i+=3)
      {
        altimeter[18*j+i] =  altimeter[18*j+i - 18]*cosf(10*M_PI/180.0f) + altimeter[18*j+i+1 - 18]*sinf(10*M_PI/180.0f) + 0.065;
        altimeter[18*j+i+ 1] = -1*altimeter[18*j+i - 18]*sinf(10*M_PI/180.0f) + altimeter[18*j+i+1 - 18]*cosf(10*M_PI/180.0f);
        altimeter[18*j+i+ 2] = 0;
      };
    }
    static GLfloat altimeter_pointer[] = {
      -0.05, 0.00, 0.0,
      0.05, 0.00, 0.0,
      0.0, 0.30, 0.0,
    };

    this->object_altimeter_pointer = create3DObject(GL_TRIANGLES, 9, altimeter_pointer, COLOR_SPRING, GL_FILL);
    this->object_altimeter = create3DObject(GL_TRIANGLES, num_circles*6, altimeter, COLOR_SPRING, GL_FILL);


    //----------------------------------------------------------------------------//


    static GLfloat speedometer[1000];

    speedometer[0] = -0.05; speedometer[1] = -0.05; speedometer[2] = 0.0;
    speedometer[3] = -0.05; speedometer[4] = 0.05; speedometer[5] = 0.0;
    speedometer[6] = 0.05; speedometer[7] = -0.05; speedometer[8] = 0.0;

    speedometer[9] = 0.05; speedometer[10] = -0.05; speedometer[11] = 0.0;
    speedometer[12] = 0.05; speedometer[13] = 0.05; speedometer[14] = 0.0;
    speedometer[15] = -0.05; speedometer[16] = 0.05; speedometer[17] = 0.0;

    for(int j = 1;j<(num_circles/2)+2;++j)
    {
      for(int i = 0;i<18;i+=3)
      {
        speedometer[18*j+i] =  speedometer[18*j+i - 18]*cosf(10*M_PI/180.0f) + speedometer[18*j+i+1 - 18]*sinf(10*M_PI/180.0f) + 0.065;
        speedometer[18*j+i+ 1] = -1*speedometer[18*j+i - 18]*sinf(10*M_PI/180.0f) + speedometer[18*j+i+1 - 18]*cosf(10*M_PI/180.0f);
        speedometer[18*j+i+ 2] = 0;
      };
    }

    this->object_speedometer = create3DObject(GL_TRIANGLES, ((num_circles/2)+2)*6, speedometer, COLOR_SPRING, GL_FILL);
}

void Dashboard::draw(glm::mat4 VP) {
    glm::mat4 MVP;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position_altimeter);    // glTranslatef
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_altimeter);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (glm::vec3(this->position_altimeter.x + 0.05, this->position_altimeter.y - 0.45, this->position_altimeter.z) );    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation_altimeter * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_altimeter_pointer);

    //----------------------------------------------------------------------------//

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position_speedometer);    // glTranslatef
    rotate    = glm::rotate((float) (92 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate*rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_speedometer);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (glm::vec3(this->position_speedometer.x + 0.35, this->position_speedometer.y - 0.075, this->position_speedometer.z) );    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation_speedometer * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_altimeter_pointer);

    //----------------------------------------------------------------------------//

    GLfloat fuelbar_buffer[] =
    {
      -0.1f, this->height_fuelbar, 0.0f,
       -0.1f, 0.0f, 0.0f,
        0.1f, this->height_fuelbar, 0.0f,

       -0.1f, 0.0f, 0.0f,
        0.1f, this->height_fuelbar, 0.0f,
       0.1f, 0.0f, 0.0f,
    };

    color_t color_fuel;
    if(this->height_fuelbar > 7.5)
    {
      color_fuel = COLOR_LIMEGREEN;;
    }
    else if(this->height_fuelbar > 5.0)
    {
      color_fuel = COLOR_YELLOW;
    }
    else if(this->height_fuelbar > 2.5)
    {
      color_fuel = COLOR_ORANGE;
    }
    else
    {
      color_fuel = COLOR_ORANGERED;
    }

    this->object_fuelbar = create3DObject(GL_TRIANGLES, 6, fuelbar_buffer, color_fuel, GL_FILL);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position_fuelbar);    // glTranslatef
    Matrices.model *= translate;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_fuelbar);
}

void Dashboard::set_position(glm::vec3 position_plane) {
    this->position_altimeter = position_plane;
    this->position_altimeter.x = position_plane.x - 3;
    this->position_altimeter.y = position_plane.y - 9;
    this->position_altimeter.z = position_plane.z - 5;

    this->position_speedometer = position_plane;
    this->position_speedometer.x = position_altimeter.x + 0.75 ;
    this->position_speedometer.y = position_plane.y - 9.5;
    this->position_speedometer.z = position_plane.z - 5;

    this->position_fuelbar = position_plane;
    this->position_fuelbar.x = position_altimeter.x + 6.75;
    this->position_fuelbar.y = position_plane.y - 9.75;
    this->position_fuelbar.z = position_plane.z - 5;
}

void Dashboard::tick(int move, int ticker, float& fuel) {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;

    if(move == 1)
    {
      this->rotation_altimeter -=0.5;

      if(this->rotation_altimeter < -360)
      {
        this->rotation_altimeter = -359;
      }
    }
    else
    {
      this->rotation_altimeter +=0.5;

      if(this->rotation_altimeter > 0)
      {
        this->rotation_altimeter = 0;
      }
    }

    if(move == 4)
    {
      this->rotation_speedometer -=0.5;

      if(this->rotation_speedometer < -86)
      {
        this->rotation_speedometer = -85;
      }
    }
    else if(move == -4)
    {
      this->rotation_speedometer +=0.5;

      if(this->rotation_speedometer > 79)
      {
        this->rotation_speedometer = 80;
      }
    }

    this->height_fuelbar -= 0.001;

    if(this->height_fuelbar < 0)
      this->height_fuelbar = 0.05;

    fuel -= (10.0 - this->height_fuelbar)*0.1;
    // std::cout<<fuel<<"\n";

}
