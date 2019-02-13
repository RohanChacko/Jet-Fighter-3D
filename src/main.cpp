#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "floor.h"
#include "enemy.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

/* Object Declaration */
Airplane airplane;
Floors floors;
Enemy enemy[3000];
int enemy_count = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int set = 1;
Timer t60(1.0 / 60);
glm::vec3 cam_position;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw(int x) {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!

    // LEFT ARROW KEY AND RIGHT ARROW KEY CHANGES THE VIEW FROM TOWER VIEW TO INSIDE CUBE VIEW

    // cam_position.z = airplane.position.z - 2;
    cam_position.y = airplane.position.y + 3;
    cam_position.x = airplane.position.x;
    cam_position.z = airplane.position.z + 3;
    // cam_position.z+=airplane.speed;
    // cout<<airplane.position.x<<" "<<airplane.position.y<<" "<<airplane.position.z<<endl;
    glm::vec3 eye (cam_position.x, cam_position.y, cam_position.z);
    // cout<<cam_position.x<<" "<<cam_position.y<<" "<< cam_position.z<<endl;
    // glm::vec3 eye (5*cos(camera_rotation_angle*M_PI/180.0f), 3, 5*sin(camera_rotation_angle*M_PI/180.0f));
    // Target - Where is the camera looking at.  Don't change unless you are sure!!

    glm::vec3 target (airplane.position.x, airplane.position.y, airplane.position.z);

    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    floors.draw(VP);
    airplane.draw(VP);

    for(int i = 0;i < enemy_count; ++i)
    {
      enemy[i].draw(VP);
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

    if (left) {
      cam_position.x+=0.03;
    }
    else if(right){
      cam_position.x-=0.03;
    }
    else if(up){
      cam_position.z+=0.03;
    }
    else if(down){
      cam_position.z-=0.03;
    }

    else if(speed_up){
      airplane.speed+=0.001;
    }
    else if(speed_down && airplane.speed>0.005){
      airplane.speed-=0.001;
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
    return INT_MIN;
}

void tick_elements(int move) {
    airplane.tick(move);
    floors.tick(airplane.speed);

    for(int i = 0;i < enemy_count; ++i)
    {
      enemy[i].tick(airplane.position);
    }

    camera_rotation_angle += 0.7;

    int random = rand();

    if(random % 2 == 0 && enemy_count < 3000)
    {
      enemy[enemy_count++] = Enemy(rand()%1000 - 500 , 0, rand()%1000 - 500, COLOR_RED);
    }
    cout<<enemy[enemy_count-1].position.x<<" "<<enemy[enemy_count-1].position.z<<endl;

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    airplane = Airplane(0, 5, 0, COLOR_RED);
    floors = Floors(0, 0, COLOR_BLUE);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BURLYWOOD.r / 256.0, COLOR_BURLYWOOD.g / 256.0, COLOR_BURLYWOOD.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;
    //Camera view Initialize

    cam_position.x = 0;
    cam_position.y = 6;
    cam_position.z = -4;

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
            tick_elements(x);
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
}
