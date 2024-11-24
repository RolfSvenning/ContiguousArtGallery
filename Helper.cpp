#include "Helper.h"


// function that returns outer cbb for Polygon P
// connected component of the boundary (CCB)
// see: https://doc.cgal.org/latest/Arrangement_on_surface_2/index.html#fig__aos_fig-arr_segs
Polygon::Ccb_halfedge_const_circulator getEdgesOfPolygon(const Polygon& P) {
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

void printPolygonEdges(const Polygon& P, const std::string& name) {
    std::cout << name << ": ";
    Polygon::Ccb_halfedge_const_circulator edges = getEdgesOfPolygon(P);
    Polygon::Ccb_halfedge_const_circulator startEdge = edges;

    // print the edges of the face
    std::cout << "(" << edges->source()->point() << " -> " <<  edges->target()->point() << ") ";
    for (auto eit = ++edges; eit != startEdge; ++eit) {
        std::cout << "(" << eit->source()->point() << " -> " << eit->target()->point() << ") ";
    }
    std::cout << std::endl;

}