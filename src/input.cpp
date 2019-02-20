#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

double x_position_initial = INT_MIN;
double y_position_initial = INT_MIN;
double x_position_final = 0.0;
double y_position_final = 0.0;
float sphere_radius = 8;
float rotation_x = 0.0;
float rotation_y = 0.0;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        // quit(window);
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:

    if(cur_cam == 5)
    {
      if (action == GLFW_PRESS) {
          glfwGetCursorPos(window, &x_position_initial, &y_position_initial);
          pressed = 1;
          return;
      } else if (action == GLFW_RELEASE) {

        x_position_initial = INT_MIN;
        y_position_initial = INT_MIN;
      }
      else
      {
        x_position_initial = INT_MIN;
        y_position_initial = INT_MIN;
      }
    }
    else
    {
        if (action == GLFW_PRESS) {
            // Do something
            return;
        } else if (action == GLFW_RELEASE) {
            // Do something
            drop_ammo(6);
        }
    }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_PRESS) {
            // Do something
            return;
        } else if (action == GLFW_RELEASE) {
            // Do something
            drop_ammo(5);
        }
        break;
    // case GLFW_MOUSE_BUTTON_RIGHT:
    // if (action == GLFW_RELEASE) {
    // rectangle_rot_dir *= -1;
    // }
    // break;
    default:
        break;
    }
}

void helicopter_track(GLFWwindow *window, int height, int width, glm::vec3 &cam_position, glm::vec3 airplane_position)
{
  float x_diff,y_diff;
  if(x_position_initial!=INT_MIN && y_position_initial!=INT_MIN)
  {
    double x = x_position_final;
    double y = y_position_final;
    glfwGetCursorPos(window, &x_position_final, &y_position_final);

    x_diff = x_position_final - x_position_initial;
    y_diff = y_position_final - y_position_initial;

    if(x!=x_position_final)
      rotation_x += ( ((M_PI/8)/width )*x_diff );

    if(y!=y_position_final)
      rotation_y += ( ((M_PI/8)/height)*y_diff );

  }

  cam_position.x = airplane_position.x + sphere_radius * sin(fmod(rotation_y,360.0)) *sin(fmod(rotation_x,360.0));
  cam_position.z = airplane_position.z + sphere_radius * sin(fmod(rotation_y,360.0)) * cos(fmod(rotation_x,360.0));
  cam_position.y = airplane_position.y + sphere_radius * -1*cos(fmod(rotation_y,360.0));
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something

    if(cur_cam == 5)
    {
      sphere_radius-=yoffset*1;

      if(sphere_radius <3)
        sphere_radius = 3;
      if(sphere_radius > 18)
        sphere_radius = 18;

    }
    else
      screen_zoom+=yoffset*1;
    reset_screen();
}
