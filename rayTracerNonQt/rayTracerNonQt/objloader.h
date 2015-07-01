#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <utility>
#include "point3d.h"
#include "vector3d.h"

bool loadOBJ(
	const char * path, 
    std::vector<Point3D> & out_vertices,
    std::vector<std::pair<float, float> > & out_uvs,
    std::vector<Vector3D> & out_normals
);

#endif
