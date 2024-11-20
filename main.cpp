//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
//#include <CGAL/Constrained_Delaunay_triangulation_2.h>
//#include <CGAL/mark_domain_in_triangulation.h>
//#include <CGAL/Polygon_2.h>
//#include <CGAL/draw_triangulation_2.h>
//#include "CGAL-6.0.1/examples/Triangulation_2/polygon_triangulation_graphics_scene_options.h"

#include <iostream>
#include <CGAL/Exact_rational.h>
//#include <unordered_map>

//#include <boost/property_map/property_map.hpp>

// Mine
#include "Algorithm1.h"


//typedef Kernel::Point_2 Point_2;
//typedef Kernel::Segment_2 Segment_2;


int main( )
{
    //construct two non-intersecting nested polygons
//    Polygon polygon1;
//    polygon1.push_back(Point_2(0, 0));
//    polygon1.push_back(Point_2(2, 0));
//    polygon1.push_back(Point_2(2, 2));
//    polygon1.push_back(Point(1, 1.75));
//    polygon1.push_back(Point(0, 2));
//    Polygon polygon2;
//    polygon2.push_back(Point(0.5, 0.5));
//    polygon2.push_back(Point(1.5, 0.5));
//    polygon2.push_back(Point(1.5, 1.5));
//    polygon2.push_back(Point(0.5, 1.5));

    algorithm1();

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
    int count = -1;
    std::cout << "There are " << count << " faces in the domain." << std::endl;

//    Polygon_triangulation_gs_options<CDT> gso(in_domain);
//    CGAL::draw(polygon1);
    return 0;
}
