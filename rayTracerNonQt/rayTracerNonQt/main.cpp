#include <iostream>
#include "scene.h"
#include "vector3d.h"

using namespace std;

int main()
{
    Vector3D v1(1,1,1), v2(2,2,0), v3(-1,0,0);

    //cout << "v1 x v2 =  " << Vector3D::crossProduct(v1, v2);


    Scene scene;
    scene.readScene("scene01.yaml");

    std::cout << scene.toString();
    return 0;
}

