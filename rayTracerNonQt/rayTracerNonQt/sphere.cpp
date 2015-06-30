#include "sphere.h"
#include <cmath>
#include <iostream>

Sphere::Sphere()
{

}

Intersection Sphere::hitTest(Ray ray, bool *success)
{
    double delta, d;
    ray.getDirection().normalize();
    Vector3D dir = ray.getOrigin() - this->center;
    //dir.normalize();
    delta = ray.getDirection().dotProduct(dir);
    delta *= delta; //sqr
    delta -= ((ray.getOrigin() - this->center).norm()) * ((ray.getOrigin() - this->center).norm());
    delta += (this->radius * this->radius);

    if(delta <= 0) {
        *success = false;
    } else if(delta >= 0.1) {
        *success = true;
        double d1, d2;
        d1 = -(ray.getDirection().dotProduct(ray.getOrigin() - this->center)) - sqrt(delta);
        d2 = -(ray.getDirection().dotProduct(ray.getOrigin() - this->center)) + sqrt(delta);
        d = (d1 < d2)? d1 : d2;
    } else {
        *success = true;
        d = -(ray.getDirection().dotProduct(ray.getOrigin() - this->center));
    }
    Vector3D normal;
    Point3D intersectionPoint;
    if(*success) {
        intersectionPoint = ray.getOrigin() + ray.getDirection().scalarProduct(d);
        normal = intersectionPoint - this->center;
        normal.normalize();
    }
    Intersection intersec;
    intersec.setNormalVector(normal);
    intersec.setIntersectionPoint(intersectionPoint);
    intersec.setT(d);
    intersec.setCauseRay(ray);
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



std::string Sphere::toString() const
{
    std::ostringstream stringStream;
    stringStream << "Center: " << this->center.toString() << " Radius: " << this->radius << " " << DrawableObject::toString();
    std::string stringPoint = stringStream.str();
    return stringPoint;
}


Color Sphere::mapTexture(Point3D point)
{
    float u, v;
    Vector3D d = this->center - point;
    d.normalize();
    float theta = acos(d.getY());
    float phi   = atan2(d.getX(), d.getZ());

    if(phi < 0.0)
        phi += 2*M_PI;

    u = phi/(2*M_PI);
    v = (M_PI - theta)/M_PI;
    //u = 0.5 + atan2(d.getZ(), d.getX()) / (2 * M_PI);
    //v = 0.5 - asin(d.getY()) / M_PI;
    //u = u > 1? 1 : (u < 0? 0 : u);
    //v = v > 1? 1 : (v < 0? 0 : v);
    int row, column;
    column = (int)((texture.getWidth() - 1) * u);
    row = (int)((texture.getHeight() - 1) * v);
    //std::cout << "textura em (" << u << ", " << v << "): " << texture.getPixel(1-v,u) << std::endl;
    return texture.getPixel(row, column);
}
