#include "scene.h"
#include "sphere.h"
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

Scene::Scene()
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
    Color color;
    materialNode["color"] >> color;
    double ka, kd, ks, exp;
    materialNode["ka"] >> ka;
    materialNode["kd"] >> kd;
    materialNode["ks"] >> ks;
    materialNode["exp"] >> exp;
    objMaterial.setMaterialColor(color);
    objMaterial.setAmbientComponent(ka);
    objMaterial.setDiffuseComponent(kd);
    objMaterial.setSpecularComponent(ks);
    objMaterial.setSpecularExponent(exp);
    return objMaterial;
}

std::string Scene::toString() const
{
    std::ostringstream ss;
    ss << "Scene: " << std::endl;
    ss << "\t" << "Camera: " << this->eye.toString() << std::endl;
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
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            img.setPixel(i, j, Color(0, 0, 0));
        }
    }

    //define the center point of the image:
    int w = img.getWidth();
    int h = img.getHeight();
    Point3D imgCenter = eye.getPosition() + eye.getEyeVector().scalarProduct(sqrt(w * h)*1.5);

    //define movement vectors
    Vector3D leftVector = eye.getUpVector().crossProduct(eye.getEyeVector());
    Vector3D rightVector = leftVector.scalarProduct(-1);
    Vector3D upVector = eye.getUpVector();
    Vector3D downVector = upVector.scalarProduct(-1);

    //define initial point of raycasting
    Vector3D tmp1 = upVector.scalarProduct(h/2);
    Vector3D tmp2 = leftVector.scalarProduct(w/2);
    Point3D imgTopLeft = imgCenter + tmp1 + tmp2;   // por algum motivo tretoso, não funcionou sem os tmp;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            //Point3D pixel(x+0.5 - w/2, h-1-y+0.5 - h/2, 0);
            tmp1 = rightVector.scalarProduct(x);
            tmp2 = downVector.scalarProduct(y);
            Point3D pixel = imgTopLeft + tmp1 + tmp2;
            Vector3D dir = pixel - eye.getPosition();
            dir.normalize();
            Ray ray;
            ray.setOrigin(eye.getPosition());
            ray.setDirection(dir);
            std::list<DrawableObject*>::iterator it;
            Color col;// = trace(ray);
            double zBuffer = -1;
            for(it = objects.begin(); it != objects.end(); it++) {
                bool success;
                Intersection intersec = (*it)->hitTest(ray, &success);
                if(success) {
                    //Point3D intersecPoint = intersec.getIntersectionPoint();
                    if(zBuffer > (intersec.getIntersectionPoint() - eye.getPosition()).norm() || zBuffer == -1) {
                        col = (*it)->getPointColor(intersec);
                        zBuffer = (intersec.getIntersectionPoint() - eye.getPosition()).norm();
                    }
                }
            }
            col.clamp();
            img.setPixel(x, y, col);
        }
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
    if(obj) {
        Material objMaterial = parseMaterial(node["material"]);
        obj->setObjectMaterial(objMaterial);
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




