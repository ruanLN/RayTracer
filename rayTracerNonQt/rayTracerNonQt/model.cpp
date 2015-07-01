#include "model.h"

Model::Model()
{

}



Intersection Model::hitTest(Ray ray, bool *success)
{
    Intersection intersec;
    Intersection ret;
    double zBuffer = -1;
    Color colLocal;
    bool sucesso;
    for(std::list<Triangle>::iterator it = faces.begin(); it != faces.end(); it++) {
        intersec = (*it).hitTest(ray, &sucesso);
        if(success) {
            if(zBuffer > (intersec.getIntersectionPoint() - ray.getOrigin()).norm() || zBuffer == -1) {
                *success = true;
                ret = intersec;
                zBuffer = (intersec.getIntersectionPoint() - ray.getOrigin()).norm();
            }
        }
    }
    return ret;
}

Color Model::mapTexture(Point3D point)
{
    return this->objectMaterial.getDiffuseMaterialColor();
}

void Model::addTriangle(Triangle t)
{
    faces.push_back(t);
}
