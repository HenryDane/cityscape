#ifndef MAIN_H
#define MAIN_H 1

#include <SFML/OpenGL.hpp>
#include <string>
#include "patch.h"
#include "camera.h"

struct vec3f_t {
    float x;
    float y;
    float z;

    vec3f_t operator- (vec3f_t &a){
        vec3f_t t = {x - a.x, y - a.y, z - a.z};
        return t;
    }

    vec3f_t operator* (float a) {
        vec3f_t t = {x * a, y * a, z * a};
        return t;
    }

    std::string str() {
        std::string str = "(" + patch::to_string(x) + "," + patch::to_string(y) + "," + patch::to_string(z) + ")";
        return str;
    }
};

struct vec2f_t {
    float x;
    float y;
};

struct face_t {
    vec3f_t a;
    vec3f_t b;
    vec3f_t c;

    vec3f_t n; // auto-computed

    vec3f_t clr_a;
    vec3f_t clr_b;
    vec3f_t clr_c;

    int material;
    float mat_param[4];

    void draw() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLES);

        glMaterialfv(GL_FRONT_AND_BACK, material, mat_param);

        glNormal3f(n.x, n.y, n.z);

        glColor3f(clr_a.x, clr_a.y, clr_a.z);
        glVertex3f(a.x, a.y, a.z);
        glColor3f(clr_b.x, clr_b.y, clr_b.z);
        glVertex3f(b.x, b.y, b.z);
        glColor3f(clr_c.x, clr_c.y, clr_c.z);
        glVertex3f(c.x, c.y, c.z);

        glEnd();
    }
};

vec3f_t calc_normal(vec3f_t a, vec3f_t b, vec3f_t c);
void hide_cursor();
void expose_cursor();

extern EulerCamera camera;

#endif // MAIN_H
