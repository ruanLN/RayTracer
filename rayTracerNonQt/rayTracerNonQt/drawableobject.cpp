#include "drawableobject.h"
#include "scene.h"
#include "sphere.h"
#include <cmath>

DrawableObject::DrawableObject()
{

}
Material DrawableObject::getObjectMaterial() const
{
    return objectMaterial;
}

void DrawableObject::setObjectMaterial(const Material &value)
{
    objectMaterial = value;
}

Color DrawableObject::getPointColor(Intersection intersection)
{
    std::list<Light*> lights = parentScene->getLights();
    std::list<Light*>::iterator it;
    std::list<DrawableObject*> objects = parentScene->getObjects();
    std::list<DrawableObject*>::iterator itObj;

    Color ia = objectMaterial.getMaterialColor() * objectMaterial.getAmbientComponent();
//    ia.normalize(1/objectMaterial.getAmbientComponent());
    Color i;
    i = ia;
    for(it = lights.begin(); it != lights.end(); it++) {
        Light actualLight = *(*it);
        Vector3D lightVector = actualLight.getPosition() - intersection.getIntersectionPoint();
        lightVector.normalize();

        Ray lightRay;
        lightRay.setDirection(lightVector);
        lightRay.setOrigin(intersection.getIntersectionPoint() + lightVector);

        bool success = false;
        for(itObj = objects.begin(); itObj != objects.end(); itObj++) {
            if((*itObj) == this) {
                continue;
            }
            Intersection intersec = (*itObj)->hitTest(lightRay, &success);
            if(success) {
                double interseDistance = (intersec.getIntersectionPoint() - actualLight.getPosition()).norm();
                double pointDistance = (lightRay.getOrigin() - actualLight.getPosition()).norm();
                if(interseDistance < pointDistance) {
                    break;
                } else {
                    success = false;
                }
            }
        }
        if(!success){
            Color id = objectMaterial.getMaterialColor() * objectMaterial.getDiffuseComponent();
            double diffuseLightFactor = (intersection.getNormalVector().dotProduct(lightVector));
            if(diffuseLightFactor < 0) {
                diffuseLightFactor = 0;
            }
            id = (id * diffuseLightFactor) * actualLight.getColor();

            Color is = objectMaterial.getMaterialColor() * objectMaterial.getSpecularComponent();
            Vector3D V = parentScene->getEye().getPosition() - intersection.getIntersectionPoint();
            V.normalize();
            Vector3D R = V - intersection.getNormalVector().scalarProduct(2).scalarProduct(intersection.getNormalVector().dotProduct(V));
            double specularLightFactor = V.dotProduct(R);
//            if(specularLightFactor < 0) {
//                specularLightFactor = 0;
//            }

            specularLightFactor = pow(specularLightFactor, objectMaterial.getSpecularExponent());
            is = (is * specularLightFactor) * actualLight.getColor();
            i = i + id * 1 + is * 1;
        }
    }
    return i;
}

std::string DrawableObject::toString() const
{
    std::ostringstream stringStream;
    stringStream << "Material: " << this->objectMaterial.toString();
    std::string stringPoint = stringStream.str();
    return stringPoint;
}
Scene *DrawableObject::getParentScene() const
{
    return parentScene;
}

void DrawableObject::setParentScene(Scene *value)
{
    parentScene = value;
}

