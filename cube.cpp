#include <vector>
#include "cube.h"

void Cube::draw() {

}

void Cube::build(std::vector<face_t> &faces){
    /* TODO: FIX NORMAL WRAPPING! */
    vec3f_t clr = {1.0, 1.0, 1.0};

    vec3f_t a = {x, y, z};
    vec3f_t b = {x, y + h, z};
    vec3f_t c = {x + w, y + h, z};
    vec3f_t i = {x + w, y, z};
    vec3f_t e = {x + w, y, z + d};
    vec3f_t f = {x + w, y + h, z + d};
    vec3f_t g = {x, y + h, z + d};
    vec3f_t h = {x, y, z + d};

    faces.push_back({a, b, c, calc_normal(a, b, c), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});
    faces.push_back({a, c, i, calc_normal(a, c, i), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});

    faces.push_back({h, g, f, calc_normal(h, g, f), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});
    faces.push_back({h, f, e, calc_normal(h, f, e), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});

    faces.push_back({h, a, i, calc_normal(h, a, i), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});
    faces.push_back({h, i, e, calc_normal(h, i, e), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});

    faces.push_back({g, b, c, calc_normal(g, b, c), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});
    faces.push_back({g, c, f, calc_normal(g, c, f), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});

    faces.push_back({h, a, b, calc_normal(h, a, b), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});
    faces.push_back({h, b, g, calc_normal(h, b, g), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});

    faces.push_back({e, i, c, calc_normal(e, i, c), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});
    faces.push_back({e, c, f, calc_normal(e, c, f), clr, clr, clr, GL_SHININESS, {1.0, 1.0, 1.0, 1.0}});
}
