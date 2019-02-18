#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard():disp(7) {}
    Dashboard(color_t color);
    glm::vec3 position_altimeter;
    float rotation_altimeter;

    glm::vec3 position_speedometer;
    float rotation_speedometer;

    glm::vec3 position_fuelbar;
    float height_fuelbar;

    int score;
    float angle;
    glm::vec3 position_scoreboard;
    std::vector<std::vector<GLfloat> > disp;

    void draw(glm::mat4 VP, int score);
    void set_position(glm::vec3 position_plane);
    void tick(int move, int ticker, float& fuel);
    double speed;

private:
    VAO *object_altimeter;
    VAO *object_altimeter_pointer;
    VAO *object_speedometer;
    VAO *object_fuelbar;
    VAO *object_scoreboard;
    VAO *object_score;

};

#endif // DASHBOARD_H
