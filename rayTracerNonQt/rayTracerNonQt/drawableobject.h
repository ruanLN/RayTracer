#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "intersection.h"
#include "material.h"
#include "ray.h"

class DrawableObject
{
public:
    DrawableObject();

    virtual Intersection hitTest(Ray ray, bool *success) = 0;

    Material getObjectMaterial() const;
    void setObjectMaterial(const Material &value);

    Color getPointColor(Intersection intersection);

private:
    Material objectMaterial;
};

#endif // DRAWABLEOBJECT_H
