#include "scene.h"
#include "sphere.h"
#include "triangle.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>

void operator >> (const YAML::Node& node, Point3D& t);
void operator >> (const YAML::Node& node, Vector3D& t);
void operator >> (const YAML::Node& node, Color& t);
//Triple parseTriple(const YAML::Node& node);

void operator >> (const YAML::Node& node, Point3D &t)
{
    assert(node.size()==3);
    double x,y,z;
    node[0] >> x;
    node[1] >> y;
    node[2] >> z;
    t.setX(x);
    t.setY(y);
    t.setZ(z);
}

void operator >> (const YAML::Node& node, Vector3D &t)
{
    assert(node.size()==3);
    double x,y,z;
    node[0] >> x;
    node[1] >> y;
    node[2] >> z;
    t.setX(x);
    t.setY(y);
    t.setZ(z);
}

void operator >> (const YAML::Node& node, Color &t)
{
    assert(node.size()==3);
    double x,y,z;
    node[0] >> x;
    node[1] >> y;
    node[2] >> z;
    t.setR(x);
    t.setG(y);
    t.setB(z);
}

Scene::Scene() :
    refractionLevel(0),
    reflectionLevel(0),
    shadows(true),
    normalColoring(false),
    normalize(false)
{

}

bool Scene::readScene(const std::string &inputFilename)
{
    // Open file stream for reading and have the YAML module parse it
     std::ifstream fin(inputFilename.c_str());
     if (!fin) {
         std::cerr << "Error: unable to open " << inputFilename << " for reading." << std::endl;
         return false;
     }
     try {
         YAML::Parser parser(fin);
         if (parser) {
             YAML::Node doc;
             parser.GetNextDocument(doc);

             // Read scene configuration options
             this->setEye(parseEye(doc["Eye"]));
             try {
                 this->setRefractionLevel(doc["RefractionLevel"]);
             }
             catch (YAML::TypedKeyNotFound<std::string> e) {
                 std::cout << e.what() << std::endl;
             }
             try {
                 this->setReflectionLevel(doc["ReflectionLevel"]);
             }
             catch (YAML::TypedKeyNotFound<std::string> e) {
                 std::cout << e.what() << std::endl;
             }
             try {
                 this->setShadows(doc["Shadows"]);
             }
             catch (YAML::TypedKeyNotFound<std::string> e) {
                 std::cout << e.what() << std::endl;
             }
             try {
                 std::string shadingType;
                 doc["shadingType"] >> shadingType;
                 if(shadingType == "normal") {
                     this->setNormalColoring(true);
                 } else if(shadingType == "z") {

                 } else if(shadingType == "phong"){

                 } else {
                     std::cout << "shading type não reconhecido, usando phong" << std::endl;
                 }
             }
             catch (YAML::TypedKeyNotFound<std::string> e) {
                 std::cout << e.what() << std::endl;
             }

             // Read and parse the scene objects
             const YAML::Node& sceneObjects = doc["Objects"];
             if (sceneObjects.GetType() != YAML::CT_SEQUENCE) {
                 std::cerr << "Error: expected a sequence of objects." << std::endl;
                 return false;
             }
             for(YAML::Iterator it=sceneObjects.begin();it!=sceneObjects.end();++it) {
                 DrawableObject *obj = parseObject(*it);
                 // Only add object if it is recognized
                 if (obj) {
                     obj->setParentScene(this);
                     this->addObject(obj);
                 } else {
                     std::cerr << "Warning: found object of unknown type, ignored." << std::endl;
                 }
             }

             // Read and parse light definitions
             const YAML::Node& sceneLights = doc["Lights"];
             if (sceneObjects.GetType() != YAML::CT_SEQUENCE) {
                 std::cerr << "Error: expected a sequence of lights." << std::endl;
                 return false;
             }
             for(YAML::Iterator it=sceneLights.begin();it!=sceneLights.end();++it) {
                 this->addLight(parseLight(*it));
             }
         }
         if (parser) {
             std::cerr << "Warning: unexpected YAML document, ignored." << std::endl;
         }
     } catch(YAML::ParserException& e) {
         std::cerr << "Error at line " << e.mark.line + 1 << ", col " << e.mark.column + 1 << ": " << e.msg << std::endl;
         return false;
     }

     std::cout << "YAML parsing results: " << this->getNumObjects() << " objects read." << std::endl;

     return true;
}

bool Scene::renderScene(const std::string &outputFilename)
{
    Image img(this->eye.getRenderedImageHeight(), this->eye.getRenderedImageWidth());

    this->renderImage(img);

    img.writeImage(outputFilename);
}

Camera Scene::parseEye(const YAML::Node &node)
{
    Camera cam;
    Point3D position;
    node["position"] >> position;
    Vector3D up, eye;
    node["upVector"] >> up;
    node["eyeVector"] >> eye;
    int h, w;
    node["imageWidth"] >> w;
    node["imageHeight"] >> h;
    int zNear;
    try {
        node["z-near"] >> zNear;
        cam.setZNear(zNear);
    } catch (YAML::TypedKeyNotFound<std::string> e) {
        std::cout << "Z-near not found; using 512." << std::endl;
    }
    int ssf;
    try {
        node["superSamplingLevel"] >> ssf;
        cam.setSuperSamplingFactor(ssf);
    } catch (YAML::TypedKeyNotFound<std::string> e) {
        std::cout << "Supersampling level not found; using 1." << std::endl;
    }

    cam.setPosition(position);
    cam.setEyeVector(eye);
    cam.setUpVector(up);
    cam.setRenderedImageWidth(w);
    cam.setRenderedImageHeight(h);
    return cam;
}

Material Scene::parseMaterial(const YAML::Node& materialNode)
{
    Material objMaterial;
    Color diffuseColor, specularColor, ambientColor;

    materialNode["diffuseColor"] >> diffuseColor;
    objMaterial.setDiffuseMaterialColor(diffuseColor);
    try {
        materialNode["specularColor"] >> specularColor;
        objMaterial.setSpecularMaterialColor(specularColor);
    }
    catch (YAML::TypedKeyNotFound<std::string> e) {
        //materialNode["diffuseColor"] >> specularColor;
        specularColor.setR(1);
        specularColor.setG(1);
        specularColor.setB(1);
        objMaterial.setSpecularMaterialColor(specularColor);
        std::cout << "Object specular color not found; using white." << std::endl;
    }
    try {
        materialNode["ambientColor"] >> ambientColor;
        objMaterial.setAmbientMaterialColor(ambientColor);
    }
    catch (YAML::TypedKeyNotFound<std::string> e) {
        materialNode["diffuseColor"] >> ambientColor;
        objMaterial.setAmbientMaterialColor(ambientColor);
        std::cout << "Object ambient color not found; using diffuse." << std::endl;
    }
    double ka, kd, ks, exp;
    materialNode["ka"] >> ka;
    materialNode["kd"] >> kd;
    materialNode["ks"] >> ks;
    materialNode["exp"] >> exp;
    objMaterial.setAmbientComponent(ka);
    objMaterial.setDiffuseComponent(kd);
    objMaterial.setSpecularComponent(ks);
    objMaterial.setSpecularExponent(exp);

    double kgr, kgt;
    try {
        materialNode["kgr"] >> kgr;
        objMaterial.setReflectionComponent(kgr);
    }
    catch (YAML::TypedKeyNotFound<std::string> e) {
        std::cout << "Object reflection component not found; using 1." << std::endl;
    }
    try {
        materialNode["kgt"] >> kgt;
        objMaterial.setTransmissionComponent(kgt);
    }
    catch (YAML::TypedKeyNotFound<std::string> e) {
        std::cout << "Object transmission component not found; using 1." << std::endl;
    }

    return objMaterial;
}

std::string Scene::toString() const
{
    std::ostringstream ss;
    ss << "Scene: " << std::endl;
    ss << "\t" << "Camera: " << this->eye.toString() << std::endl;
    ss << "\t" << "Refraction level: " << this->refractionLevel << std::endl;
    ss << "\t" << "Reflection level: " << this->reflectionLevel << std::endl;
    ss << "\t" << "Shadows: " << std::boolalpha << this->shadows << std::endl;
    ss << "\t" << "Normal coloring: " << std::boolalpha << this->normalColoring << std::endl;
    ss << "\t" << "Lights: " << std::endl;
    std::list<Light*>::const_iterator it;
    for(it = lights.begin(); it != lights.end(); it++) {
        ss << "\t\t" << (*it)->toString() << std::endl;
    }
    ss << "\t" << "Objects: " << std::endl;
    std::list<DrawableObject*>::const_iterator it2;
    for(it2 = objects.begin(); it2 != objects.end(); it2++) {
        ss << "\t\t" << (*it2)->toString() << std::endl;
    }
    std::string stringScene = ss.str();
    return stringScene;
}

bool Scene::renderImage(Image &img)
{
    int w = img.getWidth();
    int h = img.getHeight();
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            img.setPixel(i, j, Color(0, 0, 0));
        }
    }

    //define the center point of the image:
    Point3D imgCenter = eye.getPosition() + eye.getEyeVector().scalarProduct(eye.getZNear());

    //define movement vectors
    Vector3D leftVector = eye.getUpVector().crossProduct(eye.getEyeVector());
    Vector3D rightVector = leftVector.scalarProduct(-1);
    Vector3D upVector = eye.getUpVector();
    Vector3D downVector = upVector.scalarProduct(-1);

    //define initial point of raycasting
    Vector3D tmp1 = upVector.scalarProduct(h/2);
    Vector3D tmp2 = leftVector.scalarProduct(w/2);
    Point3D imgTopLeft = imgCenter + tmp1 + tmp2;   // por algum motivo tretoso, não funcionou sem os tmp;
    double highestComponentColor = 1;
    double step = 1.0 / (eye.getSuperSamplingFactor() + 1);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            Color col;
            for(int z = 1; z <= eye.getSuperSamplingFactor(); z++) {
                for(int w = 1; w <= eye.getSuperSamplingFactor(); w++) {
                    tmp1 = downVector.scalarProduct(x + step*z);
                    tmp2 = rightVector.scalarProduct(y + step*w);
                    Point3D pixel = imgTopLeft + tmp1 + tmp2;
                    Vector3D dir = pixel - eye.getPosition();
                    dir.normalize();
                    Ray ray;
                    ray.setOrigin(eye.getPosition());
                    ray.setDirection(dir);
                    std::list<DrawableObject*>::iterator it;
                    Color colLocal;// = trace(ray);
                    double zBuffer = -1;
                    for(it = objects.begin(); it != objects.end(); it++) {
                        bool success;
                        Intersection intersec = (*it)->hitTest(ray, &success);
                        if(success) {
                            //Point3D intersecPoint = intersec.getIntersectionPoint();
                            if(zBuffer > (intersec.getIntersectionPoint() - eye.getPosition()).norm() || zBuffer == -1) {
                                colLocal = (*it)->getPointColor(intersec);
                                if(colLocal.getHighestComponent() > highestComponentColor) {
                                    highestComponentColor = colLocal.getHighestComponent();
                                }
                                zBuffer = (intersec.getIntersectionPoint() - eye.getPosition()).norm();
                            }
                        }
                    }
                    col = col + colLocal;
                }
            }
            col = col * (1.0/(eye.getSuperSamplingFactor()*eye.getSuperSamplingFactor()));
            if(!normalize){
                col.clamp();
            }
            img.setPixel(x, y, col);
        }
    }
    if(normalize) {
        img.normalizeImageColor(highestComponentColor);
    }
    return true;
}

DrawableObject *Scene::parseObject(const YAML::Node &node)
{
    DrawableObject *obj = NULL;
    std::string objectType;
    node["type"] >> objectType;
    //like a switch
    if(objectType == "sphere") {
        obj = new Sphere();
        Point3D position;
        node["position"] >> position;
        double radius;
        node["radius"] >> radius;
        ((Sphere*)obj)->setCenter(position);
        ((Sphere*)obj)->setRadius(radius);
    }
    if(objectType == "triangle") {
        obj = new Triangle();
        Point3D vertex1, vertex2, vertex3;
        node["vertex1"] >> vertex1;
        node["vertex2"] >> vertex2;
        node["vertex3"] >> vertex3;
        ((Triangle*)obj)->setV1(vertex1);
        ((Triangle*)obj)->setV2(vertex2);
        ((Triangle*)obj)->setV3(vertex3);
    }
    if(objectType == "model") {
        //obj = new Triangle();
        //Point3D vertex1, vertex2, vertex3;
        //node["vertex1"] >> vertex1;
        //node["vertex2"] >> vertex2;
        //node["vertex3"] >> vertex3;
        //((Triangle*)obj)->setV1(vertex1);
        //((Triangle*)obj)->setV2(vertex2);
        //((Triangle*)obj)->setV3(vertex3);
    }
    if(obj) {
        Material objMaterial = parseMaterial(node["material"]);
        obj->setObjectMaterial(objMaterial);

        try {
            std::string textureFile;
            node["texture"] >> textureFile;
            Image objTexture;
            objTexture.readImage(node["texture"]);
            obj->setTexture(objTexture);
        } catch (YAML::TypedKeyNotFound<std::string> e) {
            std::cout << "No texture, using material" << std::endl;
        }
    }
    return obj;
}

Light *Scene::parseLight(const YAML::Node &node)
{
    Light *light = new Light();
    Point3D position;
    node["position"] >> position;
    Color color;
    node["color"] >> color;
    light->setPosition(position);
    light->setColor(color);
    double linearAttenuation, quadraticAttenuation;
    try {
        node["linearAttenuation"] >> linearAttenuation;
        light->setLinearAtt(linearAttenuation);
    }
    catch (YAML::TypedKeyNotFound<std::string> e) {
        std::cout << "Light linear attenuation factor not found; using 0." << std::endl;
    }
    try {
        node["quadraticAttenuation"] >> quadraticAttenuation;
        light->setQuadraticAtt(quadraticAttenuation);
    }
    catch (YAML::TypedKeyNotFound<std::string> e) {
        std::cout << "Light quadratic attenuation factor not found; using 0." << std::endl;
    }

    return light;
}

int Scene::getNumObjects()
{
    return this->objects.size();
}

void Scene::addObject(DrawableObject *obj)
{
    if(obj) {   //if non-null, for safety
        this->objects.push_back(obj);
    }
}

void Scene::addLight(Light *light)
{
    if(light) {
        this->lights.push_back(light);
    }
}

std::list<DrawableObject *> Scene::getObjects() const
{
    return objects;
}

void Scene::setObjects(const std::list<DrawableObject *> &value)
{
    objects = value;
}

std::list<Light *> Scene::getLights() const
{
    return lights;
}

void Scene::setLights(const std::list<Light *> &value)
{
    lights = value;
}

Camera Scene::getEye() const
{
    return eye;
}

void Scene::setEye(const Camera &value)
{
    eye = value;
}

int Scene::getRefractionLevel() const
{
    return refractionLevel;
}

void Scene::setRefractionLevel(int value)
{
    refractionLevel = value;
}

int Scene::getReflectionLevel() const
{
    return reflectionLevel;
}

void Scene::setReflectionLevel(int value)
{
    reflectionLevel = value;
}

bool Scene::areShadows() const
{
    return shadows;
}

void Scene::setShadows(bool value)
{
    shadows = value;
}

bool Scene::isNormalColoring() const
{
    return normalColoring;
}

void Scene::setNormalColoring(bool value)
{
    normalColoring = value;
}




