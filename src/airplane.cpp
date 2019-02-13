#include "airplane.h"
#include "main.h"

Airplane::Airplane(float xs, float ys, float zs, color_t color) {
    this->position = glm::vec3(xs, ys, 0);
    this->rotation_x = 0;
    this->rotation_z = 0;
    this->rotation_y = 0;

    this->orc[0][0] = 1;
    this->orc[0][1] = 0;
    this->orc[0][2] = 0;

    this->orc[1][0] = 0;
    this->orc[1][1] = 1;
    this->orc[1][2] = 0;

    this->orc[2][0] = 0;
    this->orc[2][1] = 0;
    this->orc[2][2] = 1;

    speed = 0.05;
    int stackCount = 100;
    int sectorCount = 100;
    static GLfloat g_vertex_buffer_data[100000];
    int n = 0;
    int ticker = 0;
    orc *= speed;


  float x1, y1, z, xy;                              // vertex position
  float radius = 2.9;    // vertex normal
  float s, t;                                     // vertex texCoord

  float sectorStep = 2 * M_PI / sectorCount;
  float stackStep = M_PI / stackCount;
  float sectorAngle, stackAngle;

    // for(int i = 0; i <= stackCount; ++i)
    // {
    //     stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
    //     xy = radius * cosf(stackAngle);             // r * cos(u)
    //     z = radius * sinf(stackAngle);              // r * sin(u)
    //
    //     // add (sectorCount+1) vertices per stack
    //     // the first and last vertices have same position and normal, but different tex coords
    //     for(int j = 0; j <= sectorCount; ++j)
    //     {
    //         sectorAngle = j * sectorStep;           // starting from 0 to 2pi
    //
    //         // vertex position (x, y, z)
    //         x1 = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
    //         y1 = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
    //         vertex_buffer_data[n++] = (x1);
    //         vertex_buffer_data[n++] = (y1);
    //         vertex_buffer_data[n++] = (z);
    //         // std::cout<<x1<<" "<<y1<<" "<<z<<std::endl;
    //     }
    // }

    float px, py, pz;
    int i, j;
    float incO = 2 * M_PI / 20;
    float incA = M_PI / 20;

    // for (i = 0; i <= 20; i++){
    //   for (j = 0; j <= 20; j++) {
    //     pz = cos(M_PI - (incA*j))*radius;
    //     py = sin(M_PI - (incA*j))*sin(incO*i)*radius;
    //     px = sin(M_PI - (incA*j))*cos(incO*i)*radius;
    //
    //     vertex_buffer_data[n++] = px;
    //     vertex_buffer_data[n++] = py;
    //     vertex_buffer_data[n++] = pz;
    //
    //     pz = cos(M_PI - (incA*j))*radius;
    //     py = sin(M_PI - (incA*j))*sin(incO*(i + 1))*radius;
    //     px = sin(M_PI - (incA*j))*cos(incO*(i + 1))*radius;
    //     vertex_buffer_data[n++] = px;
    //     vertex_buffer_data[n++] = py;
    //     vertex_buffer_data[n++] = pz;
    //   }
    // }
  float scale_x = 0.3;
  GLfloat x[30], y[30];

  for(int i = 0; i < 30; ++i)
    {
        x[i] = scale_x*cos(2*3.14*i/10);
        y[i] = scale_x*sin(2*3.14*i/10);
    }

    for(int i = 0; i < 10; ++i)

    {
        int j = 0;
       g_vertex_buffer_data[18*i]    = x[i+j];
       g_vertex_buffer_data[18*i+1]  = y[i+j];
       g_vertex_buffer_data[18*i+2]  = -2;
       g_vertex_buffer_data[18*i+3]  = x[(i+j+1)%30];
       g_vertex_buffer_data[18*i+4]  = y[(i+j+1)%30];
       g_vertex_buffer_data[18*i+5]  = -2;
       g_vertex_buffer_data[18*i+6]  = x[i+j];
       g_vertex_buffer_data[18*i+7]  = y[i+j];
       g_vertex_buffer_data[18*i+8]  = 3;
       g_vertex_buffer_data[18*i+9]  = x[i+j];
       g_vertex_buffer_data[18*i+10] = y[i+j];
       g_vertex_buffer_data[18*i+11] = 3;
       g_vertex_buffer_data[18*i+12] = x[(i+j+1)%30];
       g_vertex_buffer_data[18*i+13] = y[(i+j+1)%30];
       g_vertex_buffer_data[18*i+14] = 3;
       g_vertex_buffer_data[18*i+15] = x[(i+j+1)%30];
       g_vertex_buffer_data[18*i+16] = y[(i+j+1)%30];
       g_vertex_buffer_data[18*i+17] = -2;
    }

    for(int j = 0; j < 5; ++j)
    {
        for(int i = 0; i < 10; ++i)
        {
           g_vertex_buffer_data[18*i + 180* (j+1)]       = x[j] * x[i]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 1]  = x[j] * y[i]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 2]  = 3 + y[j]/scale_x; //back
           g_vertex_buffer_data[18*i + 180* (j+1) + 3]  = x[j] *x[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 4]  = x[j] *y[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 5]  = 3 + y[j]/scale_x; //back
           g_vertex_buffer_data[18*i + 180* (j+1) + 6]  = x[j+1] *x[i]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 7]  = x[j+1] *y[i]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 8]  = 3 + y[j+1]/scale_x;//front
           g_vertex_buffer_data[18*i + 180* (j+1) + 9]  = x[j+1] * x[i]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 10] = x[j+1] * y[i]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 11] = 3  + y[j+1]/scale_x;  //front
           g_vertex_buffer_data[18*i + 180* (j+1) + 12] = x[j+1] *x[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 13] = x[j+1] *y[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 14] = 3 + y[j+1]/scale_x;//front
           g_vertex_buffer_data[18*i + 180* (j+1) + 15] = x[j] *x[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 16] = x[j] *y[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 180* (j+1) + 17] = 3 + y[j]/scale_x;//back

        }
    }

    for(int i = 0; i < 10; ++i)
    {
        int j = 0;

         g_vertex_buffer_data[18*i + 1080]       = x[j] * x[i]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 1]  = x[j] * y[i]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 2]  = -2 - y[j]/scale_x; //back
           g_vertex_buffer_data[18*i + 1080 + 3]  = x[j] *x[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 4]  = x[j] *y[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 5]  = -2 - y[j]/scale_x; //back
           g_vertex_buffer_data[18*i + 1080 + 6]  = x[j+1] *x[i]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 7]  = x[j+1] *y[i]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 8]  = -2 - y[j+1]/scale_x;//front
           g_vertex_buffer_data[18*i + 1080 + 9]  = x[j+1] * x[i]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 10] = x[j+1] * y[i]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 11] = -2  - y[j+1]/scale_x;  //front
           g_vertex_buffer_data[18*i + 1080 + 12] = x[j+1] *x[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 13] = x[j+1] *y[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 14] = -2 - y[j+1]/scale_x;//front
           g_vertex_buffer_data[18*i + 1080 + 15] = x[j] *x[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 16] = x[j] *y[(i+1)%30]/scale_x;
           g_vertex_buffer_data[18*i + 1080 + 17] = -2 - y[j]/scale_x;//back
    }
    //tail 1

    g_vertex_buffer_data[1260] = 0;
    g_vertex_buffer_data[1261] = scale_x;
    g_vertex_buffer_data[1262] = -1;
    g_vertex_buffer_data[1263] = 0;
    g_vertex_buffer_data[1264] = 1.3;
    g_vertex_buffer_data[1265] = -2.2;
    g_vertex_buffer_data[1266] = 0;
    g_vertex_buffer_data[1267] = scale_x;
    g_vertex_buffer_data[1268] = -2;
    //tail 2
    g_vertex_buffer_data[1269] = 0;
    g_vertex_buffer_data[1270] = 1.3;
    g_vertex_buffer_data[1271] = -2.2;

    g_vertex_buffer_data[1272] = 0;
    g_vertex_buffer_data[1273] = scale_x;
    g_vertex_buffer_data[1274] = -2;

    g_vertex_buffer_data[1275] = 0;
    g_vertex_buffer_data[1276] = 1.3;
    g_vertex_buffer_data[1277] = -2.7;

    //fins

    g_vertex_buffer_data[1278] = 0;
    g_vertex_buffer_data[1279] = -0.15;
    g_vertex_buffer_data[1280] = -1;

    g_vertex_buffer_data[1281] = 1.5f;
    g_vertex_buffer_data[1282] = -0.15f;
    g_vertex_buffer_data[1283] = -2;

    g_vertex_buffer_data[1284] = -1.5;
    g_vertex_buffer_data[1285] = -0.15;
    g_vertex_buffer_data[1286] = -2;

    g_vertex_buffer_data[1287] = 1.5f;
    g_vertex_buffer_data[1288] = -0.15;
    g_vertex_buffer_data[1289] = -2;

    g_vertex_buffer_data[1290] = 1.5f;
    g_vertex_buffer_data[1291] = -0.15;
    g_vertex_buffer_data[1292] = -2.3;

    g_vertex_buffer_data[1293] = -0.3;
    g_vertex_buffer_data[1294] = -0.15;
    g_vertex_buffer_data[1295] = -2;


    g_vertex_buffer_data[1296] = -1.5f;
    g_vertex_buffer_data[1297] = -0.15;
    g_vertex_buffer_data[1298] = -2;

    g_vertex_buffer_data[1299] = -1.5f;
    g_vertex_buffer_data[1300] = -0.15;
    g_vertex_buffer_data[1301] = -2.3;

    g_vertex_buffer_data[1302] = 0.3;
    g_vertex_buffer_data[1303] = -0.15;
    g_vertex_buffer_data[1304] = -2;

    g_vertex_buffer_data[1305] = 0;
    g_vertex_buffer_data[1306] = -0.15;
    g_vertex_buffer_data[1307] = 1.5;

    g_vertex_buffer_data[1308] = 3.5;
    g_vertex_buffer_data[1309] = -0.15f;
    g_vertex_buffer_data[1310] = -0.5;

    g_vertex_buffer_data[1311] = 0;
    g_vertex_buffer_data[1312] = -0.15;
    g_vertex_buffer_data[1313] = 0.5;

    g_vertex_buffer_data[1314] = 0;
    g_vertex_buffer_data[1315] = -0.15;
    g_vertex_buffer_data[1316] = 1.5;

    g_vertex_buffer_data[1317] = -3.5;
    g_vertex_buffer_data[1318] = -0.15f;
    g_vertex_buffer_data[1319] = -0.5;

    g_vertex_buffer_data[1320] = 0;
    g_vertex_buffer_data[1321] = -0.15;
    g_vertex_buffer_data[1322] = 0.5;

    g_vertex_buffer_data[1323] = 0;
    g_vertex_buffer_data[1324] = -0.15;
    g_vertex_buffer_data[1325] = 1.5;

    g_vertex_buffer_data[1326] = 1.5f;
    g_vertex_buffer_data[1327] = -0.15f;
    g_vertex_buffer_data[1328] = 0.1;

    g_vertex_buffer_data[1329] = -1.5;
    g_vertex_buffer_data[1330] = -0.15;
    g_vertex_buffer_data[1331] = 0.1;

    for(int i = 2;i<1332;i+=3)
    {
      g_vertex_buffer_data[i]*=-1;
    }
    this->object = create3DObject(GL_TRIANGLES, 420 + 12 + 12, g_vertex_buffer_data, COLOR_GOLD, GL_FILL);
    // this->structure = create3DObject(GL_TRIANGLES, 420 + 12 + 12, g_vertex_buffer_data, COLOR_BLACK, GL_LINE);
    // this->object = create3DObject(GL_TRIANGLES,882, vertex_buffer_data, color, GL_FILL);
}

void Airplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 pitch    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1,0,0));
    glm::mat4 yaw    = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0,0,1));
    glm::mat4 roll    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0,1,0));

    // No need as coords centered at 0, 0, 0 of cube arouund which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= initial;
    Matrices.model *= (translate * roll*pitch*yaw);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Airplane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Airplane::tick(int move) {
    // this->rotation += speed;

    ticker++;

    // this->position.y -= speed;

    if(move == 1){
      if(this->rotation_x < 15)
        this->rotation_x += (1*0.5);
      this->position.y+=speed;
    }
    else
    {
      if(this->rotation_x >- 15)
        this->rotation_x -= (1* 0.6);

      if(this->position.y >=1)
        this->position.y-=speed;
    }

    if(move == 2)
    {
      // std::cout<<"first "<<this->rotation_z<<"\n";
      if(this->rotation_z < 30)
        {
          this->rotation_z += (1*0.5);
          // this->position.x = this->position.z*sinf(this->rotation_z * M_PI/180.0);
        }
    }
    else if(move == -2)
    {
      // std::cout<<"second "<<this->rotation_z<<"\n";
      if(this->rotation_z >- 30)
      {
        this->rotation_z -= (1*0.5);
        // this->position.x = this->position.z*sinf(this->rotation_z * M_PI/180.0);
      }
    }

    if(move == 3)
    {
      this->rotation_y += (-1*0.5);
      orc *= glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0,1,0));
    }
    else if(move == -3)
    {
      this->rotation_y -= (-1*0.5);
      orc *= glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0,1,0));
    }


    // int i,j;
    // for(i = 0;i<3;++i)
    // {
    //   for(j = 0;j<3;++j)
    //   std::cout<<orc[i][j]<<" ";
    //   std::cout<<orc[i][j]<<"\n\n\n";
    // }

    // this->position.x += orc[0][0];
    //this->position.y += orc[1][1];
    // this->position.z += orc[2][2];
    this->position.x -= speed*sinf(this->rotation_y * M_PI/180.0);
    this->position.z -= speed*cosf(this->rotation_y * M_PI/180.0);
    // std::cout<<move<<" "<<this->position.y<<"\n";
}
