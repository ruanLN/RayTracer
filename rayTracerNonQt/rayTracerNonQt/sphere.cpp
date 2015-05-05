#include "sphere.h"
#include <cmath>

Sphere::Sphere()
{

}

Intersection Sphere::hitTest(Ray ray, bool *success)
{
    double delta, d;
    ray.getDirection().normalize();
    delta = ray.getDirection().dotProduct(ray.getOrigin() - this->center);
    delta *= delta; //sqr
    delta -= ((ray.getOrigin() - this->center).norm()) * ((ray.getOrigin() - this->center).norm());
    delta += (this->radius * this->radius);

    if(delta <= -0.0001) {
        *success = false;
    } else if(delta >= 0.0001) {
        *success = true;
        d = -(ray.getDirection().dotProduct(ray.getOrigin() - this->center)) - sqrt(delta);
    } else {
        *success = true;
        d = -(ray.getDirection().dotProduct(ray.getOrigin() - this->center));
    }
    Vector3D normal;
    Point3D intersectionPoint;
    if(*success) {
        intersectionPoint = ray.getOrigin() + ray.getDirection().scalarProduct(d);
        normal = intersectionPoint - this->center;
    }
    Intersection intersec;
    intersec.setNormalVector(normal);
    intersec.setIntersectionPoint(intersectionPoint);
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
double Sphere::getRadius() const
{
    return radius;
}

void Sphere::setRadius(double value)
{
    radius = value;
}

