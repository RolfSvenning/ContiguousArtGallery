#ifndef CONTIGUOUSARTGALLERY_HELPER_H
#define CONTIGUOUSARTGALLERY_HELPER_H

#include <CGAL/draw_arrangement_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Polygon_set_2.h>
#include <CGAL/Polygon_with_holes_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel   Kernel;
typedef Kernel::Point_2                                     Point;
typedef Kernel::Segment_2                                   Segment;
typedef CGAL::Arr_segment_traits_2<Kernel>                  Traits;                 // trait: arrangement of segments
typedef CGAL::Arrangement_2<Traits>                         Arrangement_2;          // 2d arrangement
typedef CGAL::Polygon_2<Kernel>                             Polygon_2;
typedef CGAL::Polygon_set_2<Kernel>                         Polygon_set_2;
typedef CGAL::Polygon_with_holes_2<Kernel>                  Polygon_with_holes_2;
typedef Arrangement_2::Ccb_halfedge_const_circulator        Halfedge_circulator;    //traverses half edges around a face or vertex
typedef Arrangement_2::Halfedge_const_handle                Halfedge_const_handle;


void printArrangementEdges(const Arrangement_2& P, const std::string& name);

std::vector<Halfedge_circulator> getEdgesOfArrangement(const Arrangement_2& P);

void drawArrangements(const Arrangement_2& A1, const Arrangement_2& A2);

void validatePointOnEdge(const Point& p, Halfedge_circulator e);

bool pointIsOnEdgeButNotSource(const Point& p, Halfedge_circulator e);

Polygon_2 arrangement_to_polygon(const Arrangement_2& A);

Arrangement_2 polygon_to_arrangement(const Polygon_2& polygon);

Arrangement_2 polygon_set_to_arrangement(const Polygon_set_2& polygon);

#endif //CONTIGUOUSARTGALLERY_HELPER_H
