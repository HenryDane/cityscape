#ifndef STRUCTURE_H
#define STRUCTURE_H 1

#include <vector>
#include "main.h"

class Structure {
public:
    float x;
    float y;
    float z;
    float w;
    float h;
    float d;

    virtual void draw() { };
    virtual void build(std::vector<face_t> &faces) { };
};

#endif // STRUCTURE_H
