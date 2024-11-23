#ifndef CONTIGUOUSARTGALLERY_HELPER_H
#define CONTIGUOUSARTGALLERY_HELPER_H

#include <CGAL/draw_arrangement_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_segment_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel   Kernel;
typedef CGAL::Arr_segment_traits_2<Kernel>                  Traits;               // trait: arrangement of segments
typedef CGAL::Arrangement_2<Traits>                         Polygon;              // 2d arrangement
typedef Polygon::Edge_const_iterator                        Edge_iterator;

void printPolygonEdges(const Polygon& P, const std::string& name);

#endif //CONTIGUOUSARTGALLERY_HELPER_H
