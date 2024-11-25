#ifndef CONTIGUOUSARTGALLERY_ALGORITHM2_H
#define CONTIGUOUSARTGALLERY_ALGORITHM2_H

#include "Helper.h"



// Geometric primitives
typedef Arrangement_2::Ccb_halfedge_const_circulator        Halfedge_circulator;



std::tuple<Point, Halfedge_circulator> greedyStep(Arrangement_2 A, Halfedge_circulator e, Point p);

Arrangement_2 computeVisibilityArrangement(const Arrangement_2& A, const Point& p, Halfedge_circulator e);


#endif //CONTIGUOUSARTGALLERY_ALGORITHM2_H
