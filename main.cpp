//#include <CGAL/Constrained_Delaunay_triangulation_2.h>
//#include <CGAL/mark_domain_in_triangulation.h>
//#include <CGAL/Polygon_2.h>
//#include <CGAL/draw_triangulation_2.h>
//#include "CGAL-6.0.1/examples/Triangulation_2/polygon_triangulation_graphics_scene_options.h"

#include <iostream>
#include <CGAL/Exact_rational.h>

// Mine
#include "Algorithm2.h"
#include "Algorithm1.h"
#include "Helper.h"



void test() {
    Segment s1 = Segment(Point(2,2), Point(3,3));
    Segment s2 = Segment(Point(0,0), Point(1,1));

    std::cout << "intersecting..." << std::endl;
    const auto Ps = CGAL::intersection(s1, s2);
    std::cout << "done" << std::endl;

    if (Ps) {
        if (const Segment* s = std::get_if<Segment>(&*Ps)) {
            std::cout << "Segment: " << s->source() << ", " << s->target() << std::endl;
        } else {
            const Point* p = std::get_if<Point >(&*Ps);
            std::cout << "Point: " << *p << std::endl;
        }
    }
}


int main()
{


    long T = 10;

    //create polygon
    std::vector<Point> points = {Point(0,0), Point(5,-1), Point(4,0), Point(8,-2), Point(8,2), Point(4, 1), Point(6, 4),
                                 Point(10, 2), Point(8, 8), Point(4, 8), Point(6, 10), Point(0, 10), Point(0, 6), Point(8, 6)};
    std::vector<Segment> segments;
    for (int i = 0; i < points.size(); i++) {
        segments.emplace_back(points[i], points[(i + 1) % points.size()]);
    }

    // TODO: throw exception: if the vertices of the input polygon are not in general position (no three vertices, not necessarily distinct, are collinear)


    Arrangement_2 A;
    CGAL::insert_non_intersecting_curves(A,segments.begin(),segments.end());
    printArrangementEdges(A, "A");

    Polygon_2 P = arrangement_to_polygon(A);

//    test();
    algorithm1(T, A);

    return 1;
}

