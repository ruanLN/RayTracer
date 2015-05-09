//
//  Framework for a raytracer
//  File: light.h
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg.
//
//  Authors:
//    Maarten Everts
//    Jasper van de Gronde
//    Matthew van der Zwan
//
//  This framework is inspired by and uses code of the raytracer framework of 
//  Bert Freudenberg that can be found at
//  http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html 
//

#ifndef RAY_H_
#define RAY_H_

#include "triple.h"

class Ray
{
public:
    Point O;
    Vector D;

    Ray(const Point &from, const Vector &dir)
        : O(from), D(dir)
    { }

    Point at(double t) const
    { return O + t*D; }

};

#endif /* end of include guard: RAY_H_ */
