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

    int i = 0;
    for (; i < A.number_of_vertices() + 2; i++){
        p = e->target()->point();
        std :: cout << "Greedy step now at p: " << p << " for edge: " << e->source()->point() << " -> " << e->target()->point() << std::endl;

        Polygon_2 VP = arrangement_to_polygon(computeVisibilityArrangement(A, p, e));
        if (FPS.do_intersect(VP)) {
            FPS.intersection(VP);
        }
        else { break; }

        drawArrangements(A, polygon_set_to_arrangement(FPS));

        e++;
    }

    // If greedyStep can traverse the entire polygon boundary then it is trivially solved by one guard
    if (i == A.number_of_vertices() + 2){
        std :: cout << "Trivially solved by one guard << std::endl";
        throw std::invalid_argument("");
        }

    // compute feasible region for each corner of FPS and check which vertex is furthest on edge 'e'
    Point pBest = p;
    // loop over vertices of FPS
        // compute visibility polygon for each vertex
            // loop over vertices of visibility polygon
                // check if vertex is on edge 'e'
                    // if yes, check if vertex is further than pBest
                        // if yes, update pBest





    return std::make_tuple(p, e);
}

