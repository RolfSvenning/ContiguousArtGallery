#include "Helper.h"
#include <CGAL/Polygon_2.h>



// function that returns outer cbb for Polygon P
// connected component of the boundary (CCB)
// see: https://doc.cgal.org/latest/Arrangement_on_surface_2/index.html#fig__aos_fig-arr_segs
Arrangement_2::Ccb_halfedge_const_circulator getEdgesOfArrangement(const Arrangement_2& P) {
    // assert Euler's formula for planar graphs
    if (not P.number_of_vertices() - P.number_of_edges() + P.number_of_faces() == 2) {
        throw std::invalid_argument("Euler's formula for planar graphs not satisfied");
    }

    // assert number of faces is 2 else throw an error
    if (P.number_of_faces() != 2) {
        throw std::invalid_argument("Number of faces is not 2");
    }
    // get the inner face
    auto face = P.faces_begin();
    if (face->is_unbounded()) {
        face++;
    }
    if (face->is_unbounded()) {
        throw std::invalid_argument("Both faces are unbounded");
    }
    return face->outer_ccb();
}

// Function to convert arrangement (Polygon) to Polygon_2
Polygon_2 arrangement_to_polygon(const Arrangement_2& A) {
    auto ccb = getEdgesOfArrangement(A);

    // Extract points from the boundary
    Polygon_2 polygon;
    auto curr = ccb;
    do {
        polygon.push_back(curr->source()->point());
        ++curr;
    } while (curr != ccb);

    return polygon;
}

Arrangement_2 polygon_to_arrangement(const Polygon_2& polygon) {
    Arrangement_2 A;

    // Ensure the polygon is not empty
    if (polygon.is_empty()) {
        std::cerr << "The polygon is empty, can't be converted to an arrangement" << std::endl;
        throw std::invalid_argument("The polygon is empty.");
    }

    // Iterate over the edges of the polygon and insert them into the arrangement
    std::vector<Segment> segments;
    for (auto it = polygon.edges_begin(); it != polygon.edges_end(); ++it) {
        segments.push_back(*it);
    }

    // Insert the segments into the arrangement
    CGAL::insert_non_intersecting_curves(A, segments.begin(), segments.end());

    return A;
}

Arrangement_2 polygon_set_to_arrangement(const Polygon_set_2& polygon_set) {
    // Check if the polygon set contains a single polygon
    if (polygon_set.is_empty()) {
        std::cerr << "The polygon set is empty, can't be converted to an arrangement" << std::endl;
        throw std::invalid_argument("The polygon set is empty.");
    }
    if (polygon_set.number_of_polygons_with_holes() != 1) {
        std::cerr << "The polygon set contains more than one polygon, can't be converted to an arrangement" << std::endl;
        throw std::invalid_argument("The polygon set contains more than one polygon.");
    }

    // Extract the single polygon from the set
    std::list<Polygon_with_holes_2> polygons;
    polygon_set.polygons_with_holes(std::back_inserter(polygons));
    const Polygon_with_holes_2& pwh = polygons.front();

    // Ensure the polygon has no holes (i.e., it is a simple polygon)
    if (!pwh.holes().empty()) {
        std::cerr << "The polygon contains holes and is not simple, can't be converted to an arrangement" << std::endl;
        throw std::invalid_argument("The polygon contains holes and is not simple.");
    }

    // Get the outer boundary
    const Polygon_2& outer_boundary = pwh.outer_boundary();

    // Ensure the outer boundary is simple
    if (!outer_boundary.is_simple()) {
        std::cerr << "The outer boundary of the polygon is not simple, can't be converted to an arrangement" << std::endl;
        throw std::invalid_argument("The outer boundary of the polygon is not simple.");
    }

    // Create an empty arrangement
    Arrangement_2 A;

    // Insert the edges of the polygon into the arrangement
    std::vector<Segment> segments;
    for (auto it = outer_boundary.edges_begin(); it != outer_boundary.edges_end(); ++it) {
        segments.push_back(*it);
    }
    CGAL::insert_non_intersecting_curves(A, segments.begin(), segments.end());

    return A;
}



void printArrangementEdges(const Arrangement_2& P, const std::string& name) {
    std::cout << name << ": ";
    Arrangement_2::Ccb_halfedge_const_circulator edges = getEdgesOfArrangement(P);
    Arrangement_2::Ccb_halfedge_const_circulator startEdge = edges;

    // print the edges of the face
    std::cout << "(" << edges->source()->point() << " -> " <<  edges->target()->point() << ") ";
    for (auto eit = ++edges; eit != startEdge; ++eit) {
        std::cout << "(" << eit->source()->point() << " -> " << eit->target()->point() << ") ";
    }
    std::cout << std::endl;

}