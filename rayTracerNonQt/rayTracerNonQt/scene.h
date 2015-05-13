#ifndef SCENE_H
#define SCENE_H

#include <list>
#include "camera.h"
#include "drawableobject.h"
#include "image.h"
#include "light.h"
#include "yaml/yaml.h"

class Scene
{
public:
    Scene();

    bool readScene(const std::string& inputFilename);
    bool renderScene(const std::string& outputFilename);

    Camera parseEye(const YAML::Node& node);
    DrawableObject* parseObject(const YAML::Node& node);
    Light* parseLight(const YAML::Node& node);

    int getNumObjects();

    void addObject(DrawableObject *obj);
    void addLight(Light *light);

    std::list<DrawableObject *> getObjects() const;
    void setObjects(const std::list<DrawableObject *> &value);

    std::list<Light *> getLights() const;
    void setLights(const std::list<Light *> &value);

    Camera getEye() const;
    void setEye(const Camera &value);

    Material parseMaterial(const YAML::Node &materialNode);

    bool isNormalColoring() const;
    void setNormalColoring(bool value);

    //debug purposes
    std::string toString() const;

private:
    bool renderImage(Image& img);

    std::list<DrawableObject *> objects;
    std::list<Light *> lights;
    Camera eye;

    bool normalColoring;
    const bool normalize;   //define method to normalize (normalization or clamping)
};

#endif // SCENE_H
