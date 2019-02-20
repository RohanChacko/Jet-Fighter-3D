#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(color_t color) {
    this->position_altimeter = glm::vec3(-2, -3, 0);
    this->rotation_altimeter = 0;

    this->position_speedometer = glm::vec3(0, -3, 0);
    this->rotation_speedometer = 29;

    this->position_fuelbar = glm::vec3(2, -3, 0);
    this->height_fuelbar = 8.0f;

    this->position_scoreboard = glm::vec3(-2, 2, 0);

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

    //------------------------------------------------------------------------//

    angle = (M_PI / 180.0f)*90.0f;
    disp.resize(7);

    for(int i = 0;i<7; ++i)
    {
      disp[i].resize(18);
    }

    GLfloat temp[18] = {
    // 1
        -0.10f,-0.05f, 0.0f, // 1st row fire
        -0.10f, 0.05f, 0.0f, // triangle 1 : begin
        0.05f , 0.05f, 0.0f, // triangle 1 : end

        -0.10f, -0.05f, 0.0f, // triangle 2 : begin
        0.05f , -0.05f, 0.0f,
        0.05f , 0.05f, 0.0f // triangle 2 : end
    };

    for(int i = 0;i<18;++i)
    {
      disp[0][i] = temp[i];
    }

    // 2
    for(int i = 0;i<18;i+=3)
    {
      disp[1][i] = disp[0][i]* cosf(angle) + disp[0][i+1]*sinf(angle) - 0.16f;
      disp[1][i+1] = -1*disp[0][i]*sinf(angle) + disp[0][i+1]*cosf(angle) - 0.16f;
      disp[1][i+2] = 0.0f;
    }

    // 3
    for(int i = 0;i<18;i+=3)
    {
      disp[2][i] = disp[1][i];
      disp[2][i+1] = disp[1][i + 1] - 0.28f;
      disp[2][i+2] = 0.0f;
    }

    // 4
    for(int i = 0;i<18;i+=3)
    {
      disp[3][i] = disp[0][i];
      disp[3][i+1] = disp[0][i + 1] - 0.55f;
      disp[3][i+2] = 0.0f;
    }

    // 5
    for(int i = 0;i<18;i+=3)
    {
      disp[4][i] = disp[2][i] +  0.28f;
      disp[4][i+1] = disp[2][i + 1];
      disp[4][i+2] = 0.0f;
    }

    // 6
    for(int i = 0;i<18;i+=3)
    {
      disp[5][i] = disp[1][i] + 0.28f;
      disp[5][i+1] = disp[1][i + 1];
      disp[5][i+2] = 0.0f;
    }

    // 7
    for(int i = 0;i<18;i+=3)
    {
      disp[6][i] = disp[0][i];
      disp[6][i+1] = disp[0][i + 1] - 0.27f;
      disp[6][i+2] = 0.0f;
    }

    // static GLfloat scoreboard[1000];
    // int n = 0;
    //
    // // S
    // int s_index[7] = {0,1,3,4,6};
    //
    // for(int i = 0; i < 5; ++i)
    // {
    //   for(int j = 0; j<disp[s_index[i]].size(); ++j)
    //     scoreboard[n++] = disp[s_index[i]][j];
    // }
    //
    // // C
    // int c_index[4] = {0,1,2,3};
    //
    // for(int i = 0; i < 4; ++i)
    // {
    //   for(int j = 0; j<disp[c_index[i]].size(); ++j)
    //     {
    //       scoreboard[n++] = disp[c_index[i]][j];
    //       if((n-1)%3 == 0)
    //         scoreboard[n-1]+=0.44;
    //     }
    // }
    //
    // // O
    // int o_index[6] = {0,1,2,3,4,5};
    //
    // for(int i = 0; i < 6; ++i)
    // {
    //   for(int j = 0; j<disp[o_index[i]].size(); ++j)
    //     {
    //       scoreboard[n++] = disp[o_index[i]][j];
    //       if((n-1)%3 == 0)
    //         scoreboard[n-1]+=0.88;
    //     }
    // }
    //
    // // R
    // int r_index[6] = {0,1,2,4,5,6};
    //
    // for(int i = 0; i < 6; ++i)
    // {
    //   for(int j = 0; j<disp[r_index[i]].size(); ++j)
    //     {
    //       scoreboard[n++] = disp[r_index[i]][j];
    //       if((n-1)%3 == 0)
    //         scoreboard[n-1]+=1.42;
    //     }
    // }
    //
    // // E
    // int e_index[5] = {0,1,2,3,6};
    //
    // for(int i = 0; i < 5; ++i)
    // {
    //   for(int j = 0; j<disp[e_index[i]].size(); ++j)
    //     {
    //       scoreboard[n++] = disp[e_index[i]][j];
    //       if((n-1)%3 == 0)
    //         scoreboard[n-1]+=1.96;
    //     }
    // }
    //
    // this->object_scoreboard = create3DObject(GL_TRIANGLES, 2*3* (5+4+6+6+5), scoreboard, COLOR_BLACK, GL_FILL);
}

void Dashboard::draw(glm::mat4 VP, int score) {
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
    if(this->height_fuelbar > 6.0)
    {
      color_fuel = COLOR_LIMEGREEN;;
    }
    else if(this->height_fuelbar > 4.0)
    {
      color_fuel = COLOR_YELLOW;
    }
    else if(this->height_fuelbar > 2.0)
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


    //------------------------------------------------------------------------//


    static GLfloat vertex_buffer_data[1000];
    int n = 0;
    int size = 0;
    int iter = 0;
    
    if(score == 0)
    {
      int tmp[6] = {0,1,2,3,4,5};
      size+=6;
      for(int i = 0; i < 6; ++i)
      {
        for(int j = 0; j<disp[tmp[i]].size(); ++j)
          {
            vertex_buffer_data[n++] = disp[tmp[i]][j];
            if((n-1)%3 == 0)
              vertex_buffer_data[n-1]+=3.8;
          }
      }
    }
    if(score < 0)
    {
      for(int i = 0;i<18;i+=3)
      {
        vertex_buffer_data[n++] = disp[0][i] + 3.8 - 3*0.44;
        vertex_buffer_data[n++] = disp[0][i + 1] - 0.27f;
        vertex_buffer_data[n++] = 0.0f;
      }
      size++;
    }
    while(abs(score)>0)
    {
      int rem = abs(score)%10;
      switch (rem) {
        case 0: {
                    int zero_index[6] = {0,1,2,3,4,5};
                    size+=6;
                    for(int i = 0; i < 6; ++i)
                    {
                      for(int j = 0; j<disp[zero_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[zero_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }
                    break;
        };
        case 1: {
                    int one_index[2] = {1,2};
                    size+=2;
                    for(int i = 0; i < 2; ++i)
                    {
                      for(int j = 0; j<disp[one_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[one_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 2: {
                    int two_index[5] = {0,2,3,5,6};
                    size+=5;
                    for(int i = 0; i < 5; ++i)
                    {
                      for(int j = 0; j<disp[two_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[two_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 3: {
                    int three_index[5] = {0,3,4,5,6};
                    size+=5;
                    for(int i = 0; i < 5; ++i)
                    {
                      for(int j = 0; j<disp[three_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[three_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 4: {
                    int four_index[4] = {1,4,5,6};
                    size+=4;
                    for(int i = 0; i < 4; ++i)
                    {
                      for(int j = 0; j<disp[four_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[four_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 5: {
                    int five_index[5] = {0,1,3,4,6};
                    size+=5;
                    for(int i = 0; i < 5; ++i)
                    {
                      for(int j = 0; j<disp[five_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[five_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 6: {
                    int six_index[6] = {0,1,2,3,4,6};
                    size+=6;
                    for(int i = 0; i < 6; ++i)
                    {
                      for(int j = 0; j<disp[six_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[six_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 7: {
                    int seven_index[5] = {0,4,5};
                    size+=3;
                    for(int i = 0; i < 3; ++i)
                    {
                      for(int j = 0; j<disp[seven_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[seven_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 8: {
                    int eight_index[7] = {0,1,2,3,4,5,6};
                    size+=7;
                    for(int i = 0; i < 7; ++i)
                    {
                      for(int j = 0; j<disp[eight_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[eight_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 9: {
                    int nine_index[6] = {0,1,3,4,5,6};
                    size+=6;
                    for(int i = 0; i < 6; ++i)
                    {
                      for(int j = 0; j<disp[nine_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[nine_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
      }

      iter++;
      score/=10;
    }

    this->object_score = create3DObject(GL_TRIANGLES, 2*3* (size), vertex_buffer_data, COLOR_BLACK, GL_FILL);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position_scoreboard);    // glTranslatef
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object_scoreboard);
    draw3DObject(this->object_score);
}

void Dashboard::set_position(glm::vec3 position_plane) {

    this->position_altimeter.x = -3.5;
    this->position_altimeter.y = -3;
    this->position_altimeter.z = 0;


    this->position_speedometer.x = position_altimeter.x + 0.75 ;
    this->position_speedometer.y = -3.5;
    this->position_speedometer.z = 0;


    this->position_fuelbar.x = position_altimeter.x + 7.0;
    this->position_fuelbar.y = -4.0;
    this->position_fuelbar.z = 0;


    this->position_scoreboard.x = -5.75;
    this->position_scoreboard.y =  3.75;
    this->position_scoreboard.z = 0;
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
