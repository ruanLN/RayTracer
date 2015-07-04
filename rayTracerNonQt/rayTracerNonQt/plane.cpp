#include "plane.h"
#include <cmath>

Plane::Plane()
{

}



Intersection Plane::hitTest(Ray ray, bool *success)
{
    Intersection intersec;
    double epsilon = 0.0001;
    *success = true;
    Vector3D direction = ray.getDirection();
    //using v1 as a point of the plane
    double den =this->normal.dotProduct(direction);

    if(fabs(den) < epsilon) {
        *success = false;
        return intersec;
    }

    double d = -(this->normal.dotProduct(this->point.toVector()));
    double num = normal.dotProduct(ray.getOrigin().toVector()) + d;
    double t = -(num/den);
    if (t < 0) {
        *success = false;
        return intersec;
    }
    Point3D intersectionPoint;
    direction.normalize();
    intersectionPoint = ray.getOrigin() + direction.scalarProduct(t);
    //std::cout << "intersectou o plano em positivo: " << intersectionPoint.toString() << std::endl;

    this->normal.normalize();
    intersec.setNormalVector(this->normal);
    intersec.setIntersectionPoint(intersectionPoint);
    intersec.setT(t);
    intersec.setCauseRay(ray);
    return intersec;
}

Color Plane::mapTexture(Point3D point)
{
    return this->objectMaterial.getDiffuseMaterialColor();
}

Vector3D Plane::getNormal() const
{
    return normal;
}

void Plane::setNormal(const Vector3D &value)
{
    normal = value;
}
void Plane::setPoint(const Point3D &value)
{
    point = value;
}
Point3D Plane::getPoint() const
{
    return point;
}


