#include "triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle()
{

}

Intersection Triangle::hitTest(Ray ray, bool *success)
{
    const double kEpsilon = 0.0001;
    Intersection intersect;
    // compute plane's normal
    Vector3D v0v1 = v1 - v0;
    Vector3D v0v2 = v2 - v0;
    // no need to normalize
    Vector3D N = v0v1.crossProduct(v0v2); // N
    double denom = N.dotProduct(N);
    N.normalize();

    // Step 1: finding P

    // check if ray and plane are parallel ?
    Vector3D dir = ray.getDirection();
    dir.normalize();
    double NdotRayDirection = N.dotProduct(ray.getDirection());
    if (fabs(NdotRayDirection) < kEpsilon){
        // almost 0
        (*success) = false;
        return intersect; // they are parallel so they don't intersect !
    }
//até aqui beleza

    // compute d parameter using equation 2
    Vector3D v0vec = v0.toVector();
    double d = N.dotProduct(v0vec);
    //std::cout << "distance to origin: " << d << std::endl;
    // compute t (equation 3)
    Point3D orig = ray.getOrigin();
    double t;
    t = (N.dotProduct(orig.toVector()) + d) / NdotRayDirection;

    // check if the triangle is in behind the ray
    if (t < 0){
        //(*success) = false;
        //return intersect; // the triangle is behind
    }

    // compute the intersection point using equation 1
    Point3D P = orig + ray.getDirection().scalarProduct(t);

    //if(ray.getOrigin().getX() > 0.1) {
    //    std::cout << "raio origem:" << ray.getOrigin().toString() << std::endl;
    //    std::cout << "raio direction:" << ray.getDirection().toString() << std::endl;
    //    std::cout << "passa pelo plano em :" << P.toString() << std::endl << std::endl;
    //}
    // Step 2: inside-outside test
    Vector3D C; // vector perpendicular to triangle's plane

    // edge 0
    Vector3D edge0 = v1 - v0;
    Vector3D vp0 = P - v0;
    C = edge0.crossProduct(vp0);
    if (N.dotProduct(C) < 0) {
        (*success) = false;
        return intersect; // P is on the right side
    }

    // edge 1
    Vector3D edge1 = v2 - v1;
    Vector3D vp1 = P - v1;
    C = edge1.crossProduct(vp1);
    double u = N.dotProduct(C);
    if (u < 0) {
        (*success) = false;
        return intersect; // P is on the right side
    }

    // edge 2
    Vector3D edge2 = v0 - v2;
    Vector3D vp2 = P - v2;
    C = edge2.crossProduct(vp2);
    double v = N.dotProduct(C);
    if (v < 0) {
        (*success) = false;
        return intersect; // P is on the right side;
    }

    u /= denom;
    v /= denom;

    intersect.setIntersectionPoint(P);
    N.normalize();
    intersect.setNormalVector(N);
    (*success) = true;
    std::cout << "raio origem:" << ray.getOrigin().toString() << std::endl;
    std::cout << "intersect point: " << intersect.getIntersectionPoint() << std::endl << std::endl;
    return intersect; // this ray hits the triangle
}

Point3D Triangle::getV0() const
{
    return v0;
}

void Triangle::setV0(const Point3D &value)
{
    v0 = value;
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


