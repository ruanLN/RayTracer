#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "intersection.h"
#include "material.h"
#include "ray.h"
#include "image.h"

class Scene;
class DrawableObject
{
public:
    DrawableObject();

    virtual Intersection hitTest(Ray ray, bool *success) = 0;

    Material getObjectMaterial() const;
    void setObjectMaterial(const Material &value);

    Color getPointColor(Intersection intersection, int depth = 0);

    //debug purposes
    virtual std::string toString() const;
    friend std::ostream& operator<<(std::ostream& stream, const DrawableObject& obj)
    {
        stream << obj.toString();
        return stream;
    }

    Scene *getParentScene() const;
    void setParentScene(Scene *value);

    Image getTexture() const;
    void setTexture(const Image &value);
    virtual Color mapTexture(Point3D point) = 0;

protected:
    Material objectMaterial;
    Image texture;
    bool hasTexture;
    Scene *parentScene;
};

#endif // DRAWABLEOBJECT_H
