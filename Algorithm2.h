#ifndef CONTIGUOUSARTGALLERY_ALGORITHM2_H
#define CONTIGUOUSARTGALLERY_ALGORITHM2_H

#include "Helper.h"



// Geometric primitives
typedef Kernel::Point_2                                     Point;
typedef Kernel::Segment_2                                   Segment;

//typedef Polygon::Face_const_handle                          Face_handle;


std::tuple<Point, Edge_iterator> greedyStep(Polygon P, Edge_iterator e, Point p);

Polygon computeVisibilityPolygon(const Polygon& P, const Point& p, Edge_iterator e);


#endif //CONTIGUOUSARTGALLERY_ALGORITHM2_H
