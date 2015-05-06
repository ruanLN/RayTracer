#include "camera.h"

Camera::Camera()
{

}
Point3D Camera::getPosition() const
{
    return position;
}

void Camera::setPosition(const Point3D &value)
{
    position = value;
}
Vector3D Camera::getUpVector() const
{
    return upVector;
}

void Camera::setUpVector(const Vector3D &value)
{
    upVector = value;
}
Vector3D Camera::getEyeVector() const
{
    return eyeVector;
}

void Camera::setEyeVector(const Vector3D &value)
{
    eyeVector = value;
}
int Camera::getRenderedImageHeight() const
{
    return renderedImageHeight;
}

void Camera::setRenderedImageHeight(int value)
{
    renderedImageHeight = value;
}
int Camera::getRenderedImageWidth() const
{
    return renderedImageWidth;
}

void Camera::setRenderedImageWidth(int value)
{
    renderedImageWidth = value;
}

std::string Camera::toString() const
{
    std::ostringstream ss;
    ss << "Pos: " << this->position.toString() << "; up: " << this->upVector.toString() << "; eye: " << this->eyeVector.toString();
    std::string stringCam = ss.str();
    return stringCam;
}






