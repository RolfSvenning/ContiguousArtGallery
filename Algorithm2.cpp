#include "Algorithm2.h"

#include <CGAL/Triangular_expansion_visibility_2.h>
#include <CGAL/Simple_polygon_visibility_2.h>
#include <tuple>
#include <iostream>
#include <CGAL/Arr_naive_point_location.h>
#include <CGAL/draw_arrangement_2.h>
#include <sstream> // for better printing
#include <CGAL/Boolean_set_operations_2.h> // for intersection

// CGAL typedefs
typedef CGAL::Triangular_expansion_visibility_2<Arrangement_2>  VA_type;    // Visibility polygon class

void validatePointOnEdge(const Point& p, Halfedge_circulator e) {
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

    // Check if point p is within the segment bounds
    if (!(CGAL::compare(CGAL::min(source.x(), target.x()), p.x()) != CGAL::LARGER &&
          CGAL::compare(CGAL::max(source.x(), target.x()), p.x()) != CGAL::SMALLER &&
          CGAL::compare(CGAL::min(source.y(), target.y()), p.y()) != CGAL::LARGER &&
          CGAL::compare(CGAL::max(source.y(), target.y()), p.y()) != CGAL::SMALLER)) {
        std::ostringstream oss;
        oss << "Point p (" << p << ") is collinear but not within the segment bounds of edge e with endpoints ("
            << source << ") -> (" << target << ").";
        throw std::invalid_argument(oss.str());
    }
}

void drawArrangements(const Arrangement_2& A1, const Arrangement_2& A2) {
    Arrangement_2 A_merged;
    // Insert edges from the first arrangement
    for (auto edge = A1.edges_begin(); edge != A1.edges_end(); ++edge) {
        A_merged.insert_in_face_interior(Segment(edge->source()->point(), edge->target()->point()), A_merged.unbounded_face());
    }

    // Insert edges from the second arrangement
    for (auto edge = A2.edges_begin(); edge != A2.edges_end(); ++edge) {
        A_merged.insert_in_face_interior(Segment(edge->source()->point(), edge->target()->point()), A_merged.unbounded_face());
    }
    CGAL::draw(A_merged);
}

Arrangement_2 computeVisibilityArrangement(const Arrangement_2 & A, const Point& p, Halfedge_circulator e) {
    // Assert point p on edge e or throw error
    validatePointOnEdge(p, e);

    // Compute the visibility polygon
    Arrangement_2 VA;
    VA_type VP_calculator(A);
    VP_calculator.compute_visibility(p, e, VA);

    printArrangementEdges(VA, "VP ");

    return VA;
}

std::tuple<Point, Halfedge_circulator> greedyStep(Arrangement_2 A, Halfedge_circulator e, Point p){
    printArrangementEdges(A, "A");
    std::cout << "Greedy step from p: " << p << std::endl;
    std::cout << "e: " << e->source()->point() << " -> " << e->target()->point() << std::endl;

    // Compute the initial feasible polygon set
    Arrangement_2 F = computeVisibilityArrangement(A, p, e);
    drawArrangements(A, F);
    Polygon_set_2 FPS;
    FPS.insert(arrangement_to_polygon(F));

    if (p == e->target()->point()){ // if p is in the middle of e then don't move to the next edge
        e++;
    }

    for (int i = 0; A.number_of_vertices() > 0; i++){
        p = e->target()->point();
        std :: cout << "Greedy step now at p: " << p << " for edge: " << e->source()->point() << " -> " << e->target()->point() << std::endl;
        Arrangement_2 VA = computeVisibilityArrangement(A, p, e);
        // intersect F and VA
//        if (not CGAL::do_intersect(F, VA)){
//            std::cout << "Intersection detected" << std::endl;
//            drawArrangements(F, VA);
//        }
        FPS.intersection(arrangement_to_polygon(VA));
        drawArrangements(A, polygon_set_to_arrangement(FPS));


//        CGAL::intersection(F, VA);
//        drawArrangements(A, VA);
        e++;

        // if i = size of A then break => solved by 1 guard
        if (i == A.number_of_vertices() + 1){
            std :: cout << "Solved by 1 guard" << std::endl;
            throw std::invalid_argument("");
        }
    }

    return std::make_tuple(p, e);
}

