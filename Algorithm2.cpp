#include "Algorithm2.h"


#include <CGAL/Simple_polygon_visibility_2.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <CGAL/Arr_naive_point_location.h>

// CGAL typedefs
typedef CGAL::Simple_polygon_visibility_2<Polygon, CGAL::Tag_false>   VP_type;     // Visibility polygon class



void printPolygonVertices(const Polygon& P, const std::string& name) {
    std::cout << name << " vertices:" << std::endl;
    for (auto vit = P.vertices_begin(); vit != P.vertices_end(); ++vit)
        std::cout << " (" << vit->point() << ") ";
    std::cout << std::endl;
}


Polygon computeVisibilityPolygon(const Polygon & P, const Point& p, Edge_iterator e) {
    printPolygonVertices(P, "P");

    // Compute the visibility polygon
    Polygon VP;
    VP_type VP_calculator(P);

    // Locate the query point `p`
    Point q = Point(1, 1);
    Polygon::Face_const_handle * face;
    CGAL::Arr_naive_point_location<Polygon> locator(P);
    auto location = locator.locate(q);
    face = std::get_if<Polygon::Face_const_handle>(&location);

    if (!face) {
        throw std::runtime_error("Query point is not inside a valid face.");
    }

    VP_calculator.compute_visibility(q, *face, VP); // two implementations for in / on half-edge

    printPolygonVertices(VP, "VP");

    return VP;
}




std::tuple<Point, Edge_iterator> greedyStep(Polygon P, Edge_iterator e, Point p){
    std::cout << "Greedy step now at p: " << p << std::endl;
    std::cout << "p: " << p << std::endl;
    std::cout << "e: " << e->source()->point() << " -> " << e->target()->point() << std::endl;
    std::cout << "pFace is unbounded: " << e->face()->is_unbounded() << std::endl;
    std::cout << "pFace: " << e->face()->outer_ccb()->next()->source()->point() << " -> " << e->face()->outer_ccb()->next()->target()->point() << std::endl;

    // Compute the initial visibility polygon
    Polygon F = computeVisibilityPolygon(P, p, e);

    for (int i = 0; F.number_of_vertices() > 0; i++){
        std::cout << "Polygon P[" << i << "]: " << P.vertices_begin()->point() << std::endl;




        // if i = size of P then break => solved by 1 guard
        if (i == P.number_of_vertices() + 1){
            break;
        }
    }

    return std::make_tuple(p, e);
}

