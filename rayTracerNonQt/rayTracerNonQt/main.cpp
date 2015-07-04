#include <iostream>
#include <time.h>
#include "scene.h"
#include "vector3d.h"

using namespace std;

int main()
{
    Scene scene;
    clock_t t1,t2;
    t1=clock();
    scene.readScene("scene01-zoom-ss-reflect-lights-shadows.yaml");
    //code goes here
    scene.renderScene("face.png");
    std::cout << "time 2, cena renderizada" << std::endl;
    t2=clock();
    float diff = ((float)t2-(float)t1) / CLOCKS_PER_SEC;

    std::cout<<diff<<std::endl;
    return 0;
}

