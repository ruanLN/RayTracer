#include <iostream>
#include "scene.h"
#include "vector3d.h"

using namespace std;

int main()
{
    Scene scene;
    scene.readScene("scene01-zoom-ss-reflect-lights-shadows.yaml");
    std::cout << "time 1, cena lida" << std::endl;
    scene.renderScene("scene01-zoom-ss-reflect-lights-shadows-tex.png");
    std::cout << "time 2, cena renderizada" << std::endl;
    return 0;
}

