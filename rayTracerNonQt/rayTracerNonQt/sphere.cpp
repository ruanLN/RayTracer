#include "sphere.h"

Sphere::Sphere()
{

}

Intersection Sphere::hitTest(Ray ray, bool *success)
{
    Vector3D OC = (this->center - ray.getDirection()).toVector();
    OC.normalize();
    Intersection intersec;
    Vector3D normal;
    if(OC.dotProduct(ray.getDirection()) < 0.999) {
        *success = true;
    } else {
        *success = false;
    }
    intersec.setNormalVector(normal);
    intersec.setIntersectionPoint(this->center - ray.getDirection()); // ERRADO
    return intersec;
}
Point3D Sphere::getCenter() const
{
    return center;
}

void Sphere::setCenter(const Point3D &value)
{
    center = value;
}
double Sphere::getRay() const
{
    return ray;
}

void Sphere::setRay(double value)
{
    ray = value;
}

