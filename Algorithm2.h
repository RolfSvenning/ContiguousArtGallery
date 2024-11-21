#ifndef CONTIGUOUSARTGALLERY_ALGORITHM2_H
#define CONTIGUOUSARTGALLERY_ALGORITHM2_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_segment_traits_2.h>

// Geometric primitives
typedef CGAL::Exact_predicates_exact_constructions_kernel   Kernel;
typedef Kernel::Point_2                                     Point;
typedef Kernel::Segment_2                                   Segment;
typedef CGAL::Arr_segment_traits_2<Kernel>                  Traits;               // trait: arrangement of segments
typedef CGAL::Arrangement_2<Traits>                         Polygon;              // 2d arrangement
typedef Polygon::Edge_const_iterator                        Edge_iterator;
typedef Polygon::Face_const_handle                          Face_handle;


std::tuple<Point, Edge_iterator> greedyStep(Polygon P, Edge_iterator e, Point p);

Polygon computeVisibilityPolygon(const Polygon& P, const Point& p, Edge_iterator e);


#endif //CONTIGUOUSARTGALLERY_ALGORITHM2_H
