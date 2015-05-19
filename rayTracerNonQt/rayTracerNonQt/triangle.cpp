#include "triangle.h"
#include <cmath>

Triangle::Triangle()
{

}

Intersection Triangle::hitTest(Ray ray, bool *success)
{
    Vector3D edge1, edge2, edge3, triangleNormal;
    double epsilon = 0.00001;
    double dir, d, t;
    *success = true;

    edge1 = this->v2 - this->v1;
    edge2 = this->v3 - this->v1;
    triangleNormal = edge1.crossProduct(edge2);
    triangleNormal.normalize();

    dir = ray.getDirection().dotProduct(triangleNormal);
    if(fabs(dir) < epsilon) {
        *success = false;
    }

    d = triangleNormal.dotProduct((this->v1).toVector());
    t = triangleNormal.dotProduct(ray.getOrigin().toVector());
    t += d;
    t /= dir;
    if (t < 0) {
        *success = false;
    }

    Vector3D normal;
    Point3D intersectionPoint;
    intersectionPoint = ray.getOrigin() + ray.getDirection().scalarProduct(t);

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

    Intersection intersec;
    intersec.setNormalVector(triangleNormal);
    intersec.setIntersectionPoint(intersectionPoint);
    intersec.setT(t);
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


