#include "drawableobject.h"
#include "scene.h"
#include "sphere.h"
#include <cmath>

DrawableObject::DrawableObject() :
    hasTexture(false)
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
            Color id = hasTexture? mapTexture(intersection.getIntersectionPoint()) : objectMaterial.getDiffuseMaterialColor();
            id = id * objectMaterial.getDiffuseComponent();
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
            //double naturalColorReduction = 1 - (combineReflectedLight ? objectMaterial.getReflectionComponent() : 0) - (combineTransmitedLight ? objectMaterial.getTransmissionComponent() : 0);
            is = is * specularLightFactor * actualLight.getColor();
            i = (i + id*attenuationFactor + is*attenuationFactor);
            //i = i*(naturalColorReduction) + (combineReflectedLight?reflectedColor*objectMaterial.getReflectionComponent() : Color()) + (combineTransmitedLight? refratedColor*objectMaterial.getTransmissionComponent(): Color());
        }
        //i = i + reflectedColor;
    }
    Color reflectedColor, refratedColor;
    bool combineReflectedLight = false;
    bool combineTransmitedLight = false;
    if(depth < parentScene->getReflectionLevel()) {
        //Vector3D V = parentScene->getEye().getPosition() - intersection.getIntersectionPoint();
        Vector3D V = intersection.getCauseRay().getOrigin() - intersection.getIntersectionPoint();
        V.normalize();
        Vector3D reflectedVec;// = V - intersection.getNormalVector().scalarProduct(2).scalarProduct(intersection.getNormalVector().dotProduct(V));
        reflectedVec = intersection.getNormalVector().scalarProduct(2);
        double NL = intersection.getNormalVector().dotProduct(V);
        reflectedVec = reflectedVec.scalarProduct(NL);
        reflectedVec = reflectedVec - V;
        reflectedVec.normalize();
        int zBuffer = -1;
        double highestComponentColor = 1;
        Intersection reflectedIntersection;
        bool reflectionIntersectedSomething;
        Ray reflectedRay;
        reflectedRay.setDirection(reflectedVec);
        reflectedRay.setOrigin(intersection.getIntersectionPoint());

        for(itObj = objects.begin(); itObj != objects.end(); itObj++) {
            if((*itObj) == this) {
                continue;
            }
            reflectedIntersection = (*itObj)->hitTest(reflectedRay, &reflectionIntersectedSomething);
            if(reflectionIntersectedSomething) {
                //Point3D intersecPoint = intersec.getIntersectionPoint();
                if(zBuffer > (reflectedIntersection.getIntersectionPoint() - reflectedRay.getOrigin()).norm() || zBuffer == -1) {
                    if(reflectedIntersection.getT() < 0) {
                        continue;
                    }
                    combineReflectedLight = true;
                    reflectedColor = (*itObj)->getPointColor(reflectedIntersection, depth+1);
                    if(reflectedColor.getHighestComponent() > highestComponentColor) {
                        highestComponentColor = reflectedColor.getHighestComponent();
                    }
                    zBuffer = (reflectedIntersection.getIntersectionPoint() - reflectedRay.getOrigin()).norm();
                }
            }
        }
        //reflectedColor.clamp();
        //reflectedColor.normalize(highestComponentColor);
    }
    if(depth < parentScene->getRefractionLevel()) {

    }
    if(combineReflectedLight) {
        i = i + reflectedColor * this->objectMaterial.getSpecularComponent();
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
Image DrawableObject::getTexture() const
{
    return texture;
}

void DrawableObject::setTexture(const Image &value)
{
    hasTexture = true;
    texture = value;
}


