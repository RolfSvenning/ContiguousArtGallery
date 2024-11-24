#include "Helper.h"
#include <CGAL/Polygon_2.h>



// function that returns outer cbb for Polygon P
// connected component of the boundary (CCB)
// see: https://doc.cgal.org/latest/Arrangement_on_surface_2/index.html#fig__aos_fig-arr_segs
std::vector<Halfedge_circulator> getEdgesOfArrangement(const Arrangement_2& P) {
    // assert Euler's formula for planar graphs
    if (not P.number_of_vertices() - P.number_of_edges() + P.number_of_faces() == 2) {
        std::cerr << "Euler's formula for planar graphs is not satisfied" << std::endl;
        throw std::invalid_argument("");
    }

    // assert number of faces is 2 else throw an error
    if (P.number_of_faces() != 2) {
        std::cerr << "The number of faces is not 2" << std::endl;
        throw std::invalid_argument("");
    }
    // get the inner face
    auto face = P.faces_begin();
    if (face->is_unbounded()) {
        face++;
    }
    if (face->is_unbounded()) {
        std::cerr << "Both faces are unbounded" << std::endl;
        throw std::invalid_argument("");
    }

    std::vector<Halfedge_circulator> E;
    auto curr = face->outer_ccb();

    do {
        E.push_back(curr);
        curr++;
    } while (curr != face->outer_ccb());

    return E;
}

// Function to convert arrangement (Polygon) to Polygon_2
Polygon_2 arrangement_to_polygon(const Arrangement_2& A) {
    Polygon_2 polygon;

    for (auto e : getEdgesOfArrangement(A)) {
        polygon.push_back(e->source()->point());
    }

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
        throw std::invalid_argument("");
    }
    if (polygon_set.number_of_polygons_with_holes() != 1) {
        std::cerr << "The polygon set contains more than one polygon, can't be converted to an arrangement" << std::endl;
        throw std::invalid_argument("");
    }

    // Extract the single polygon from the set
    std::list<Polygon_with_holes_2> polygons;
    polygon_set.polygons_with_holes(std::back_inserter(polygons));
    const Polygon_with_holes_2& pwh = polygons.front();

    // Ensure the polygon has no holes (i.e., it is a simple polygon)
    if (!pwh.holes().empty()) {
        std::cerr << "The polygon contains holes and is not simple, can't be converted to an arrangement" << std::endl;
        throw std::invalid_argument("");
    }

    // Get the outer boundary
    const Polygon_2& outer_boundary = pwh.outer_boundary();

    // Ensure the outer boundary is simple
    if (!outer_boundary.is_simple()) {
        std::cerr << "The outer boundary of the polygon is not simple, can't be converted to an arrangement" << std::endl;
        throw std::invalid_argument("");
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



void printArrangementEdges(const Arrangement_2& A, const std::string& name) {
    std::cout << name << ": ";
    std::vector<Halfedge_circulator > E = getEdgesOfArrangement(A);

    // print the edges E of A
    for (auto e : E) {
        std::cout << "(" << e->source()->point() << " -> " << e->target()->point() << ") ";
    }
    std::cout << std::endl;
}

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

bool pointIsOnEdgeButNotSource(const Point& p, Halfedge_circulator e) {
    // Extract endpoints of the edge
    const Point& source = e->source()->point();
    const Point& target = e->target()->point();

    // Allow p to the target of the edge but not the source
    if (p == source) {
        return false;
    }

    if (p == target) {
        return true;
    }

    std::ostringstream oss;
    // Check if p is collinear with the edge
    if (!CGAL::collinear(source, target, p)) {
        return false;
    }

    // Check if point p is within the segment bounds
    if (!(CGAL::compare(CGAL::min(source.x(), target.x()), p.x()) != CGAL::LARGER &&
          CGAL::compare(CGAL::max(source.x(), target.x()), p.x()) != CGAL::SMALLER &&
          CGAL::compare(CGAL::min(source.y(), target.y()), p.y()) != CGAL::LARGER &&
          CGAL::compare(CGAL::max(source.y(), target.y()), p.y()) != CGAL::SMALLER)) {
        return false;
    }
    return true;
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