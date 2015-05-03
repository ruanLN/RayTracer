#include "raytracer.h"

RayTracer::RayTracer(QObject *parent) : QObject(parent)
{

}
QString RayTracer::getInFile() const
{
    return inFile;
}

void RayTracer::setInFile(const QString &value)
{
    inFile = value;
}
QString RayTracer::getOutFile() const
{
    return outFile;
}

void RayTracer::setOutFile(const QString &value)
{
    outFile = value;
}



