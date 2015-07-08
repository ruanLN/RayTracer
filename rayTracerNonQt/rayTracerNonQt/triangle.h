#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "drawableobject.h"

class Triangle : public DrawableObject
{
public:
    Triangle(Point3D v1, Point3D v2, Point3D v3);

    virtual Intersection hitTest(Ray ray, bool *success);
    virtual Color mapTexture(Point3D point);

    Vector3D getPointNormal(Point3D);

    Point3D getV1() const;
    void setV1(const Point3D &value);

    Point3D getV2() const;
    void setV2(const Point3D &value);

    Point3D getV3() const;
    void setV3(const Point3D &value);

    Vector3D getNv1() const;
    void setNv1(const Vector3D &value);

    Vector3D getNv2() const;
    void setNv2(const Vector3D &value);

    Vector3D getNv3() const;
    void setNv3(const Vector3D &value);

    bool isSimpleNormal() const;
    void setSimpleNormal(bool value);

    std::pair<float, float> getUvCoordV1() const;
    void setUvCoordV1(const std::pair<float, float> &value);

    std::pair<float, float> getUvCoordV2() const;
    void setUvCoordV2(const std::pair<float, float> &value);

    std::pair<float, float> getUvCoordV3() const;
    void setUvCoordV3(const std::pair<float, float> &value);

private:
    Point3D v1, v2, v3;
    Vector3D nv1, nv2, nv3;
    std::pair<float, float> uvCoordV1, uvCoordV2, uvCoordV3;
    bool simpleNormal;
};

#endif // TRIANGLE_H
