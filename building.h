#ifndef BUILDING_H
#define BUILDING_H 1

#include <vector>
#include "main.h"
#include "structure.h"

class Building : public Structure {
    int stories;
    float story_height;
    int windows_per_story;
    float margin;

    void build_face(std::vector<face_t> &faces, int side);
public:
    Building () {

    }

    //      |       |        |        |  x + w |  z + d | y + (stories * story_height + margin)
    Building(float x, float y, float z, float w, float d, int stories, float margin) {

    }
};

#endif // BUILDING_H
