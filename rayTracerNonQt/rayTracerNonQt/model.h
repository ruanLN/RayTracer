#ifndef MODEL_H
#define MODEL_H

#include "drawableobject.h"
#include "triangle.h"
#include <list>


class Model : public DrawableObject
{
public:
    Model();

    virtual Intersection hitTest(Ray ray, bool *success);
    virtual Color mapTexture(Point3D point);

    void addTriangle(Triangle t);

private:
    std::list<Triangle> faces;
};

#endif // MODEL_H
