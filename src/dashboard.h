#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(color_t color);
    glm::vec3 position_altimeter;
    float rotation_altimeter;

    glm::vec3 position_speedometer;
    float rotation_speedometer;

    glm::vec3 position_fuelbar;
    float height_fuelbar;

    void draw(glm::mat4 VP);
    void set_position(glm::vec3 position_plane);
    void tick(int move, int ticker, float& fuel);
    double speed;
private:
    VAO *object_altimeter;
    VAO *object_altimeter_pointer;
    VAO *object_speedometer;
    VAO *object_fuelbar;

};

#endif // DASHBOARD_H
