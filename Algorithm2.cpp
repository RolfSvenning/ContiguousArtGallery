#include "Algorithm2.h"

#include <CGAL/Triangular_expansion_visibility_2.h>
#include <CGAL/Simple_polygon_visibility_2.h>
#include <tuple>
#include <iostream>
#include <CGAL/Arr_naive_point_location.h>
#include <CGAL/draw_arrangement_2.h>
#include <CGAL/enum.h> // For comparison enums (CGAL::SMALLER, etc.)
#include <sstream> // for better printing


// CGAL typedefs
typedef CGAL::Triangular_expansion_visibility_2<Polygon>  VP_type;     // Visibility polygon class
typedef Polygon::Halfedge_const_handle                    Halfedge_const_handle;



void validatePointOnEdge(const Point& p, Edge_iterator e) {
    // Extract endpoints of the edge
    const Point& source = e->source()->point();
    const Point& target = e->target()->point();

    // Allow p to be exactly the source or target of the edge
    if (p == source || p == target) {
        return; // Valid case, no exception
    }

    std::ostringstream oss;
    // Check if p is collinear with the edge
    if (!CGAL::collinear(source, target, p)) {
        throw std::invalid_argument([&]() {
            oss << "Point p (" << p << ") is not collinear with edge e defined by endpoints ("
                << source << ") -> (" << target << ").";
            return oss.str();
        }());
    }

    // Check if p is within the segment bounds
    if (!(CGAL::compare(source.x(), p.x()) != CGAL::LARGER &&
          CGAL::compare(target.x(), p.x()) != CGAL::SMALLER &&
          CGAL::compare(source.y(), p.y()) != CGAL::LARGER &&
          CGAL::compare(target.y(), p.y()) != CGAL::SMALLER)) {
        throw std::invalid_argument([&]() {
            oss << "Point p (" << p << ") is collinear but not within the segment bounds of edge e with endpoints ("
                << source << ") -> (" << target << ").";
            return oss.str();
        }());
    }
}

void drawPolygons(const Polygon& P1, const Polygon& P2) {
    Polygon P_merged;
    // Insert edges from the first arrangement
    for (auto edge = P1.edges_begin(); edge != P1.edges_end(); ++edge) {
        P_merged.insert_in_face_interior(Segment(edge->source()->point(), edge->target()->point()), P_merged.unbounded_face());
    }

    // Insert edges from the second arrangement
    for (auto edge = P2.edges_begin(); edge != P2.edges_end(); ++edge) {
        P_merged.insert_in_face_interior(Segment(edge->source()->point(), edge->target()->point()), P_merged.unbounded_face());
    }
    CGAL::draw(P_merged);
}

Polygon computeVisibilityPolygon(const Polygon & P, const Point& p, Edge_iterator e) {
    // Assert point p on edge e or throw error
    validatePointOnEdge(p, e);

    // Compute the visibility polygon
    Polygon VP;
    VP_type VP_calculator(P);
    VP_calculator.compute_visibility(p, e, VP);

    return VP;
}

std::tuple<Point, Edge_iterator> greedyStep(Polygon P, Edge_iterator e, Point p){
    printPolygonEdges(P, "P");
    std::cout << "Greedy step from p: " << p << std::endl;
    std::cout << "e: " << e->source()->point() << " -> " << e->target()->point() << std::endl;

    // Compute the initial visibility polygon
    Polygon F = computeVisibilityPolygon(P, p, e);
    printPolygonEdges(F, "F");
    drawPolygons(P, F);

    if (p == e->target()->point()){ // if p is in the middle of e then don't move to the next edge
        if (e == P.edges_end()) {
            e = P.edges_begin();
        }
        else {
            e++;
        }
    }

    for (int i = 0; F.number_of_vertices() > 0; i++){
        p = e->target()->point();
        std :: cout << "Greedy step now at p: " << p << " for edge: " << e->source()->point() << " -> " << e->target()->point() << std::endl;
//        Polygon VP = computeVisibilityPolygon(P, p, e);

        // Move to the next edge (or start from beginning if at the end)
        if (e == P.edges_end()) {
            std::cout << "Resetting edge iterator" << std::endl;
            e = P.edges_begin();
        }
        else {
            e++;
        }


        // if i = size of P then break => solved by 1 guard
        if (i == P.number_of_vertices() + 1){
            break;
        }
    }

    return std::make_tuple(p, e);
}
