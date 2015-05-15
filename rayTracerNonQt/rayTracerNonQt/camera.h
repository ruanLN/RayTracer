#ifndef CAMERA_H
#define CAMERA_H

#include "point3d.h"
#include "vector3d.h"



class Camera
{
public:
    Camera();

    Point3D getPosition() const;
    void setPosition(const Point3D &value);

    Vector3D getUpVector() const;
    void setUpVector(const Vector3D &value);

    Vector3D getEyeVector() const;
    void setEyeVector(const Vector3D &value);

    int getRenderedImageHeight() const;
    void setRenderedImageHeight(int value);

    int getRenderedImageWidth() const;
    void setRenderedImageWidth(int value);

    int getZNear() const;
    void setZNear(int value);

    int getSuperSamplingFactor() const;
    void setSuperSamplingFactor(int value);

    //debug purposes
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& stream, const Camera& cam)
    {
        stream << cam.toString();
        return stream;
    }
private:
    Point3D position;
    Vector3D upVector;
    Vector3D eyeVector;

    int renderedImageHeight;
    int renderedImageWidth;

    int zNear;
    int superSamplingFactor;
};

#endif // CAMERA_H
