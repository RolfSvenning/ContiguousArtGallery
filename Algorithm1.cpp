#include "Algorithm1.h"
#include <CGAL/Exact_rational.h>

typedef CGAL::Exact_rational Rational;
typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;


void algorithm1(){
    std::cout << "Algorithm 1" << std::endl;


//    return 0;
}

//#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
//#include <CGAL/Polygon_2.h>
//#include <CGAL/Visibility_2/Visibility_2.h>
//#include <CGAL/Visibility_2/Polygon_2_visibility_2.h>
//#include <iostream>
//
//typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
//typedef Kernel::Point_2 Point_2;
//typedef CGAL::Polygon_2<Kernel> Polygon_2;
//typedef CGAL::Polygon_2_visibility_2<Kernel> Visibility_2;
//
//int main() {
//    // Define a simple polygon with exact coordinates
//    Polygon_2 polygon;
//    polygon.push_back(Point_2(0, 0));
//    polygon.push_back(Point_2(4, 0));
//    polygon.push_back(Point_2(4, 4));
//    polygon.push_back(Point_2(2, 2)); // A reflex vertex (creates a notch)
//    polygon.push_back(Point_2(0, 4));
//
//    // Check if the polygon is simple
//    if (!polygon.is_simple()) {
//        std::cerr << "The polygon is not simple!" << std::endl;
//        return 1;
//    }
//
//    // Print the polygon vertices
//    std::cout << "Polygon vertices:" << std::endl;
//    for (const auto& point : polygon) {
//        std::cout << "(" << point.x() << ", " << point.y() << ")" << std::endl;
//    }
//
//    // Visibility computation: point of interest inside the polygon
//    Point_2 query_point(2, 1); // A point inside the polygon
//
//    // Compute visibility region
//    Visibility_2 visibility;
//    Polygon_2 visibility_region;
//
//    visibility.compute_visibility(query_point, polygon, visibility_region);
//
//    // Print the visibility region
//    std::cout << "Visibility region vertices:" << std::endl;
//    for (const auto& point : visibility_region) {
//        std::cout << "(" << point.x() << ", " << point.y() << ")" << std::endl;
//    }
//
//    return 0;
//}
