#ifndef CONTIGUOUSARTGALLERY_ALGORITHM2_H
#define CONTIGUOUSARTGALLERY_ALGORITHM2_H

#include "Helper.h"



// Geometric primitives
typedef Kernel::Point_2                                     Point;
typedef Kernel::Segment_2                                   Segment;
typedef Polygon::Ccb_halfedge_const_circulator              Halfedge_circulator;



std::tuple<Point, Halfedge_circulator> greedyStep(Polygon P, Halfedge_circulator e, Point p);

Polygon computeVisibilityPolygon(const Polygon& P, const Point& p, Halfedge_circulator e);


#endif //CONTIGUOUSARTGALLERY_ALGORITHM2_H
