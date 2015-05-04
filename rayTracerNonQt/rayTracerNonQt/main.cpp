#include <iostream>
#include "vector3d.h"

using namespace std;

int main()
{
    Vector3D v1(1,1,1), v2(2,2,0), v3(-1,0,0);

    cout << "v1 x v2 =  " << Vector3D::crossProduct(v1, v2);
    return 0;
}

