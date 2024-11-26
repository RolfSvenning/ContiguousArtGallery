#include "Algorithm2.h"

#include <CGAL/Triangular_expansion_visibility_2.h>
#include <CGAL/Simple_polygon_visibility_2.h>
#include <tuple>
#include <iostream>
#include <CGAL/Boolean_set_operations_2.h> // for intersection

// CGAL typedefs
typedef CGAL::Triangular_expansion_visibility_2<Arrangement_2>      VA_type;    // Visibility polygon class
typedef CGAL::Simple_polygon_visibility_2<Arrangement_2, CGAL::Tag_false> VP_type_non_regular_face;
typedef Arrangement_2::Face_const_handle                            Face_const_handle;



Arrangement_2 computeVisibilityArrangementAtEdge(const Arrangement_2 & A, const Point& p, Halfedge_const_handle e) {
    // Assert point p on edge e or throw error
    validatePointOnEdge(p, e);

    // Compute the visibility polygon
    Arrangement_2 VA;
    VA_type VP_calculator(A);
    VP_calculator.compute_visibility(p, e, VA);

    printArrangementEdges(VA, "VP ");

    return VA;
}

Arrangement_2 computeVisibilityArrangementAtFace(const Arrangement_2 & A, const Point& p) {
    // assert point p is inside face f or throw error
    // TODO: implement this

    // Compute the visibility polygon
    Face_const_handle f;
    if (A.edges_begin()->face()->is_unbounded()){
        f = A.edges_begin()->twin()->face();
    }
    else {
        f = A.edges_begin()->face();
    }

    Arrangement_2 VA;
    VP_type_non_regular_face VP_calculator(A);
    VP_calculator.compute_visibility(p, f, VA);

    printArrangementEdges(VA, "VP ");

    return VA;
}

std::tuple<Point, Point, Halfedge_circulator> greedyStep(Arrangement_2 A, Halfedge_circulator e, Point p){
    printArrangementEdges(A, "A");
    std::cout << "Greedy step from p: " << p << std::endl;
    std::cout << "e: " << e->source()->point() << " -> " << e->target()->point() << std::endl;

    // Compute the initial feasible polygon set
    Arrangement_2 F1 = computeVisibilityArrangementAtEdge(A, p, e);
//    drawArrangements(A, F1);
    Polygon_set_2 F;
    F.insert(arrangement_to_polygon(F1));

    if (p == e->target()->point()){ // if p is in the middle of e then don't move to the next edge
        e++;
    }

    int i = 0;
    for (; i < A.number_of_vertices() + 2; i++){
        p = e->target()->point();
        std :: cout << "Greedy step now at p: " << p << " for edge: " << e->source()->point() << " -> " << e->target()->point() << std::endl;

        Polygon_2 VP = arrangement_to_polygon(computeVisibilityArrangementAtEdge(A, p, e));
        if (F.do_intersect(VP)) {
            F.intersection(VP);
        }
        else { break; }

//        drawArrangements(A, polygon_set_to_arrangement(F));

        e++;
    }

    // If greedyStep can traverse the entire polygon boundary then it is trivially solved by one guard
    if (i == A.number_of_vertices() + 2){
        std :: cout << "Trivially solved by one guard << std::endl";
        throw std::invalid_argument("");
        }

    // compute feasible region for each corner of F and check which vertex is furthest on edge 'e'
    Point pFirst = e->source()->point();
    Point pBest = e->source()->point();
    std::cout << "Greedy step finished at pBest: " << pBest << " on edge: " << pFirst << " -> " << e->target()->point() << std::endl;
    Arrangement_2 FA = polygon_set_to_arrangement(F);
    drawArrangements(A, FA);
    Point guard = FA.vertices_begin()->point();

    // loop over vertices of FA and compute visibility polygon for each vertex
    for (auto vit = FA.vertices_begin(); vit != FA.vertices_end(); ++vit){
        Point f = vit->point();
        Arrangement_2 VP_f;
        // if f is on an edge of A then find that edge (loop over edges of A using getEdgesOfArrangement
        for (auto eA :getEdgesOfArrangement(A)){
            // check if f is on edge e using pointIsOnEdge e
            if (pointIsOnEdgeButNotSource(f, eA)){
                // if yes, compute visibility polygon for f on edge e
                std::cout << "Point f: " << f << " is on edge: " << eA->source()->point() << " -> " << eA->target()->point() << std::endl;
                VP_f = computeVisibilityArrangementAtEdge(A, f, eA);
                break;
            }
        }

        if (VP_f.is_empty()) {
            // TODO: Then f must be strictly inside A (assert), so compute visibility polygon for q on the inner face of A
            VP_f = computeVisibilityArrangementAtFace(A, f);
//            std::cout << "ERROR: Point f: " << f << " is strictly inside A (can't compute visibility polygon)" << std::endl;
//            throw std::invalid_argument("");
        }

        std::cout << "edge e is: " << e->source()->point() << " -> " << e->target()->point() << std::endl;

        // loop over vertices of visibility polygon
        for (auto vit2 = VP_f.vertices_begin(); vit2 != VP_f.vertices_end(); ++vit2) {
            Point q = vit2->point();
            if (pointIsOnEdgeButNotSource(q, e)){
                std::cout << "Point q: " << q << " is on edge e: " << e->source()->point() << " -> " << e->target()->point() << std::endl;
                // Check if vertex is further than pBest
                if (CGAL::squared_distance(pFirst, q) > CGAL::squared_distance(pFirst, pBest)){
                    std::cout << "Found a better point: (" << q << ") at distance: " << CGAL::squared_distance(pFirst, q) << std::endl;
                    std::cout << "Previous best point: (" << pBest << ") at distance: " << CGAL::squared_distance(pFirst, pBest) << std::endl;
                    pBest = q;
                    guard = f;
                }
            }
        }
    }

    // if pBest == pFirst then 'e' must be set to the previous edge since 'p' must be on 'e' but not its the source
    if (pBest == pFirst){
        e--;
    }

    return std::make_tuple(guard, pBest, e);
}

