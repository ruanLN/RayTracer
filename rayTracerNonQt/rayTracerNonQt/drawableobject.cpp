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

Color DrawableObject::getPointColor(Intersection intersection, int depth)
{
    std::list<Light*> lights = parentScene->getLights();
    std::list<Light*>::iterator it;
    std::list<DrawableObject*> objects = parentScene->getObjects();
    std::list<DrawableObject*>::iterator itObj;

    Color i;
    double attenuationFactor = 1;
    Color ia = objectMaterial.getAmbientMaterialColor() * objectMaterial.getAmbientComponent();
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
                    //attenuationFactor += pointDistance*actualLight.getLinearAtt() + pow(pointDistance,2)*actualLight.getQuadraticAtt();
                }
            }
        }
        if(!success){
            double pointDistance = (lightRay.getOrigin() - actualLight.getPosition()).norm();
            attenuationFactor += pointDistance*actualLight.getLinearAtt() + pow(pointDistance,2)*actualLight.getQuadraticAtt();
            attenuationFactor = 1.0/attenuationFactor;
            Color id = objectMaterial.getDiffuseMaterialColor() * objectMaterial.getDiffuseComponent();
            double diffuseLightFactor = (lightVector.dotProduct(intersection.getNormalVector()));
            if(diffuseLightFactor < 0) {
                diffuseLightFactor = 0;
            }
            id = (id * diffuseLightFactor) * actualLight.getColor();

            Color is = objectMaterial.getSpecularMaterialColor() * objectMaterial.getSpecularComponent();
            Vector3D V = parentScene->getEye().getPosition() - intersection.getIntersectionPoint();
            V.normalize();
            Vector3D R;// = V - intersection.getNormalVector().scalarProduct(2).scalarProduct(intersection.getNormalVector().dotProduct(V));
            R = intersection.getNormalVector().scalarProduct(2);
            double NL = intersection.getNormalVector().dotProduct(lightVector);
            R = R.scalarProduct(NL);
            R = R - lightVector;
            R.normalize();
            double specularLightFactor = V.dotProduct(R);
//            if(specularLightFactor < 0) {
//                specularLightFactor = 0;
//            }

            specularLightFactor = pow(specularLightFactor, objectMaterial.getSpecularExponent());
            is = (is * specularLightFactor) * actualLight.getColor();
            i = i + id*attenuationFactor + is*attenuationFactor;
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

