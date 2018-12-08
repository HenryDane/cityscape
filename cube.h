#ifndef CUBE_H
#define CUBE_H 1

#include <vector>
#include "main.h"
#include "structure.h"

class Cube : public Structure {
public:
    Cube () {
        x = 0; y = 0; z = 0;
        w = 1; h = 1; d = 1;
    }

    Cube (float x, float y, float z, float w, float d, float h) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->h = h;
        this->d = d;
    }

    void draw();
    void build(std::vector<face_t> &faces);
};

#endif // CUBE_H
