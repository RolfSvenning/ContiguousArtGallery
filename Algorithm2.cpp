#include "Algorithm2.h"

#include <CGAL/Triangular_expansion_visibility_2.h>
#include <CGAL/Simple_polygon_visibility_2.h>
#include <tuple>
#include <iostream>
#include <CGAL/Boolean_set_operations_2.h> // for intersection
#include <optional> // for optional point Fp


// CGAL typedefs
typedef CGAL::Triangular_expansion_visibility_2<Arrangement_2>              VA_type;                    // Visibility polygon class
typedef CGAL::Simple_polygon_visibility_2<Arrangement_2, CGAL::Tag_false>   VP_type_non_regular_face;   // computes non-regularized area
typedef Arrangement_2::Face_const_handle                                    Face_const_handle;



Arrangement_2 computeVisibilityArrangementAtEdge(const Arrangement_2 & A, const Point& p, Halfedge_const_handle e) {
    // Assert point p on edge e or throw error
    validatePointOnEdge(p, e);

    // Compute the visibility polygon
    Arrangement_2 VA;
    VA_type VP_calculator(A);
    VP_calculator.compute_visibility(p, e, VA);

    return VA;
}

Arrangement_2 computeVisibilityArrangementAtFace(const Arrangement_2 & A, const Point& p) {
    // assert point p is inside face f or throw error
    if (arrangement_to_polygon(A).has_on_unbounded_side(p)) {
        std::cout << "ERROR: p must be in polygon" << std::endl;
        throw std::logic_error("");
    }

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

    return VA;
}

Arrangement_2 computeVisibilityArrangementGeneral(const Arrangement_2& A, const Point& p) {
    Arrangement_2 VP;
    // Check if p is on an edge of A
    for (auto eA: getEdgesOfArrangement(A)) {
        if (pointIsOnEdgeButNotSource(p, eA)) {
            VP = computeVisibilityArrangementAtEdge(A, p, eA);
            break;
        }
    }

    if (VP.is_empty()) {
        VP = computeVisibilityArrangementAtFace(A, p);
    }
    return VP;
}


std::vector<Point> findAllIntersectionsBetweenEdgesOfPolygons(const Polygon_2& P, const Polygon_2& Q){
    std::vector<Point> I;
    for (auto eP: P.edges()) {
        for (auto eQ: Q.edges()) {
            auto intersection = CGAL::intersection(eP, eQ);

            if (intersection) {
//                std::cout << "Intersection found" << std::endl;
                if (const Point *pI = std::get_if<Point>(&*intersection)) {
                    I.push_back(*pI);
                } else if (const Segment *sI = std::get_if<Segment>(&*intersection)) {
                    I.push_back(sI->source());
                    I.push_back(sI->target());
                } else {
                    std::cerr << "ERROR: should never happen, intersection is neither a point nor a segment" << std::endl;
                    throw std::invalid_argument("");
                }
            }
        }
    }
    return I;
}

bool passedStart(const Halfedge_circulator e, const std::optional<Point>& start, const Point p) {
    if (start.has_value() and pointIsOnEdgeButNotSource(start.value(), e)){
        // check if 'p' is closer than 'start' to 'e''s target
        if (CGAL::squared_distance(p, e->target()->point()) <= CGAL::squared_distance(start.value(), e->target()->point())){
//            std::cout << "Found a solution" << std::endl;
            return true;
        }
    }
    return false;
}

std::tuple<Point, Halfedge_circulator, Point, bool> greedyStep(const Arrangement_2& A, Halfedge_circulator e, Point p, const std::optional<Point>& start) {
//    std::cout << "Greedy step from p: " << p << std::endl;
//    std::cout << "e: " << e->source()->point() << " -> " << e->target()->point() << std::endl;
    bool isFinished = false;

    // Compute the initial feasible polygon set
    Arrangement_2 F1 = computeVisibilityArrangementAtEdge(A, p, e);
    Polygon_set_2 F;
    F.insert(arrangement_to_polygon(F1));
    std::vector<Point> Fs;

    if (p == e->target()->point()){ // 'p' must be on edge 'e' but not its target
        e++;
    }

    // #==============================================#
    // #  1) EXPAND THE GREEDY STEP BY ENTIRE EDGES   #
    // #==============================================#

    int i = 0;
    for (; i < A.number_of_vertices() + 2; i++){
        p = e->target()->point();
//        std :: cout << "Greedy step now at p: " << p << " for edge: " << e->source()->point() << " -> " << e->target()->point() << std::endl;

        Polygon_2 VP = arrangement_to_polygon(computeVisibilityArrangementAtEdge(A, p, e));

        if (not Fs.empty()) {
//            std::cout << "F is a single point" << std::endl;
            if (size(Fs) == 1) {
                // Fs is a point, check if it is in VP (including its boundary)
                if (VP.has_on_unbounded_side(Fs[0])) {
//                    std::cout << "Fs is not in VP" << std::endl;
//                    std::cout << "Fs: " << Fs[0] << std::endl;
                    break;
                }
            } else {
                // Fs is a segment, check what part of the segment is in VP (including its boundary)
                std::cout << "ERROR: should not happen for general position input, Fs is a segment" << std::endl;
                throw std::invalid_argument("");
            }

        } else {
            // F is a polygon
//            drawArrangements(A, polygon_set_to_arrangement(F));
            if (F.do_intersect(VP)) {
                F.intersection(VP);
            } else {
                // also check if F and VP intersect at their boundary (i.e., if they share a point or a segment)
//                std::cout << "Checking if F and VP intersect at their boundary" << std::endl;
                auto FP = polygon_set_to_polygon(F);
                std::vector<Point> I = findAllIntersectionsBetweenEdgesOfPolygons(FP, VP);
//                std::cout << "#intersections: " << size(I) << std::endl;

                if (size(I) == 0) {
                    break;
                } else if (size(I) == 1) {
                    std::cout << "Should never happen since at least two endpoints will be at the intersection" << std::endl;
                    throw std::invalid_argument("");
                } else {
                    for (const auto& pI: I) {
                        if (I[0] != pI) {
                            std::cout << "ERROR: for general position input all intersections should be at a single point" << std::endl;
                            throw std::invalid_argument("");
                        }
                    }
                    Fs.push_back(I[0]);
                }
            }
        }
        // assert that the polygon_set F contains a single polygon
        if (F.number_of_polygons_with_holes() != 1){
            std::cerr << "The polygon set F contains more than one polygon" << std::endl;
            throw std::invalid_argument("");
        }

        // check if we passed the starting point and have found a solution
        isFinished = isFinished or passedStart(e, start, p);
        e++;
    }

    // If greedyStep can traverse the entire polygon boundary then it is trivially solved by one guard
    if (i == A.number_of_vertices() + 2){
        return std::make_tuple(p, e, p, true);
        }

    // #===============================================#
    // #  2) EXPAND THE GREEDY STEP ON THE FINAL EDGE  #
    // #===============================================#

    Point pFirst = e->source()->point();
    Point pBest = e->source()->point();
//    std::cout << "Greedy step (FINAL EDGE) at pBest: " << pBest << " on edge: " << pFirst << " -> " << e->target()->point() << std::endl;

    Arrangement_2 FA;
    Point guard;

    // set FA to be the arrangement for the remaining feasible region
    if (not Fs.empty()){
        for (auto f: Fs){
            FA.insert_in_face_interior(f, FA.unbounded_face());
        }
        guard = Fs[0];
    } else {
        FA = polygon_set_to_arrangement(F);
        guard = FA.vertices_begin()->point();
    }
//    drawArrangements(A, FA);

    // loop over vertices of FA and compute the visibility polygon of each vertex 'f' to find the point furthest on 'e'
    for (auto vit = FA.vertices_begin(); vit != FA.vertices_end(); ++vit) {
        Point f = vit->point();
        Arrangement_2 VP_f;
        VP_f = computeVisibilityArrangementGeneral(A, f);

//        std::cout << "edge e is: " << e->source()->point() << " -> " << e->target()->point() << std::endl;

        // loop over vertices of visibility polygon
        for (auto vit2 = VP_f.vertices_begin(); vit2 != VP_f.vertices_end(); ++vit2) {
            Point q = vit2->point();
            if (pointIsOnEdgeButNotSource(q, e)) {
//                std::cout << "Point q: " << q << " is on edge e: " << e->source()->point() << " -> "
//                          << e->target()->point() << std::endl;
                // Check if vertex is further than pBest
                if (CGAL::squared_distance(pFirst, q) > CGAL::squared_distance(pFirst, pBest)) {
//                    std::cout << "Found a better point: (" << q << ") at distance: "
//                              << CGAL::squared_distance(pFirst, q) << std::endl;
//                    std::cout << "Previous best point: (" << pBest << ") at distance: "
//                              << CGAL::squared_distance(pFirst, pBest) << std::endl;
                    pBest = q;
                    guard = f;
                }
            }
        }
    }

    isFinished = isFinished or passedStart(e, start, pBest);
    // if pBest == pFirst then 'e' must be set to the previous edge since 'p' must be on 'e' but not its the source
    if (pBest == pFirst){
        e--;
    }

    return std::make_tuple(guard, e, pBest, isFinished);
}





// Below code is needed to extend the implementation to handle inputs in general position where the feasible region may be a segment
//
//std::tuple<Point, Point> furthestPointsAlongLine(const std::vector<Point>& I) {
//    Point p1 = I[0];
//    Point p2 = I[1];
//    for (int j = 2; j < size(I); j++) {
//        if (CGAL::squared_distance(p1, I[j]) < CGAL::squared_distance(p1, p2)
//            and CGAL::squared_distance(p2, I[j]) < CGAL::squared_distance(p1, p2)) {
//            // I[j] is between p1 and p2
//            continue;
//        }
//        if (CGAL::squared_distance(p1, I[j]) < CGAL::squared_distance(p2, I[j])) {
//            p1 = I[j];
//        } else {
//            p2 = I[j];
//        }
//    }
//    return std::make_tuple(p1, p2);

//    // Find the two points in I that are furthest apart along a common line
//    auto [p1, p2] = furthestPointsAlongLine(I);
//
//    std::cout << "Found two points p1: " << p1 << " and p2: " << p2
//              << " furthest apart along a common line" << std::endl;
////                    std::cout << "Points in I: " << std::endl;
////                    for (const auto &pI: I) {
////                        std::cout << "Point: " << pI << std::endl;
////                    }
//
//    if (p1 == p2) {
//        // F is a single point
//        Fs.push_back(p1);
//        std::cout << "F is a single point" << std::endl;
//    } else {
//        Fs.push_back(p1);
//        Fs.push_back(p2);
//        std::cout << "F is a segment" << std::endl;
//    }
//}


























