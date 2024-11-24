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
    long T = 1;
//
    //create polygon
    std::vector<Point> points = {Point(0,4), Point(0,0), Point(3,2), Point(4,0), Point(4,4), Point(1,2)};
    std::vector<Segment> segments;
    for (int i = 0; i < points.size(); i++) {
        segments.emplace_back(points[i], points[(i + 1) % points.size()]);
    }

    Polygon P;
    CGAL::insert_non_intersecting_curves(P,segments.begin(),segments.end());
    printPolygonEdges(P, "P");

    algorithm1(T, P);

    return 1;
}


//    //Insert the polygons into a constrained triangulation
//    CDT cdt;
//    cdt.insert_constraint(polygon1.vertices_begin(), polygon1.vertices_end(), true);
//    cdt.insert_constraint(polygon2.vertices_begin(), polygon2.vertices_end(), true);
//    cdt.insert_constraint(Point3(0.25, 0.25), Point3(0.25, 1.75));
//
//    std::unordered_map<Face_handle, bool> in_domain_map;
//    boost::associative_property_map< std::unordered_map<Face_handle,bool> >
//            in_domain(in_domain_map);
//
//    //Mark facets that are inside the domain bounded by the polygon
//    CGAL::mark_domain_in_triangulation(cdt, in_domain);
//
//    unsigned int count=0;
//    for (Face_handle f : cdt.finite_face_handles())
//    {
//        if ( get(in_domain, f) ) ++count;
//    }
//    Polygon_triangulation_gs_options<CDT> gso(in_domain);
//    CGAL::draw(polygon1);