#include "triangle.h"
#include <cmath>

#include <iostream>

Triangle::Triangle()
{

}

Intersection Triangle::hitTest(Ray ray, bool *success)
{
    Intersection intersec;
    Vector3D edge1, edge2, edge3, triangleNormal;
    double epsilon = 0.0001;
    double dir, t;
    *success = true;

    edge1 = this->v2 - this->v1;
    edge2 = this->v3 - this->v1;
    triangleNormal = edge1.crossProduct(edge2);
    triangleNormal;
    Vector3D direction = ray.getDirection();
    //using v1 as a point of the plane
    double den = triangleNormal.getX() * direction.getX() + triangleNormal.getY() * direction.getY() + triangleNormal.getZ() * direction.getZ();
    double d = -(triangleNormal.getX() * this->v1.getX() + triangleNormal.getY() * this->v1.getY() + triangleNormal.getZ() * this->v1.getZ());

    //dir = ray.getDirection().dotProduct(triangleNormal);
    if(fabs(den) < epsilon) {
        *success = false;
        return intersec;
    }
    Point3D orig = ray.getOrigin();
    double num = triangleNormal.getX() * orig.getX() + triangleNormal.getY() * orig.getY() + triangleNormal.getZ() * orig.getZ() + d;
    t = -(num/den);
   // std::cout << "intersecta o plano anyway, t: " << t << std::endl;
    if (t < 0) {
        *success = false;
        return intersec;
    }
    Point3D intersectionPoint;
    Vector3D rayDirection = ray.getDirection();
    rayDirection.normalize();
    intersectionPoint = ray.getOrigin() + rayDirection.scalarProduct(t);
    //std::cout << "intersectou o plano em positivo: " << intersectionPoint.toString() << std::endl;

    Vector3D perpendicular;
    edge1 = this->v2 - this->v1;
    Point3D vp1 = intersectionPoint - (this->v1).toVector();
    perpendicular = edge1.crossProduct(vp1.toVector());
    if (triangleNormal.dotProduct(perpendicular) < 0) {
        *success = false;
    }
    edge2 = this->v3 - this->v2;
    Point3D vp2 = intersectionPoint - (this->v2).toVector();
    perpendicular = edge2.crossProduct(vp2.toVector());
    if (triangleNormal.dotProduct(perpendicular) < 0) {
        *success = false;
    }
    edge3 = this->v1 - this->v3;
    Point3D vp3 = intersectionPoint - (this->v3).toVector();
    perpendicular = edge3.crossProduct(vp3.toVector());
    if (triangleNormal.dotProduct(perpendicular) < 0) {
        *success = false;
    }

    triangleNormal.normalize();
    //triangleNormal = triangleNormal.scalarProduct(-1);
    intersec.setNormalVector(triangleNormal);
    intersec.setIntersectionPoint(intersectionPoint);
    intersec.setT(t);
    intersec.setCauseRay(ray);
    return intersec;
}

Point3D Triangle::getV1() const
{
    return v1;
}

void Triangle::setV1(const Point3D &value)
{
    v1 = value;
}
Point3D Triangle::getV2() const
{
    return v2;
}

void Triangle::setV2(const Point3D &value)
{
    v2 = value;
}
Point3D Triangle::getV3() const
{
    return v3;
}

void Triangle::setV3(const Point3D &value)
{
    v3 = value;
}


