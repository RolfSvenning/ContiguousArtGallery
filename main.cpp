//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
//#include <CGAL/Constrained_Delaunay_triangulation_2.h>
//#include <CGAL/mark_domain_in_triangulation.h>
//#include <CGAL/Polygon_2.h>
//#include <CGAL/draw_triangulation_2.h>
//#include "CGAL-6.0.1/examples/Triangulation_2/polygon_triangulation_graphics_scene_options.h"

#include <iostream>
#include <CGAL/Exact_rational.h>


// Mine
#include "Algorithm1.h"
#include "Helper.h"



int main( )
{
    long T = 5;

    //create polygon
    std::vector<Point> points = {Point(0,4), Point(0,0), Point(4,4), Point(1,2), Point(1,3), Point(2, 4)};
    std::vector<Segment> segments;
    for (int i = 0; i < points.size(); i++) {
        segments.emplace_back(points[i], points[(i + 1) % points.size()]);
    }

    // TODO: throw exception: if the vertices of the input polygon are not in general position (no three vertices, not necessarily distinct, are collinear)


    Arrangement_2 A;
    CGAL::insert_non_intersecting_curves(A,segments.begin(),segments.end());
    printArrangementEdges(A, "A");

    Polygon_2 P = arrangement_to_polygon(A);

    algorithm1(T, A);

    return 1;
}

