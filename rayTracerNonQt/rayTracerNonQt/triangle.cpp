#include "triangle.h"
#include <cmath>

#include <iostream>

Triangle::Triangle(Point3D v1, Point3D v2, Point3D v3) :
    v1(v1),
    v2(v2),
    v3(v3),
    simpleNormal(true)
{
    Vector3D edge1, edge2;
    edge1 = this->v2 - this->v1;
    edge2 = this->v3 - this->v1;
    nv1 = edge1.crossProduct(edge2);
    nv1.normalize();
    nv2 = nv1;
    nv3 = nv1;
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
    intersec.setIntersectionPoint(intersectionPoint);
    intersec.setNormalVector(simpleNormal? triangleNormal : getPointNormal(intersectionPoint));
    //intersec.setNormalVector(triangleNormal);
    intersec.setT(t);
    intersec.setCauseRay(ray);
    return intersec;
}

Color Triangle::mapTexture(Point3D point)
{
    return this->objectMaterial.getDiffuseMaterialColor();
}

Vector3D Triangle::getPointNormal(Point3D)  //TODO: use barycentric coordinates to map normal
{
    Vector3D edge1, edge2, triangleNormal;

    edge1 = this->v2 - this->v1;
    edge2 = this->v3 - this->v1;
    triangleNormal = edge1.crossProduct(edge2);
    triangleNormal.normalize();
    return triangleNormal;
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
Vector3D Triangle::getNv1() const
{
    return nv1;
}

void Triangle::setNv1(const Vector3D &value)
{
    nv1 = value;
    simpleNormal = false;
}
Vector3D Triangle::getNv2() const
{
    return nv2;
}

void Triangle::setNv2(const Vector3D &value)
{
    nv2 = value;
    simpleNormal = false;
}
Vector3D Triangle::getNv3() const
{
    return nv3;
}

void Triangle::setNv3(const Vector3D &value)
{
    nv3 = value;
    simpleNormal = false;
}
bool Triangle::isSimpleNormal() const
{
    return simpleNormal;
}

void Triangle::setSimpleNormal(bool value)
{
    simpleNormal = value;
}
std::pair<float, float> Triangle::getUvCoordV1() const
{
    return uvCoordV1;
}

void Triangle::setUvCoordV1(const std::pair<float, float> &value)
{
    uvCoordV1 = value;
}
std::pair<float, float> Triangle::getUvCoordV2() const
{
    return uvCoordV2;
}

void Triangle::setUvCoordV2(const std::pair<float, float> &value)
{
    uvCoordV2 = value;
}
std::pair<float, float> Triangle::getUvCoordV3() const
{
    return uvCoordV3;
}

void Triangle::setUvCoordV3(const std::pair<float, float> &value)
{
    uvCoordV3 = value;
}









