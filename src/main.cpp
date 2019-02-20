#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "floor.h"
#include "enemy.h"
#include "checkpoint.h"
#include "dashboard.h"
#include "land.h"
#include "ammunition.h"
#include "volcano.h"
#include "addons.h"
#include "parachute.h"
#include "smokering.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices_dashboard;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

/* Object Declaration */
Airplane airplane;
Floors floors;
Dashboard dashboard;
Land land;
Ammunition ammunition;
Addon addon[MAX_ADDON_COUNT];
Volcano volcano[MAX_VOLCANO_COUNT];
Checkpoint checkpoint[MAX_CHECKPOINT_COUNT];
Smokering smokering[MAX_SMOKERING_COUNT];
Enemy enemy[MAX_ENEMY_COUNT];
Parachute parachute[MAX_PARACHUTE_COUNT];

int cur_cam = 4; //Follow cam
int pressed = -1;
int enemy_count = 0;
int passed_count = 0;
int disable_input = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int set = 1;
Timer t60(1.0 / 60);


glm::vec3 cam_position;
glm::vec3 target_position;

int width;
int height;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw(int x) {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera

    if(cur_cam !=5)
    {
      pressed = -1;
      rotation_x = 0;
      rotation_y = 0;
    }
    // Plane View
    if(cur_cam == 1)
    {
      cam_position.x = airplane.position.x;
      cam_position.y = airplane.position.y + 2.0;
      cam_position.z = airplane.position.z;

      target_position.x = airplane.position.x - 50 * sin(airplane.rotation_y * M_PI / 180.0);
      target_position.y = airplane.position.y + cos(airplane.rotation_x * M_PI / 180.0);;
      target_position.z = airplane.position.z - 50 * cos(airplane.rotation_y * M_PI / 180.0);
      // target_position.x = (airplane.position.x)*cos(airplane.rotation_y * M_PI / 180.0) + (airplane.position.z - 10) * sin(airplane.rotation_y * M_PI / 180.0);
      // target_position.y = airplane.position.y;
      // target_position.z = -1*(airplane.position.x)*sin(airplane.rotation_y * M_PI / 180.0) + (airplane.position.z - 10)*cos(airplane.rotation_y * M_PI / 180.0);
    }
    // Top View
    else if(cur_cam == 2)
    {
      cam_position.x = airplane.position.x + 0.25;
      cam_position.y = airplane.position.y + 10;
      cam_position.z = airplane.position.z;

      target_position.x = airplane.position.x;
      target_position.y = airplane.position.y;
      target_position.z = airplane.position.z;
    }
    // Tower View
    else if(cur_cam == 3)
    {
      cam_position.x = 475;
      cam_position.y = 50;
      cam_position.z = -100;

      target_position.x = airplane.position.x;
      target_position.y = airplane.position.y;
      target_position.z = airplane.position.z;
    }
    // Follow View
    else if(cur_cam == 4)
    {
      target_position.x = airplane.position.x;
      target_position.y = airplane.position.y;
      target_position.z = airplane.position.z;

      cam_position.x = airplane.position.x + 2 * sin(airplane.rotation_y * M_PI / 180.0);
      cam_position.y = airplane.position.y + 3;// + cos(airplane.rotation_x * M_PI / 180.0);;
      cam_position.z = airplane.position.z + 2 * cos(airplane.rotation_y * M_PI / 180.0);
    }
    //Helicopter View
    else if(cur_cam == 5)
    {
      target_position.x = airplane.position.x;
      target_position.y = airplane.position.y;
      target_position.z = airplane.position.z;

      //Initial value
      if(pressed == -1)
      {
        cam_position.x = airplane.position.x + 7 * sin(airplane.rotation_y * M_PI / 180.0);
        cam_position.y = airplane.position.y + 7;// + cos(airplane.rotation_x * M_PI / 180.0);;
        cam_position.z = airplane.position.z + 7* cos(airplane.rotation_y * M_PI / 180.0);
      }

      helicopter_track(window, height, width, cam_position, airplane.position);
    }



    // cout<<airplane.position.x<<" "<<airplane.position.y<<" "<<airplane.position.z<<endl;
    glm::vec3 eye (cam_position.x, cam_position.y, cam_position.z);
    // cout<<"cam: "<<cam_position.x<<" "<<cam_position.y<<" "<< cam_position.z<<endl;
    // cout<<"airplane: "<<airplane.position.x<<" "<<airplane.position.y<<" "<< airplane.position.z<<endl;
    // cout<<"target: "<<target_position.x<<" "<<target_position.y<<" "<< target_position.z<<"\n\n";
    // std::cout<<"angles: "<<airplane.rotation_x<<" "<<airplane.rotation_y<<" "<<airplane.rotation_z<<"\n\n";
    // glm::vec3 eye (5*cos(camera_rotation_angle*M_PI/180.0f), 3, 5*sin(camera_rotation_angle*M_PI/180.0f));


    // Target - Where is the camera looking at.  Don't change unless you are sure!!

    glm::vec3 target (target_position.x, target_position.y, target_position.z);

    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

    glm::vec3 eye_dash (0, 0, 1);
    glm::vec3 target_dash (0, 0, 0);
    Matrices_dashboard.view = glm::lookAt( eye_dash, target_dash, up ); // Rotating Camera for 3D

    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 VP_DASH = Matrices_dashboard.projection * Matrices_dashboard.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    floors.draw(VP);

    airplane.draw(VP, cam_position, target_position);

    land.draw(VP);

    if(ammunition.active_bomb)
      ammunition.draw_bomb(VP);
    if(ammunition.active_missile)
      ammunition.draw_missile(VP, airplane.rotation_y);

    dashboard.draw(VP_DASH, airplane.score);
    for(int i = 0;i < MAX_CHECKPOINT_COUNT; ++i)
    {
      checkpoint[i].draw(VP, passed_count);

      if(i==MAX_CHECKPOINT_COUNT - 1)
        checkpoint[i].draw_arrow(VP_DASH);
    }

    for(int i = 0;i < MAX_SMOKERING_COUNT; ++i)
    {
      smokering[i].draw(VP);
    }

    for(int i = 0;i < enemy_count; ++i)
    {
      enemy[i].draw(VP);
    }

    for(int i = 0;i < MAX_VOLCANO_COUNT; ++i)
    {
      volcano[i].draw(VP);
    }

    for(int i = 0;i < MAX_ADDON_COUNT/2; ++i)
    {
      addon[i].draw(VP);
    }

    for(int i = 0;i < MAX_PARACHUTE_COUNT; ++i)
    {
      parachute[i].draw(VP);
    }

}

int tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int speed_up = glfwGetKey(window, GLFW_KEY_W);
    int speed_down = glfwGetKey(window, GLFW_KEY_S);
    int pitch = glfwGetKey(window, GLFW_KEY_SPACE);
    int yaw_left = glfwGetKey(window, GLFW_KEY_A);
    int yaw_right = glfwGetKey(window, GLFW_KEY_D);
    int roll_left = glfwGetKey(window, GLFW_KEY_Q);
    int roll_right = glfwGetKey(window, GLFW_KEY_E);
    int bomb = glfwGetKey(window, GLFW_KEY_C);
    int missile = glfwGetKey(window, GLFW_KEY_Z);
    int cam_1 = glfwGetKey(window, GLFW_KEY_1);
    int cam_2 = glfwGetKey(window, GLFW_KEY_2);
    int cam_3 = glfwGetKey(window, GLFW_KEY_3);
    int cam_4 = glfwGetKey(window, GLFW_KEY_4);
    int cam_5 = glfwGetKey(window, GLFW_KEY_5);
    int barrel_roll = glfwGetKey(window, GLFW_KEY_7);

    set = INT_MIN;
    if (left) {
      // cam_position.x+=0.03;
    }
    else if(right){
      // cam_position.x-=0.03;
    }
    else if(up){
      // cam_position.z+=0.03;
    }
    else if(down){
      // cam_position.z-=0.03;
    }

    else if(speed_up){
      airplane.speed+=0.001;
      return 4;
    }
    else if(speed_down && airplane.speed>0.005){
      airplane.speed-=0.001;
      return -4;
    }

    else if(pitch){
      set = 1;
      return 1;
    }
    else if(yaw_left)
    {
      set = 2;
      return set;
    }
    else if(yaw_right)
    {
      set = -2;
      return set;
    }

    if(roll_right)
    {
      set = 3;
      return set;
    }
    else if(roll_left)
    {
      set = -3;
      return set;
    }

    if(bomb)
    {
      set = 5;
      return set;
    }

    if(missile)
    {
      set = 6;
      return set;
    }

    if(cam_1)
    {
      cur_cam = 1;
    }
    else if(cam_2)
    {
      cur_cam = 2;
    }
    else if(cam_3)
    {
      cur_cam = 3;
    }
    else if(cam_4)
    {
      cur_cam = 4;
    }
    else if(cam_5)
    {
      cur_cam = 5;
    }

    if(barrel_roll)
    {
      disable_input = 1;
    }
    return set;
}

void tick_elements(int move, GLFWwindow *window) {

    if(disable_input == 1)
    {
      int ret = airplane.barrel_roll();

      if(ret == 1)
        disable_input = 0;
    }
    else
      airplane.tick(move, cam_position, target_position);
    floors.tick(airplane.speed);
    dashboard.tick(move, airplane.ticker, airplane.fuel, airplane.rotation_y);
    dashboard.set_position(airplane.position);
    ammunition.tick(move, airplane.position, airplane.rotation_y);

    for(int i = 0;i<MAX_VOLCANO_COUNT; ++i)
      volcano[i].tick(airplane.position, window);


    for(int i = 0;i < MAX_CHECKPOINT_COUNT; ++i)
    {
      passed_count = checkpoint[i].tick(airplane.position,passed_count );

      if(passed_count < MAX_CHECKPOINT_COUNT && i == MAX_CHECKPOINT_COUNT - 1){

      // cout<<"[plane pos: ] "<<airplane.position.y<<" "<<airplane.position.z<<" "<<passed_count<<endl;
        checkpoint[i].tick_arrow(airplane.position, checkpoint[passed_count].position_checkpoint );
      }
    }

    for(int i = 0;i < MAX_SMOKERING_COUNT; ++i)
    {
      airplane.score += smokering[i].tick(airplane.position);
    }

    for(int i = 0;i < MAX_ENEMY_COUNT; ++i)
    {
      enemy[i].tick(airplane.position, floors.position, airplane.score);
      // cout<<"SCORE: "<<airplane.score<<"\n";
    }

    for(int i = 0;i < MAX_ENEMY_COUNT; ++i)
    {
      for(int j = 0;j<MAX_BOMB_STOCK - ammunition.bomb_stock; ++j)
      {
        if(ammunition.active_bomb[j])
        {
            airplane.score+=enemy[i].collision(ammunition.position_bomb[j]);
        }
      }
    }

    for(int i = 0; i< MAX_ADDON_COUNT/2 ; ++i )
    {
      int ret=addon[i].tick_fuel(airplane.position);

      if(ret != INT_MIN)
        {
          dashboard.height_fuelbar += ret;

          if(dashboard.height_fuelbar > 8)
            dashboard.height_fuelbar = 8;
        }
    }

    for(int i = 0;i < MAX_PARACHUTE_COUNT; ++i)
    {
      parachute[i].tick();
    }

    for(int i = 0;i < MAX_PARACHUTE_COUNT; ++i)
    {
      for(int j = 0;j<MAX_MISSILE_STOCK - ammunition.missile_stock; ++j)
      {
        if(ammunition.active_missile[j])
        {
            airplane.score+=parachute[i].collision(ammunition.position_missile[j]);
        }
      }
    }
    camera_rotation_angle += 0.7;

}

void drop_ammo(int s)
{
  tick_elements(s, window);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    airplane = Airplane(500, 100, 0, COLOR_RED);

    cam_position.x = 500; cam_position.y = 55; cam_position.z = 2;
    floors = Floors(0, 8, COLOR_SEABLUE);
    dashboard = Dashboard(COLOR_BLACK);
    land = Land(1000, 0, COLOR_FORESTGREEN);
    ammunition = Ammunition(airplane.position, COLOR_GREY);
    int random = rand();
    for(int i = 0; i< MAX_VOLCANO_COUNT; ++i)
    {
      random = rand();
      volcano[i] = Volcano(rand()%450 + 530 , rand()%1000 - 501);
    }
    random = rand();
    checkpoint[0] = Checkpoint(rand()%50 - 10 , rand()%60 + 20, -15, COLOR_BLACK);

    for(int i = 1;i < MAX_CHECKPOINT_COUNT; ++i)
    {
      checkpoint[i] = Checkpoint(rand()%50 - 10 , rand()%60 + 20, checkpoint[i-1].position_checkpoint.z - 35, COLOR_BLACK);
    }

    for(int i = 0;i < MAX_SMOKERING_COUNT; ++i)
    {
      smokering[i] = Smokering(checkpoint[i].position_checkpoint.x + rand()%100 + 15, rand()%60 + 20, checkpoint[i].position_checkpoint.z +rand()%25, COLOR_WHITE);
    }
    float enemy_y;
    int temp;

    for(int i = 0;i<MAX_ENEMY_COUNT; ++i)
    {
      random = rand();
        if(random % 2 == 0 && enemy_count < MAX_ENEMY_COUNT)
        {
          temp = rand()%1000 - 501;

          if(temp <= -400)
          {
            enemy_y = floors.position[0].y;
          }
          else if(temp <= -300)
          {
            enemy_y = floors.position[1].y;
          }
          else if(temp <= -200)
          {
            enemy_y = floors.position[2].y;
          }
          else if(temp <= -100)
          {
            enemy_y = floors.position[3].y;
          }
          else if(temp <= 0)
          {
            enemy_y = floors.position[4].y;
          }
          else if(temp <= 100)
          {
            enemy_y = floors.position[5].y;
          }
          else if(temp <= 200)
          {
            enemy_y = floors.position[6].y;
          }
          else if(temp <= 300)
          {
            enemy_y = floors.position[7].y;
          }
          else if(temp <= 400)
          {
            enemy_y = floors.position[8].y;
          }
          else if(temp <= 500)
          {
            enemy_y = floors.position[9].y;
          }
          enemy[enemy_count++] = Enemy(rand()%1000 - 500 , enemy_y + 2, temp, COLOR_RED);
        }
      }

    for(int i = 0;i <MAX_ADDON_COUNT/2; ++i)
    {
      addon[i] = Addon(rand()%1000 - 500 , rand()%60 + 30, rand()%200 - 100, 1);
    }

    for(int i = 0;i <MAX_PARACHUTE_COUNT; ++i)
    {
      parachute[i] = Parachute(rand()%1000 - 500 , 150, rand()%200 - 100);
    }


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices_dashboard.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_SKYBLUE.r / 256.0, COLOR_SKYBLUE.g / 256.0, COLOR_SKYBLUE.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    // INTERNAL INFORMATION
    // cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    // cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    // cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    // cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    width  = 1000;
    height = 1000;

    //Camera view Initialize



    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands

            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            int x = tick_input(window);
            tick_elements(x, window);
            draw(x);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(90.0f, 1.0f, 0.01f, 1000.0f);
    Matrices_dashboard.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
